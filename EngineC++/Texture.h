#pragma once

#include "stdafx.h"
#include "Draw.h"
#include "OpenGL.h"

class Texture
{
public:
	Texture();
	~Texture();

	virtual Image load(fs::path fileLoc);

	void setTextureId(GLuint *tex);
	GLuint *getTextureId();

	virtual int getMipmap();
	GLuint width();
	GLuint height();

protected:
	GLuint *textureId;
	Image image;
};


