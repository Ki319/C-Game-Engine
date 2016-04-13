#include "Settings.h"

Settings::Settings(std::string resourceLocation)
{
	textureDirectory = resourceLocation.append("/textures");
	modelDirectory = resourceLocation.append("/models");
	soundDirectory = resourceLocation.append("/sounds");
}

Settings::~Settings()
{
}
