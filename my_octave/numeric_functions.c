//copyright Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_alloc.h"
#define SMALL 10007

void read_matrix(int **a, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &a[i][j]);
}

void print_matrix(int **a, int m, int n)
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}

int **resize_matrix(int **mx, int *lines, int l, int *col, int c, int *f)
{
	int **p;
	alloc_mx(&p, l, c, f);
	if (*f)
		return NULL;

	for (int i = 0; i < l; ++i)
		for (int j = 0; j < c; ++j)
			p[i][j] = mx[lines[i]][col[j]];
	return p;
}

int **mp(int **a, int **b, int m, int n, int q, int *f)
{
	//m = nr linii a, n = nr col a, p = nr linii b, q = nr col b
	int **res;
	alloc_mx(&res, m, q, f);
	if (*f)
		return NULL;

	for (int i = 0; i < m; ++i)
		for (int j = 0; j < q; ++j) {
			res[i][j] = 0;
			for (int k = 0; k < n; ++k)
				res[i][j] += (((a[i][k] * b[k][j] % SMALL) + SMALL) % SMALL);
			res[i][j] = ((res[i][j] % SMALL) + SMALL) % SMALL;
		}
	return res;
}

int sum_mx(int **a, int m, int n)
{
	int s = 0;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			s += ((a[i][j] % SMALL + SMALL) % SMALL);

	s = (s % SMALL + SMALL) % SMALL;
	return s;
}

void swap_nr(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void swap_mx(int ***mxs, int i, int j)
{
	int **aux = mxs[i];
	mxs[i] = mxs[j];
	mxs[j] = aux;
}

int **transpose(int **a, int m, int n, int *f)
{
	//transpusa va avea n linii si m coloane
	int **tr;
	alloc_mx(&tr, n, m, f);
	if (*f)
		return NULL;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			tr[i][j] = a[j][i];

	return tr;
}

int **power_mx(int **mx, int n, int x, int *f)
{
	/*I va fi matricea unitate de ordin n, iar x
	puterea*/
	int **I;
	alloc_mx(&I, n, n, f);
	if (*f)
		return NULL;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i == j)
				I[i][j] = 1;
			else
				I[i][j] = 0;

	if (x == 0) {
		free(mx);
		return I;
	}
	/*daca x este par, ridicam la patrat matricea si injumatatim
	puterea, daca x este impar, decrementam puterea si inmultim
	rezultatul cu matricea*/
	while (x) {
		if (x % 2 == 0) {
			x /= 2;
		int **aux = mp(mx, mx, n, n, n, f);
		if (*f) {
			free_matrix(I, n);
			/*matricea mx va fi eliberata ulterior in
			functia free_memory*/
			return NULL;
		}
		free_matrix(mx, n);
		mx = aux;
		} else {
			x--;
			int **aux = mp(I, mx, n, n, n, f);
			if (*f) {
				free_matrix(I, n);
				return NULL;
			}
			free_matrix(I, n);
			I = aux;
		}
	}
	free_matrix(mx, n);
	return I;
}
