#pragma once

#include "pch.h"
#include "Texture.h"

//structure containing each letters individual data
struct CharData;

class Font : public Texture
{
public:
	//not sure if either of these are required.
	Font() {}
	~Font() {}

	//implemented from it's parent, meant to read the font file for character information.
	char *load(fs::path pathLoc);

	//receive character data based on its char value.
	CharData getCharData(char letter);

	//draw a regular string
	void drawString(std::string whatchars, double x, double y, double z, float pointFont);

	//draw a string aligned to either left (0), center (1), or right (2).
	void drawAlignedString(std::string whatchars, double x, double y, double z, float pointFont, int alignment);
	
	//draw a string bounded to a width and height.
	void drawFittedString(std::string whatchars, double x, double y, double z, double width, double height);

	//draw string aligned to either left (0), center (1), or right (2) and bounded to a width and height.
	void drawAlignedFittedString(std::string whatchars, double x, double y, double z, int alignment, double width, double height);


	//draw a colored string
	void drawColorString(std::string whatchars, double x, double y, double z, float pointFont, Color rightColor);

	//draw a colored string aligned to either left (0), center (1), or right (2).
	void drawAlignedCString(std::string whatchars, double x, double y, double z, float pointFont, int alignment, Color rightColor);

	//draw a colored string bounded to a width and height.
	void drawFittedCString(std::string whatchars, double x, double y, double z, float pointFont, double width, double height, Color rightColor);

	//draw colored string aligned to either left (0), center (1), or right (2) and bounded to a width and height.
	void drawAlignedFCString(std::string whatchars, double x, double y, double z, int alignment, double width, double height, Color rightColor);


	//get the width of the text without a point font affecting it
	float getTextWidth(std::string whatchars);

	//get the width of the text.
	float getTextWidth(std::string whatchars, float pointFont);


	//get the height of the text without a point font affecting it.
	float getTextHeight(std::string whatchars);

	//get the height of the text.
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