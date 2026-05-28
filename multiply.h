#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "float_ops.h"
#include "int_ops.h"

void multiply(BIG_INTEGER *num_int,BIG_FLOAT *num_float, BIG_FLOAT *result);
int check_for_all_null(BIG_FLOAT *num_float, BIG_INTEGER *num_int);

#endif