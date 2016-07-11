#pragma once
#include "pch.h"
#include "Texture.h"

namespace Engine
{
	std::map<std::string, Texture *> textureMap = std::map<std::string, Texture *>();
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
