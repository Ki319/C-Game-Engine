#include "Application.h"

void App::run()
{
	application = this;
	createSettings();
	Window::setupConsts();
	if (glfwInit() || Window::setup())
		return;

	init();
	//glDefaults();
	resetTimer;
	srand(std::time(0));
	while (Window::shouldClose())
	{
		float delta = timer;
		resetTimer;

		if (checkUpdateWindow())
			break;

		pollEvents;

		handleKeyInput(delta);

		//glClearBuffers();
		update(delta);
		render(delta);
		mousePosition.mouseDeltaX = mousePosition.mouseDeltaY = 0;
		Window::swapBuffers();
	}

	Window::destroy();
}

bool App::checkUpdateWindow()
{
	if (currentSettings->getNextWindow() != currentWindowMode)
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
		if (Window::getKey(key) == 1)
		{
			if ((keyboardVec->x -= delta) <= .005f)
			{
				keyboardVec->x = currentGui->keyHeld(key, keyboardVec->y, Window::getModKeys()) / 60.0f;
				if (keyboardVec->x <= 0)
				{
					if (Window::notModKey(key))
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
			if (!Window::notModKey(key))
				Window::removeModKey(key);
			currentGui->keyRelease(key, Window::getModKeys());
			keyboardPress.erase(key);
			delete keyboardVec;
		}
	}
}

void App::setGui(Gui *newGui)
{
	if (!newGui)
	{
		Window::close();
		return;
	}
	if (currentGui)
		delete currentGui;
	newGui->init();
	currentGui = newGui;
}

void App::cursorMove(double mouseX, double mouseY)
{
	mousePosition.mouseDeltaX = (mouseX - mousePosition.mouseX) * Window::widthScaled();
	mousePosition.mouseDeltaY = (mouseY - mousePosition.mouseY) * Window::heightScaled();
	mousePosition.mouseX = mouseX * Window::widthScaled();
	mousePosition.mouseY = mouseY * Window::heightScaled();
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

void App::cursorScroll(double xOffset, double yOffset)
{
	currentGui->mouseScroll(xOffset, yOffset);
}

void App::keyboardClick(int key, int action, int mods)
{
	bool shiftFlag = (mods & 1) == 1;
	if (key >= 65 && key <= 90)
		key = key + 32 * (Window::getKey(GLFW_KEY_CAPS_LOCK) > 0 || shiftFlag ? 0 : 1);
	switch (action)
	{
	case 1:
	{
		float time = currentGui->keyPressed(key, mods) / 60.0f;
		if (Window::notModKey(key))
		{
			if (time > 0)
			{
				if (keyboardPress.find(key) != keyboardPress.end())
				{
					delete keyboardPress.at(key);
					keyboardPress.erase(key);
				}
				glm::vec2 *timerAndCalls = new glm::vec2(time, 0);
				keyboardPress[key] = timerAndCalls;
			}
		}
	}
	case 0:
		if (keyboardPress.find(key) == keyboardPress.end())
		{
			if (!Window::notModKey(key))
			{
				Window::removeModKey(key);
			}
			currentGui->keyRelease(key, mods);
		}
	}
}

void App::windowClose()
{
	
}

void App::windowSize(int width, int height)
{
	if (width + height != 0)
		Window::updateSize();
}

void App::update(float delta)
{
	currentGui->update(delta);
}

void App::render(float delta)
{
	currentGui->render(delta);
}

void App::createSettings()
{
	if (currentSettings)
		delete currentSettings;
	currentSettings = new Settings();
}

Gui *App::getCurrentScreen()
{
	return currentGui;
}

float App::getMouseX()
{
	return mousePosition.mouseX;
}

float App::getMouseY()
{
	return mousePosition.mouseY;
}

float App::getMouseDeltaX()
{
	return mousePosition.mouseDeltaX;
}

float App::getMouseDeltaY()
{
	return mousePosition.mouseDeltaY;
}

void Window::setupConsts()
{
	isRunning = true;
	windowWidth = windowHeight = currentModKeys = 0;
	modKeys.push_back(GLFW_KEY_LEFT_SHIFT);
	modKeys.push_back(GLFW_KEY_RIGHT_SHIFT);
	modKeys.push_back(GLFW_KEY_LEFT_CONTROL);
	modKeys.push_back(GLFW_KEY_RIGHT_CONTROL);
	modKeys.push_back(GLFW_KEY_LEFT_ALT);
	modKeys.push_back(GLFW_KEY_RIGHT_ALT);
	modKeys.push_back(GLFW_KEY_LEFT_SUPER);
	modKeys.push_back(GLFW_KEY_RIGHT_SUPER);
	shiftKeys[(int)'0'] = (int)')';
	shiftKeys[(int)'1'] = (int)'!';
	shiftKeys[(int)'2'] = (int)'@';
	shiftKeys[(int)'3'] = (int)'#';
	shiftKeys[(int)'4'] = (int)'$';
	shiftKeys[(int)'5'] = (int)'%';
	shiftKeys[(int)'6'] = (int)'^';
	shiftKeys[(int)'7'] = (int)'&';
	shiftKeys[(int)'8'] = (int)'*';
	shiftKeys[(int)'9'] = (int)'(';
	shiftKeys[(int)'`'] = (int)'~';
	shiftKeys[(int)'-'] = (int)'_';
	shiftKeys[(int)'='] = (int)'+';
	shiftKeys[(int)'['] = (int)'{';
	shiftKeys[(int)']'] = (int)'}';
	shiftKeys[(int)';'] = (int)':';
	shiftKeys[(int)'\''] = (int)'"';
	shiftKeys[(int)']'] = (int)'<';
	shiftKeys[(int)'.'] = (int)'>';
	shiftKeys[(int)'/'] = (int)'?';
	shiftKeys[(int)'\\'] = (int)'|';
}

bool Window::setup()
{
	GLFWwindow *instance;
	if (currentSettings->getNextWindow() == 0)
	{
		instance = application->createWindow();
	}
	else if (currentSettings->getNextWindow() == 1)
	{
		const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);
		instance = glfwCreateWindow(vidmode->width, vidmode->height, "", glfwGetPrimaryMonitor(), windowInstance);
	}
	else
	{
		const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		instance = glfwCreateWindow(vidmode->width, vidmode->height, "", glfwGetPrimaryMonitor(), windowInstance);
	}
	currentWindowMode = currentSettings->getNextWindow();
	if (!instance)
	{
		glfwTerminate();
		return false;
	}
	if (windowInstance)
	{
		glfwDestroyWindow(windowInstance);
	}
	windowInstance = instance;
	setEvents();
	glfwMakeContextCurrent(windowInstance);
	glfwSwapInterval(1);
	updateSize();
	glfwShowWindow(windowInstance);
	return instance != nullptr;
}

void Window::setEvents()
{
	glfwSetCursorEnterCallback(windowInstance, &cursorBounds);
	glfwSetCursorPosCallback(windowInstance, &cursorPos);
	glfwSetMouseButtonCallback(windowInstance, &cursorButton);
	glfwSetScrollCallback(windowInstance, &cursorScroll);
	glfwSetKeyCallback(windowInstance, &keyboard);
	glfwSetWindowCloseCallback(windowInstance, &windowClose);
	glfwSetWindowFocusCallback(windowInstance, &windowFocus);
	glfwSetWindowIconifyCallback(windowInstance, &windowIconify);
	glfwSetWindowPosCallback(windowInstance, &windowPos);
	glfwSetWindowRefreshCallback(windowInstance, &windowRefresh);
	glfwSetWindowSizeCallback(windowInstance, &windowSize);
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(windowInstance) && isRunning;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(windowInstance);
}

void Window::updateSize()
{
	glfwGetWindowSize(windowInstance, &windowWidth, &windowHeight);
	windowWidthScale = windowWidth / defaultWindowWidth;
	windowHeightScale = windowHeight / defaultWindowHeight;
}

void Window::gl2d()
{
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, defaultWindowWidth, defaultWindowHeight, 0, -windowZScale, windowZScale);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Window::gl3d(float fovy, float zNear, float zFar)
{
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ymax = zNear * tan(fovy * PI / 360.0);
	double ymin = -ymax;
	double xmin = ymin * windowWidth / windowHeight;
	double xmax = ymax * windowWidth / windowHeight;
	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Window::close()
{
	isRunning = false;
}

void Window::destroy()
{
	glfwDestroyWindow(windowInstance);
	glfwTerminate();
}

GLFWwindow *Window::createAndCenter(int width, int height, const char *title, GLFWmonitor *monitor)
{
	GLFWwindow *instance = glfwCreateWindow(width, height, title, monitor, !windowInstance ? nullptr : windowInstance);
	const GLFWvidmode *vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(instance, (vidMode->width - width) / 2, (vidMode->height - height) / 2);
	return instance;
}

int Window::width()
{
	return windowWidth;
}

int Window::height()
{
	return windowHeight;
}

float Window::widthScaled()
{
	return windowWidthScale;
}

void Window::setWidthScaled(int defaultWidth)
{
	defaultWindowWidth = defaultWidth;
}

float Window::heightScaled()
{
	return windowHeightScale;
}

void Window::setHeightScaled(int defaultHeight)
{
	defaultWindowHeight = defaultHeight;
}

float Window::zLength()
{
	return windowZScale;
}

void Window::setZLength(float defaultZScale)
{
	windowZScale = defaultZScale;
}

int Window::getModKeys()
{
	return currentModKeys;
}

int Window::getKey(int key)
{
	return glfwGetKey(windowInstance, key);
}

int Window::getKeyWithShift(int key)
{
	return shiftKeys.find(key) != shiftKeys.end() ? shiftKeys.at(key) : key;
}

bool Window::notModKey(int key)
{
	return std::find(modKeys.begin(), modKeys.end(), key) == modKeys.end();
}

void Window::addModKey(int key)
{
	for (unsigned int i = 0; i < modKeys.size(); i += 2)
	{
		if (key == modKeys.at(i) || key == modKeys.at(i + 1))
		{
			currentModKeys += (int)(pow(2, i / 2));
			break;
		}
	}
}

void Window::removeModKey(int key)
{
	for (unsigned int i = 0; i < modKeys.size(); i += 2)
	{
		if (key == modKeys.at(i) || key == modKeys.at(i + 1))
		{
			currentModKeys &= ~(int)(pow(2, i / 2));
			break;
		}
	}
}