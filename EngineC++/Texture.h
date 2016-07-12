#pragma once

#include "pch.h"
#include "Color.h"
#include "Draw.h"
#include "OpenGL.h"

using namespace Engine;

class Texture;
class Font;
class TextureAtlas;

namespace Engine
{
	std::map<std::string, Texture *> textureMap;
	Texture *currentTexture;

	void loadTextures(fs::path texturePath);
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

	virtual TexCoord getTexture();
protected:
	const GLuint *textureId;
	int width;
	int height;
	char *image = nullptr;
};


