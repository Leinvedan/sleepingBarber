#include "camera.h"

void Camera::getXnY(float& x,float& y){
	mHost->getXnY(x,y);
	x = x - mSizeW/2;
	y = y - mSizeH/2;
}

void Camera::getCenterXnY(float& x,float& y){
	mHost->getXnY(x,y);
}

void Camera::attachTo(Entity* e){
	mHost = e;
}

int32_t Camera::getCameraRatio(){
	return mSizeW/mSizeH;
}

uint32_t Camera::getScale(){
	return mScale;
}

void Camera::setCameraSize(int32_t sizeW,int32_t sizeH){
	mSizeH = sizeH;
	mSizeW = sizeW;
}

void Camera::setScale(uint32_t scale){
	mScale = scale;
}

void Camera::getWnH(float& w, float& h){
	w = mSizeW;
	h = mSizeH;
}

bool Camera::checkVisible(float x,float y){
	float camX,camY;
	getCenterXnY(camX,camY);
	//distance is within 70% of the respective size to be rendered
	//FROM THE CENTER OF THE SCREEN (the normal would be 50%)
	if (((mSizeW*0.7) < abs(x-camX))||((mSizeH*0.7) < abs(y-camY) )){
		return false;
	}
	return true;
}