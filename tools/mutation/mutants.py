#!/usr/bin/env python
"""Enumerate Mull-profile mutants of one re3 source file from clang's AST.

    python tools/mutation/mutants.py src/peds/PedFight.cpp > mutants.json

The operator set is the "Mull profile" used for the ImageMagick and 3SX harnesses and
reported for Jellyfin: Mull's cxx_default plus cxx_remove_void_call.

    equality      == -> !=, != -> ==                        (cxx_eq_to_ne, cxx_ne_to_eq)
    relational    < -> >=, <= -> >, > -> <=, >= -> <         (cxx_lt_to_ge, ...)
    boundary      < -> <=, <= -> <, > -> >=, >= -> >         (cxx_lt_to_le, ...)
    arithmetic    + -> -, - -> +, * -> /, / -> *, % -> /     (cxx_add_to_sub, ...)
    increment     ++ -> -- (pre and post)                    (cxx_pre_inc_to_pre_dec, cxx_post_inc_to_post_dec)
    unary minus   -x -> x                                    (cxx_minus_to_noop)
    void call     f(x); -> (void)0;                          (cxx_remove_void_call)

This is exactly the set mull-runner 0.34.1 (WSL, mull-ir-frontend-18) generates for
mutators [cxx_default, cxx_remove_void_call] on a test file, checked 2026-11-21: no
compound assignment (+= etc.) and no decrement (-- -> ++), which cxx_default leaves out.

Mull mutates LLVM IR; this tool mutates source text at the same AST nodes, so counts are
close to Mull's but not identical (Mull also sees operators the front end introduces).
Only code in the file itself is mutated: nothing inside macro expansions or headers, and
only what the harness configuration compiles (inactive #ifdef branches are not in the AST).

Each mutant is applied by replacing bytes [offset, offset+length) with `replacement`.
Needs MSYS2 clang-cl and VS 2022 Build Tools; include paths and defines come from
build/re3.vcxproj (Release, win-amd64-librw_d3d9-oal), so run premake first.
"""

import json
import os
import re
import subprocess
import sys
import tempfile

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
CONFIG = "Release win-amd64-librw_d3d9-oal|x64"
VCVARS = r"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
CLANG_CL = r"C:\msys64\mingw64\bin\clang-cl.exe"

BINARY = {
    "==": [("cxx_eq_to_ne", "!=")],
    "!=": [("cxx_ne_to_eq", "==")],
    "<": [("cxx_lt_to_ge", ">="), ("cxx_lt_to_le", "<=")],
    "<=": [("cxx_le_to_gt", ">"), ("cxx_le_to_lt", "<")],
    ">": [("cxx_gt_to_le", "<="), ("cxx_gt_to_ge", ">=")],
    ">=": [("cxx_ge_to_lt", "<"), ("cxx_ge_to_gt", ">")],
    "+": [("cxx_add_to_sub", "-")],
    "-": [("cxx_sub_to_add", "+")],
    "*": [("cxx_mul_to_div", "/")],
    "/": [("cxx_div_to_mul", "*")],
    "%": [("cxx_rem_to_div", "/")],
}
FUNCTION_KINDS = ("FunctionDecl", "CXXMethodDecl", "CXXConstructorDecl", "CXXDestructorDecl", "CXXConversionDecl")


def compile_flags():
    s = open(os.path.join(REPO, "build", "re3.vcxproj"), encoding="utf-8").read()
    start = s.index("<ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='%s'\">" % CONFIG)
    block = s[start:s.index("</ItemDefinitionGroup>", start)]
    incs = re.search(r"<AdditionalIncludeDirectories>(.*?)</AdditionalIncludeDirectories>", block).group(1)
    defs = re.search(r"<PreprocessorDefinitions>(.*?)</PreprocessorDefinitions>", block).group(1)
    flags = ['/I"%s"' % os.path.normpath(os.path.join(REPO, "build", i)) for i in incs.split(";") if i and "%(" not in i]
    flags += ["/D%s" % d for d in defs.split(";") if d and "%(" not in d]
    flags += ["/D_CRT_SECURE_NO_WARNINGS", "/D_CRT_NONSTDC_NO_DEPRECATE", "/std:c++14", "/EHsc", "-Wno-everything"]
    return flags


def dump_ast(path):
    tmp = tempfile.mkdtemp(prefix="mutants_")
    rsp = os.path.join(tmp, "flags.rsp")
    out = os.path.join(tmp, "ast.json")
    cmdf = os.path.join(tmp, "ast.cmd")
    open(rsp, "w").write(" ".join(compile_flags()))
    open(cmdf, "w").write('@call "%s" >nul\r\n@"%s" @"%s" -fsyntax-only -Xclang -ast-dump=json "%s" > "%s"\r\n'
                          % (VCVARS, CLANG_CL, rsp, path, out))
    subprocess.run(["cmd", "/c", cmdf], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    with open(out, encoding="utf-8") as f:
        ast = json.load(f)
    return ast


class Walker:
    """Walks the JSON AST in dump order. clang prints a location's "file" only when it
    differs from the previously printed one, so the current file is tracked as state."""

    def __init__(self, target):
        self.target = os.path.normcase(os.path.abspath(target))
        self.last_file = None
        self.mutants = []
        self.seen = set()

    def loc(self, l):
        """Returns (file, offset, line, col, toklen, is_macro) of a location object."""
        if not l:
            return None
        if "spellingLoc" in l or "expansionLoc" in l:
            for k in ("spellingLoc", "expansionLoc"):
                if k in l:
                    self.plain(l[k])
            return None  # inside a macro: not mutated
        return self.plain(l)

    def plain(self, l):
        if "file" in l:
            self.last_file = os.path.normcase(os.path.abspath(l["file"]))
        if "offset" not in l:
            return None
        return (self.last_file, l["offset"], l.get("line"), l.get("col"), l.get("tokLen", 0))

    def walk(self, node, func=None, parent_kind=None):
        kind = node.get("kind")
        loc = self.loc(node.get("loc"))
        rng = node.get("range") or {}
        begin = self.loc(rng.get("begin"))
        end = self.loc(rng.get("end"))
        if kind in FUNCTION_KINDS and loc and loc[0] == self.target and not node.get("isImplicit"):
            func = self.qualified(node)
        # expressions carry only a range, declarations a loc
        here = loc or begin
        if func and here and here[0] == self.target and begin and end and begin[0] == self.target                 and end[0] == self.target:
            self.consider(node, kind, here, begin, end, func, parent_kind)
        for child in node.get("inner", ()):
            self.walk(child, func, kind)

    def qualified(self, node):
        name = node.get("name", "?")
        parent = node.get("parentDeclContextId")
        cls = self.classes.get(parent) if parent else None
        return "%s::%s" % (cls, name) if cls else name

    def add(self, op, loc, length, original, replacement, func):
        key = (loc[1], op)
        if key in self.seen:
            return
        self.seen.add(key)
        line = self.data.count(b"\n", 0, loc[1]) + 1  # the JSON prints "line" only when it changes
        self.mutants.append({"op": op, "function": func, "line": line,
                             "offset": loc[1], "length": length, "original": original,
                             "replacement": replacement})

    def operator_between(self, node, opcode):
        """Offset of the operator token of a binary node: between the end of the left
        operand and the start of the right one, as written in the source."""
        inner = node.get("inner") or []
        if len(inner) != 2:
            return None
        lend = (inner[0].get("range") or {}).get("end") or {}
        rbeg = (inner[1].get("range") or {}).get("begin") or {}
        if "offset" not in lend or "offset" not in rbeg or "spellingLoc" in lend or "spellingLoc" in rbeg:
            return None
        lo, hi = lend["offset"] + lend.get("tokLen", 0), rbeg["offset"]
        gap = self.data[lo:hi].decode("latin-1")
        # the gap holds whitespace, comments, closing/opening parens and the operator
        idx = [i for i in range(len(gap)) if gap.startswith(opcode, i)
               and not gap.startswith(opcode + "=", i) and (opcode not in ("<", ">") or not gap.startswith(opcode * 2, i))]
        if len(idx) != 1:
            return None
        return lo + idx[0]

    def consider(self, node, kind, loc, begin, end, func, parent_kind):
        opcode = node.get("opcode")
        # Mull's cxx_default has no compound-assignment operators (+= etc.): checked
        # against mull-runner 0.34.1, which leaves them alone
        if kind == "BinaryOperator" and opcode in BINARY:
            table = BINARY
            inner = node.get("inner") or []
            if len(inner) == 2 and is_literal(inner[0]) and is_literal(inner[1]):
                return  # folded at compile time, invisible to Mull
            at = self.operator_between(node, opcode)
            if at is None:
                return
            line = self.data[:at].count(b"\n") + 1
            for op, rep in table[opcode]:
                self.add(op, (self.target, at, line, None, len(opcode)), len(opcode), opcode, rep, func)
        elif kind == "UnaryOperator" and opcode == "++":
            # cxx_default has the increment group only (++ -> --); decrement (-- -> ++) is
            # not in it, as mull-runner 0.34.1 confirms
            post = node.get("isPostfix", False)
            # the operator token: at the start (prefix) or at the end (postfix) of the range
            at = end if post else begin
            if at and at[0] == self.target:
                op = "cxx_post_inc_to_post_dec" if post else "cxx_pre_inc_to_pre_dec"
                self.add(op, at, 2, "++", "--", func)
        elif kind == "UnaryOperator" and opcode == "-":
            if is_literal(node.get("inner", [None])[0]):
                return  # -1.0f is a constant to the compiler; Mull's IR never sees a negation
            if begin and begin[0] == self.target:
                self.add("cxx_minus_to_noop", begin, 1, "-", " ", func)
        elif kind in ("CallExpr", "CXXMemberCallExpr") and parent_kind in ("CompoundStmt", "IfStmt", "ForStmt",
                                                                          "WhileStmt", "DoStmt", "CaseStmt",
                                                                          "DefaultStmt", "LabelStmt"):
            qt = (node.get("type") or {}).get("qualType", "")
            if qt == "void" and begin and end and begin[0] == self.target and end[0] == self.target:
                length = end[1] + end[4] - begin[1]
                if 0 < length < 2000:
                    self.add("cxx_remove_void_call", begin, length, None, "((void)0)", func)


LITERALS = ("IntegerLiteral", "FloatingLiteral", "CharacterLiteral", "CXXBoolLiteralExpr")


def is_literal(node):
    while node and node.get("kind") in ("ImplicitCastExpr", "ParenExpr", "CStyleCastExpr", "UnaryOperator")             and node.get("kind") != "UnaryOperator" or (node and node.get("kind") == "UnaryOperator"
                                                         and node.get("opcode") == "-"):
        inner = node.get("inner") or [None]
        node = inner[0]
    return bool(node) and node.get("kind") in LITERALS


def collect_classes(node, out):
    if node.get("kind") in ("CXXRecordDecl", "ClassTemplateDecl") and node.get("name") and node.get("id"):
        out[node["id"]] = node["name"]
    for child in node.get("inner", ()):
        collect_classes(child, out)


def enumerate_mutants(path):
    path = os.path.abspath(path)
    ast = dump_ast(path)
    w = Walker(path)
    w.data = open(path, "rb").read()
    w.classes = {}
    collect_classes(ast, w.classes)
    w.walk(ast)
    data = open(path, "rb").read()
    rel = os.path.relpath(path, REPO).replace("\\", "/")
    out = []
    for m in sorted(w.mutants, key=lambda m: (m["offset"], m["op"])):
        if m["original"] is not None:
            got = data[m["offset"]:m["offset"] + m["length"]].decode("latin-1")
            if got != m["original"]:
                continue  # offset does not point at the operator token: skip rather than guess
        else:
            m["original"] = data[m["offset"]:m["offset"] + m["length"]].decode("latin-1")
            if not m["original"].rstrip().endswith(")"):
                continue
        m["file"] = rel
        m["id"] = "%s:%d:%s" % (rel, m["offset"], m["op"])
        out.append(m)
    return out


def main():
    if len(sys.argv) != 2:
        print(__doc__)
        return 2
    mutants = enumerate_mutants(sys.argv[1])
    json.dump(mutants, sys.stdout, indent=1)
    sys.stderr.write("%d mutants\n" % len(mutants))
    return 0


if __name__ == "__main__":
    sys.exit(main())
