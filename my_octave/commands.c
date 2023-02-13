//copyright Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_alloc.h"
#include "numeric_functions.h"
#include "strassen.h"
#define SMALL 10007

void error(void)
{
	printf("No matrix with the given index\n");
}

void cmd_read_matrix(int ***mxs, int *v_l, int *v_cl, int *count, int *f)
{
	int m, n;
	scanf("%d%d", &m, &n);

	alloc_mx(&mxs[*count], m, n, f);
	if (*f)
		return;
	read_matrix(mxs[*count], m, n);
	v_l[*count] = m;
	v_cl[(*count)++] = n;
}

int cmd_multiply(int *i, int *j, int *v_l, int *v_cl, int size)
{
	scanf("%d%d", i, j);
	//i, j vor fi index uri pentru matricile dorite

	if (*i > size - 1 || *i < 0 || *j > size - 1 || *j < 0) {
		error();
		return 0;
	} else  if (v_cl[*i] != v_l[*j]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

void cmd_show_dim(int *v_l, int *v_cl, int count)
{
	int index;
	scanf("%d", &index);
	if (index > count - 1 || index < 0) {
		error();
		return;
	}
	printf("%d %d\n", v_l[index], v_cl[index]);
}

void cmd_show_matrix(int ***mxs, int *v_l, int *v_cl, int count)
{
	int index;
	scanf("%d", &index);
	if (index > (count - 1) || index < 0) {
		error();
		return;
	}
	print_matrix(mxs[index], v_l[index], v_cl[index]);
}

void cmd_resize(int ***mxs, int count, int *v_l, int *v_cl, int *f)
{
	int index;
	scanf("%d", &index);
	if (index > (count - 1) || index < 0) {
		error();
		return;
	}

	int l, *lines, c, *col;

	scanf("%d", &l);
	alloc_v(&lines, l, f);
	if (*f)
		return;
	for (int i = 0; i < l; ++i)
		scanf("%d", &lines[i]);

	scanf("%d", &c);
	alloc_v(&col, c, f);
	if (*f) {
		free(lines);
		return;
	}
	for (int i = 0; i < c; ++i)
		scanf("%d", &col[i]);

	//cream noua matrice
	int **aux = resize_matrix(mxs[index], lines, l, col, c, f);
	//eliberam din memorie matricea index
	free_matrix(mxs[index], v_l[index]);
	mxs[index] = aux;
	v_l[index] = l;
	v_cl[index] = c;

	free(lines);
	free(col);
}

void cmd_transpose(int ***mxs, int *v_l, int *v_cl, int count, int *f)
{
	int index;
	scanf("%d", &index);
	if (index > count - 1 || index < 0) {
		error();
		return;
	}
	int **aux = transpose(mxs[index], v_l[index], v_cl[index], f);
	free_matrix(mxs[index], v_l[index]);
	mxs[index] = aux;
	swap_nr(&v_l[index], &v_cl[index]);
}

void cmd_sort_mxs(int ***mxs, int count, int *v_cl, int *v_l, int *f)
{
	int *v_sum;
	alloc_v(&v_sum, count, f);
	if (*f)
		return;
	for (int i = 0; i < count; ++i)
		v_sum[i] = sum_mx(mxs[i], v_l[i], v_cl[i]);

	//sortam vectorul de matrici folosind vectorul de sume
	for (int i = 0; i < count - 1; ++i)
		for (int j = i + 1; j < count; ++j)
			if (v_sum[i] > v_sum[j]) {
				swap_nr(&v_sum[i], &v_sum[j]);
				swap_nr(&v_l[i], &v_l[j]);
				swap_nr(&v_cl[i], &v_cl[j]);
				swap_mx(mxs, i, j);
			}
	free(v_sum);
}

void cmd_power(int ***mxs, int *v_l, int *v_cl, int count, int *f)
{
	int index, x;
	scanf("%d%d", &index, &x);
	if (index > count - 1 || index < 0) {
		error();
		return;
	}

	if (x < 0) {
		printf("Power should be positive\n");
		return;
	}

	if (v_l[index] != v_cl[index]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	mxs[index] = power_mx(mxs[index], v_l[index], x, f);
}

int cmd_remove_mx(int ***mxs, int *v_l, int *v_cl, int count)
{
	int index;
	scanf("%d", &index);
	if (index > count - 1 || index < 0) {
		error();
		return 0;
	}

	/*eliberam matricea dorita si mutam toate matricile
	cu o pozitite spre stanga, dar si valorile vectorilor de
	linii / coloane */
	free_matrix(mxs[index], v_l[index]);
	mxs[index] = NULL;

	for (int i = index; i < count - 1; ++i) {
		swap_mx(mxs, i, i + 1);
		swap_nr(&v_l[i], &v_l[i + 1]);
		swap_nr(&v_cl[i], &v_cl[i + 1]);
	}
	return 1;
}

int check_command(char command)
{
	/*functia returneaza 1 daca char-ul memorat de
	command este o litera mare (comanda invalida)*/
	char v[] = "LDPCMOTRFSQ";
	int n = strlen(v);
	for (int i = 0; i < n; ++i)
		if (command == v[i])
			return 1;

	if (command >= 'A' && command <= 'Z')
		return 0;
	else
		return 1;
}

int cmd_s(int *i, int *j, int *v_l, int *v_cl, int size)
{
	scanf("%d%d", i, j);
	if (*i > size - 1 || *i < 0 || *j > size - 1 || *j < 0) {
		error();
		return 0;
	} else  if (v_cl[*i] != v_l[*j]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}

	return 1;
}
