#include "Texture.h"

Texture::Texture() 
{
	textureId = nullptr;
}

Texture::~Texture()
{
	if(textureId != nullptr)
	{
		glDeleteTextures(1, textureId);

		delete textureId;
	}
}

Image Texture::load(fs::path fileLoc)
{
	Image image = Image();
	readImage(fileLoc, image);

	imageWidth = image.width();
	imageHeight = image.height();
	return image;
}

void Texture::setTextureId(GLuint *tex)
{
	textureId = tex;
}

GLuint *Texture::getTextureId()
{
	return textureId;
}

int Texture::getMipmap()
{
	return currentSettings->getMipmap();
}

GLuint Texture::width()
{
	return imageWidth;
}

GLuint Texture::height()
{
	return imageHeight;
}