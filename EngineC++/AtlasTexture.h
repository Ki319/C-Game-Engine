#pragma once

#include "Texture.h"

class AtlasTexture : public Texture
{
public:
	Image load(fs::path fileLoc);
	bool bind(std::string subtexture);

protected:
	std::map<std::string, TexCoord> textures;
	TexCoord currentTexture;

};