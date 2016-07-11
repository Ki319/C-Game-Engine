#pragma once
#include "Texture.h"
#include "TextureManager.h"

class TextureAtlas : public Texture
{
public:
	TextureAtlas();
	~TextureAtlas();

	char *load(fs::path pathLoc);

	TexCoord getTexture();

	TexCoord getTexture(std::string textureName);
protected:
	std::map<std::string, TexCoord> textureMap = std::map<std::string, TexCoord>();
	TexCoord currentTexture;

};