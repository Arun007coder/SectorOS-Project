#include "string.h"
#include "errno.h"

void* memcpy(void *dst, const void *src, int n)
{
	if(dst == NULL || src == NULL)
	{
		ERRNO_SET(EINVAL);
		return NULL;
	}

	register uint8_t* d = (uint8_t*)dst;
	register uint8_t* s = (uint8_t*)src;

	int i = 0;
	while(i < n)
	{
		d[i] = s[i];
		++i;
	}

	ERRNO_SET(ENOERR);
	return dst;
}

uint16_t *memsetw(uint16_t *dest, uint16_t val, uint32_t count)
{
	if(dest == NULL)
	{
		ERRNO_SET(EINVAL);
		return NULL;
	}

	while(count--)
	{
		*(dest++) = val;
	}

	ERRNO_SET(ENOERR);
	return dest;
}

void *memset(void *dst, char val, int n)
{
	if(dst == NULL)
	{
		ERRNO_SET(EINVAL);
		return NULL;
	}

	register uint8_t* d = (uint8_t*)dst;

	while(n--)
	{
		d[n] = val;
	}

	return dst;
}