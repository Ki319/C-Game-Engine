#include "Draw.h"

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
*/
void Engine::rect(double x, double y, double x1, double y1, double z)
{
	glVertex3d(x, y1, z);
	glVertex3d(x1, y1, z);
	glVertex3d(x1, y, z);
	glVertex3d(x, y, z);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param thickness
*/
void Engine::rect(double x, double y, double x1, double y1, double z, double thickness)
{
	rect(x, y1 - thickness, x1, y1, z);
	rect(x1 - thickness, y, x1, y1 - thickness, z);
	rect(x, y, x1 - thickness, y + thickness, z);
	rect(x, y + thickness, x + thickness, y1 - thickness, z);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param thickness
* @param innerColor
*/
void Engine::rect(double x, double y, double x1, double y1, double z, double thickness, Color innerColor)
{
	Color outerColor = Color(getColor());

	glVertex3d(x1, y, z);
	glVertex3d(x, y, z);
	glVertex(x + thickness, y + thickness, z, innerColor);
	glVertex3d(x1 - thickness, y + thickness, z);

	glVertex3d(x1 - thickness, y + thickness, z);
	glVertex3d(x1 - thickness, y1 - thickness, z);
	glVertex(x1, y1, z, outerColor);
	glVertex3d(x1, y, z);

	glVertex3d(x, y1, z);
	glVertex3d(x1, y1, z);
	glVertex(x1 - thickness, y1 - thickness, z, innerColor);
	glVertex3d(x + thickness, y1 - thickness, z);

	glVertex3d(x + thickness, y1 - thickness, z);
	glVertex3d(x + thickness, y + thickness, z);
	glVertex(x, y, z, outerColor);
	glVertex3d(x, y1, z);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param color0
* @param color1
* @param color2
* @param color3
*/
void Engine::rect(double x, double y, double x1, double y1, double z, Color color0, Color color1, Color color2, Color color3)
{
	glVertex(x, y1, z, color0);
	glVertex(x1, y1, z, color1);
	glVertex(x1, y, z, color2);
	glVertex(x, y, z, color3);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param shiftToColor
*/
void Engine::colorHRect(double x, double y, double x1, double y1, double z, Color shiftToColor)
{
	glVertex3d(x, y, z);
	glVertex3d(x, y1, z);
	glVertex(x1, y1, z, shiftToColor);
	glVertex3d(x1, y, z);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param shiftToColor
*/
void Engine::colorVRect(double x, double y, double x1, double y1, double z, Color shiftToColor)
{
	glVertex3d(x1, y, z);
	glVertex3d(x, y, z);
	glVertex(x, y1, z, shiftToColor);
	glVertex3d(x1, y1, z);
}


/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param u
* @param v
* @param u1
* @param v1
*/
void Engine::rectUV(double x, double y, double x1, double y1, double z, double u, double v, double u1, double v1)
{
	glVertex(x, y1, z, u, v1);
	glVertex(x1, y1, z, u1, v1);
	glVertex(x1, y, z, u1, v);
	glVertex(x, y, z, u, v);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param texture
*/
void Engine::rectUV(double x, double y, double x1, double y1, double z, TexCoord texture)
{
	glVertex(x, y, z, texture.getMinU(), texture.getMinV());
	glVertex(x, y1, z, texture.getMinU(), texture.getMaxV());
	glVertex(x1, y1, z, texture.getMaxU(), texture.getMaxV());
	glVertex(x1, y, z, texture.getMaxU(), texture.getMinV());
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param texture
* @param animationID
*/
void Engine::rectUV(double x, double y, double x1, double y1, double z, TexCoord texture, int animationID)
{
	float u = texture.getMinU(animationID);
	float u1 = texture.getMaxU(animationID);
	float v = texture.getMinV(animationID);
	float v1 = texture.getMaxV(animationID);
	glVertex(x, y, z, u, v);
	glVertex(x, y1, z, u, v1);
	glVertex(x1, y1, z, u1, v1);
	glVertex(x1, y, z, u1, v);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param texture
* @param shiftToColor
*/
void Engine::colorHRectUV(double x, double y, double x1, double y1, double z, double u, double v, double u1, double v1, Color shiftToColor)
{
	glVertex(x, y, z, u, v);
	glVertex(x, y1, z, u, v1);
	glVertex(x1, y1, z, u1, v1, shiftToColor);
	glVertex(x1, y, z, u1, v);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param texture
* @param shiftToColor
*/
void Engine::colorHRectUV(double x, double y, double x1, double y1, double z, TexCoord texture, Color shiftToColor)
{
	glVertex(x, y, z, texture.getMinU(), texture.getMinV());
	glVertex(x, y1, z, texture.getMinU(), texture.getMaxV());
	glVertex(x1, y1, z, texture.getMaxU(), texture.getMaxV(), shiftToColor);
	glVertex(x1, y, z, texture.getMaxU(), texture.getMinV());
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param texture
* @param animationID
* @param shiftToColor
*/
void Engine::colorHRectUV(double x, double y, double x1, double y1, double z, TexCoord texture, int animationID, Color shiftToColor)
{
	float u = texture.getMinU(animationID);
	float u1 = texture.getMaxU(animationID);
	float v = texture.getMinV(animationID);
	float v1 = texture.getMaxV(animationID);
	glVertex(x, y, z, u, v);
	glVertex(x, y1, z, u, v1);
	glVertex(x1, y1, z, u1, v1, shiftToColor);
	glVertex(x1, y, z, u1, v);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param u
* @param v
* @param u1
* @param v1
* @param shiftToColor
*/
void Engine::colorVRectUV(double x, double y, double x1, double y1, double z, double u, double v, double u1, double v1, Color shiftToColor)
{
	glVertex(x1, y, z, u1, v);
	glVertex(x, y, z, u, v);
	glVertex(x, y1, z, u, v1, shiftToColor);
	glVertex(x1, y1, z, u1, v1);
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param texture
* @param shiftToColor
*/
void Engine::colorVRectUV(double x, double y, double x1, double y1, double z, TexCoord texture, Color shiftToColor)
{
	glVertex(x1, y, z, texture.getMaxU(), texture.getMinV());
	glVertex(x, y, z, texture.getMinU(), texture.getMinV());
	glVertex(x, y1, z, texture.getMinU(), texture.getMaxV(), shiftToColor);
	glVertex(x1, y1, z, texture.getMaxU(), texture.getMaxV());
}

/**
* draws a rectangle, must have glBegin(GL_QUADS) enabled!
* @param x
* @param y
* @param x1
* @param y1
* @param z
* @param texture
* @param animationID
* @param shiftToColor
*/
void Engine::colorVRectUV(double x, double y, double x1, double y1, double z, TexCoord texture, int animationID, Color shiftToColor)
{
	float u = texture.getMinU(animationID);
	float u1 = texture.getMaxU(animationID);
	float v = texture.getMinV(animationID);
	float v1 = texture.getMaxV(animationID);
	glVertex(x1, y, z, u1, v);
	glVertex(x, y, z, u, v);
	glVertex(x, y1, z, u, v1, shiftToColor);
	glVertex(x1, y1, z, u1, v1);
}

/**
* draws an arc, must have glBegin(GL_QUADS) enabled!
* @param circleX
* @param circleY
* @param z
* @param radius
* @param lineCount
* @param thickness
*/
void Engine::arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, double startAngle = 0, double endAngle = TWO_PI)
{
	double theta = (endAngle - startAngle) / (lineCount);
	double x = radius * cos(startAngle);
	double y = radius * sin(startAngle);
	for (int i = 0; i < lineCount; i++)
	{
		glVertex3d(circleX + x, circleY + y, z);
		glVertex3d(circleX + (radius - thickness) * cos(startAngle), circleY + (radius - thickness) * sin(startAngle), z);
		startAngle += theta;
		x = radius * cos(startAngle);
		y = radius * sin(startAngle);
		glVertex3d(circleX + (radius - thickness) * cos(startAngle), circleY + (radius - thickness) * sin(startAngle), z);
		glVertex3d(circleX + x, circleY + y, z);
	}
}

/**
* draws an arc, must have glBegin(GL_QUADS) enabled!
* @param circleX
* @param circleY
* @param z
* @param radius
* @param lineCount
* @param thickness
* @param endColor
*/
void Engine::arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, Color endColor, double startAngle = 0, double endAngle = TWO_PI)
{
	double deltaTheta = (endAngle - startAngle) / lineCount;
	double x = radius * cos(startAngle);
	double y = radius * sin(startAngle);
	double rShift = (endColor.getRed() - getRed()) / lineCount;
	double gShift = (endColor.getGreen() - getGreen()) / lineCount;
	double bShift = (endColor.getBlue() - getBlue()) / lineCount;
	double aShift = (endColor.getAlpha() - getAlpha()) / lineCount;
	for (int i = 0; i < lineCount; i++)
	{
		glVertex3d(circleX + x, circleY + y, z);
		glVertex3d(circleX + (radius - thickness) * cos(startAngle), circleY + (radius - thickness) * sin(startAngle), z);
		startAngle += deltaTheta;
		x = radius * cos(startAngle);
		y = radius * sin(startAngle);
		glColor(getRed() + rShift, getGreen() + gShift, getBlue() + bShift, getAlpha() + aShift);
		glVertex3d(circleX + (radius - thickness) * cos(startAngle), circleY + (radius - thickness) * sin(startAngle), z);
		glVertex3d(circleX + x, circleY + y, z);
	}
	glColor(getRed() - rShift * lineCount, getGreen() - gShift * lineCount, getBlue() - bShift * lineCount, getAlpha() - aShift * lineCount);
}

/**
* draws a circle, do not have any glBegin!
* @param circleX
* @param circleY
* @param z
* @param radius
* @param lineCount
*/
void Engine::circle(double circleX, double circleY, double z, double radius, int lineCount, double startAngle = 0, double endAngle = TWO_PI)
{
	double deltaTheta = (endAngle - startAngle) / lineCount;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(circleX, circleY, z);
	for (int i = 0; i <= lineCount; i++)
	{
		glVertex3d(circleX + (radius * cos((endAngle -= deltaTheta))), circleY + (radius * sin(endAngle)), z);
	}
	glEnd();
}

/**
* draws a circle, do not have any glBegin!
* @param circleX
* @param circleY
* @param z
* @param radius
* @param lineCount
* @param innerColor
*/
void Engine::circle(double circleX, double circleY, double z, double radius, int lineCount, Color innerColor, double startAngle = 0, double endAngle = TWO_PI)
{
	double deltaTheta = (endAngle - startAngle) / lineCount;
	Color color = Color(getColor());
	glBegin(GL_TRIANGLE_FAN);
	glColor(innerColor);
	glVertex3d(circleX, circleY, z);
	glColor(color);
	for (int i = 0; i <= lineCount; i++)
	{
		glVertex3d(circleX + radius * cos((endAngle -= deltaTheta)), circleY + radius * sin(endAngle), z);
	}
	glEnd();
}

/**
* draws a circle, do not have any glBegin!
* @param circleX
* @param circleY
* @param z
* @param radius
* @param u
* @param v
* @param u1
* @param v1
* @param lineCount
*/
void Engine::circle(double circleX, double circleY, double z, double radius, int lineCount, TexCoord texture/*= getTexture()*/, double startAngle = 0, double endAngle = TWO_PI)
{
	double deltaTheta = (endAngle - startAngle) / lineCount;
	double difU = (texture.getMaxU() - texture.getMinU()) / 2;
	double difV = (texture.getMaxV() - texture.getMinV()) / 2;
	double centerU = texture.getMinU() + difU;
	double centerV = texture.getMinV() + difV;
	glBegin(GL_TRIANGLE_FAN);
	glVertex(circleX, circleY, z, centerU, centerV);
	for (int i = 0; i <= lineCount; i++)
	{
		glVertex(circleX + radius * cos((endAngle -= deltaTheta)), circleY + radius * sin(endAngle), z, centerU + difU * cos(endAngle), centerV + difV * sin(endAngle), texture);
	}
	glEnd();
}

/**
* draws a circle, do not have any glBegin!
* @param circleX
* @param circleY
* @param z
* @param radius
* @param u
* @param v
* @param u1
* @param v1
* @param animationID
* @param lineCount
*/
void Engine::circle(double circleX, double circleY, double z, double radius, int lineCount, TexCoord texture/*= getTexture()*/, int animationID, double startAngle = 0, double endAngle = TWO_PI)
{
	float u = texture.getMinU(animationID);
	float v = texture.getMinV(animationID);
	float u1 = texture.getMaxU(animationID);
	float v1 = texture.getMaxV(animationID);
	double deltaTheta = (endAngle - startAngle) / lineCount;
	double difU = (u1 - u) / 2;
	double difV = (v1 - v) / 2;
	double centerU = u + difU;
	double centerV = v + difV;
	glBegin(GL_TRIANGLE_FAN);
	glVertex(circleX, circleY, z, centerU, centerV);
	for (int i = 0; i <= lineCount; i++)
	{
		glVertex(circleX + radius * cos((endAngle -= deltaTheta)), circleY + radius * sin(endAngle), z, centerU + difU * cos(endAngle), centerV + difV * sin(endAngle), texture, animationID);
	}
	glEnd();
}