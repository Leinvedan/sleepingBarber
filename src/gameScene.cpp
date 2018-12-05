
#include "gameScene.h"


GameScene::GameScene(std::string filePath){
	std::ifstream iFile;
	iFile.open(filePath);
	if (iFile.is_open()){
		//parsing...
		iFile >> mTilesLine >> mTilesColumn >> mTileVariants; //lines and columns
		iFile >> mTileW >> mTileH;
		mTotalTiles = mTilesLine*mTilesColumn;
		//initialize tile variants paths
		mTilePaths.clear();
		mTilePaths.resize(mTileVariants);
		//get the paths
		for (int i = 0; i < mTileVariants; ++i){
			int index;
			std::string tilePath;
			iFile >> index >> tilePath;
			mTilePaths[index] = tilePath;
		}

		//Initialize map array
		mMap.resize(mTilesLine);
		for (int i = 0; i < mMap.size(); ++i){
			mMap[i].resize(mTilesColumn);
		}
		
		//read the tiles
		for (int i = 0; i < mTilesLine; ++i){
			for (int j = 0; j < mTilesColumn; ++j){
				iFile >> mMap[i][j];
			}
		}
		iFile.close();
	}
	else{
		std::cout << "Error: Level not found :" << filePath << std::endl;
	}
}


uint32_t GameScene::getTotalLineTiles(){
	return mTilesLine;
}
uint32_t GameScene::getTotalColumnTiles(){
	return mTilesColumn;
}
uint32_t GameScene::getTotalTileVariants(){
	return mTileVariants;
}
uint32_t GameScene::getTotalTiles(){
	return mTotalTiles;
}
std::string GameScene::getTileTexFilePath(uint32_t index){
	return mTilePaths[index];
}
uint32_t GameScene::getTileReferenceFromMap(uint32_t x,uint32_t y){
	return mMap[x][y];
}

void GameScene::getTilesWnH(uint32_t& w,uint32_t& h){
	w = mTileH;
	h = mTileW;
}