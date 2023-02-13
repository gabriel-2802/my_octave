//copyright Carauleanu Valentin Gabriel 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_alloc.h"
#define SMALL 10007

int **add_mxs(int **a, int **b, int n, int *f);

int **sub_mxs(int **a, int **b, int n, int *f);

void split_matrix(int **a, int **mini, int istart, int jstart, int n);

void join_matrix(int **a, int **greater, int istart, int jstart, int n);

void free_strassen_a(int **a1, int **a2, int **a3, int **a4, int n);

void free_strassen_b(int **b1, int **b2, int **b4, int **b3, int n);

void free_strassen_c(int **c1, int **c2, int **c3, int **c4, int n);

void f_m(int **a, int **b, int **c, int **d, int **e, int **f, int **g, int n);

void free_strassen_aux(int **aux1, int **aux2, int n);

int **strassen_base_case(int **a, int **b, int n, int *f);

int **strassen(int **a, int **b, int n, int *f);
