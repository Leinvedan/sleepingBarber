#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"

class Camera{
private:
	Entity* mHost;
	uint32_t mSizeW;
	uint32_t mSizeH;
	uint32_t mScale = 1; //temp at 1
	float mOffsetX;
	float mOffsetY;
public:
	void getXnY(float&,float&);
	void getCenterXnY(float&,float&);
	void getWnH(float&, float&);
	void attachTo(Entity*);
	int32_t getCameraRatio();
	uint32_t getScale();
	void setCameraSize(int32_t,int32_t);
	void setScale(uint32_t);
	bool checkVisible(float,float);
};






#endif