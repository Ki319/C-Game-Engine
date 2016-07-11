#include "Font.h"

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
	glBegin(GL_QUADS);
	for (i = 0; i < whatchars.length(); i++)
	{
		letter = getCharData(whatchars.at(i));
		if (letter.width != -1)
		{
			width = letter.getWidth() * pointFont;
			xOffset = letter.getXOffset() * pointFont;
			yOffset = letter.getYOffset() * pointFont;
			if (whatchars.at(i) != ' ')
				rectTex(x + xOffset, y + yOffset, x + width + xOffset, y + letter.getHeight() * pointFont + yOffset, z, letter.getTexture());
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
	double textWidth = getTextWidth(whatchars, pointFont);
	double redShift = (rightColor.getRed() - getRed()) / textWidth;
	double greenShift = (rightColor.getGreen() - getGreen()) / textWidth;
	double blueShift = (rightColor.getBlue() - getBlue()) / textWidth;
	double alphaShift = (rightColor.getAlpha() - getAlpha()) / textWidth;

	CharData pastLetter;
	CharData letter;
	int i;
	double width = 0;
	double xOffset;
	double yOffset;
	glBegin(GL_QUADS);
	for (i = 0; i < whatchars.length(); i++)
	{
		letter = getCharData(whatchars.at(i));
		if (letter.width != -1)
		{
			width = letter.getWidth() * pointFont;
			xOffset = letter.getXOffset() * pointFont;
			if (pastLetter.width != -1)
			{
				xOffset += letter.getKerning().get(pastLetter) * pointFont;
			}
			yOffset = letter.getYOffset() * pointFont;
			if (whatchars.at(i) != ' ')
				rectLRTex(x + xOffset, y + yOffset, x + width + xOffset, y + letter.getHeight() * pointFont + yOffset, z, Color(getRed() + (redShift * width), getGreen() + (greenShift * width), getBlue() + (blueShift * width), getAlpha() + (alphaShift * width)), letter.getTexture());
			x += letter.getAdvance() * pointFont;
			pastLetter = letter;
		}
	}
	glEnd();
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