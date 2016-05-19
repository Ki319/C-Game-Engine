#include "OpenGL.h"

/**
* User inputed values for alpha rendering
* @param src
* @param output
*/
void Engine::glBlend(int src = GL_SRC_ALPHA, int output = GL_ONE_MINUS_SRC_ALPHA)
{
	glEnable(GL_BLEND);
	glBlendFunc(src, output);
}

/**
* begin drawing quads
*/
void Engine::glStart()
{
	glBegin(GL_QUADS);
}

/**
* Called to clear color, depth, and stencil buffers
*/
void Engine::glClearBuffers(int bufferClear = GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glColor(1, 1, 1, 1);
}

/**
* called to reset application to default content
*/
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

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glColor(1, 1, 1, 1);
}

/**
* color scheme for rendering
* @param r
* @param g
* @param b
* @param a
*/
void Engine::glColor(double r, double g, double b, double a = 1)
{
	glColor4d(r, g, b, a);
	getColor().setColor(r, g, b, a);
}

/**
* color scheme for rendering
* @param color
*/
void Engine::glColor(Color color)
{
	glColor4d(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	getColor().setColor(color);
}

/**
* get current set color
* @return
*/
Color Engine::getColor()
{
	return currentColor;
}

/**
* get current red
* @return
*/
double Engine::getRed()
{
	return getColor().getRed();
}

/**
* get current green
* @return
*/
double Engine::getGreen()
{
	return getColor().getGreen();
}

/**
* get current blue
* @return
*/
double Engine::getBlue()
{
	return getColor().getBlue();
}

/**
* get current alpha
* @return
*/
double Engine::getAlpha()
{
	return getColor().getAlpha();
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param color
*/
void Engine::glVertex(double x, double y, double z, Color color)
{
	glColor(color);
	glVertex3d(x, y, z);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param r
* @param g
* @param b
* @param a
*/
void Engine::glVertex(double x, double y, double z, double r, double g, double b, double a = 1)
{
	glColor(r, g, b, a);
	glVertex3d(x, y, z);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
*/
void Engine::glVertex(double x, double y, double z, double u, double v)
{
	glTexCoord2d(u, v);
	glVertex3d(x, y, z);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
* @param color
*/
void Engine::glVertex(double x, double y, double z, double u, double v, Color color)
{
	glColor(color);
	glVertex(x, y, z, u, v);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
* @param r
* @param g
* @param b
* @param a
*/
void Engine::glVertex(double x, double y, double z, double u, double v, double r, double g, double b, double a = 1)
{
	glColor(r, g, b, a);
	glVertex(x, y, z, u, v);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
* @param texture
*/
void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture)
{
	glTexCoord2d((texture.getMaxU() - texture.getMinU()) * u + texture.getMinU(), (texture.getMaxV() - texture.getMinV()) * v + texture.getMinV());
	glVertex3d(x, y, z);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
* @param texture
*/
void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, Color color)
{
	glColor(color);
	glVertex(x, y, z, u, v, texture);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
* @param texture
* @param r
* @param g
* @param b
* @param a
*/
void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, double r, double g, double b, double a = 1)
{
	glColor(r, g, b, a);
	glVertex(x, y, z, u, v, texture);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
* @param texture
* @param animationID
*/
void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, int animationID)
{
	glTexCoord2d((texture.getMaxU(animationID) - texture.getMinU(animationID)) * u + texture.getMinU(animationID), (texture.getMaxV(animationID) - texture.getMinV(animationID)) * v + texture.getMinV(animationID));
	glVertex3d(x, y, z);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
* @param texture
* @param animationID
* @param color
*/
void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, int animationID, Color color)
{
	glColor(color);
	glVertex(x, y, z, u, v, texture, animationID);
}

/**
* called after glBegin(...), sets a vertex with extra data
* @param x
* @param y
* @param z
* @param u
* @param v
* @param texture
* @param animationID
* @param r
* @param g
* @param b
* @param a
*/
void Engine::glVertex(double x, double y, double z, double u, double v, TexCoord texture, int animationID, double r, double g, double b, double a = 1)
{
	glColor(r, g, b, a);
	glVertex(x, y, z, u, v, texture, animationID);
}