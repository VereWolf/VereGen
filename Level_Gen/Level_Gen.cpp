// Level_Gen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Terrain_Gen.h"



int _tmain(int argc, _TCHAR* argv[])
{
	TerrainGen ter;
	ter.LoadHeightPattern("heightPattern.raw");

	ter.LoadImageFile(PIXELSINROW, PIXELSINROW, L"AL01.bmp");

	ter.ErosionGenerate2(PIXELSINROW, PIXELSINROW, 30);
	ter.Addition(0.2f);

	ter.LoadImageFile(PIXELSINROW, PIXELSINROW, L"AL02.bmp");

	ter.ErosionGenerate2(PIXELSINROW, PIXELSINROW, 30);
	ter.Addition(0.3f);

	ter.LoadImageFile(PIXELSINROW, PIXELSINROW, L"AL03.bmp");

	ter.ErosionGenerate2(PIXELSINROW, PIXELSINROW, 30);
	ter.Addition(0.4f);

	ter.LoadImageFile(PIXELSINROW, PIXELSINROW, L"AL04.bmp");

	ter.ErosionGenerate2(PIXELSINROW, PIXELSINROW, 30);
	ter.Addition(0.27f);

	ter.SaveHeightFile(PIXELSINROW, PIXELSINROW, "tam.raw");

	//ter.DivideToTiles(PIXELSINROW, 64);

	UINT a;

	cin >> a;

	return 0;
}

