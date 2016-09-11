#include "Font.h"

CharData::CharData(int charData[])
{
	width = (float) charData[3];
	height = (float) charData[4];
	xOffset = (float) charData[5];
	yOffset = (float) charData[6];
	xadvance = (float) charData[7];
}

void CharData::reduce(int largestWidth, int largestHeight)
{
	width /= (float) largestWidth;
	height /= (float) largestHeight;
	xOffset /= (float) largestWidth;
	yOffset /= (float) largestHeight;
	xadvance /= (float) largestWidth;
}

void CharData::add(char otherChar, float adjustment)
{
	kernings[otherChar] = adjustment;
}

float CharData::get(char otherChar)
{
	return kernings[otherChar];
}

Image Font::load(fs::path fileLoc)
{
	Image image = Texture::load(fileLoc);
	if (image.imageData == nullptr)
		return image;

	fs::path path = fileLoc.replace_extension("font");
	std::vector<std::string> lines;
	std::vector<std::string>::iterator lineIt;
	std::vector<std::string> numbers;
	std::vector<std::string>::iterator numberIt;

	int largestWidth = 0;
	int largestHeight = 0;

	if (fs::is_regular_file(path))
	{
		if (!readLines(path, lines))
			return Image();

		int data[8];

		for (lineIt = lines.begin(); lineIt != lines.end(); ++lineIt)
		{
			boost::split(numbers, *lineIt, boost::is_any_of(" "));
			for (numberIt = numbers.begin(); numberIt != numbers.end(); ++numberIt)
			{
				data[numberIt - numbers.begin()] = atoi((*numberIt).c_str());
			}
			fontBitmap[data[0]] = CharData(data);
		}

		std::map<char, CharData>::iterator mapIt;
		for (mapIt = fontBitmap.begin(); mapIt != fontBitmap.end(); ++mapIt)
		{
			mapIt->second.reduce(largestWidth, largestHeight);
		}
	}

	path = path.replace_extension("kerning");

	lines.clear();
	numbers.clear();

	if (fs::is_regular_file(path))
	{
		if (!readLines(path, lines))
			return image;

		int kerningData[3];

		for (lineIt = lines.begin(); lineIt != lines.end(); ++lineIt)
		{
			boost::split(numbers, *lineIt, boost::is_any_of(" "));
			for (numberIt = numbers.begin(); numberIt != numbers.end(); ++numberIt)
			{
				kerningData[numberIt - numbers.begin()] = atoi((*numberIt).c_str());
			}
			fontBitmap[kerningData[1]].add(kerningData[0], (float) kerningData[2] / (float) largestWidth);
		}
	}
	return image;
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
		if (letter.width != -1)
		{
			width = letter.width * pointFont;
			xOffset = letter.xOffset * pointFont;
			if (i > 0)
			{
				xOffset += letter.get(pastLetter) * pointFont;
			}
			yOffset = letter.yOffset * pointFont;
			if (whatchars[i] != ' ')
				Engine::rectTex(x + xOffset, y + yOffset, x + width + xOffset, y + letter.height * pointFont + yOffset, z, letter.texture);
			x += letter.xadvance * pointFont;
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
	drawString(whatchars, x, y, z, fminf((float) height / getTextHeight(whatchars), (float) width / getTextWidth(whatchars)));
}

void Font::drawAlignedFittedString(std::string whatchars, double x, double y, double z, int alignment, double width, double height)
{
	float pointFont = std::min<float>((float) height / getTextHeight(whatchars), (float) width / getTextWidth(whatchars));
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
	double redShift = (rightColor.getRed() - Engine::getRed()) / textWidth;
	double greenShift = (rightColor.getGreen() - Engine::getGreen()) / textWidth;
	double blueShift = (rightColor.getBlue() - Engine::getBlue()) / textWidth;
	double alphaShift = (rightColor.getAlpha() - Engine::getAlpha()) / textWidth;

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
		if (letter.width != -1)
		{
			width = letter.width * pointFont;
			xOffset = letter.xOffset * pointFont;
			if (i > 0)
			{
				xOffset += letter.get(pastLetter) * pointFont;
			}
			yOffset = letter.yOffset * pointFont;
			if (whatchars[i] != ' ')
			{
				Engine::rectLRTex(x + xOffset, y + yOffset, x + width + xOffset,
					y + letter.height * pointFont + yOffset, z,
					Color(Engine::getRed() + (float) (redShift * width),
						Engine::getGreen() + (float) (greenShift * width),
						Engine::getBlue() + (float) (blueShift * width),
						Engine::getAlpha() + (float) (alphaShift * width)),
					letter.texture);
			}
			x += letter.xadvance * pointFont;
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

void Font::drawFittedCString(std::string whatchars, double x, double y, double z, double width, double height, Color rightColor)
{
	drawColorString(whatchars, x, y, z, std::min<float>((float) height / getTextHeight(whatchars), (float) width / getTextWidth(whatchars)), rightColor);
}

void Font::drawAlignedFCString(std::string whatchars, double x, double y, double z, int alignment, double width, double height, Color rightColor)
{
	float pointFont = std::min<float>((float) height / getTextHeight(whatchars), (float) width / getTextWidth(whatchars));
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
		if (letter.width != -1)
		{
			totalWidth += letter.xadvance;
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
		if (letter.width != -1)
		{
			largestHeight = fmax(letter.height + letter.yOffset, largestHeight);
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