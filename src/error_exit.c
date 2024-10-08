#include <stdio.h>
#include <stdlib.h>

void ErrorExit(char *ErrMsg)
{
    fprintf(stderr, "\e[1;31m%s\e[0m\n", ErrMsg);
    exit(1);
}