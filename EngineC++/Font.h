#pragma once

#include "Texture.h"

//structure containing each letters individual data
struct CharData
{
public:
	TexCoord texture;
	std::map<char, float> kernings;
	float width = -1, height, xOffset, yOffset, xadvance;

	CharData() {}
	CharData(int charData[]);

	void reduce(int largestWidth, int largestHeight);
	void add(char otherChar, float adjustment);
	float get(char otherChar);
};

class Font : public Texture
{
public:
	//implemented from it's parent, meant to read the font file for character information.
	Image load(fs::path pathLoc);

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
	void drawFittedCString(std::string whatchars, double x, double y, double z, double width, double height, Color rightColor);

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