#define _CRT_SECURE_NO_WARNINGS
/*
 * Coverage builds only. MSYS2 ships the LLVM profile runtime built against the MinGW
 * C runtime; re3 links the static MSVC C runtime. This file supplies the handful of
 * MinGW-side symbols that runtime references. ___chkstk_ms is mapped to MSVC's
 * __chkstk with /alternatename in coverage.props (same x64 contract: probe RAX bytes,
 * leave RSP alone).
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <direct.h>
#include <io.h>

int
__mingw_fprintf(FILE *f, const char *fmt, ...)
{
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = vfprintf(f, fmt, ap);
	va_end(ap);
	return r;
}

int
__mingw_snprintf(char *buf, size_t n, const char *fmt, ...)
{
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = vsnprintf(buf, n, fmt, ap);
	va_end(ap);
	return r;
}

uintptr_t __stack_chk_guard = (uintptr_t)0x595e9fbd94fda766ULL;

void
__stack_chk_fail(void)
{
	abort();
}

/* The runtime calls these through dllimport thunks; the static CRT has no __imp_ symbols. */
void *__imp__fdopen = (void *)&_fdopen;
void *__imp__mkdir = (void *)&_mkdir;
void *__imp__putenv = (void *)&_putenv;
void *__imp_strerror = (void *)&strerror;

/*
 * The MinGW runtime registers its initialiser (which installs the write-profile-at-exit
 * hook) in .ctors, which the MSVC C runtime never runs. Run it from .CRT$XCU instead.
 */
void __llvm_profile_initialize(void);

static void
shim_profile_init(void)
{
	__llvm_profile_initialize();
}

#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void (*shim_profile_init_entry)(void) = shim_profile_init;
