#!/bin/sh
# Builds an LLVM-coverage-instrumented re3 (x64, D3D9, OpenAL) into bin/coverage/
# with MSYS2's clang-cl, without touching the normal build output.
# Needs: VS 2022 Build Tools, MSYS2 mingw64 clang (clang-cl, lld-link); the static
# library step uses MSVC lib.exe. Run premake5 vs2019 --with-librw first.
set -e
cd "$(dirname "$0")/../.."
LLVM=/c/msys64/mingw64
MSB="/c/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/MSBuild/Current/Bin/amd64/MSBuild.exe"
VCVARS='C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat'
mkdir -p build/obj-coverage/rt build/obj-coverage/librw build/obj-coverage/re3 bin/coverage

# Profile runtime under the name clang-cl's objects ask the linker for.
cp "$LLVM"/lib/clang/*/lib/windows/libclang_rt.profile-x86_64.a build/obj-coverage/rt/clang_rt.profile.lib

W=$(cygpath -w "$PWD")
LW=$(cygpath -w "$LLVM/bin")

# MSVC-runtime shim for the MinGW-built profile runtime (see clang_rt_msvc_shim.c),
# compiled inside the VS environment so the SDK headers are found.
cat > build/obj-coverage/rt/shim.cmd <<EOF
@call "$VCVARS" >nul
@"$LW\\clang-cl.exe" -nologo /c /O2 /MT /GS- "$W\\tools\\replay_harness\\clang_rt_msvc_shim.c" "/Fo$W\\build\\obj-coverage\\rt\\clang_rt_msvc_shim.obj"
EOF
cmd //c "$(cygpath -w build/obj-coverage/rt/shim.cmd)"

"$MSB" build/re3.sln -m -nologo -v:m \
  -p:Configuration=Release -p:Platform=win-amd64-librw_d3d9-oal \
  -p:PlatformToolset=v143 -p:WindowsTargetPlatformVersion=10.0 \
  -p:CLToolExe=clang-cl.exe "-p:CLToolPath=$LW" \
  -p:LinkToolExe=lld-link.exe "-p:LinkToolPath=$LW" \
  "-p:ForceImportBeforeCppTargets=$W\\tools\\replay_harness\\coverage_dirs.props" \
  "-p:ForceImportAfterCppTargets=$W\\tools\\replay_harness\\coverage.props" \
  "-p:ClangRtDir=$W\\build\\obj-coverage\\rt"
