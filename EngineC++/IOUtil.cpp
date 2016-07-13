#include "IOUtil.h"

bool readImage(std::string file, int &width, int &height, bool &hasAlpha, GLubyte **data)
{
	png_structp png;
	png_infop info;

	FILE *fileLoc;

	errno_t err;

	if (!(err = fopen_s(&fileLoc, file.c_str(), "rb")))
	{
		fprintf(stderr, "Cannot open image file %s!\n", file);
		return false;
	}

	if (!(png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)))
	{
		fclose(fileLoc);
		return false;
	}

	if (!(info = png_create_info_struct(png)))
	{
		fclose(fileLoc);
		png_destroy_read_struct(&png, NULL, NULL);
		return false;
	}

	if (setjmp(png_jmpbuf(png)))
	{
		png_destroy_read_struct(&png, &info, NULL);
		fclose(fileLoc);
		return false;
	}

	png_init_io(png, fileLoc);

	png_read_png(png, info, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
	
	width = png_get_image_width(png, info);
	height = png_get_image_height(png, info);

	unsigned int rowBytes = png_get_rowbytes(png, info);
	*data = (unsigned char *)malloc(rowBytes * height);
	
	png_bytepp rows = png_get_rows(png, info);

	for (int i = 0; i < height; i++)
	{
		memcpy(*data + (rowBytes * (height - 1 - i)), rows[i], rowBytes);
	}

	png_destroy_read_struct(&png, &info, NULL);
	fclose(fileLoc);

	return true;
}

bool writeImage(std::string file, int width, int height, GLubyte **data)
{
	png_structp png;
	png_infop info;

	FILE *fileLoc;

	errno_t err;
	if (!(err = fopen_s(&fileLoc, file.c_str(), "wb")))
	{
		fprintf(stderr, "Cannot open image file %s!\n", file);
		return false;
	}

	if (!(png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)))
	{
		fclose(fileLoc);
		return false;
	}

	if (!(info = png_create_info_struct(png)))
	{
		fclose(fileLoc);
		png_destroy_write_struct(&png, NULL);
		return false;
	}

	if (setjmp(png_jmpbuf(png)))
	{
		png_destroy_write_struct(&png, &info);
		fclose(fileLoc);
		return false;
	}

	png_init_io(png, fileLoc);

	png_set_IHDR(png, info, width, height, 8, 
		PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, 
		PNG_FILTER_TYPE_DEFAULT);

	png_write_info(png, info);

	png_write_image(png, data);
	png_write_end(png, NULL);

	png_destroy_write_struct(&png, &info);
	fclose(fileLoc);

	return true;
}