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
	float getMinU();
	float getMinV();
	float getMaxU();
	float getMaxV();
	float getMinU(int animationId);
	float getMinV(int animationId);
	float getMaxU(int animationId);
	float getMaxV(int animationId);

private:
	float minU, minV, maxU, maxV;
};