#include <cstdio>
#include <cstdint>
#include "tiny_printf.h"

void tiny_putc(const char c)
{
    printf("%c", c);
}

int main(int argc, char ** argv)
{
    (void)argc;
    (void)argv;

    tiny_printf("Hello world from tiny_printf()\n");
    tiny_printf("printing string: [%s]\n", "test_string");
    tiny_printf("printing char: [%c, %c, %c]\n", 'C', 'A', 'D');
    tiny_printf("print 16bit int:\n");
    return 0;
}

