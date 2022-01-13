#include "codegen.h"
#include "hash.h"

#include <sys/ptrace.h>
#include <errno.h>
#include <stdarg.h>

mkwrap_init(long int, ptrace, (enum __ptrace_request __request, ...),
		(enum __ptrace_request , ...))

long int
ptrace (enum __ptrace_request request, ...)
{
	int r;
	int fstatus;
	va_list ap;
	pid_t pid;
	void *addr, *data;

	va_start (ap, request);
	pid = va_arg (ap, pid_t);
	addr = va_arg (ap, void *);
	data = va_arg (ap, void *);
	va_end (ap);

mkwrap_body_called(ptrace, (request, pid, addr, data), -1)

	static const int valid_errnos[] = {
	#ifdef ENOMEM
	ENOMEM,
	#endif
	};
mkwrap_body_errno("libc/proc/ptrace", -1)
mkwrap_bottom(ptrace, (request, pid, addr, data))
