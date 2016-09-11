#pragma once

#include <cmath>

struct TexCoord
{
public:
	TexCoord();
	TexCoord(float u, float v, float u1, float v1);
	TexCoord(float data[4], int aniData[2]);

	void reduce(int width, int height);
	void setMinU(float u);
	void setMinV(float v);
	void setMaxU(float u);
	void setMaxV(float v);
	float getMinU(char animationId = 0);
	float getMinV(char animationId = 0);
	float getMaxU(char animationId = 0);
	float getMaxV(char animationId = 0);

private:
	float minU, minV, maxU, maxV;
	char width = 1, height = 1;
};