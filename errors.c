#include "errors.h"
#include <stdio.h>

void print_error(int rc)
{
    switch (rc)
    {

    case ERR_INPUT_STR:
        printf("Ошибка ввода строки\n");
        break;

    case ERR_NOT_CORRECT_DATA:
        printf("Некорректное число\n");
        break;

    case ERR_TOO_MUCH_MANTIS:
        printf("Слишком большая мантиса\n");
        break;

    case ERR_TOO_MUCH_DEGREE:
        printf("Слишком большая степень\n");
        break;

    case ERR_TOO_MUCH_DIGITS:
        printf("Слишком много цифр в числе\n");
        break;

    case ERR_SAME_TYPE:
        printf("Введены числа одинакового типа\n");
        break;

    default:
        break;
    }
}