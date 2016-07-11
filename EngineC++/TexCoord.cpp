
#include "TexCoord.h"

TexCoord::TexCoord() {}

TexCoord::TexCoord(float u, float v, float u1, float v1)
{
	minU = u;
	minV = v;
	maxU = u1;
	maxV = v1;
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

float TexCoord::getMinU(int animationID)
{
	return minU;
}

float TexCoord::getMinV(int animationID)
{
	return minV;
}

float TexCoord::getMaxU(int animationID)
{
	return maxU;
}

float TexCoord::getMaxV(int animationID)
{
	return maxV;
}