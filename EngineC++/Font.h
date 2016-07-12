#pragma once

#include "pch.h"
#include "Texture.h"

struct CharData;
struct Kerning;

class Font : public Texture
{
public:
	Font() {}
	~Font() {}

	char *load(fs::path pathLoc);

	CharData getCharData(char letter);

	void drawString(std::string whatchars, double x, double y, double z, float pointFont);
	void drawAlignedString(std::string whatchars, double x, double y, double z, float pointFont, int alignment);
	void drawFittedString(std::string whatchars, double x, double y, double z, double width, double height);
	void drawAlignedFittedString(std::string whatchars, double x, double y, double z, int alignment, double width, double height);
	void drawColorString(std::string whatchars, double x, double y, double z, float pointFont, Color rightColor);
	void drawAlignedCString(std::string whatchars, double x, double y, double z, float pointFont, int alignment, Color rightColor);
	void drawAlignedFCString(std::string whatchars, double x, double y, double z, int alignment, double width, double height, Color rightColor);
	float getTextWidth(std::string whatchars);
	float getTextWidth(std::string whatchars, float pointFont);
	float getTextHeight(std::string whatchars);
	float getTextHeight(std::string whatchars, float pointFont);

private:
	std::map<char, CharData> fontBitmap = std::map<char, CharData>();
};

struct CharData
{
	friend class Font;

public:
	CharData();

	TexCoord getTexture();

	void add(char otherChar, float adjustment);
	float get(char otherChar);

	float getWidth();
	float getHeight();
	float getXOffset();
	float getYOffset();
	float getAdvance();

private:
	TexCoord texture;
	std::map<char, float> kernings;
	float width, height, xOffset, yOffset, xadvance;
};