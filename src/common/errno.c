#include "errno.h"

static int errno = 0;

static char errno_file[1024];
static char errno_func[512];

static const char* errno_str[] = {
    "No error",
    "Invalid arguments",
    "Requested data not available",
    "Unknown error occurred",
    NULL
};

void set_errno(int f_errno, const char* function, const char* file)
{
    errno = f_errno;

    int i = 0;

    for(i = 0; (i < 1024) && (file[i] != 0); i++)
        errno_file[i] = file[i];

    errno_file[i] = '\0';

    i = 0;

    for(i = 0; (i < 512) && (function[i] != 0); i++)
        errno_func[i] = function[i];

    errno_func[i] = '\0';
}

int get_errno()
{
    return errno;
}

const char* errno_to_str(int f_errno)
{
    return errno_str[f_errno];
}

const char* get_last_errno_file()
{
    return errno_file;
}

const char* get_last_errno_function()
{
    return errno_func;
}