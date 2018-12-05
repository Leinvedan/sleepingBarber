
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vectorTwo.h"


class SpriteComponent{
private:
	bool mAnimated;
	SDL_Texture* mSpriteSheet;
	uint32_t mTotalAnimationFrames;
	SDL_Rect mSheetRect; //sheet total size rect
	SDL_Rect mSpriteRect;
	float mDefaultSpeedInMS;
	float mSpeedInMS;
	uint32_t mCurrentFrame;
	double mLastUpdateTime;
	VectorTwo mMatrixBounds;
	uint32_t mFirstFrameColumn;
	
public:
	SpriteComponent();
	//non animated constructor
	SpriteComponent(SDL_Texture*);
	SDL_Rect getRect();
	SDL_Rect getNextFrameRect();
	SDL_Texture* getTexture();
	void getWnH(int&,int&);
	void resetCurrentFrame();
	void copy(SpriteComponent);
};



#endif