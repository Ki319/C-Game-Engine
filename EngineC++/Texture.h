#pragma once
#include "pch.h"
#define loadTextures Texture::lt()
#define debugLoadTextures Texture::dlt()
#define getTextureMap Texture::gtd()
#define loadTextureMap(textureData) Texture::ltd(textureData)
#define clearAllTextures Texture::cat()
#define clearStitchedTextures Texture::cst()
#define clearFontTextures Texture::cft()
#define clearVirtualTextures Texture::cvt()
#define clearTexture(textureName) Texture::ct(textureName)
#define loadStitchedTexture(textureName) Texture::lst(textureName)
#define loadFont(fontName) Texture::lf(fontName)
#define loadModel(modelName) Texture::lm(modelName)
#define glBindTexture(textureId)

class ITexture;
struct Model;

struct Texture
{
public:
	Texture();
	~Texture();

	static void lt();
private:
	static const std::map<std::string, ITexture> textureMap;
	static const std::map<std::string, Model> modelMap;
	static ITexture currentTexture;
};

class ITexture
{

};


