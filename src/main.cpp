#include <cstdio>
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
    return 0;
}

