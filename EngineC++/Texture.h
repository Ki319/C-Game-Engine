#pragma once
#include "pch.h"
#include "Application.h"

class Texture;
class TextureAtlas;
class Font;
class IModel;
class ObjModel;

namespace Engine
{
	std::map<std::string, Texture *> textureMap = std::map<std::string, Texture *>();
	std::map<std::string, IModel *> modelMap = std::map<std::string, IModel *>();
	Texture *currentTexture;

	void loadTextures();
	void debugLoadTextures();
	std::map<std::string, char *> getTextureMap();
	void loadTextureMap(std::map<std::string, char *> textureMap);
	void deleteTextureMap();
	void deleteAtlasTextures();
	void deleteFontTextures();
	void deleteTextures();
	void deleteTexture(std::string texture);
	void loadTexture(std::string texture);
	void loadAtlasTexture(std::string atlasTexture);
	void loadFont(std::string font);
	void bindTexture(const GLuint *textureId);
	bool bindTexture(std::string texture);
	bool bindTexture(std::string texture, std::string subtexture);
	const GLuint *getTextureId(std::string texture);
	Font *getFont(std::string font);
	const GLuint *createTextureId(char * image, int width, int height, bool mipmap);
}

struct TexCoords
{
public:
	TexCoords(float u, float v, float u1, float v1);

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

class Texture
{
public:
	Texture();
	~Texture();

	void setTextureId(const GLuint *texId);
	const GLuint *getTextureId();
	void load(char *image);
	char *getImage();
	int getWidth();
	int getHeight();

	bool mipmap();

	virtual char *load(fs::path pathLoc);

	virtual TexCoords getTexture();
protected:
	const GLuint *textureId;
	int width;
	int height;
	char *image = nullptr;
};

class TextureAtlas : public Texture
{
public:
	TexCoords getTexture();
	char *load(fs::path pathLoc);
};

class Font : public Texture
{
public:
	Font();
	~Font();

	char *load(fs::path pathLoc);
};

