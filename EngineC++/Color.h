#pragma once
struct Color
{
private:
	float red;
	float green;
	float blue;
	float alpha;

public:
	/**
	* Initiate a 4 value color
	* red : 0 - 255
	* green : 0 - 255
	* blue : 0 - 255
	* alpha : 0 - 255
	*/
	Color(int red, int green, int blue, int alpha);

	/**
	* Initiate a 4 value color
	* red : 0 - 1
	* green : 0 - 1
	* blue : 0 - 1
	* alpha : 0 - 1
	*/
	Color(float red, float green, float blue, float alpha);

	/**
	* @return red value 0 - 1
	*/
	float getRed();

	/**
	* red : value 0 - 1
	*/
	void setRed(float red);

	/**
	* @return green value 0 - 1
	*/
	float getGreen();

	/**
	* green : value 0 - 1
	*/
	void setGreen(float green);

	/**
	* @return blue value 0 - 1
	*/
	float getBlue();

	/**
	* blue : value 0 - 1
	*/
	void setBlue(float blue);

	/**
	* @return alpha value 0 - 1
	*/
	float getAlpha();

	/**
	* alpha : value 0 - 1
	*/
	void setAlpha(float alpha);

	/**
	* Sets all color values from one <b>Color4d</b> object to another
	* color : the color to copy from
	*/
	void setColor(Color color);

	/**
	* Sets all color values
	* red : value 0 - 1
	* green : value 0 - 1
	* blue : value 0 - 1
	* alpha : value 0 - 1
	*/
	void setColor(float red, float green, float blue, float alpha);
};

