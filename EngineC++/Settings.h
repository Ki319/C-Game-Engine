#pragma once

#include "pch.h"

class Settings
{
public:

	Settings();
	~Settings();

	int getNextWindow();
	fs::path getResourcePath();
	fs::path getTexturePath();
	fs::path getModelPath();
	fs::path getSoundPath();

	void setNextWindow(int windowMode);

private:
	int nextWindowMode;
	fs::path resourcePath;
	fs::path texturePath;
	fs::path modelPath;
	fs::path soundPath;

};

