#!/bin/bash

gcc -Werror -Wall -Wextra -std=c99 int_ops.c main.c errors.c multiply.c float_ops.c io.c -o a.out
