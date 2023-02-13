//copyright Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_alloc.h"
#include "numeric_functions.h"
#include "commands.h"
#include "strassen.h"
#define SMALL 10007

int main(void)
{
	int ***mxs, *v_l, *v_cl, size = 1, count = 0, end = 0, i, j, f = 0;
	/*size reprez capacitatea sirului de matrice mxs, count reprezinta
	numarul de matrice din sir, f va memora eventualul esec al
	alocarii dinamice*/
	alloc_set_up(&mxs, &v_l, &v_cl, size, &f);
	test_failure(&mxs, &v_l, &v_cl, count, f);

	while (1) {
		char command;
		scanf(" %c", &command);

		switch (command) {
		case 'L':
			expand(&mxs, &v_l, &v_cl, &size, count, &f);
			test_failure(&mxs, &v_l, &v_cl, count, f);
			cmd_read_matrix(mxs, v_l, v_cl, &count, &f);
			test_failure(&mxs, &v_l, &v_cl, count, f);
			break;
		case 'D':
			cmd_show_dim(v_l, v_cl, count);
			break;
		case 'P':
			cmd_show_matrix(mxs, v_l, v_cl, count);
			break;
		case 'C':
			cmd_resize(mxs, count, v_l, v_cl, &f);
			test_failure(&mxs, &v_l, &v_cl, count, f);
			break;
		case 'M':
			if (cmd_multiply(&i, &j, v_l, v_cl, size)) {
				expand(&mxs, &v_l, &v_cl, &size, count, &f);
				test_failure(&mxs, &v_l, &v_cl, count, f);
				mxs[count] = mp(mxs[i], mxs[j], v_l[i], v_cl[i], v_cl[j], &f);
				test_failure(&mxs, &v_l, &v_cl, count, f);
				v_l[count] = v_l[i];
				v_cl[count++] = v_cl[j];
			}
			break;
		case 'O':
			cmd_sort_mxs(mxs, count, v_cl, v_l, &f);
			test_failure(&mxs, &v_l, &v_cl, count, f);
			break;
		case 'T':
			cmd_transpose(mxs, v_l, v_cl, count, &f);
			test_failure(&mxs, &v_l, &v_cl, count, f);
			break;
		case 'R':
			cmd_power(mxs, v_l, v_cl, count, &f);
			test_failure(&mxs, &v_l, &v_cl, count, f);
			break;
		case 'F':
			if (cmd_remove_mx(mxs, v_l, v_cl, count))
				shrink(&mxs, &v_l, &v_cl, &size, &count, &f);
			test_failure(&mxs, &v_l, &v_cl, count, f);
			break;
		case 'S':
			if (cmd_s(&i, &j, v_l, v_cl, size)) {
				expand(&mxs, &v_l, &v_cl, &size, count, &f);
				test_failure(&mxs, &v_l, &v_cl, count, f);
				mxs[count] = strassen(mxs[i], mxs[j], v_l[i], &f);
				test_failure(&mxs, &v_l, &v_cl, count, f);
				v_l[count] = v_l[i];
				v_cl[count++] = v_l[i];
			}
			break;
		case 'Q':
			end = 1;
			free_memory(mxs, count, v_l, v_cl);
			break;
		}

		if (end)
			break;

		if (!check_command(command))
			printf("Unrecognized command\n");
	}
	return 0;
}
