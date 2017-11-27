#ifndef IFJ_UTILS_H
#define IFJ_UTILS_H

#define NEW(var) \
	((var) = malloc(sizeof(*(var))))

#define NEWC(c, var) \
	((var) = calloc((c), sizeof(*(var))))

#define DEL(var) \
	do { \
		free(var); \
		var = NULL; \
	} while (0)

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#endif
