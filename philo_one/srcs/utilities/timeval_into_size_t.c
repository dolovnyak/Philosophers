#include "philosophers.h"

inline size_t timeval_to_size_t(struct timeval timeval)
{
	return (timeval.tv_sec * 1000 + (size_t)(timeval.tv_usec * 0.001));
}
