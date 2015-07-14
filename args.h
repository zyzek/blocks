#ifndef ARGS_H
#define ARGS_H
typedef struct Arg Arg;

struct Arg {
	const char *flag;
	const char *val;
}
#endif