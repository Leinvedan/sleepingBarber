
#include "vectorTwo.h"

VectorTwo::VectorTwo(){
	x = 0;
	y = 0;
}
VectorTwo::VectorTwo(int32_t newX, int32_t newY){
	x = newX;
	y = newY;
}
VectorTwo::VectorTwo(const VectorTwo& vt){
	x = vt.x;
	y = vt.y;
}
const VectorTwo &VectorTwo::operator=(const VectorTwo vt){
	x = vt.x;
	y = vt.y;
}

const VectorTwo &VectorTwo::operator+(const VectorTwo vt){
	x +=vt.x;
	y +=vt.y;
}

const VectorTwo &VectorTwo::operator-(const VectorTwo vt){
	x -=vt.x;
	y -=vt.y;
}
