#include "pch.h"
#include "Color.h"
#include "Texture.h"
#include "TexCoord.h"
#include "OpenGL.h"

namespace Engine
{
	void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z);

	void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double tickness);

	void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double thickness, Color innerColor);

	void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color topLeftColor, Color bottomLeftColor, Color bottomRightColor, Color topRightColor);

	void colorHRect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor);

	void colorVRect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor);

	void rectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, TexCoord texture/*= getTexture()*/);
	void rectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, TexCoord texture/*= getTexture()*/, int animationID = 0);
	void rectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double u, double v, double u1, double v1);

	void colorHRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, TexCoord texture/*= getTexture()*/, Color rightColor);
	void colorHRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, TexCoord texture/*= getTexture()*/, int animationID, Color rightColor);
	void colorHRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double u, double v, double u1, double v1, Color rightColor);

	void colorVRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, TexCoord texture/*= getTexture()*/, Color bottomColor);
	void colorVRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, TexCoord texture/*= getTexture()*/, int animationID, Color bottomColor);
	void colorVRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double u, double v, double u1, double v1, Color bottomColor);

	void arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, double startAngle = 0, double endAngle = TWO_PI);
	void arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, Color endColor, double startAngle = 0, double endAngle = TWO_PI);

	void circle(double circleX, double circleY, double z, double radius, int lineCount, double startAngle = 0, double endAngle = TWO_PI);
	void circle(double circleX, double circleY, double z, double radius, int lineCount, Color innerColor, double startAngle = 0, double endAngle = TWO_PI);

	void circle(double circleX, double circleY, double z, double radius, int lineCount, TexCoord texture/*= getTexture()*/, double startAngle = 0, double endAngle = TWO_PI);
	void circle(double circleX, double circleY, double z, double radius, int lineCount, TexCoord texture/*= getTexture()*/, int animationID, double startAngle = 0, double endAngle = TWO_PI);
}