//copyright Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_alloc.h"
#define SMALL 10007

int **add_mxs(int **a, int **b, int n, int *f)
{
	int **res;
	alloc_mx(&res, n, n, f);
	if (*f)
		return NULL;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			res[i][j] = ((a[i][j] + b[i][j]) % SMALL + SMALL) % SMALL;

	return res;
}

int **sub_mxs(int **a, int **b, int n, int *f)
{
	//algoritmul de scadere a 2 matrice
	int **res;
	alloc_mx(&res, n, n, f);
	if (*f)
		return NULL;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			res[i][j] = ((a[i][j] - b[i][j]) % SMALL + SMALL) % SMALL;

	return res;
}

void split_matrix(int **a, int **mini, int istart, int jstart, int n)
{
	/*vom completa toate elementele din matricea mini cu elemente
	din matricea a pornind de la linia istart si coloana jstart*/

	for (int i1 = 0, i2 = istart; i1 < n; ++i1, ++i2)
		for (int j1 = 0, j2 = jstart; j1 < n; ++j1, ++j2)
			mini[i1][j1] = a[i2][j2];
}

void join_matrix(int **a, int **greater, int istart, int jstart, int n)
{
	/*vom completa in matricea greater cu toate elementele matricii a,
	pornind de la linia istart si coloana jstart*/

	for (int i1 = 0, i2 = istart; i1 < n; ++i1, ++i2)
		for (int j1 = 0, j2 = jstart; j1 < n; ++j1, ++j2)
			greater[i2][j2] = a[i1][j1];
}

void free_strassen_a(int **a1, int **a2, int **a3, int **a4, int n)
{
	free_matrix(a1, n);
	free_matrix(a2, n);
	free_matrix(a3, n);
	free_matrix(a4, n);
}

void free_strassen_b(int **b1, int **b2, int **b4, int **b3, int n)
{
	free_matrix(b1, n);
	free_matrix(b2, n);
	free_matrix(b3, n);
	free_matrix(b4, n);
}

void free_strassen_c(int **c1, int **c2, int **c3, int **c4, int n)
{
	free_matrix(c1, n);
	free_matrix(c2, n);
	free_matrix(c3, n);
	free_matrix(c4, n);
}

void f_m(int **a, int **b, int **c, int **d, int **e, int **f, int **g, int n)
{
	//free_strassen_m
	free_matrix(a, n);
	free_matrix(b, n);
	free_matrix(c, n);
	free_matrix(d, n);
	free_matrix(e, n);
	free_matrix(f, n);
	free_matrix(g, n);
}

void free_strassen_aux(int **aux1, int **aux2, int n)
{
	free_matrix(aux1, n);
	free_matrix(aux2, n);
}

int **strassen_base_case(int **a, int **b, int n, int *f)
{
	int a_, b_, c, d, e, f_, g, h;
	a_ = a[0][0];
	b_ = a[0][1];
	c = a[1][0];
	d = a[1][1];

	e = b[0][0];
	f_ = b[0][1];
	g = b[1][0];
	h = b[1][1];

	int m1, m2, m3, m4, m5, m6, m7;
	m1 = (a_ + d) * (e + h);
	m2 = (c + d) * e;
	m3 = a_ * (f_ - h);
	m4 = d * (g - e);
	m5 = (a_ + b_) * h;
	m6 = (c - a_) * (e + f_);
	m7 = (b_ - d) * (g + h);

	int **res;
	alloc_mx(&res, n, n, f);
	res[0][0] = m1 + m4 - m5 + m7;
	res[0][1] = m3 + m5;
	res[1][0] = m2 + m4;
	res[1][1] = m1 - m2 + m3 + m6;

	return res;
}

int **strassen(int **a, int **b, int n, int *f)
{
	if (n == 2)
		return strassen_base_case(a, b, n, f);

	n /= 2;
	int **a1, **a2, **a3, **a4, **b1, **b2, **b3, **b4;
	alloc_mx(&a1, n, n, f);
	alloc_mx(&a2, n, n, f);
	alloc_mx(&a3, n, n, f);
	alloc_mx(&a4, n, n, f);
	alloc_mx(&b1, n, n, f);
	alloc_mx(&b2, n, n, f);
	alloc_mx(&b3, n, n, f);
	alloc_mx(&b4, n, n, f);

	//impartire matrice in sub matrice
	split_matrix(a, a1, 0, 0, n);
	split_matrix(a, a2, 0, n, n);
	split_matrix(a, a3, n, 0, n);
	split_matrix(a, a4, n, n, n);
	split_matrix(b, b1, 0, 0, n);
	split_matrix(b, b2, 0, n, n);
	split_matrix(b, b3, n, 0, n);
	split_matrix(b, b4, n, n, n);

	//vom folosi 2 matrice aux pentru a putea elibera memoria ulterior
	int **m1, **m2, **m3, **m4, **m5, **m6, **m7, **aux1, **aux2;
	aux1 = add_mxs(a1, a4, n, f);
	aux2 = add_mxs(b1, b4, n, f);
	m1 = strassen(aux1, aux2, n, f);
	free_strassen_aux(aux1, aux2, n);
	aux1 = add_mxs(a3, a4, n, f);
	m2 = strassen(aux1, b1, n, f);
	free_matrix(aux1, n);
	aux1 = sub_mxs(b2, b4, n, f);
	m3 = strassen(a1, aux1, n, f);
	free_matrix(aux1, n);
	aux1 = sub_mxs(b3, b1, n, f);
	m4 = strassen(a4, aux1, n, f);
	free_matrix(aux1, n);
	aux1 = add_mxs(a1, a2, n, f);
	m5 = strassen(aux1, b4, n, f);
	free_matrix(aux1, n);
	aux1 = sub_mxs(a3, a1, n, f);
	aux2 = add_mxs(b1, b2, n, f);
	m6 = strassen(aux1, aux2, n, f);
	free_strassen_aux(aux1, aux2, n);
	aux1 = sub_mxs(a2, a4, n, f);
	aux2 = add_mxs(b3, b4, n, f);
	m7 = strassen(aux1, aux2, n, f);
	free_strassen_aux(aux1, aux2, n);

	int **c1, **c2, **c3, **c4;
	aux1 = add_mxs(m1, m4, n, f);
	aux2 = sub_mxs(aux1, m5, n, f);
	c1 = add_mxs(aux2, m7, n, f);
	free_strassen_aux(aux1, aux2, n);
	c2 = add_mxs(m3, m5, n, f);
	c3 = add_mxs(m2, m4, n, f);
	aux1 = sub_mxs(m1, m2, n, f);
	aux2 = add_mxs(aux1, m3, n, f);
	c4 = add_mxs(aux2, m6, n, f);
	free_strassen_aux(aux1, aux2, n);

	int **res;
	alloc_mx(&res, 2 * n, 2 * n, f);
	//unim matricele in matricea rezultat
	join_matrix(c1, res, 0, 0, n);
	join_matrix(c2, res, 0, n, n);
	join_matrix(c3, res, n, 0, n);
	join_matrix(c4, res, n, n, n);

	free_strassen_a(a1, a2, a3, a4, n);
	free_strassen_b(b1, b2, b3, b4, n);
	free_strassen_c(c1, c2, c3, c4, n);
	f_m(m1, m2, m3, m4, m5, m6, m7, n);
	return res;
}
