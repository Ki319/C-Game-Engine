#pragma once

#include "Texture.h"

class AtlasTexture : public Texture
{
public:
	AtlasTexture();
	~AtlasTexture();

protected:
	std::map<std::string, TexCoord> textureMap = std::map<std::string, TexCoord>();
	TexCoord currentTexture;

};