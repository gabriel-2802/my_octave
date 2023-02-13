//copyright Carauleanu Valentin Gabriel 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>

void alloc_v(int **v, int n, int *f);

void alloc_mx_series(int ****mxs, int n, int *f);

void alloc_mx(int ***matrix, int m, int n, int *f);

void free_matrix(int **matrix, int lines);

void realloc_v(int **v, int n, int *f);

void realloc_mx_series(int ****mxs, int n, int *f);

void free_memory(int ***mxs, int n, int *v_l, int *v_cl);

void expand(int ****mxs, int **v_l, int **v_cl, int *size, int count, int *f);

void shrink(int ****mxs, int **v_l, int **v_cl, int *size, int *count, int *f);

void alloc_set_up(int ****mxs, int **v_l, int **v_cl, int size, int *f);

void test_failure(int ****mxs, int **v_l, int **v_cl, int count, int f);
