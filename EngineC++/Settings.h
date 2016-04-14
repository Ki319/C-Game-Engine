#include "pch.h"

struct Settings
{
	int nextWindowMode;
	std::string textureDirectory;
	std::string modelDirectory;
	std::string soundDirectory;

	std::string getTextureDirectory()
	{
		return textureDirectory;
	}

	std::string getModelDirectory()
	{
		return modelDirectory;
	}

	std::string getSoundDirectory()
	{
		return soundDirectory;
	}

	int getNextWindow()
	{
		return nextWindowMode;
	}

	void setNextWindow(int windowMode)
	{
		nextWindowMode = windowMode;
	}
	
};

