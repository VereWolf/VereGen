#include "stdafx.h"
#include "Terrain_Gen.h"

TerrainGen::TerrainGen()
{
	//srand(17984);
	mGeologyMap.resize(pow(PIXELSINROW, 2.0f), 0);
	mHeightMap.resize(pow(PIXELSINROW, 2.0f), -9999.0f);
	mHeightMap2.resize(pow(PIXELSINROW, 2.0f), 0.0f);
	mHeightMap3.resize(pow(PIXELSINROW, 2.0f));
	mHeightPattern.resize(pow(PIXELSINROW, 2.0f), 0.0f);
};

void TerrainGen::ErosionGenerate2(int itsWidthOfImage, int itsHeightOfImage, int itsLenghtOfStamp)
{
	float dist1;
	float dist2;

	float index[3];
	float height[4];

	UINT geologyType;

	srand(17431);

	for (int y = 0; y < itsHeightOfImage; ++y)
	{
		for (int x = 0; x < itsWidthOfImage; ++x)
		{
			mHeightMap3.at(y * itsWidthOfImage + x).height1 = -9999.0f;
			mHeightMap3.at(y * itsWidthOfImage + x).height2 = -9999.0f;
			mHeightMap3.at(y * itsWidthOfImage + x).sourceCoord[0] = y;
			mHeightMap3.at(y * itsWidthOfImage + x).sourceCoord[1] = x;

			mHeightMap3.at(y * itsWidthOfImage + x).canChange = false;
		}
	}

	mNoiseMap.resize(mGeologyMap.size());

	for (int i = 0; i < mNoiseMap.size(); i++)
	{
		mNoiseMap.at(i) = rand() % 8;
	}


	for (int i = 0; i <= itsLenghtOfStamp; ++i)
	{
		for (int y = 1; y < itsHeightOfImage - 1; ++y)
		{
			for (int x = 1; x < itsWidthOfImage - 1; ++x)
			{
				geologyType = mGeologyMap.at(y * itsWidthOfImage + x);

				switch (geologyType)
				{
				case 0:
					index[0] = 1.0f;
					index[1] = 1.0f;

					height[0] = -1.0f;
					height[1] = -1.0f;
					break;

				case 1:
					index[0] = 0.80f;
					index[1] = 0.85f;

					height[0] = -0.3f;
					height[1] = -0.2f;
					break;
				case 2:
					index[0] = 0.95f;
					index[1] = 1.0f;

					height[0] = 0.2f;
					height[1] = 0.35f;
					break;
				case 3:
					index[0] = 0.85f;
					index[1] = 0.9f;

					height[0] = 0.2f;
					height[1] = 0.35f;
					break;
				case 4:
					index[0] = 0.70f;
					index[1] = 0.45f;

					height[0] = 0.5f;
					height[1] = 0.7f;
					break;
				case 5:
					index[0] = 0.65f;
					index[1] = 0.35f;

					height[0] = 0.8f;
					height[1] = 1.0f;
					break;

				default:
					break;
				}

				if (i == 0)
				{
					mHeightMap3.at(y * itsWidthOfImage + x).height1 = mHeightPattern.at(y * itsWidthOfImage + x) * height[0];
					mHeightMap3.at(y * itsWidthOfImage + x).height2 = mHeightMap3.at(y * itsWidthOfImage + x).height1;

					/*for (int n = -1; n <= 1; ++n)
					{
					for (int m = -1; m <= 1; ++m)
					{
					if (mGeologyMap.at(y * itsWidthOfImage + x) != mGeologyMap.at((y + n) * itsWidthOfImage + x + m));
					{
					mHeightMap3.at(y * itsWidthOfImage + x).canChange = true;
					}
					}
					}*/
				}

				if (i != 0/* && mHeightMap3.at(y * itsWidthOfImage + x).canChange == true*/)
				{
					index[2] = (float)mNoiseMap.at(y * itsWidthOfImage + x) / 7.0f;
					index[2] = index[0] + index[2] * (index[1] - index[0]);


					for (int n = -1; n <= 1; ++n)
					{
						for (int m = -1; m <= 1; ++m)
						{
							if (n != 0 && m != 0)
							{
								dist1 = pow(pow(float(mHeightMap3.at((y + n) * itsWidthOfImage + x + m).sourceCoord[0]) - y - n, 2.0f)
									+ pow(float(mHeightMap3.at((y + n) *itsWidthOfImage + (x + m)).sourceCoord[1]) - x - m, 2.0f), 0.5f) / float(itsLenghtOfStamp);

								dist2 = pow(pow(float(mHeightMap3.at((y + n) * itsWidthOfImage + x + m).sourceCoord[0]) - y, 2.0f)
									+ pow(float(mHeightMap3.at((y + n) *itsWidthOfImage + (x + m)).sourceCoord[1]) - x, 2.0f), 0.5f) / float(itsLenghtOfStamp);
								dist2 = dist2 + (1.0f - index[2]) * (dist2*dist2 - dist2);

								height[2] = abs(dist1 + (1.0f - index[2]) * (dist1*dist1 - dist1) - dist2);
								height[3] = (float)mNoiseMap.at(y * itsWidthOfImage + x) / 7.0f;
								height[3] = height[0] + height[3] * (height[1] - height[0]);
								height[3] *= mHeightPattern.at(y * itsWidthOfImage + x);
								height[3] *= height[2];
								height[2] = abs(mHeightMap3.at((y + n) * itsWidthOfImage + x + m).height1);
								height[3] += height[2];

								if ((mHeightMap3.at(y * itsWidthOfImage + x).height2 == -9999.0f ||
									mHeightMap3.at(y * itsWidthOfImage + x).height2 > height[3]) && mHeightMap3.at((y + n) * itsWidthOfImage + x + m).height1 != -9999.0f)
								{
									mHeightMap3.at(y * itsWidthOfImage + x).height2 = height[3];
									mHeightMap3.at(y * itsWidthOfImage + x).sourceCoord[0] = mHeightMap3.at((y + n) * itsWidthOfImage + x + m).sourceCoord[0];
									mHeightMap3.at(y * itsWidthOfImage + x).sourceCoord[1] = mHeightMap3.at((y + n) * itsWidthOfImage + x + m).sourceCoord[1];
								}

							}
						}
					}
				}
			}
		}
		for (int y = 0; y < itsHeightOfImage; ++y)
		{
			for (int x = 0; x < itsHeightOfImage; ++x)
			{
				mHeightMap3.at(y * itsWidthOfImage + x).height1 = mHeightMap3.at(y * itsWidthOfImage + x).height2;
			}

		}
	}
}

void TerrainGen::DivideToTiles(int itsWidthOfMap, int itsWidthOfTile)
{
	int itsAbsWidth = itsWidthOfMap + itsWidthOfTile;

	mHeightMap.resize(pow(itsAbsWidth, 2.0f), 0.0f);

	for (int y = 0; y < itsWidthOfMap; ++y)
	{
		for (int x = 0; x < itsWidthOfMap; ++x)
		{
			mHeightMap.at((y + itsWidthOfTile / 2) * itsAbsWidth + x + itsWidthOfTile / 2) = mHeightMap2.at(y * itsWidthOfMap + x);
		}
	}

	mHeightMap2.resize(pow(2 * itsWidthOfTile, 2.0f), 0.0f);

	int coord[] = { 0, 0 };

	for (int y = itsWidthOfTile / 2; y < (itsWidthOfMap + itsWidthOfTile / 2); y += itsWidthOfTile)
	{
		for (int x = itsWidthOfTile / 2; x < (itsWidthOfMap + itsWidthOfTile / 2); x += itsWidthOfTile)
		{
			for (int y2 = 0; y2 < (2 * itsWidthOfTile); ++y2)
			{
				for (int x2 = 0; x2 < (2 * itsWidthOfTile); ++x2)
				{
					mHeightMap2.at(2 * y2 * itsWidthOfTile + x2) = mHeightMap.at((y + y2 - itsWidthOfTile / 2) * itsAbsWidth + x + x2 - itsWidthOfTile / 2);
				}
			}

			std::string rawFile = ".raw";
			std::string file = "NE";
			std::string s;
			s = (char)((int)'0' + coord[0] % 10);
			file.insert(2, s);
			//assistFile.insert(2, s);
			s = (char)((int)'0' + (coord[0] % 100) / 10);
			file.insert(2, s);
			//assistFile.insert(2, s);
			s = (char)((int)'0' + (coord[0] % 1000) / 100);
			file.insert(2, s);
			//assistFile.insert(2, s);
			s = (char)((int)'0' + (coord[0] % 10000) / 1000);
			file.insert(2, s);

			s = (char)((int)'0' + coord[1] % 10);
			file.insert(1, s);
			//assistFile.insert(1, s);
			s = (char)((int)'0' + (coord[1] % 100) / 10);
			file.insert(1, s);
			//assistFile.insert(1, s);
			s = (char)((int)'0' + (coord[1] % 1000) / 100);
			file.insert(1, s);
			//assistFile.insert(1, s);
			s = (char)((int)'0' + (coord[1] % 10000) / 1000);
			file.insert(1, s);

			file.insert(0, "../Debug/LevelRAW/");
			rawFile.insert(0, file);

			SaveHeightFile(2 * itsWidthOfTile, 2 * itsWidthOfTile, rawFile);

			++coord[1];
		}
		++coord[1] = 0;
		++coord[0];
	}

}

bool TerrainGen::LoadImageFile(ULONG height, ULONG width, WCHAR *nameFile)
{

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	Color color;
	Bitmap *bitmap = new Bitmap(nameFile);
	if (!bitmap)
		return 0;

	mGeologyMap.resize(height*width);

	srand(179611);

	for (ULONG i = 0; i < height; ++i)
	{
		for (ULONG j = 0; j < width; ++j)
		{
			bitmap->GetPixel(j, i, &color);
			mGeologyMap.at(i*width + j) = color.GetR();
		}
	}

	delete bitmap;

	return true;
}

void TerrainGen::Addition(float index)
{
	for (UINT i = 0; i < mHeightMap3.size(); i++)
	{
		mHeightMap2.at(i) += mHeightMap3.at(i).height1 * index;
	}
}

bool TerrainGen::SaveHeightFile(ULONG height, ULONG width, std::string nameFile)
{
	cout << endl << "Begin Save File " << "\"" << nameFile << "\"" << "." << endl;
	float number;
	ofstream outImageFile(nameFile, ios::binary);

	if (!outImageFile)
	{
		cout << endl << "Unable to open." << endl;
		return false;
	}

	for (ULONG i = 0; i < mHeightMap2.size(); i++)
	{
		if (mHeightMap2.at(i) < 0.0f/* || mHeightMap2.at(i) > 8000.0f*/)
		{
			mHeightMap2.at(i) = 0.0f;
			number = 0.0f;
		}

		number = mHeightMap2.at(i);

		outImageFile.write((char*)&number, 4);
	}
	outImageFile.close();
	cout << endl << "Complete Save File: " << 100 << " %" << endl;
	return true;
}

bool TerrainGen::LoadHeightPattern(string nameFile)
{
	std::cout << std::endl << "Begin Load File " << std::endl;
	float number;
	std::ifstream inImageFile(nameFile, std::ios::binary);

	if (!inImageFile)
	{
		std::cout << std::endl << "Unable to open." << std::endl;
		return false;
	}

	for (long j = 0; j < PIXELSINROW; j++)
	{
		for (long i = 0; i < PIXELSINROW; i++)
		{
			number = 0;
			inImageFile.read((char*)&number, 4);
			mHeightPattern.at(j * PIXELSINROW + i) = number;
		}
	}
	inImageFile;
	std::cout << endl << "Complete Load File: " << 100 << " %" << endl;
	return true;
}