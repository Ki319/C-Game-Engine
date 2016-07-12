#include "Window.h"

void Window::run()
{
	loadSettings();

	isRunning = true;
	windowWidth = windowHeight = currentModKeys = 0;

	if (modKeys.size() == 0)
		setupModKeys();

	if (shiftKeys.size() == 0)
		setupShiftKeys();
	
	if (glfwInit() || setup())
		return;

	init();
	glDefaults();

	glfwSetTime(0);
	srand(std::time(0));

	while (!glfwWindowShouldClose(windowInstance) && isRunning)
	{
		glfwMakeContextCurrent(windowInstance);

		float delta = glfwGetTime();
		glfwSetTime(0);

		if (checkUpdateWindow())
			break;

		glfwPollEvents();

		handleKeyInput(delta);

		glClearBuffers();

		update(delta);
		render(delta);

		mousePosition.mouseDeltaX = mousePosition.mouseDeltaY = 0;
		glfwSwapBuffers(windowInstance);
	}

	destroy();
}

void Window::loadSettings()
{
	currentSettings = new Settings();
}

void Window::update(float delta)
{
	currentGui->update(delta);
}

void Window::render(float delta)
{
	currentGui->render(delta);
}

bool Window::checkUpdateWindow()
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

void Window::handleKeyInput(float delta)
{
	for (std::map<int, glm::vec2*>::iterator it = keyboardPress.begin(); it != keyboardPress.end(); it++)
	{
		int key = it->first;
		glm::vec2 *keyboardVec = keyboardPress.at(key);
		if (getKey(key) == 1)
		{
			if ((keyboardVec->x -= delta) <= .005f)
			{
				keyboardVec->x = currentGui->keyHeld(key, keyboardVec->y, getModKeys()) / 60.0f;
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
			currentGui->keyRelease(key, getModKeys());
			keyboardPress.erase(key);
			delete keyboardVec;
		}
	}
}

void Window::cursorMove(double mouseX, double mouseY)
{
	mousePosition.mouseDeltaX = (mouseX - mousePosition.mouseX) * widthScaled();
	mousePosition.mouseDeltaY = (mouseY - mousePosition.mouseY) * heightScaled();
	mousePosition.mouseX = mouseX * widthScaled();
	mousePosition.mouseY = mouseY * heightScaled();
}

void Window::mouseClick(int button, int action)
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

void Window::mouseScroll(double xOffset, double yOffset)
{
	currentGui->mouseScroll(xOffset, yOffset);
}

void Window::keyboardClick(int key, int action, int mods)
{
	bool shiftFlag = (mods & 1) == 1;
	if (key >= 65 && key <= 90)
		key = key + 32 * (getKey(GLFW_KEY_CAPS_LOCK) > 0 || shiftFlag ? 0 : 1);
	switch (action)
	{
	case 1:
	{
		float time = currentGui->keyPressed(key, mods) / 60.0f;
		if (notModKey(key))
		{
			if (time > 0)
			{
				if (keyboardPress.find(key) != keyboardPress.end())
				{
					keyboardPress.erase(key);
					delete keyboardPress[key];
				}
				glm::vec2 *timerAndCalls = new glm::vec2(time, 0);
				keyboardPress[key] = timerAndCalls;
			}
		}
	}
	case 0:
		if (keyboardPress.find(key) == keyboardPress.end())
		{
			if (!notModKey(key))
			{
				removeModKey(key);
			}
			currentGui->keyRelease(key, mods);
		}
	}
}

void Window::windowSize(int width, int height)
{
	if (width + height != 0)
		updateSize();
}

bool Window::setup()
{
	GLFWwindow *instance;

	//regular window, not fullscreen or borderless fullscreen
	if (currentSettings->getNextWindow() == 0)
	{
		instance = createWindow();
	}
	//fullscreen borderless
	else if (currentSettings->getNextWindow() == 1)
	{
		const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

		instance = glfwCreateWindow(vidmode->width, vidmode->height, getTitle(), glfwGetPrimaryMonitor(), windowInstance);
	}
	//fullscreen
	else
	{
		const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		instance = glfwCreateWindow(vidmode->width, vidmode->height, getTitle(), glfwGetPrimaryMonitor(), windowInstance);
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
	glfwSetWindowUserPointer(windowInstance, this);
	glfwSetCursorEnterCallback(windowInstance, &glfwCursorBounds);
	glfwSetCursorPosCallback(windowInstance, &glfwCursorPos);
	glfwSetMouseButtonCallback(windowInstance, &glfwMouseButton);
	glfwSetScrollCallback(windowInstance, &glfwMouseScroll);
	glfwSetKeyCallback(windowInstance, &glfwKeyboard);
	glfwSetWindowCloseCallback(windowInstance, &glfwWindowClose);
	glfwSetWindowFocusCallback(windowInstance, &glfwWindowFocus);
	glfwSetWindowIconifyCallback(windowInstance, &glfwWindowIconify);
	glfwSetWindowPosCallback(windowInstance, &glfwWindowPos);
	glfwSetWindowRefreshCallback(windowInstance, &glfwWindowRefresh);
	glfwSetWindowSizeCallback(windowInstance, &glfwWindowSize);
}

void Window::updateSize()
{
	glfwGetWindowSize(windowInstance, &windowWidth, &windowHeight);
	windowWidthScale = windowWidth / defaultWindowWidth;
	windowHeightScale = windowHeight / defaultWindowHeight;
}

void Window::gl2d()
{
	glSetup2d(glm::vec4(0, 0, windowWidth, windowHeight),
		defaultWindowWidth, defaultWindowHeight,
		windowZScale);
}

void Window::gl3d(float fovy, float zNear, float zFar)
{
	glSetup3d(glm::vec4(0, 0, windowWidth, windowHeight),
		windowWidth / windowHeight,
		fovy, zNear, zFar);
}

void Window::setToClose()
{
	isRunning = false;
}

void Window::destroy()
{
	glfwDestroyWindow(windowInstance);
	glfwTerminate();
}

GLFWwindow *Window::createAndCenter(int width, int height, GLFWmonitor *monitor)
{
	GLFWwindow *instance = glfwCreateWindow(width, height, getTitle(), monitor, !windowInstance ? nullptr : windowInstance);
	const GLFWvidmode *vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(instance, (vidMode->width - width) / 2, (vidMode->height - height) / 2);
	return instance;
}

void Window::setGui(Gui *newGui)
{
	if (!newGui)
	{
		setToClose();
		return;
	}
	if (currentGui)
		delete currentGui;
	newGui->init();
	currentGui = newGui;
}


Gui *Window::getCurrentScreen()
{
	return currentGui;
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

float Window::zScale()
{
	return windowZScale;
}

void Window::setZScale(float defaultZScale)
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

float Window::mouseX()
{
	return mousePosition.mouseX;
}

float Window::mouseY()
{
	return mousePosition.mouseY;
}

float Window::mouseDeltaX()
{
	return mousePosition.mouseDeltaX;
}

float Window::mouseDeltaY()
{
	return mousePosition.mouseDeltaY;
}

void Window::setupModKeys()
{
	modKeys.push_back(GLFW_KEY_LEFT_SHIFT);
	modKeys.push_back(GLFW_KEY_RIGHT_SHIFT);
	modKeys.push_back(GLFW_KEY_LEFT_CONTROL);
	modKeys.push_back(GLFW_KEY_RIGHT_CONTROL);
	modKeys.push_back(GLFW_KEY_LEFT_ALT);
	modKeys.push_back(GLFW_KEY_RIGHT_ALT);
	modKeys.push_back(GLFW_KEY_LEFT_SUPER);
	modKeys.push_back(GLFW_KEY_RIGHT_SUPER);
}

void Window::setupShiftKeys()
{
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

Gui::Gui(Window *application) :
	window(application), parent(nullptr), ticksExisted(0) {}

Gui::Gui(Gui *gui)
{
	window = gui->window;
	parent = gui;
	ticksExisted = 0;
}

void Gui::update(float delta)
{
	ticksExisted += delta;
}

Gui *Gui::getParent()
{
	return parent;
}

void glfwCursorBounds(GLFWwindow *window, int entered)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->cursorMoveBounds(entered == GL_TRUE);
}

void glfwCursorPos(GLFWwindow *window, double xpos, double ypos)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->cursorMove(xpos, ypos);
}

void glfwMouseButton(GLFWwindow *window, int button, int action, int mods)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->mouseClick(button, action);
}

void glfwMouseScroll(GLFWwindow *window, double xoffset, double yoffset)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->mouseScroll(xoffset, yoffset);
}

void glfwKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->keyboardClick(key, action, mods);
}

void glfwWindowClose(GLFWwindow *window)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->windowClose();
}

void glfwWindowFocus(GLFWwindow *window, int focused)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->windowFocus(focused == GL_TRUE);
}

void glfwWindowIconify(GLFWwindow *window, int iconified)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->windowIconify(iconified == GL_TRUE);
}

void glfwWindowPos(GLFWwindow *window, int xpos, int ypos)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->windowPos(xpos, ypos);
}

void glfwWindowRefresh(GLFWwindow *window)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->windowRefresh();
}

void glfwWindowSize(GLFWwindow *window, int width, int height)
{
	Window *application = static_cast<Window *>(glfwGetWindowUserPointer(window));
	application->windowSize(width, height);
}