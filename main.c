#include "errors.h"
#include "float_ops.h"
#include "int_ops.h"
#include "io.h"
#include "multiply.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void)
{
    printf("\nПрограмма умножает вещественное число на целое.\nПорядок вводимых типов не важен.\nВ вещественном числе обязателен знак 'E/e' или '.'.\nИначе число будет считаться целым.\nЦелое число не может содержать больше 40 цифр.\nМантиса вещественного числа не может быть длинее 30 цифр.\nПорядок не больше 5 цифр.\n\n");

    int rc = OK;

    BIG_INTEGER num_int;
    BIG_FLOAT num_float;
    BIG_FLOAT result;

    char str_num[MAX_STR];

    print_scale();

    if ((rc = input_num(str_num)) != OK)
    {
        print_error(rc);
        return rc;
    }

    bool is_int, tmp_is_int;

    is_num_int(&is_int, str_num);

    tmp_is_int = is_int;

    if (is_int)
    {
        if ((rc = check_correctness_int(str_num)) != OK)
        {
            print_error(rc);
            return rc;
        }

        read_int(str_num, &num_int);
    }
    else
    {
        correct_float(str_num);
        if ((rc = check_correctness_float(str_num)) != OK)
        {
            print_error(rc);
            return rc;
        }

        read_float(str_num, &num_float);
    }

    str_num[0] = '\0';

    print_scale();

    if ((rc = input_num(str_num)) != OK)
    {
        print_error(rc);
        return rc;
    }

    is_num_int(&is_int, str_num);

    if (tmp_is_int == is_int)
    {
        rc = ERR_SAME_TYPE;
        print_error(rc);
        return rc;
    }

    if (is_int)
    {
        if ((rc = check_correctness_int(str_num)) != OK)
        {
            print_error(rc);
            return rc;
        }

        read_int(str_num, &num_int);
    }
    else
    {
        correct_float(str_num);
        if ((rc = check_correctness_float(str_num)) != OK)
        {
            print_error(rc);
            return rc;
        }

        read_float(str_num, &num_float);
    }

    get_mantis(&num_float);

    if(check_for_all_null(&num_float,&num_int))
    {
        result.count_elem_int_p = 1;
        result.degree = 0;
        result.sign_flag = true;
        result.sign_plus = true;
        result.count_elem_fract_p = 1;
        result.int_part[0] = 0;
        result.fract_part[0] = 0;
        print_float(result);

        return rc;
    }

    switch_endian_int(&num_int);

    switch_endian_float(&num_float);

    multiply(&num_int, &num_float, &result);

    switch_endian_int(&num_int);

    del_zero(&result);

    if(result.count_elem_int_p > 40)
        round_res(&result);
        
    switch_endian_float(&result);

    get_fract_p(&result);

    if(result.degree / 100000 != 0)
    {
        printf("Переполнение порядка\n");
        return 404;
    }


    print_float(result);

    return rc;
}
