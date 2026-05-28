#include "float_ops.h"
#include "errors.h"
#include "io.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_correctness_float(char *str_num)
{
    char *c = str_num;
    int digit_counter = 0;

    if (*c == '+' || *c == '-')
        c++;

    if (*c == '0' && *(c + 1) != '.')
        return ERR_NOT_CORRECT_DATA;
    
    if (*c == '0' && *(c + 1) == '.')
        digit_counter--;

    if (*c == '.' || *c == 'e' || *c == 'E' || *c == '\0')
        return ERR_NOT_CORRECT_DATA;

    while (*c != '.' && *c != 'e' && *c != 'E' && *c != '\0')
    {
        if (!isdigit(*c))
            return ERR_NOT_CORRECT_DATA;

        digit_counter++;
        c++;
    }

    if (*c != '\0')
    {
        if (*c == '.' && (*(c + 1) == 'e' || *(c + 1) == 'E' || *(c + 1) == '\0'))
            return ERR_NOT_CORRECT_DATA;

        if(*c == '.' && (*(c + 1) == '0') && (*(c + 2) == 'e' || *(c + 2) == 'E' || *(c + 2) == '\0'))
            digit_counter--;

        if (*c == '.')
            c++;

        while (*c != 'e' && *c != 'E' && *c != '\0')
        {
            if (!isdigit(*c))
                return ERR_NOT_CORRECT_DATA;

            digit_counter++;
            c++;
        }

        if (digit_counter > MAX_COUNT_DIGITS_MANTIS)
            return ERR_TOO_MUCH_MANTIS;

        if (*c == 'e' || *c == 'E')
        {
            int digit_counter_degree = 0;

            c++;

            if (*c == '+' || *c == '-')
                c++;

            if (*c == '\0')
                return ERR_NOT_CORRECT_DATA;

            if (*c == '0' && *(c+1) != '\0')
                return ERR_NOT_CORRECT_DATA;

            while (*c != '\0')
            {
                if (!isdigit(*c))
                    return ERR_NOT_CORRECT_DATA;

                digit_counter_degree++;
                c++;
            }

            if (digit_counter_degree > MAX_COUNT_DIGITS_DEGREE)
                return ERR_TOO_MUCH_DEGREE;
        }
    }

    return OK;
}

void read_float(char *str_num, BIG_FLOAT *num_float)
{
    char *c = str_num;

    if (*c == '+')
    {
        num_float->sign_flag = true;
        num_float->sign_plus = true;
        c++;
    }
    else if (*c == '-')
    {
        num_float->sign_flag = true;
        num_float->sign_plus = false;
        c++;
    }
    else
    {
        num_float->sign_flag = false;
        num_float->sign_plus = true;
    }

    int count_elements = 0;
    char tmp[2];

    while (*c != '\0' && *c != '.' && *c != 'e' && *c != 'E')
    {
        tmp[0] = *c;
        tmp[1] = '\0';

        num_float->int_part[count_elements++] = atoi(tmp);

        c++;
    }
    num_float->count_elem_int_p = count_elements;
    count_elements = 0;

    if (*c == '.')
    {
        c++;
        while (*c != '\0' && *c != 'e' && *c != 'E')
        {
            tmp[0] = *c;
            tmp[1] = '\0';

            num_float->fract_part[count_elements++] = atoi(tmp);

            c++;
        }
        num_float->count_elem_fract_p = count_elements;
        count_elements = 0;
    }
    else
        num_float->count_elem_fract_p = count_elements;

    if (*c == 'e' || *c == 'E')
    {
        int sign = 1;
        c++;
        if (*c == '+')
            c++;
        else if (*c == '-')
        {
            sign = -1;
            c++;
        }

        int counter_enough_digits = 0;
        char element[MAX_COUNT_DIGITS_DEGREE];

        while (*c != '\0')
        {
            element[counter_enough_digits++] = *c;

            if (counter_enough_digits == MAX_COUNT_DIGITS_DEGREE || *(c + 1) == '\0')
            {
                element[counter_enough_digits] = '\0';
                num_float->degree = (atoi(element) * sign);
                counter_enough_digits = 0;
            }
            c++;
        }
    }
    else
        num_float->degree = 0;
}

void correct_float(char *str_num)
{
    int len_str = strlen(str_num);
    char tmp[MAX_STR];

    if (len_str == 0)
        return;

    if (str_num[len_str - 1] == '.')
    {
        str_num[len_str] = '0';
        str_num[len_str + 1] = '\0';
    }
    else if (str_num[0] == '.')
    {
        tmp[0] = '0';
        tmp[1] = '\0';
        strcat(tmp, str_num);
        strcpy(str_num, tmp);
    }
}

void print_float(BIG_FLOAT num)
{
    printf(" ");

    if (num.sign_flag == true && num.sign_plus == true)
        printf("+");
    else if (num.sign_flag == true && num.sign_plus == false)
        printf("-");

    for (int i = 0; i < num.count_elem_int_p; i++)
        printf("%d", num.int_part[i]);

    if (num.count_elem_fract_p > 0)
    {
        printf(".");
        for (int i = 0; i < num.count_elem_fract_p; i++)
            printf("%d", num.fract_part[i]);
    }

    printf("E");
    if (num.degree > 0)
    {
        printf("+");
        printf("%d", num.degree);
    }
    else
        printf("%d", num.degree);

    printf("\n");
}

void get_mantis(BIG_FLOAT *num_float)
{
    int mantis[MAX_COUNT_NUMS_FLOAT];
    int len_mantis = 0;

    
    if(num_float->int_part[0] != 0)
    {
        for(int i = 0; i < num_float -> count_elem_int_p; i++)
            mantis[len_mantis++] = num_float->int_part[i];
        
        for(int i = 0; i < num_float ->count_elem_fract_p; i++)
            mantis[len_mantis++] = num_float->fract_part[i];
    }
    else
    {
        int i = 0;
        while(num_float->fract_part[i] == 0)
            i++;
        
        for(int j = i; j < num_float ->count_elem_fract_p; j++)
            mantis[len_mantis++] = num_float->fract_part[j];
        
    }

    num_float->degree = num_float-> degree - num_float ->count_elem_fract_p;

    memcpy(num_float ->int_part, mantis, len_mantis * sizeof(int));
    num_float -> count_elem_int_p = len_mantis;
    num_float -> count_elem_fract_p = 0;
}

void switch_endian_float(BIG_FLOAT *num_float)
{
    int tmp[MAX_COUNT_NUMS_FLOAT];
    
    for(int i = 0; i < num_float -> count_elem_int_p; i++)
        tmp[i] = num_float->int_part[num_float -> count_elem_int_p - 1 - i];

    memcpy(num_float ->int_part, tmp, sizeof(tmp));
}

void del_zero(BIG_FLOAT *result)
{
    while(result->int_part[0] == 0)
    {
        for (int i = 0; i < result->count_elem_int_p - 1; i++)
        {
            result->int_part[i] = result->int_part[i+1];
        }
        result->degree++;
        result->count_elem_int_p--;
    }
}

void round_res(BIG_FLOAT *result)
{
    while(result->count_elem_int_p > 40)
    {
        if(result->int_part[0] > 4)
        {
            result->int_part[1]++;
            result->int_part[0] = 0;
        }
        else
            result->int_part[0] = 0;

        int count_ops = 1;

        while(count_ops)
        {
            count_ops = 0;
            int last_round_index = 0;
            for(int i = 0; i < result->count_elem_int_p; i++)
            {
                if(result->int_part[i] / 10 != 0)
                {
                    last_round_index = i;
                    result->int_part[i+1] += (result->int_part[i] / 10);
                    result->int_part[i] = result->int_part[i] - ((result->int_part[i] / 10)*10);
                    count_ops++;
                }
            }
            if(last_round_index + 1 == result->count_elem_int_p)
                result->count_elem_int_p++;
        }

        del_zero(result);
    }
}

void get_fract_p(BIG_FLOAT *result)
{
    result->count_elem_fract_p = result->count_elem_int_p;

    memcpy(result->fract_part,result->int_part,result->count_elem_fract_p * sizeof(int));

    result->degree += result->count_elem_int_p;
    result->count_elem_int_p = 1;
    result->int_part[0] = 0;
}
