#include "multiply.h"
#include "errors.h"
#include "float_ops.h"
#include "int_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNT_RESULT_MANTIS 40

void multiply(BIG_INTEGER *num_int,BIG_FLOAT *num_float, BIG_FLOAT *result)
{
    int count_ops = 1;
    
    result->count_elem_int_p = num_float->count_elem_int_p;
    result->degree = num_float->degree;
    result->sign_flag = true;
    result->sign_plus = (num_float->sign_plus == num_int->sign_plus);
    result->count_elem_fract_p = num_float->count_elem_fract_p;
    
    memset(result->int_part,0,sizeof(result->int_part));
    
    for(int i = 0; i < num_int->count_elements; i++)
    {
        result->count_elem_int_p++;
        for(int j = 0; j < result->count_elem_int_p ; j++)
        {
            int pos = i + j;
            result->int_part[pos] += num_float->int_part[j] * num_int->nums[i];
        }
        
    }
    result->count_elem_int_p--;

    while(count_ops)
    {
        count_ops = 0;
        int last_round_index = -1;
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
    
}

int check_for_all_null(BIG_FLOAT *num_float, BIG_INTEGER *num_int)
{
    bool is_nul_1 = true, is_nul_2 = true;

    for(int i = 0; i < num_float->count_elem_int_p; i++)
    {
        if(num_float->int_part[i] != 0)
            is_nul_1 = false;
    }

    for(int i = 0; i < num_int->count_elements; i++)
    {
        if(num_int->nums[i] != 0)
            is_nul_2 = false;
    }

    return is_nul_1 || is_nul_2;
}