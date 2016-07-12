#pragma once

struct Color
{
private:
	float red;
	float green;
	float blue;
	float alpha;

public:

	//Initiate a 4 value color
	//red : 0 - 1
	//green : 0 - 1
	//blue : 0 - 1
	//alpha : 0 - 1
	Color(float red = 1, float green = 1, float blue = 1, float alpha = 1);

	//returns red
	float getRed();

	//sets red
	void setRed(float red);

	//returns green
	float getGreen();

	//sets green
	void setGreen(float green);

	//returns blue
	float getBlue();

	//sets blue
	void setBlue(float blue);

	//returns alpha
	float getAlpha();

	//sets alpha
	void setAlpha(float alpha);

	
	//Sets all color values from one Color4d object to another
	//color : the color to copy from
	void setColor(Color color);

	
	//Sets all color values
	//red : value 0 - 1
	//green : value 0 - 1
	//blue : value 0 - 1
	//alpha : value 0 - 1
	void setColor(float red, float green, float blue, float alpha);
};

