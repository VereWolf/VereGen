
#ifndef TERRAIN_GEN
#define TERRAIN_GEN

#include "stdafx.h"

#define PIXELSINROW 2048
#define PIXELSINROWINCELL 12
#define MAXSPACE 16

struct Height
{
	Height()
	{
		height1 = -9999.0f;
		height2 = -9999.0f;
		canChange = true;
	}

	float height1;
	float height2;
	int sourceCoord[2];
	bool canChange;
};

struct TerrainType
{
	float maxHeight;
	float minHeight;
};

class TerrainGen
{
public:
	TerrainGen();
	~TerrainGen(){};


	void ErosionGenerate2(int itsWidthOfImage, int itsHeightOfImage, int itsLenghtOfStamp);
	void DivideToTiles(int itsWidthOfMap, int itsWidthOfTile);
	bool LoadImageFile(ULONG height, ULONG width, WCHAR *nameFile);
	void Addition(float index);
	bool SaveHeightFile(ULONG height, ULONG width, std::string nameFile);
	bool LoadHeightPattern(string nameFile);
	

private:
	UINT a;
	std::vector<std::vector<float>> mStamp;
	std::vector<UINT> mGeologyMap;
	std::vector<float> mHeightMap;
	std::vector<float> mHeightMap2;
	std::vector<Height> mHeightMap3;
	std::vector<float> mHeightPattern;
	std::vector<UINT> mNoiseMap;
	std::vector<TerrainType> mTerrainType;
	std::ofstream openMapFile;
	std::ofstream openAssistFile;
};

#endif /*TERRAIN_GEN*/