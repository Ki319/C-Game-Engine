#include "Textures.h"


std::map<std::string, Texture *> textureMap;
Texture *currentTexture;

void engine::genTex(GLuint textureId, GLuint width, GLuint height, GLubyte *data, int numMipmaps)
{
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (numMipmaps > 1)
	{
		glTexStorage2D(GL_TEXTURE_2D, numMipmaps, GL_RGBA8, width, height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

}

GLuint *engine::genTexId(Image image, int numMipmaps)
{
	if (image.imageData != nullptr)
	{
		GLuint *tex;
		glGenTextures(1, tex);

		genTex(*tex, image.width(), image.height(), image.imageData, numMipmaps);

		return tex;
	}
	return nullptr;
}

bool genTexture(Texture *tex, std::string texture, fs::path textureFile)
{
	Image image = tex->load(textureFile);

	if (image.imageData == nullptr)
		return false;

	GLuint *textureId = engine::genTexId(image, std::min<int>(tex->getMipmap(), currentSettings->getMipmap()));

	if (textureId == nullptr)
	{
		return false;
	}

	tex->setTextureId(textureId);

	textureMap[texture] = tex;

	return true;
}

bool loadTexture(Texture *tex, std::string texture, std::string infoFile = "")
{
	if (textureMap.find(texture) != textureMap.end)
		return false;

	std::string texturePath = std::string(texture);

	std::replace(texturePath.begin(), texturePath.end(), ':', '/');

	fs::path textureFile = fs::path(currentSettings->getTexturePath());
	textureFile /= texturePath + ".png";

	if (fs::is_regular_file(textureFile))
	{
		if (infoFile.length() == 0 || fs::is_regular_file(textureFile.replace_extension(infoFile)))
		{
			if (!genTexture(tex, texture, textureFile))
			{
				delete tex;
				return false;
			}
		}
	}
	return true;
}

bool engine::loadTexture(std::string texture)
{
	return loadTexture(new Texture(), texture);
}

bool engine::loadAtlasTexture(std::string atlasTexture)
{
	return loadTexture(new AtlasTexture(), atlasTexture, "info");
}

bool engine::loadFont(std::string font)
{
	return loadTexture(new Font(), font, "font");
}

void engine::deleteTextureMap()
{
	currentTexture = nullptr;

	std::map<std::string, Texture *>::iterator it = textureMap.begin();
	for (; it != textureMap.end(); ++it)
	{
		delete it->second;
		textureMap.erase(it->first);
	}
}

template<typename T>
void engine::deleteTextures()
{
	std::map<std::string, Texture *>::iterator it = textureMap.begin();
	for (; it != textureMap.end(); ++it)
	{
		Texture *texture = it->second;

		if (dynamic_cast<T *>(texture) != nullptr)
		{
			if (currentTexture == texture)
				currentTexture = nullptr;

			delete texture;
			textureMap.erase(it->first);
		}
	}
}

void engine::deleteTexture(std::string texture)
{
	Texture *tex = textureMap[texture];
	if (tex)
	{
		if (currentTexture == tex)
			currentTexture = nullptr;

		delete tex;
		textureMap.erase(texture);
	}
}

bool bindTexture()