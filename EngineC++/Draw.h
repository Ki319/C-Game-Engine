#pragma once

#include "stdafx.h"
#include "Texture.h"
#include "TexCoord.h"
#include "OpenGL.h"

namespace Engine
{
	//draws a regular rectangle.
	void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z);

	//draws a rectangular outline with a thickness specified.
	void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double tickness);

	//draws a rectangle with an outer color the shifts into an inner color at the center.
	void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double thickness, Color innerColor);

	//draws a rectangle with four corners with four different colors.
	void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color topLeftColor, Color bottomLeftColor, Color bottomRightColor, Color topRightColor);


	//draws a rectangle with a left right gradient.
	void rectLRGradient(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor);

	//draws a rectangle with a top bottom gradient.
	void rectTBGradient(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor);


	//draws a rectangle with a specified u min, u max, v min, and v max
	void rectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double u, double v, double u1, double v1);

	//draws a rectangle with a specified u min, u max, v min, v max and a left right gradient.
	void rectLRUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor, double u, double v, double u1, double v1);

	//draws a rectangle with a specfied u min, u max, v min, v max and a top bottom gradient.
	void rectTBUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor, double u, double v, double u1, double v1);

	//draws a rectangle with a mapped texture to it.
	void rectTex(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, TexCoord texture, int animationID = 0);

	//draws a rectangle with a mapped texture to it and a left right gradient.
	void rectLRTex(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor, TexCoord texture, int animationID = 0);

	//draws a rectangle with a mapped texture to it and a top bottom gradient.
	void rectTBTex(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor, TexCoord texture, int animationID = 0);


	//draws an arc with a specified amount of rectangles (or lines) to make it.
	void arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, double startAngle = 0, double endAngle = TWO_PI);
	
	//draws an arc with a specified amount of rectangles (or lines) to make it and has
	//an end color.
	void arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, Color endColor, double startAngle = 0, double endAngle = TWO_PI);

	//draws a circle with a specified amount of triangles (or lines) to make it.
	void circle(double circleX, double circleY, double z, double radius, int lineCount, double startAngle = 0, double endAngle = TWO_PI);
	
	//draws a circle with a specified amount of triangles (or lines) to make it and has
	//an inner color.
	void circle(double circleX, double circleY, double z, double radius, int lineCount, Color innerColor, double startAngle = 0, double endAngle = TWO_PI);
	
	//draws a circle with a specified amount of triangles (or lines) to make it and has
	//a texture mapped to it
	void circle(double circleX, double circleY, double z, double radius, int lineCount, TexCoord texture, int animationID = 0, double startAngle = 0, double endAngle = TWO_PI);

	//draws a circle with a specified amount of triangles (or lines) to make it and has
	//an inner color and texture mapped to it.
	void circle(double circleX, double circleY, double z, double radius, int lineCount, Color innerColor, TexCoord texture, int animationID = 0, double startAngle = 0, double endAngle = TWO_PI);
}