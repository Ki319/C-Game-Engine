#include "AtlasTexture.h"

Image AtlasTexture::load(fs::path fileLoc)
{
	Image image = Texture::load(fileLoc);
	if (image.imageData == nullptr)
		return image;

	fs::path path = fileLoc.replace_extension("info");
	std::vector<std::string> lines;
	std::vector<std::string>::iterator lineIt;
	std::vector<std::string> partions;
	std::vector<std::string>::iterator partionIt;

	if (fs::is_regular_file(path))
	{
		if (!readLines(path, lines))
			return Image();

		for (lineIt = lines.begin(); lineIt != lines.end(); ++lineIt)
		{
			boost::split(partions, *lineIt, boost::is_any_of(" "));
			if (partions.size() == 0)
				continue;
			float data[4] = {0, 0, 0, 0};
			int aniData[2] = { 0, 0 };
			for (partionIt = partions.begin() + 1; partionIt != partions.end(); ++partionIt)
			{
				if (partionIt - partions.begin() - 1 < 4)
				{
					data[partionIt - partions.begin() - 1] = (float) atof((*partionIt).c_str());
				}
				else
				{
					aniData[partionIt - partions.begin() - 5] = atoi((*partionIt).c_str());
				}
			}
			textures[partions[0]] = TexCoord(data, aniData);
		}
	}

	return image;
}

bool AtlasTexture::bind(std::string subtexture)
{
	return false;
}