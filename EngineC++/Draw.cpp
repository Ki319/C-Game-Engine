#include "Draw.h"

void Engine::rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z)
{
	glVertex3d(topLeftX, bottomRightY, z);
	glVertex3d(bottomRightX, bottomRightY, z);
	glVertex3d(bottomRightX, topLeftY, z);
	glVertex3d(topLeftX, topLeftY, z);
}

void Engine::rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double thickness)
{
	rect(topLeftX, bottomRightY - thickness, bottomRightX, bottomRightY, z);
	rect(bottomRightX - thickness, topLeftY, bottomRightX, bottomRightY - thickness, z);
	rect(topLeftX, topLeftY, bottomRightX - thickness, topLeftY + thickness, z);
	rect(topLeftX, topLeftY + thickness, topLeftX + thickness, bottomRightY - thickness, z);
}

void Engine::rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double thickness, Color innerColor)
{
	Color outerColor = Color(getColor());

	glVertex3d(bottomRightX, topLeftY, z);
	glVertex3d(topLeftX, topLeftY, z);
	glVertex(topLeftX + thickness, topLeftY + thickness, z, innerColor);
	glVertex3d(bottomRightX - thickness, topLeftY + thickness, z);

	glVertex3d(bottomRightX - thickness, topLeftY + thickness, z);
	glVertex3d(bottomRightX - thickness, bottomRightY - thickness, z);
	glVertex(bottomRightX, bottomRightY, z, outerColor);
	glVertex3d(bottomRightX, topLeftY, z);

	glVertex3d(topLeftX, bottomRightY, z);
	glVertex3d(bottomRightX, bottomRightY, z);
	glVertex(bottomRightX - thickness, bottomRightY - thickness, z, innerColor);
	glVertex3d(topLeftX + thickness, bottomRightY - thickness, z);

	glVertex3d(topLeftX + thickness, bottomRightY - thickness, z);
	glVertex3d(topLeftX + thickness, topLeftY + thickness, z);
	glVertex(topLeftX, topLeftY, z, outerColor);
	glVertex3d(topLeftX, bottomRightY, z);
}

void Engine::rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color color0, Color color1, Color color2, Color color3)
{
	glVertex(topLeftX, bottomRightY, z, color0);
	glVertex(bottomRightX, bottomRightY, z, color1);
	glVertex(bottomRightX, topLeftY, z, color2);
	glVertex(topLeftX, topLeftY, z, color3);
}

void Engine::rectLRGradient(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color shiftToColor)
{
	glVertex3d(topLeftX, topLeftY, z);
	glVertex3d(topLeftX, bottomRightY, z);
	glVertex(bottomRightX, bottomRightY, z, shiftToColor);
	glVertex3d(bottomRightX, topLeftY, z);
}

void Engine::rectTBGradient(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color shiftToColor)
{
	glVertex3d(bottomRightX, topLeftY, z);
	glVertex3d(topLeftX, topLeftY, z);
	glVertex(topLeftX, bottomRightY, z, shiftToColor);
	glVertex3d(bottomRightX, bottomRightY, z);
}

void Engine::rectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double u, double v, double u1, double v1)
{
	glVertex(topLeftX, bottomRightY, z, u, v1);
	glVertex(bottomRightX, bottomRightY, z, u1, v1);
	glVertex(bottomRightX, topLeftY, z, u1, v);
	glVertex(topLeftX, topLeftY, z, u, v);
}

void Engine::rectLRUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color shiftToColor, double u, double v, double u1, double v1)
{
	glVertex(topLeftX, topLeftY, z, u, v);
	glVertex(topLeftX, bottomRightY, z, u, v1);
	glVertex(bottomRightX, bottomRightY, z, u1, v1, shiftToColor);
	glVertex(bottomRightX, topLeftY, z, u1, v);
}

void Engine::rectTBUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color shiftToColor, double u, double v, double u1, double v1)
{
	glVertex(bottomRightX, topLeftY, z, u1, v);
	glVertex(topLeftX, topLeftY, z, u, v);
	glVertex(topLeftX, bottomRightY, z, u, v1, shiftToColor);
	glVertex(bottomRightX, bottomRightY, z, u1, v1);
}

void Engine::rectTex(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, TexCoord texture, int animationID)
{
	float u = texture.getMinU(animationID);
	float u1 = texture.getMaxU(animationID);
	float v = texture.getMinV(animationID);
	float v1 = texture.getMaxV(animationID);

	glVertex(topLeftX, topLeftY, z, u, v);
	glVertex(topLeftX, bottomRightY, z, u, v1);
	glVertex(bottomRightX, bottomRightY, z, u1, v1);
	glVertex(bottomRightX, topLeftY, z, u1, v);
}

void Engine::rectLRTex(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color shiftToColor, TexCoord texture, int animationID)
{
	float u = texture.getMinU(animationID);
	float u1 = texture.getMaxU(animationID);
	float v = texture.getMinV(animationID);
	float v1 = texture.getMaxV(animationID);

	glVertex(topLeftX, topLeftY, z, u, v);
	glVertex(topLeftX, bottomRightY, z, u, v1);
	glVertex(bottomRightX, bottomRightY, z, u1, v1, shiftToColor);
	glVertex(bottomRightX, topLeftY, z, u1, v);
}

void Engine::rectTBTex(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color shiftToColor, TexCoord texture, int animationID)
{
	float u = texture.getMinU(animationID);
	float u1 = texture.getMaxU(animationID);
	float v = texture.getMinV(animationID);
	float v1 = texture.getMaxV(animationID);

	glVertex(bottomRightX, topLeftY, z, u1, v);
	glVertex(topLeftX, topLeftY, z, u, v);
	glVertex(topLeftX, bottomRightY, z, u, v1, shiftToColor);
	glVertex(bottomRightX, bottomRightY, z, u1, v1);
}

void Engine::arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, double startAngle, double endAngle)
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

void Engine::arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, Color endColor, double startAngle, double endAngle)
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

void Engine::circle(double circleX, double circleY, double z, double radius, int lineCount, double startAngle, double endAngle)
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

void Engine::circle(double circleX, double circleY, double z, double radius, int lineCount, Color innerColor, double startAngle, double endAngle)
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

void Engine::circle(double circleX, double circleY, double z, double radius, int lineCount, TexCoord texture, int animationID, double startAngle, double endAngle)
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

void Engine::circle(double circleX, double circleY, double z, double radius, int lineCount, Color innerColor, TexCoord texture, int animationID, double startAngle, double endAngle)
{
	float u = texture.getMinU(animationID);
	float v = texture.getMinV(animationID);
	float u1 = texture.getMaxU(animationID);
	float v1 = texture.getMaxV(animationID);

	double deltaTheta = (endAngle - startAngle) / lineCount;

	Color color = Color(getColor());

	double difU = (u1 - u) / 2;
	double difV = (v1 - v) / 2;
	double centerU = u + difU;
	double centerV = v + difV;

	glBegin(GL_TRIANGLE_FAN);
	glColor(innerColor);
	glVertex(circleX, circleY, z, centerU, centerV);
	glColor(color);

	for (int i = 0; i <= lineCount; i++)
	{
		glVertex(circleX + radius * cos((endAngle -= deltaTheta)), circleY + radius * sin(endAngle), z, centerU + difU * cos(endAngle), centerV + difV * sin(endAngle), texture, animationID);
	}
	glEnd();
}