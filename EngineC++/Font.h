#pragma once
#include "pch.h"
#include "Texture.h"
#include "TextureManager.h"

struct CharData;
struct Kerning;

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