#include "Color.h"

Color::Color(int red, int green, int blue, int alpha)
{
	setColor(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
}

/**
* Initiate a 4 value color
* red : 0 - 1
* green : 0 - 1
* blue : 0 - 1
* alpha : 0 - 1
*/
Color::Color(float red, float green, float blue, float alpha)
{
	setColor(red, green, blue, alpha);
}

/**
* @return red value 0 - 1
*/
float Color::getRed()
{
	return red;
}

/**
* red : value 0 - 1
*/
void Color::setRed(float red)
{
	this->red = red;
}

/**
* @return green value 0 - 1
*/
float Color::getGreen()
{
	return green;
}

/**
* green : value 0 - 1
*/
void Color::setGreen(float green)
{
	this->green = green;
}

/**
* @return blue value 0 - 1
*/
float Color::getBlue()
{
	return blue;
}

/**
* blue : value 0 - 1
*/
void Color::setBlue(float blue)
{
	this->blue = blue;
}

/**
* @return alpha value 0 - 1
*/
float Color::getAlpha()
{
	return alpha;
}

/**
* alpha : value 0 - 1
*/
void Color::setAlpha(float alpha)
{
	this->alpha = alpha;
}

/**
* Sets all color values from one <b>Color4d</b> object to another
* color : the color to copy from
*/
void Color::setColor(Color color)
{
	setRed(color.getRed());
	setGreen(color.getGreen());
	setBlue(color.getBlue());
	setAlpha(color.getAlpha());
}

/**
* Sets all color values
* red : value 0 - 1
* green : value 0 - 1
* blue : value 0 - 1
* alpha : value 0 - 1
*/
void Color::setColor(float red, float green, float blue, float alpha)
{
	setRed(red);
	setGreen(green);
	setBlue(blue);
	setAlpha(alpha);
}