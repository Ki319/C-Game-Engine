#include "Texture.h"

TexCoords::TexCoords(float u, float v, float u1, float v1)
{
	minU = u;
	minV = v;
	maxU = u1;
	maxV = v1;
}

void TexCoords::reduce(int width, int height)
{
	minU /= (float)width;
	maxU /= (float)width;
	minV /= (float)height;
	maxV /= (float)height;
}

void TexCoords::setMinU(float u)
{
	minU = u;
}

void TexCoords::setMinV(float v)
{
	minV = v;
}

void TexCoords::setMaxU(float u)
{
	maxU = u;
}

void TexCoords::setMaxV(float v)
{
	maxV = v;
}

float TexCoords::getMinU()
{
	return minU;
}

float TexCoords::getMinV()
{
	return minV;
}

float TexCoords::getMaxU()
{
	return maxU;
}

float TexCoords::getMaxV()
{
	return maxV;
}

float TexCoords::getMinU(int animationID)
{
	return getMinU();
}

float TexCoords::getMinV(int animationID)
{
	return getMinV();
}

float TexCoords::getMaxU(int animationID)
{
	return getMaxU();
}

float TexCoords::getMaxV(int animationID)
{
	return getMaxV();
}

void Texture::setTextureId(const GLuint *texId)
{
	textureId = texId;
}

const GLuint *Texture::getTextureId()
{
	return textureId;
}

void Engine::loadTextures()
{
	fs::path texturePath = currentSettings->getTexturePath();

	fs::directory_iterator end_itr;
	std::string font("font:");
	std::string noload("$");
	bool load = true;

	Texture *texture;

	for (fs::directory_iterator itr(texturePath); itr != end_itr; ++itr)
	{
		fs::path iteratedPath = itr->path();
		if (fs::is_regular_file(iteratedPath))
		{
			std::string filename = iteratedPath.stem().string();
			load = filename.compare(0, noload.length(), noload) != 0;

			if (load)
			{
				if (filename.compare(1, font.length(), font) == 0)
				{
					texture = new Font();
				}
				else
				{
					fs::path infoPath = iteratedPath.replace_extension(".info");
					if (fs::is_regular_file(infoPath))
					{
						texture = new TextureAtlas();
					}
					else
					{
						texture = new Texture();
					}
				}
				textureMap[filename.substr(1)] = texture;
				texture->setTextureId(createTextureId(texture->load(iteratedPath), texture->getWidth(), texture->getHeight(), texture->mipmap()));
			}
		}
	}
}

void Engine::debugLoadTextures()
{

}

std::map<std::string, char *> Engine::getTextureMap()
{
	std::map<std::string, char *> textures;
	std::map<std::string, Texture *>::iterator it = textureMap.begin();
	for (; it != textureMap.end(); ++it)
	{
		char* buffer = new char[strlen(it->second->getImage()) + 1];
		strcpy(buffer, it->second->getImage());
		textures[it->first] = buffer;
		bindTexture(0);
		glDeleteTextures(1, it->second->getTextureId());
	}
	return textures;
}

void Engine::loadTextureMap(std::map<std::string, char *> map)
{
	std::map<std::string, char *>::iterator it = map.begin();
	for (; it != map.end(); ++it)
	{
		Texture *texture = textureMap[it->first];
		int width = 0;
		int height = 0;

		texture->load(it->second);
		bindTexture(texture->getTextureId());
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, it->second);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, it->second);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}

void Engine::deleteTextureMap()
{
	std::map<std::string, Texture *>::iterator it = textureMap.begin();
	for (; it != textureMap.end(); ++it)
	{
		Texture *texture = it->second;
		glDeleteTextures(1, texture->getTextureId());
		textureMap.erase(it->first);
		delete texture;
	}
}

template<typename T>
void delTextures()
{
	std::map<std::string, Texture *>::iterator it = Engine::textureMap.begin();
	for (; it != Engine::textureMap.end(); ++it)
	{
		Texture *texture = it->second;
		if (dynamic_cast<const T*>(texture) != nullptr)
		{
			Engine::deleteTexture(texture->getTextureId());
			Engine::textureMap.erase(it->first);
			delete texture;
		}
	}
}

void Engine::deleteAtlasTextures()
{
	delTextures<TextureAtlas>();
}

void Engine::deleteFontTextures()
{
	delTextures<Font>();
}

void Engine::deleteTextures()
{
	delTextures<Texture>();
}

void Engine::deleteTexture(std::string texture)
{
	if (textureMap[texture])
	{
		delete textureMap[texture];
		textureMap.erase(texture);
	}
}

template<typename T>
void loadTex(std::string texture, std::string secondCond = "")
{
	std::string texturePath = std::string(texture);
	std::replace(texturePath.begin(), texturePath.end(), ':', '/');
	fs::path textureFile = fs::path(currentSettings->getTexturePath());
	textureFile /= texturePath + ".png";
	if (fs::is_regular_file(textureFile))
	{
		if (secondCond.length() == 0 || fs::is_regular_file(textureFile.replace_extension(secondCond)))
		{
			if (!textureMap[texture])
			{
				T *tex = new T();
				tex->setTextureId(Engine::createTextureId(tex->load(textureFile), tex->getWidth(), tex->getHeight(), tex->mipmap()));
				Engine::textureMap[texture] = tex;
			}
		}
	}
}

void Engine::loadTexture(std::string texture)
{
	loadTex<Texture>(texture);
}

void Engine::loadAtlasTexture(std::string texture)
{
	loadTex<TextureAtlas>(texture, ".info");
}

void Engine::loadFont(std::string font)
{
	loadTex<Font>(font, ".font");
}

void Engine::bindTexture(const GLuint *textureId)
{
	currentTexture = nullptr;
	glBindTexture(GL_TEXTURE_2D, *textureId);
}

bool Engine::bindTexture(std::string texture)
{
	Texture *tex = textureMap[texture];
	if (tex != nullptr && tex != currentTexture)
	{
		glBindTexture(GL_TEXTURE_2D, *tex->getTextureId());
		currentTexture = tex;
		return true;
	}
	return false;
}

bool Engine::bindTexture(std::string texture, std::string subtexture)
{
	Texture *tex = textureMap[texture];
	if (tex != nullptr && tex != currentTexture && instanceof<TextureAtlas, Texture>(tex))
	{
		glBindTexture(GL_TEXTURE_2D, *tex->getTextureId());
		currentTexture = tex;
		return true;
	}
	return false;
}

const GLuint *Engine::getTextureId(std::string texture)
{
	if (textureMap[texture])
		return textureMap[texture]->getTextureId();
	return nullptr;
}

Font *Engine::getFont(std::string font)
{
	font = "font:" + font;
	if (textureMap[font])
		return (Font *)textureMap[font];
	return nullptr;
}

const GLuint *Engine::createTextureId(char *image, int width, int height, bool mipmap)
{
	if (image != nullptr)
	{
		GLuint *tex;
		glGenTextures(1, tex);

		const GLuint *texture = tex;

		bindTexture(texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		return texture;
	}
	return nullptr;
}