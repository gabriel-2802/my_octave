//copyright Carauleanu Valentin Gabriel 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_alloc.h"
#define SMALL 10007

void read_matrix(int **a, int n, int m);

void print_matrix(int **a, int m, int n);

int **resize_matrix(int **mx, int *lines, int l, int *col, int c, int *f);

int **mp(int **a, int **b, int m, int n, int q, int *f);

void swap_nr(int *a, int *b);

void swap_mx(int ***mxs, int i, int j);

int sum_mx(int **a, int m, int n);

int **transpose(int **a, int m, int n, int *f);

int **power_mx(int **mx, int n, int x, int *f);
