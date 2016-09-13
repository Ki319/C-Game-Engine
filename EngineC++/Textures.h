#pragma once
#include "stdafx.h"
#include "Texture.h"
#include "Font.h"
#include "AtlasTexture.h"

namespace engine
{
	void genTex(GLuint textureId, GLuint width, GLuint height, GLubyte *data, int numMipmaps);
	GLuint *genTexId(Image image, int numMipmaps);

	bool loadTexture(std::string texture);
	bool loadAtlasTexture(std::string atlasTexture);
	bool loadFont(std::string font);

	void deleteTextureMap();

	template<typename T>
	void deleteTextures();

	void deleteTexture(std::string texture);

	bool bindTexture(std::string texture);
	bool bindTexture(std::string texture, std::string subtexture);
	bool bindTexture(std::string texture, int coords);

	Font * getFont(std::string font);
	Font * bindFont(std::string font);
	void bindFont(Font * font);

}