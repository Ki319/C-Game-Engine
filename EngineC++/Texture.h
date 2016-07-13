#pragma once

#include "pch.h"
#include "Color.h"
#include "Draw.h"
#include "OpenGL.h"
#include "IOUtil.h"

class Texture
{
public:
	Texture();
	~Texture();

	GLubyte *load(std::string filename, int &width, int &height, bool &hasAlpha);

	void setTextureId(GLuint *tex);
	GLuint *getTextureId();

	int getMipmap();

protected:
	GLuint *textureId;
	GLubyte *image;
	int width;
	int height;
};


