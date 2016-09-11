
#include "TexCoord.h"

TexCoord::TexCoord() {}

TexCoord::TexCoord(float u, float v, float u1, float v1)
{
	minU = u;
	minV = v;
	maxU = u1;
	maxV = v1;
}

TexCoord::TexCoord(float data[4], int aniData[2])
{
	minU = data[0];
	minV = data[1];
	maxU = data[2];
	maxV = data[3];
	width = aniData[0];
	height = aniData[1];
}

void TexCoord::reduce(int width, int height)
{
	minU /= (float)width;
	maxU /= (float)width;
	minV /= (float)height;
	maxV /= (float)height;
}

void TexCoord::setMinU(float u)
{
	minU = u;
}

void TexCoord::setMinV(float v)
{
	minV = v;
}

void TexCoord::setMaxU(float u)
{
	maxU = u;
}

void TexCoord::setMaxV(float v)
{
	maxV = v;
}

float TexCoord::getMinU(char animationID)
{
	if(animationID == 0)
		return minU;
	return ((maxU - minU) / width * (animationID % width));
}

float TexCoord::getMinV(char animationID)
{
	if(animationID == 0)
		return minV;
	return ((maxV - minV) / height * (animationID / width));
}

float TexCoord::getMaxU(char animationID)
{
	if(animationID == 0)
		return maxU;
	return ((maxU - minU) / width * ((animationID % width) + 1));
}

float TexCoord::getMaxV(char animationID)
{
	if(animationID == 0)
		return maxV;
	return ((maxV - minV) / height * ((animationID / width) + 1));
}