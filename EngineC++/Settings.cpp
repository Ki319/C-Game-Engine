#include "Settings.h"

Settings::Settings()
{

}

Settings::~Settings()
{

}

int Settings::getNextWindow()
{
	return nextWindowMode;
}

boost::filesystem::path Settings::getResourcePath()
{
	return resourcePath;
}

boost::filesystem::path Settings::getTexturePath()
{
	return resourcePath;
}

boost::filesystem::path Settings::getModelPath()
{
	return modelPath;
}

boost::filesystem::path Settings::getSoundPath()
{
	return soundPath;
}

void Settings::setNextWindow(int windowMode)
{
	nextWindowMode = windowMode;
}