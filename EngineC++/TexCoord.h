#pragma once

struct TexCoord
{
public:
	TexCoord();
	TexCoord(float u, float v, float u1, float v1);

	void reduce(int width, int height);
	void setMinU(float u);
	void setMinV(float v);
	void setMaxU(float u);
	void setMaxV(float v);
	float getMinU(int animationId = 0);
	float getMinV(int animationId = 0);
	float getMaxU(int animationId = 0);
	float getMaxV(int animationId = 0);

private:
	float minU, minV, maxU, maxV;
};