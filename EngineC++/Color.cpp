#include "Color.h"

Color::Color(float red, float green, float blue, float alpha)
{
	setColor(red, green, blue, alpha);
}

float Color::getRed()
{
	return red;
}

void Color::setRed(float red)
{
	this->red = red;
}

float Color::getGreen()
{
	return green;
}

void Color::setGreen(float green)
{
	this->green = green;
}

float Color::getBlue()
{
	return blue;
}

void Color::setBlue(float blue)
{
	this->blue = blue;
}

float Color::getAlpha()
{
	return alpha;
}

void Color::setAlpha(float alpha)
{
	this->alpha = alpha;
}

void Color::setColor(Color color)
{
	setRed(color.getRed());
	setGreen(color.getGreen());
	setBlue(color.getBlue());
	setAlpha(color.getAlpha());
}

void Color::setColor(float red, float green, float blue, float alpha)
{
	setRed(red);
	setGreen(green);
	setBlue(blue);
	setAlpha(alpha);
}