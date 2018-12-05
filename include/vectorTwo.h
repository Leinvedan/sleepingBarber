#ifndef VECTORTWO_H
#define VECTORTWO_H

#include <cstdint>

struct VectorTwo{
	int32_t x,y;
	VectorTwo();
	VectorTwo(int32_t, int32_t);
	VectorTwo(const VectorTwo&);
	const VectorTwo &operator=(const VectorTwo);
	const VectorTwo &operator+(const VectorTwo vt);
	const VectorTwo &operator-(const VectorTwo vt);
};

#endif