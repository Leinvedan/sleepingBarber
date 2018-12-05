#include "spriteComponent.h"
#include "gameEngine.h"

SpriteComponent::SpriteComponent(){}
//SpriteComponent(tex)
SpriteComponent::SpriteComponent(SDL_Texture* ss){
	mSpriteSheet = ss;
	mAnimated = false;
	mLastUpdateTime = GameEngine::getCurrentTime();
	SDL_QueryTexture(ss,NULL,NULL,&mSheetRect.w,&mSheetRect.h);
	mSpriteRect.x = 0;
	mSpriteRect.y = 0;
	mSpriteRect.w = mSheetRect.w;
	mSpriteRect.h = mSheetRect.h;
}

SDL_Rect SpriteComponent::getNextFrameRect(){
	SDL_Rect target = mSpriteRect;
	if (mAnimated){
		//update X
		target.x = target.x + (mCurrentFrame * mSpriteRect.w); //update the position that will be rendered
		
		//update Y and fix X
		int nFrame = mFirstFrameColumn + mCurrentFrame;
		if (nFrame > mMatrixBounds.y){ //if the frames has reached a newline
			int yCurrentLine = (nFrame/mMatrixBounds.y);
			target.y += yCurrentLine*mSpriteRect.h; //update the line
			//fixing the x(column) back to the first frame of the next line
			//the x is higher than the matrixBounds, this removes the difference
			target.x -= (yCurrentLine * mMatrixBounds.y * mSpriteRect.w); 

		}

		//Check if speed has reached, if true, update the frame to the next
		double currentTime = GameEngine::getCurrentTime();
		if (currentTime - mLastUpdateTime >= mSpeedInMS){
			mCurrentFrame = (mCurrentFrame + 1) % mTotalAnimationFrames; //update counter
			mLastUpdateTime = GameEngine::getCurrentTime();
		}
	}
	return target;
}

SDL_Texture* SpriteComponent::getTexture(){
	return mSpriteSheet;
}

SDL_Rect SpriteComponent::getRect(){
	return mSpriteRect;
}

void SpriteComponent::getWnH(int& w,int& h){
	w = mSpriteRect.w;
	h = mSpriteRect.h;
}

void SpriteComponent::resetCurrentFrame(){
	//used when changing animations
	mCurrentFrame = 0;
}



