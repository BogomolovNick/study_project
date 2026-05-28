#include "int_ops.h"
#include "errors.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_correctness_int(char *str_num)
{
    char *c = str_num;
    int digit_counter = 0;
    int sign_is = 0;
    if (*c == '-' || *c == '+')
    {
        c++;
        sign_is = 1;
    }

    if (*c == '0' && (strlen(str_num) - sign_is) != 1)
        return ERR_NOT_CORRECT_DATA;

    while (*c != '\0')
    {
        if (!isdigit(*c))
            return ERR_NOT_CORRECT_DATA;

        c++;
        digit_counter++;
    }

    if (digit_counter == 0)
        return ERR_NOT_CORRECT_DATA;

    if (digit_counter > MAX_COUNT_NUMS_INT)
        return ERR_TOO_MUCH_DIGITS;

    return OK;
}

void read_int(char *str_num, BIG_INTEGER *num_int)
{
    char *c = str_num;

    if (*c == '+')
    {
        num_int->sign_flag = true;
        num_int->sign_plus = true;
        c++;
    }
    else if (*c == '-')
    {
        num_int->sign_flag = true;
        num_int->sign_plus = false;
        c++;
    }
    else
    {
        num_int->sign_flag = false;
        num_int->sign_plus = true;
    }

    int count_elements = 0;
    char tmp[2];

    while (*c != '\0')
    {
        tmp[0] = *c;
        tmp[1] = '\0';
        num_int->nums[count_elements++] = atoi(tmp);
        c++;
    }
    num_int->count_elements = count_elements;
}

void print_int(BIG_INTEGER num)
{
    printf(" ");

    if (num.sign_flag == true && num.sign_plus == true)
        printf("+");
    else if (num.sign_flag == true && num.sign_plus == false)
        printf("-");

    for (int i = 0; i < num.count_elements; i++)
        printf("%d", num.nums[i]);

    printf("\n");
}

void is_num_int(bool *is_int, char *str_num)
{
    char *c = str_num;
    *is_int = true;

    while (*c != '\0')
    {
        if (*c == '.' || *c == 'e' || *c == 'E')
        {
            *is_int = false;
            break;
        }
        c++;
    }
}

void switch_endian_int(BIG_INTEGER *num_int)
{
    int tmp[MAX_COUNT_NUMS_INT];
    
    for(int i = 0; i < num_int -> count_elements; i++)
        tmp[i] = num_int->nums[num_int -> count_elements - 1 - i];

    memcpy(num_int ->nums, tmp, sizeof(tmp));
}
