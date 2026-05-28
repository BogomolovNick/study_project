#ifndef INT_OPS_H
#define INT_OPS_H

#include <stdbool.h>
#define MAX_COUNT_NUMS_INT 40

typedef struct
{
    bool sign_flag;
    bool sign_plus;
    int nums[MAX_COUNT_NUMS_INT];
    int count_elements;
} BIG_INTEGER;

int check_correctness_int(char *str_num);
void read_int(char *str_num, BIG_INTEGER *num_int);
void print_int(BIG_INTEGER num);
void is_num_int(bool *is_int, char *str_num);
void switch_endian_int(BIG_INTEGER *num_int);

#endif
