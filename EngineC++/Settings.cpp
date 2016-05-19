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

fs::path Settings::getResourcePath()
{
	resourcePath;
}

fs::path Settings::getTexturePath()
{
	resourcePath;
}

fs::path Settings::getModelPath()
{
	return modelPath;
}

fs::path Settings::getSoundPath()
{
	return soundPath;
}

void Settings::setNextWindow(int windowMode)
{
	nextWindowMode = windowMode;
}