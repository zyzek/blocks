#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "args.h"

Arg *args;
Arg **matches;
size_t n_args = 0;
bool allocated = false;

void free_arglist() {
	if (!allocated) return;

	allocated = false;

	for (int i = 0; i < n_args; ++i) {
		if (args[i].flag) free(args[i].flag);
		if (args[i].val) free(args[i].val);
	}

	free(args);
	free(matches);
}

Arg *init_arglist(int argc, const char *argv[]) {
	size_t curr_arg = 0;
	Arg *p_arg = NULL;

	args = (Arg *)calloc(argc, sizeof(Arg*) + 1);
	allocated = true;

	for (int i = 1; i < argc; ++i) {
		if (!p_arg) {
			p_arg = &args[curr_arg];
			++curr_arg;

			if (argv[i][0] == '-') {
				p_arg->flag = (char *)malloc(strlen(argv[i]) + 1);
				strcpy(p_arg->flag, argv[i]);
			}
			else {
				p_arg->flag = (char *)calloc(1, sizeof(char));
				p_arg->val = (char *)malloc(strlen(argv[i]) + 1);
				strcpy(p_arg->val, argv[i]);
				p_arg = NULL;
			}
		}
		else {
			if (argv[i][0] == '-') {
				p_arg->val = (char *)calloc(1, sizeof(char));
				p_arg = &args[curr_arg];
				p_arg->flag = (char *)malloc(strlen(argv[i]) + 1);
				strcpy(p_arg->flag, argv[i]);
				++curr_arg;
			}
			else {
				p_arg->val = (char *)malloc(strlen(argv[i]) + 1);
				strcpy(p_arg->val, argv[i]);
				p_arg = NULL;
			}
		}
	}

	n_args = curr_arg;
	matches = (Arg **)calloc(n_args, sizeof(Arg *) + 1);
	return args;
}

Arg *get_args() {
	return args;
}

size_t get_n_args() {
	return n_args;
}

Arg **args_flag(const char *flag) {
	size_t m = 0;

	for (int i = 0; i < n_args; ++i) {
		if (!strcmp(args[i].flag, flag)) {
			matches[m] = &args[i];
			++m;
		}
	}

	matches[m] = NULL;

	return matches;
}