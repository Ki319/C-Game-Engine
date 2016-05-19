#pragma once
#include "pch.h"
#include "Color.h"
#include "Draw.h"
#include "OpenGL.h"
#include "Application.h"
#include "TexCoord.h"

struct CharData;
struct Kerning;
class Texture;
class TextureAtlas;
class Font;
class IModel;
class ObjModel;

namespace Engine
{
	std::map<std::string, Texture *> textureMap = std::map<std::string, Texture *>();
	std::map<std::string, IModel *> modelMap = std::map<std::string, IModel *>();
	Texture *currentTexture;

	void loadTextures();
	void debugLoadTextures();
	std::map<std::string, char *> getTextureMap();
	void loadTextureMap(std::map<std::string, char *> textureMap);
	void deleteTextureMap();
	void deleteAtlasTextures();
	void deleteFontTextures();
	void deleteTextures();
	void deleteTexture(std::string texture);
	void loadTexture(std::string texture);
	void loadAtlasTexture(std::string atlasTexture);
	void loadFont(std::string font);
	void bindTexture(const GLuint *textureId);
	bool bindTexture(std::string texture);
	bool bindTexture(std::string texture, std::string subtexture);
	const GLuint *getTextureId(std::string texture);
	Font *getFont(std::string font);
	const GLuint *createTextureId(char * image, int width, int height, bool mipmap);
}

struct CharData
{
	friend class Font;

public:
	CharData();
	TexCoord getTexture();
	Kerning getKerning();
	float getWidth();
	float getHeight();
	float getXOffset();
	float getYOffset();
	float getAdvance();

private:
	TexCoord texture;
	Kerning kerning;
	float width, height, xOffset, yOffset, xadvance;
};

struct Kerning
{
public:
	void add(CharData otherChar, float adjustment);
	float get(CharData otherChar);

private:
	std::map<CharData, float> kernings = std::map<CharData, float>();
};

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

class TextureAtlas : public Texture
{
public:
	TextureAtlas();
	~TextureAtlas();

	char *load(fs::path pathLoc);

	TexCoord getTexture();

	TexCoord getTexture(std::string textureName);
protected:
	std::map<std::string, TexCoord> textureMap = std::map<std::string, TexCoord>();
	TexCoord currentTexture;

};

class Font : public Texture
{
public:
	Font();
	~Font();

	char *load(fs::path pathLoc);

	CharData getCharData(char letter);

	void drawString(std::string whatchars, double x, double y, double z, double pointFont);
	void drawAlignedString(std::string whatchars, double x, double y, double z, double pointFont, int alignment);
	void drawFittedString(std::string whatchars, double x, double y, double z, double width, double height);
	void drawAlignedFittedString(std::string whatchars, double x, double y, double z, int alignment, double width, double height);
	void drawColorString(std::string whatchars, double x, double y, double z, double pointFont, Color rightColor);
	void drawAlignedCString(std::string whatchars, double x, double y, double z, double pointFont, int alignment, Color rightColor);
	void drawAlignedFCString(std::string whatchars, double x, double y, double z, int alignment, double width, double height, Color rightColor);
	double getTextWidth(std::string whatchars);
	double getTextWidth(std::string whatchars, double pointFont);
	double getTextHeight(std::string whatchars);
	double getTextHeight(std::string whatchars, double pointFont);

private:
	std::map<char, CharData> fontBitmap = std::map<char, CharData>();
};

