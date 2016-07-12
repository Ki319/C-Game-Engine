#include "OpenGL.h"

#pragma once

Color currentColor;

void Engine::glBlend(int src, int output)
{
	glEnable(GL_BLEND);
	glBlendFunc(src, output);
}

void Engine::glClearBuffers(int bufferClear)
{
	glClear(bufferClear);
	glColor(1, 1, 1, 1);
}

void Engine::glDefaults()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClearStencil(0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, .05f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_DITHER);
	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glColor(1, 1, 1, 1);
}

void Engine::glSetup2d(glm::vec4 renderArea, GLdouble width, GLdouble height, GLdouble zScaleMax)
{
	glViewport(renderArea.x, renderArea.y, renderArea.z + renderArea.x, renderArea.w + renderArea.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -zScaleMax, zScaleMax);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Engine::glSetup3d(glm::vec4 renderArea, float windowRatio, float fovy, float zNear, float zFar)
{
	glViewport(renderArea.x, renderArea.y, renderArea.z + renderArea.x, renderArea.w + renderArea.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ymax = zNear * tan(fovy * PI / 360.0);
	double ymin = -ymax;
	double xmin = ymin * windowRatio;
	double xmax = ymax * windowRatio;
	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Engine::glVertex(double x, double y, double z, Color color)
{
	glColor(color);
	glVertex3d(x, y, z);
}

void Engine::glVertex(double x, double y, double z, double r, double g, double b, double a)
{
	glColor(r, g, b, a);
	glVertex3d(x, y, z);
}

void Engine::glVertex(double x, double y, double z, double u, double v)
{
	glTexCoord2d(u, v);
	glVertex3d(x, y, z);
}

void Engine::glVertex(double x, double y, double z, double u, double v, Color color)
{
	glColor(color);
	glVertex(x, y, z, u, v);
}

void Engine::glVertex(double x, double y, double z, double u, double v, double r, double g, double b, double a)
{
	glColor(r, g, b, a);
	glVertex(x, y, z, u, v);
}

void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture)
{
	glTexCoord2d((texture.getMaxU() - texture.getMinU()) * u + texture.getMinU(), (texture.getMaxV() - texture.getMinV()) * v + texture.getMinV());
	glVertex3d(x, y, z);
}

void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, Color color)
{
	glColor(color);
	glVertex(x, y, z, u, v, texture);
}

void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, double r, double g, double b, double a)
{
	glColor(r, g, b, a);
	glVertex(x, y, z, u, v, texture);
}

void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, int animationID)
{
	glTexCoord2d((texture.getMaxU(animationID) - texture.getMinU(animationID)) * u + texture.getMinU(animationID), (texture.getMaxV(animationID) - texture.getMinV(animationID)) * v + texture.getMinV(animationID));
	glVertex3d(x, y, z);
}

void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, int animationID, Color color)
{
	glColor(color);
	glVertex(x, y, z, u, v, texture, animationID);
}

void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, int animationID, double r, double g, double b, double a)
{
	glColor(r, g, b, a);
	glVertex(x, y, z, u, v, texture, animationID);
}

void Engine::glColor(double r, double g, double b, double a)
{
	glColor4d(r, g, b, a);
	getColor().setColor(r, g, b, a);
}

void Engine::glColor(Color color)
{
	glColor4d(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	getColor().setColor(color);
}

Color Engine::getColor()
{
	return currentColor;
}

double Engine::getRed()
{
	return getColor().getRed();
}

double Engine::getGreen()
{
	return getColor().getGreen();
}

double Engine::getBlue()
{
	return getColor().getBlue();
}

double Engine::getAlpha()
{
	return getColor().getAlpha();
}