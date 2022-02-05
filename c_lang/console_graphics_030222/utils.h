#ifndef UTILS_H
#define UTILS_H

#define MIN(a, b) ({ __typeof__(a) _a=(a); \
									 __typeof__(b) _b=(b); \
										_a < _b ? _a : _b; })
#define MAX(a, b) ({ __typeof__(a) _a=(a); \
									 __typeof__(b) _b=(b); \
										_a > _b ? _a : _b; })
#define TRIM(a, b, c) ({MIN(MAX(a, b), c);})

#define ABS(a) ({__typeof__(a) _a=(a);\
								 _a<0?-_a:a;})

void i_swap(void *a, void *b);

#endif
