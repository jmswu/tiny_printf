/*
 * tiny_printf.c
 *
 *  Created on: 2/06/2017
 *      Author: james
 */

#include "tiny_printf.h"

static void xtoa(unsigned long x, const unsigned long *dp);
static void tiny_putHex(unsigned n);
static void tiny_putStr(const char * str);

static const unsigned long dv[] = {
//  4294967296      // 32 bit unsigned max
		1000000000,// +0
		100000000, // +1
		10000000, // +2
		1000000, // +3
		100000, // +4
//       65535      // 16 bit unsigned max
		10000, // +5
		1000, // +6
		100, // +7
		10, // +8
		1, // +9
		};


static void xtoa(unsigned long x, const unsigned long *dp) {
	char c;
	unsigned long d;
	if (x) {
		while (x < *dp)
			++dp;
		do {
			d = *dp++;
			c = '0';
			while (x >= d)
				++c, x -= d;
			tiny_putc(c);
		} while (!(d & 1));
	} else
		tiny_putc('0');
}

static void tiny_putHex(unsigned n) {
	static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	tiny_putc(hex[n & 15]);
}

static void tiny_putStr(const char * str)
{
	while(*str)
	{
		tiny_putc(*str);
		str++;
	}
}

void tiny_printf(const char *format, ...)
{
	char formatChar;
	int number;
	long num32bit;

	va_list a;
	va_start(a, format);
	while(formatChar = *format++) {
		if(formatChar == '%') {
			switch(formatChar = *format++) {
				case 's': // String
					tiny_putStr(va_arg(a, char*));
					break;
				case 'c':// Char
					tiny_putc((char)va_arg(a, int));
					break;
				case 'i':// 16 bit Integer
				case 'u':// 16 bit Unsigned
					number = va_arg(a, int);
					if(formatChar == 'i' && number < 0) number = -number, tiny_putc('-');
					xtoa((unsigned)number, dv + 5);
					break;
				case 'l':// 32 bit Long
				case 'n':// 32 bit uNsigned loNg
					num32bit = va_arg(a, long);
					if(formatChar == 'l' && num32bit < 0) num32bit = -num32bit, tiny_putc('-');
					xtoa((unsigned long)num32bit, dv);
					break;
				case 'x':// 16 bit heXadecimal
					number = va_arg(a, int);
					tiny_putHex(number >> 12);
					tiny_putHex(number >> 8);
					tiny_putHex(number >> 4);
					tiny_putHex(number);
					break;
				case 0: return;
				default: goto bad_fmt;
			}
		} else
			bad_fmt: tiny_putc(formatChar);
	}
	va_end(a);
}


