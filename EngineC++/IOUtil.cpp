#include "IOUtil.h"

bool read(boost::filesystem::path file, std::string &content)
{
	FILE *fileLoc;
	errno_t err;

	if (!(err = fopen_s(&fileLoc, boost::filesystem::complete(file).string().c_str(), "rb")))
	{
		fprintf(stderr, "Cannot open file %s!\n", file.string().c_str());
		return false;
	}

	fseek(fileLoc, 0, SEEK_END);
	content.resize(ftell(fileLoc));
	rewind(fileLoc);
	fread(&content[0], 1, content.size(), fileLoc);
	fclose(fileLoc);

	return true;
}

bool readLines(boost::filesystem::path file, std::vector<std::string> &lines)
{
	std::string content;
	if (!read(file, content))
		return false;
	boost::split(lines, content, boost::is_any_of("\n"));
	return true;
}

bool readImage(boost::filesystem::path file, Image &image)
{
	png_structp png;
	png_infop info;

	int width, height;
	GLubyte *data;

	std::string filename = boost::filesystem::complete(file).string();
	FILE *fileLoc;

	errno_t err;

	if (!(err = fopen_s(&fileLoc, filename.c_str(), "rb")))
	{
		fprintf(stderr, "Cannot open image file %s!\n", file.string().c_str());
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

	unsigned int rowBytes = (unsigned int) png_get_rowbytes(png, info);
	data = new GLubyte[rowBytes * height];
	
	png_bytepp rows = png_get_rows(png, info);

	for (int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < rowBytes; j++)
		{
			data[i * rowBytes + j] = rows[i][j];
		}
	}

	png_destroy_read_struct(&png, &info, NULL);
	fclose(fileLoc);

	image.init(data, width, height);

	return true;
}

bool writeImage(boost::filesystem::path file, Image image)
{
	png_structp png;
	png_infop info;

	std::string filename = boost::filesystem::complete(file).string();
	FILE *fileLoc;

	errno_t err;
	if (!(err = fopen_s(&fileLoc, filename.c_str(), "wb")))
	{
		fprintf(stderr, "Cannot open image file %s!\n", file.string().c_str());
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

	png_set_IHDR(png, info, image.width(), image.height(), 8, 
		PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, 
		PNG_FILTER_TYPE_DEFAULT);

	png_write_info(png, info);
	png_write_image(png, &image.imageData);
	png_write_end(png, NULL);

	png_destroy_write_struct(&png, &info);
	fclose(fileLoc);

	return true;
}