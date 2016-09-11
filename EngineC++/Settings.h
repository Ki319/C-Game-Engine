#pragma once

#include <boost\filesystem.hpp>

class Settings
{
public:

	Settings();
	~Settings();

	int getNextWindow();
	boost::filesystem::path getResourcePath();
	boost::filesystem::path getTexturePath();
	boost::filesystem::path getModelPath();
	boost::filesystem::path getSoundPath();

	int getMipmap();

	void setNextWindow(int windowMode);

private:
	int nextWindowMode;
	boost::filesystem::path resourcePath;
	boost::filesystem::path texturePath;
	boost::filesystem::path modelPath;
	boost::filesystem::path soundPath;
};

//settings that the game is based off.
extern Settings *currentSettings;

