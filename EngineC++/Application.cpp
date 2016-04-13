#include "Application.h"

void App::run()
{
	currentSettings = getSettings();
	setupWindowConsts(this);
	if (glfwInit() || setupWindow)
		return;

	init();
	//glDefaults();
	resetTimer;
	while (shouldClose)
	{
		float delta = getTimer;
		resetTimer;

		if (checkUpdateWindow())
			break;

		pollEvents;

		handleKeyInput(delta);

		//glClearBuffers();
		update(delta);
		render(delta);
		mousePosition.mouseDeltaX = mousePosition.mouseDeltaY = 0;
		swapBuffers;
	}

	destroyWindow;
}

bool App::checkUpdateWindow()
{
	if (currentSettings.getNextWindow() != currentWindowMode)
	{
		/*
		std::map<std::string, byte[]> textureData = getTextureData();
		if(setupWindow)
			return true;
		loadTextureData(textureData);
		currentGui.reload();
		*/
	}
	return false;
}

void App::handleKeyInput(float delta)
{
	for (std::map<int, glm::vec2*>::iterator it = keyboardPress.begin(); it != keyboardPress.end(); it++)
	{
		int key = it->first;
		glm::vec2 *keyboardVec = keyboardPress.at(key);
		if (getKey(key) == 1)
		{
			if ((keyboardVec->x -= delta) <= .005f)
			{
				keyboardVec->x = currentGui->keyHeld(key, keyboardVec->y, getModKeys) / 60.0f;
				if (keyboardVec->x <= 0)
				{
					if (notModKey(key))
					{
						keyboardPress.erase(key);
						delete keyboardVec;
					}
				}
				else
					keyboardVec->y++;
			}
		}
		else
		{
			if (!notModKey(key))
				removeModKey(key);
			currentGui->keyRelease(key, getModKeys);
			keyboardPress.erase(key);
			delete keyboardVec;
		}
	}
}

void App::setGui(Gui *newGui)
{
	if (!newGui)
	{
		closeWindow;
		return;
	}
	if (currentGui)
		delete currentGui;
	newGui->init();
	currentGui = newGui;
}

void App::cursorMove(double mouseX, double mouseY)
{
	mousePosition.mouseDeltaX = (mouseX - mousePosition.mouseX) * getWindowWidthScale;
	mousePosition.mouseDeltaY = (mouseY - mousePosition.mouseY) * getWindowHeightScale;
	mousePosition.mouseX = mouseX * getWindowWidthScale;
	mousePosition.mouseY = mouseY * getWindowHeightScale;
}

void App::cursorClick(int button, int action)
{
	switch (action)
	{
	case 1:
		currentGui->mouseClick(button);
		break;
	case 2:
		currentGui->mouseHeld(button);
		break;
	case 3:
		currentGui->mouseRelease(button);
	}
}