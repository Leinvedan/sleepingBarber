#ifndef GAMESSCENE_H
#define GAMESSCENE_H

#include <fstream>
#include <vector>
#include <iostream>

class GameScene{
private:
	uint32_t mTilesColumn;
	uint32_t mTilesLine;
	uint32_t mTileVariants;
	uint32_t mTotalTiles;
	std::vector<std::string> mTilePaths;
	std::vector< std::vector<uint32_t> > mMap;
	uint32_t mTileW,mTileH;
public:
	GameScene(std::string);
	uint32_t getTotalLineTiles();
	uint32_t getTotalColumnTiles();
	uint32_t getTotalTileVariants();
	uint32_t getTotalTiles();
	std::string getTileTexFilePath(uint32_t);
	uint32_t getTileReferenceFromMap(uint32_t,uint32_t);
	void getTilesWnH(uint32_t&,uint32_t&);
};


#endif