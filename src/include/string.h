#if !defined(__STRING_H__)
#define __STRING_H__

#include "system.h"

int memcmp(uint8_t *data1, uint8_t *data2, int n);
void *memcpy(void *dst, const void *src, int n);

uint16_t *memsetw(uint16_t *dest, uint16_t val, uint32_t count);
uint16_t *memsetdw(uint32_t *dest, uint32_t val, uint32_t count);
void *memset(void *dst, char val, int n);

int strlen(const char *s);

char *strncpy(char *destString, const char *sourceString, int maxLength);
int strcpy(char *dst, const char *src);

int strcmp(const char *dst, char *src);
int strncmp(const char *s1, const char *s2, int c);

char *strstr(const char *in, const char *str);
void strcat(void *dest, const void *src);

char* itoa_r(unsigned long int n, int base);   //! Not implemented
void itoa(char *buf, unsigned long int n, int base);
int atoi(char *string);

int isspace(char c);
int isprint(char c);

char *strdup(const char *src);  //! Not implemented
char *strndup(const char *src, uint32_t len);   //! Not implemented
char *strsep(char **stringp, const char *delim);


#endif // __STRING_H__
