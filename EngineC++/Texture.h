#pragma once
#include "pch.h"
#include "Color.h"
#include "Draw.h"
#include "OpenGL.h"
#include "TexCoord.h"
#include "Font.h"
#include "TextureAtlas.h"

using namespace Engine;

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
