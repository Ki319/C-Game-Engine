#include "Font.h"

char *Font::load(fs::path pathLoc)
{
	char *data = nullptr;
	return data;
}

CharData Font::getCharData(char letter)
{
	std::map<char, CharData>::iterator it = fontBitmap.find(letter);
	if (it != fontBitmap.end())
	{
		return it->second;
	}
	return CharData();
}

void Font::drawString(std::string whatchars, double x, double y, double z, float pointFont)
{
	CharData letter;
	char pastLetter;
	int i;
	double width;
	double xOffset;
	double yOffset;
	glBegin(GL_QUADS);
	for (i = 0; i < whatchars.length(); i++)
	{
		letter = getCharData(whatchars[i]);
		if (letter.getWidth() != -1)
		{
			width = letter.getWidth() * pointFont;
			xOffset = letter.getXOffset() * pointFont;
			if (i > 0)
			{
				xOffset += letter.get(pastLetter) * pointFont;
			}
			yOffset = letter.getYOffset() * pointFont;
			if (whatchars[i] != ' ')
				rectTex(x + xOffset, y + yOffset, x + width + xOffset, y + letter.getHeight() * pointFont + yOffset, z, letter.getTexture());
			x += letter.getAdvance() * pointFont;
			pastLetter = whatchars[i];
		}
	}
	glEnd();
}

void Font::drawAlignedString(std::string whatchars, double x, double y, double z, float pointFont, int alignment)
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

void Font::drawColorString(std::string whatchars, double x, double y, double z, float pointFont, Color rightColor)
{
	double textWidth = getTextWidth(whatchars, pointFont);
	double redShift = (rightColor.getRed() - getRed()) / textWidth;
	double greenShift = (rightColor.getGreen() - getGreen()) / textWidth;
	double blueShift = (rightColor.getBlue() - getBlue()) / textWidth;
	double alphaShift = (rightColor.getAlpha() - getAlpha()) / textWidth;

	char pastLetter;
	CharData letter;
	int i;
	double width = 0;
	double xOffset;
	double yOffset;
	glBegin(GL_QUADS);
	for (i = 0; i < whatchars.length(); i++)
	{
		letter = getCharData(whatchars[i]);
		if (letter.getWidth() != -1)
		{
			width = letter.getWidth() * pointFont;
			xOffset = letter.getXOffset() * pointFont;
			if (i > 0)
			{
				xOffset += letter.get(pastLetter) * pointFont;
			}
			yOffset = letter.getYOffset() * pointFont;
			if (whatchars[i] != ' ')
				rectLRTex(x + xOffset, y + yOffset, x + width + xOffset, y + letter.getHeight() * pointFont + yOffset, z, Color(getRed() + (redShift * width), getGreen() + (greenShift * width), getBlue() + (blueShift * width), getAlpha() + (alphaShift * width)), letter.getTexture());
			x += letter.getAdvance() * pointFont;
			pastLetter = whatchars[i];
		}
	}
	glEnd();
}

void Font::drawAlignedCString(std::string whatchars, double x, double y, double z, float pointFont, int alignment, Color rightColor)
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

float Font::getTextWidth(std::string whatchars)
{
	float totalWidth = 0;
	CharData letter;

	for (int i = 0; i < whatchars.length(); i++)
	{
		letter = getCharData(whatchars[i]);
		if (letter.getWidth() != -1)
		{
			totalWidth += letter.getAdvance();
		}
		else
		{
			return 0;
		}
	}
	return totalWidth;
}

float Font::getTextWidth(std::string whatchars, float pointFont)
{
	return getTextWidth(whatchars) * pointFont;
}

float Font::getTextHeight(std::string whatchars)
{
	float largestHeight = 0;
	CharData letter;

	for (int i = 0; i < whatchars.length(); i++)
	{
		letter = getCharData(whatchars[i]);
		if (letter.getWidth() != -1)
		{
			largestHeight = fmax(letter.getHeight() + letter.getYOffset(), largestHeight);
		}
		else
		{
			return 0;
		}
	}
	return largestHeight;
}

float Font::getTextHeight(std::string whatchars, float pointFont)
{
	return getTextHeight(whatchars) * pointFont;
}

CharData::CharData() 
{
	kernings = std::map<char, float>();
	width = height = xOffset = yOffset = xadvance = -1;
}

TexCoord CharData::getTexture()
{
	return texture;
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

void CharData::add(char otherChar, float adjustment)
{
	kernings[otherChar] = adjustment;
}

float CharData::get(char otherChar)
{
	return kernings[otherChar];
}