#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>

struct cvec_header
{
	size_t len;
};

#define cvec_len(arr) (((struct cvec_header *)(((char *)arr) - sizeof(struct cvec_header)))->len)
#define cvec_free(arr)                                  \
	do                                                   \
	{                                                    \
		free(((char *)arr) - sizeof(struct cvec_header)); \
		arr = 0;                                          \
	} while (0)
#define cvec_push(arr, val)                                                                                    \
	do                                                                                                          \
	{                                                                                                           \
		if (arr == 0)                                                                                            \
		{                                                                                                        \
			arr = malloc(sizeof(struct cvec_header) + sizeof(*arr));                                              \
			((struct cvec_header *)arr)->len = 1;                                                                 \
			arr = (void *)(((char *)arr) + sizeof(struct cvec_header));                                           \
		}                                                                                                        \
		else                                                                                                     \
		{                                                                                                        \
			arr = (void *)(((char *)arr) - sizeof(struct cvec_header));                                           \
			((struct cvec_header *)arr)->len++;                                                                   \
			arr = realloc(arr, sizeof(struct cvec_header) + (sizeof(*arr) * (((struct cvec_header *)arr)->len))); \
			arr = (void *)(((char *)arr) + sizeof(struct cvec_header));                                           \
		}                                                                                                        \
		arr[vec_len(arr) - 1] = val;                                                                             \
	} while (0)

#endif /* CVECTOR_H */