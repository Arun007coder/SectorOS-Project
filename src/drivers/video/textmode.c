#include "textmode.h"
#include "config.h"

typedef struct textmode_instance_struct
{
	uint32_t width;
	uint32_t height;

	int x;
	int y;

	uint8_t fg;
	uint8_t bg;

	uint16_t *framebuffer;
} textmode_instance_t;

static textmode_instance_t ti;

#define TEXTMODE_DEF_WIDTH 80
#define TEXTMODE_DEF_HEIGHT 25

void disable_blink()
{
	uint32_t a = inb(0x3DA);
	outb(0x3C0, 0x30);
	a = inb(0x3C1);
	a = a & 0xF7;
	outb(0x3C0, a);
}

void move_cursor()
{
	uint16_t pos = (ti.y * 80 + ti.x);
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

int textmode_init()
{
	disable_blink();
	ti.width = TEXTMODE_DEF_WIDTH;
	ti.height = TEXTMODE_DEF_HEIGHT;

	ti.x = 0;
	ti.y = 0;

	ti.fg = 15;
	ti.bg = 0;

	ti.framebuffer = (uint16_t *)0xB8000;

	return 0;
}

void textmode_putc(char c)
{
	if (c == '\n')
	{
		ti.x = 0;
		ti.y++;
	}
	else if (c == '\t')
	{
		ti.x += __TEXTMODE_TAB_SIZE;
	}
	else if (c == '\b')
	{
		if (ti.x != 0)
			ti.x--;
	}
	else if (c == '\r')
	{
		ti.x = 0;
	}
	else if (c >= ' ')
	{
		uint8_t attr = ((ti.bg << 4) & 0xF0) | (ti.fg & 0x0F);
		ti.framebuffer[ti.x + ti.y * ti.width] = c | (attr << 8);
		ti.x++;
	}

	if (ti.x > ti.width)
	{
		ti.x = 0;
		ti.y++;
	}

	if (ti.y > ti.height)
	{
		textmode_clear();
	}

	move_cursor();
}

void textmode_puts(char *str)
{
	while (*str)
	{
		textmode_putc(*(str++));
	};
}

void textmode_clear()
{
	uint8_t attr = ((ti.bg << 4) & 0xF0) | (ti.fg & 0x0F);
	uint16_t data = ' ' | (attr << 8);

	for (int i = 0; i < (ti.width * ti.height); i++)
	{
		ti.framebuffer[i] = data;
	}

	ti.x = 0;
	ti.y = 0;
}

void textmode_chpos(int x, int y)
{
	ti.x = x;
	ti.y = y;
}

void textmode_chattr(uint8_t fg, uint8_t bg)
{
	ti.fg = fg;
	ti.bg = bg;
}
