//copyright Carauleanu Valentin Gabriel 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_alloc.h"
#include "numeric_functions.h"
#define SMALL 10007

void error(void);

void cmd_read_matrix(int ***mxs, int *v_l, int *v_cl, int *count, int *f);

int cmd_multiply(int *i, int *j, int *v_l, int *v_cl, int size);

void cmd_show_dim(int *v_l, int *v_cl, int count);

void cmd_show_matrix(int ***mxs, int *v_l, int *v_cl, int count);

void cmd_resize(int ***mxs, int count, int *v_l, int *v_cl, int *f);

void cmd_transpose(int ***mxs, int *v_l, int *v_cl, int count, int *f);

void cmd_sort_mxs(int ***mxs, int count, int *v_cl, int *v_l, int *f);

void cmd_power(int ***mxs, int *v_l, int *v_cl, int count, int *f);

int cmd_remove_mx(int ***mxs, int *v_l, int *v_cl, int count);

int check_command(char command);

int cmd_s(int *i, int *j, int *v_l, int *v_cl, int size);
