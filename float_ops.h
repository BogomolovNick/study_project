#ifndef FLOAT_OPS_H
#define FLOAT_OPS_H

#include <stdbool.h>

#define MAX_COUNT_NUMS_FLOAT 100040
#define MAX_COUNT_DIGITS_MANTIS 30
#define MAX_COUNT_DIGITS_DEGREE 5

typedef struct
{
    bool sign_flag;
    bool sign_plus;
    int int_part[MAX_COUNT_NUMS_FLOAT];
    int fract_part[MAX_COUNT_NUMS_FLOAT];
    int count_elem_int_p;
    int count_elem_fract_p;
    int degree;
} BIG_FLOAT;

int check_correctness_float(char *str_num);
void read_float(char *str_num, BIG_FLOAT *num_float);
void correct_float(char *str_num);
void print_float(BIG_FLOAT num);
void get_mantis(BIG_FLOAT *num_float);
void switch_endian_float(BIG_FLOAT *num_float);
void del_zero(BIG_FLOAT *result);
void round_res(BIG_FLOAT *result);
void get_fract_p(BIG_FLOAT *result);

#endif