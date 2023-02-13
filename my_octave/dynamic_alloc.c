//copyright Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#include <stdlib.h>

/*in cele ce urmeaza variabila f(failure) va deveni 1,
daca malloc sau realloc vor esua*/

void alloc_v(int **v, int n, int *f)
{
	int *p = malloc(n * sizeof(int));
	if (!p) {
		*v = NULL;
		*f = 1;
		return;
	}
	*v = p;
}

void alloc_mx_series(int ****mxs, int n, int *f)
{
	int ***p = malloc(n * sizeof(int **));
	if (!p) {
		*mxs = NULL;
		*f = 1;
		return;
	}
	*mxs = p;
}

void alloc_mx(int ***matrix, int m, int n, int *f)
{
	int **p = malloc(m * sizeof(int *));
	if (!p) {
		*matrix = NULL;
		*f = 1;
		return;
	}
	*matrix = p;

	for (int i = 0; i < m; ++i) {
		p[i] = malloc(n * sizeof(int));
		if (!p[i]) {
			for (int j = 0; j < i; ++j)
				free(p[j]);
			*f = 1;
			//p va fi eliberata in free_memory
			return;
		}
	}
}

void free_matrix(int **matrix, int lines)
{
	for (int i = 0; i < lines; ++i)
		free(matrix[i]);
	free(matrix);
}

void free_memory(int ***mxs, int n, int *v_l, int *v_cl)
{
	//eliberam fiecare matrice
	for (int i = 0; i < n; ++i)
		free_matrix(mxs[i], v_l[i]);

	//eliberam sirul de matrici si vectorii de linii/coloane
	free(mxs);
	free(v_l);
	free(v_cl);
}

void realloc_v(int **v, int n, int *f)
{
	/*nu facem realocarea in acelasi vecctor din
	considerente defensive*/
	int *p = realloc(*v, n * sizeof(int));
	if (!p) {
		*v = NULL;
		*f = 1;
		return;
	}
	*v = p;
}

void realloc_mx_series(int ****mxs, int n, int *f)
{
	int ***p = realloc(*mxs, n * sizeof(int **));
	if (!p) {
		*mxs = NULL;
		*f = 1;
		return;
	}
	*mxs = p;
}

void expand(int ****mxs, int **v_l, int **v_cl, int *size, int count, int *f)
{
	/*Sirul de matrice va incepe cu o marime de un element. Pentru a avea
	in sirul de matrice exact capacitatea maxima, in cazul primei alocari
	(size == 1 si count == 0), nu vom mari sirul de matrice*/
	if (*size == count) {
		(*size)++;
		realloc_mx_series(mxs, *size, f);
		realloc_v(v_l, *size, f);
		realloc_v(v_cl, *size, f);
	}
}

void shrink(int ****mxs, int **v_l, int **v_cl, int *size, int *count, int *f)
{
	(*count)--;
	//daca sirul de matrice are un singur elemnet nu il vom micsora
	if (*size != 1) {
		(*size)--;
		realloc_mx_series(mxs, *size, f);
		realloc_v(v_l, *size, f);
		realloc_v(v_cl, *size, f);
	}
}

void alloc_set_up(int ****mxs, int **v_l, int **v_cl, int size, int *f)
{
	//initializam toti vectorii cu capacitatea 1
	alloc_v(v_l, size, f);
	alloc_v(v_cl, size, f);
	alloc_mx_series(mxs, size, f);
}

void test_failure(int ****mxs, int **v_l, int **v_cl, int count, int f)
{
	/*daca f  == 1, malloc sau realloc au esuat, prin urmare vom
	elibera resursele si inchidem programul*/
	if (f) {
		free_memory(*mxs, count, *v_l, *v_cl);
		exit(0);
	}
}
