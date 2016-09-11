#include "Image.h"

Image::Image() 
{
	imageData = nullptr;
}

Image::Image(GLuint width, GLuint height)
{
	imageData = new GLubyte[width * height * 4];
}

Image::Image(GLubyte *data, GLuint width, GLuint height)
{
	imageData = data;
	imageWidth = width;
	imageHeight = height;
}

Image::~Image()
{
	if(imageData != nullptr)
		delete[] imageData;
}

void Image::init(GLuint width, GLuint height)
{
	imageData = new GLubyte[width * height * 4];
}

void Image::init(GLubyte *data, GLuint width, GLuint height)
{
	imageData = data;
	imageWidth = width;
	imageHeight = height;
}

void Image::resize(int newWidth, int newHeight, bool clear)
{
	if (clear)
	{
		delete[] imageData;
		imageData = new GLubyte[newWidth * newHeight];
		imageWidth = newWidth;
		imageHeight = newHeight;
	}
	else
	{
		GLubyte *newImageData = new GLubyte[newWidth * newHeight * 4];
		for (int i = 0; i < imageWidth && i < newWidth; i++)
		{
			for (int j = 0; j < imageHeight && j < newHeight; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					int location = (i * imageWidth + j) * 4 + k;
					int newLocation = (i * newWidth + j) * 4 + k;
					newImageData[newLocation] = imageData[location];
				}
			}
		}
		delete[] imageData;
		imageData = newImageData;
	}
}

void Image::putImage(Image image, int posX, int posY)
{
	putImage(image, posX, posY, 0, 0, image.width(), image.height());
}

void Image::putImage(Image image, int posX, int posY, int offX, int offY, int width, int height)
{
	for (int i = 0; i < width && i + offX < image.width() && i + posX < imageWidth; i++)
	{
		for (int j = 0; j < height && j + offY < image.height() && j + posY < imageHeight; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int location = ((i + offX) * imageWidth + j + offX) * 4 + k;
				int otherLocation = ((i + posX) * image.width() + j + posY) * 4 + k;
				imageData[location] = image.imageData[otherLocation];
			}
		}
	}
}

GLuint Image::width()
{
	return imageWidth;
}

GLuint Image::height()
{
	return imageHeight;
}