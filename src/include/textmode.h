#ifndef __TEXTMODE_H__

#include "system.h"

int textmode_init();

void textmode_putc(char c);
void textmode_puts(char* str);

void textmode_chpos(int x, int y);
void textmode_chattr(uint8_t fg, uint8_t bg);

void textmode_clear();

#endif // !__TEXTMODE_H__

