#include "Texture.h"

Texture::Texture() 
{
	textureId = nullptr;
	image = nullptr;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	if(textureId != nullptr)
	{
		glDeleteTextures(1, textureId);

		delete textureId;
		delete image;
	}
}