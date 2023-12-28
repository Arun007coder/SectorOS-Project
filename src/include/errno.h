#if !defined(__ERRNO_H__)
#define __ERRNO_H__

#include "system.h"

void set_errno(int f_errno, const char* function, const char* file);
int get_errno();

const char* get_last_errno_file();
const char* get_last_errno_function();

#define ERRNO_SET(n) set_errno(n, __func__, __FILE__)

#define ENOERR 0 			// No error occurred
#define EINVAL 1 			// Invalid arguments given
#define ENODATA 2 			// Requested data not available
#define EUNKNOWN 3 			// Unknown error occurred
#define ENOACTION 4			// Cannot do specified action / Locked

const char* errno_to_str(int errno);

#endif // __ERRNO_H__