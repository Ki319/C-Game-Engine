#include "Texture.h"

CharData::CharData() {}

TexCoord CharData::getTexture()
{
	return texture;
}

Kerning CharData::getKerning()
{
	return kerning;
}

float CharData::getWidth()
{
	return width;
}

float CharData::getHeight()
{
	return height;
}

float CharData::getXOffset()
{
	return xOffset;
}

float CharData::getYOffset()
{
	return yOffset;
}

float CharData::getAdvance()
{
	return xadvance;
}

void Kerning::add(CharData otherChar, float adjustment)
{
	kernings[otherChar] = adjustment;
}

float Kerning::get(CharData otherChar)
{
	return kernings[otherChar];
}

Texture::Texture() {}

Texture::~Texture()
{
	delete textureId;
	delete image;
}

void Texture::setTextureId(const GLuint *texId)
{
	textureId = texId;
}

const GLuint *Texture::getTextureId()
{
	return textureId;
}

void Texture::load(char *image)
{
	this->image = image;
}

char *Texture::getImage()
{
	return image;
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

bool Texture::mipmap()
{
	return false;
}

char *Texture::load(fs::path pathLoc)
{
	char *data;
	return data;
}

TexCoord Texture::getTexture()
{
	return TexCoord(0, 0, 1, 1);
}

Font::Font()
{

}

Font::~Font()
{
	
}

char *Font::load(fs::path pathLoc)
{
	char *data;
	return data;
}

CharData Font::getCharData(char letter)
{
	std::map<char, CharData>::iterator it = fontBitmap.find(letter);
	if (it != fontBitmap.end())
	{
		return it->second;
	}
	CharData data = CharData();
	data.width = -1;
	return data;
}

void Font::drawString(std::string whatchars, double x, double y, double z, double pointFont)
{
	CharData letter;
	int i;
	double width;
	double xOffset;
	double yOffset;
	glStart();
	for (i = 0; i < whatchars.length(); i++)
	{
		letter = getCharData(whatchars.at(i));
		if (letter.width != -1)
		{
			width = letter.getWidth() * pointFont;
			xOffset = letter.getXOffset() * pointFont;
			yOffset = letter.getYOffset() * pointFont;
			if (whatchars.at(i) != ' ')
				rectUV(x + xOffset, y + yOffset, x + width + xOffset, y + letter.getHeight() * pointFont + yOffset, z, letter.getTexture());
			x += letter.getAdvance() * pointFont;
		}
	}
	glEnd();
}

void Font::drawAlignedString(std::string whatchars, double x, double y, double z, double pointFont, int alignment)
{
	switch (alignment)
	{
	case 1:
		x -= getTextWidth(whatchars, pointFont) / 2;
		break;
	case 2:
		x -= getTextWidth(whatchars, pointFont);
		break;
	}
	drawString(whatchars, x, y, z, pointFont);
}

void Font::drawFittedString(std::string whatchars, double x, double y, double z, double width, double height)
{
	drawString(whatchars, x, y, z, fminf(height / getTextHeight(whatchars), width / getTextWidth(whatchars)));
}

void Font::drawAlignedFittedString(std::string whatchars, double x, double y, double z, int alignment, double width, double height)
{
	double pointFont = fminf(height / getTextHeight(whatchars), width / getTextWidth(whatchars));
	switch (alignment)
	{
	case 1:
		x -= getTextWidth(whatchars, pointFont) / 2;
		break;
	case 2:
		x -= getTextWidth(whatchars, pointFont);
		break;
	}
	drawString(whatchars, x, y, z, pointFont);
}

void Font::drawColorString(std::string whatchars, double x, double y, double z, double pointFont, Color rightColor)
{

}

void Font::drawAlignedCString(std::string whatchars, double x, double y, double z, double pointFont, int alignment, Color rightColor)
{
	switch (alignment)
	{
	case 1:
		x -= getTextWidth(whatchars, pointFont) / 2;
		break;
	case 2:
		x -= getTextWidth(whatchars, pointFont);
		break;
	}
	drawColorString(whatchars, x, y, z, pointFont, rightColor);
}

void Font::drawAlignedFCString(std::string whatchars, double x, double y, double z, int alignment, double width, double height, Color rightColor)
{
	double pointFont = fminf(height / getTextHeight(whatchars), width / getTextWidth(whatchars));
	switch (alignment)
	{
	case 1:
		x -= getTextWidth(whatchars, pointFont) / 2;
		break;
	case 2:
		x -= getTextWidth(whatchars, pointFont);
		break;
	}
	drawColorString(whatchars, x, y, z, pointFont, rightColor);
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