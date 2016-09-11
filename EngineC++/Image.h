#pragma once

#include <GL\glew.h>

struct Image
{
public:
	GLubyte *imageData;

	Image();
	Image(GLuint width, GLuint height);
	Image(GLubyte *data, GLuint width, GLuint height);
	~Image();

	void init(GLuint width, GLuint height);
	void init(GLubyte *data, GLuint width, GLuint height);

	void resize(int newWidth, int newHeight, bool clear = false);
	void putImage(Image image, int posX, int posY);
	void putImage(Image image, int posX, int posY, int offX, int offY, int width, int height);

	GLuint width();
	GLuint height();

private:
	GLuint imageWidth;
	GLuint imageHeight;
};