#include "io.h"
#include "errors.h"
#include <stdio.h>
#include <string.h>

int input_num(char *str)
{
    if (fgets(str, MAX_STR, stdin) == NULL)
        return ERR_INPUT_STR;

    if (str[strlen(str) - 1] != '\n')
        return ERR_INPUT_STR;

    str[strlen(str) - 1] = '\0';

    return OK;
}

void print_scale(void)
{
    printf(" +----1----2----3----4----5----6----7----8----9----0\n");
    printf(">");
}