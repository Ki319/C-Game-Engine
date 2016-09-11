#include "Window.h"

void Window::run()
{
	//setting up the settings for the game to run on.
	loadSettings();

	isRunning = true;
	windowWidth = windowHeight = currentModifierKeys = 0;

	//checking if the mod keys and shift keys are initialized.
	if (modifierKeys.size() == 0)
		setupModKeys();

	if (shiftKeys.size() == 0)
		setupShiftKeys();

	//create the window instance
	if (glfwInit() || setup())
		return;

	//if debug is enabled then this calls handleDebug
	//doDebug

	//initialize default stuff for the window
	init();
	glDefaults();

	//set glfw time to 0 and set up default seed for random
	glfwSetTime(0);
	srand((unsigned int)std::time(NULL));

	//while loop for main update and render
	while (!glfwWindowShouldClose(windowInstance) && isRunning)
	{
		glfwMakeContextCurrent(windowInstance);

		//called to check if window needs to be recreated
		checkUpdateWindow();

		float delta = (float)glfwGetTime();
		glfwSetTime(0);

		//clear opengl buffer memory
		glClearBuffers();

		update(delta);

		//event handling
		glfwPollEvents();

		//handle key and mouse repeating input because GLFW is buggy :(
		handleKeyInput(delta);
		handleMouseInput(delta);

		render(delta);

		mousePosition.mouseDeltaX = mousePosition.mouseDeltaY = 0;
		//clear opengl memory
		glfwSwapBuffers(windowInstance);
	}
	//destroy the application
	destroy();
}

void Window::loadSettings()
{
	currentSettings = new Settings();
}

GLFWmonitor* Window::getMonitor()
{
	return glfwGetPrimaryMonitor();
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
	std::map<int, glm::vec2>::iterator it;
	//iterate through all keys actively being pressed
	for (it = keyboard.begin(); it != keyboard.end(); ++it)
	{
		int keyCode = it->first;
		glm::vec2 key = it->second;

		//check if key is still being pressed
		if (getKeyState(keyCode) == GLFW_PRESS)
		{
			//check if the timer for the next call of keyHeld
			if ((key.x -= delta) <= .00005f)
			{
				//call keyHeld, probably going to remove this soon and change it into float data due to unknown FPS from GLFW
				key.x = currentGui->keyHeld(keyCode, (int)key.y, getModKeys());

				//check if returned value is 0 or below
				if (key.x <= 0.00001f)
				{
					//if key isn't a modifier key then erase it, no call to the release function
					if (notModifierKey(keyCode))
					{
						keyboard.erase(keyCode);
					}
				}
				else
				{
					//add to the key's called amount
					key.y++;
				}
			}
		}
		else
		{
			//before performing anything else, if the key is a modifier key, 
			//then remove it from the modifier integer. Checks if key is caps_lock
			//since caps_lock is handled elsewhere.
			if (!notModifierKey(keyCode) && keyCode != GLFW_KEY_CAPS_LOCK)
			{
				removeModifierKey(keyCode);
			}

			//call the gui keyRelease function and erase the key from the keyboardPress map
			currentGui->keyRelease(keyCode, key.y, getModKeys());
			keyboard.erase(keyCode);
		}
	}
}

void Window::handleMouseInput(float delta)
{
	std::map<int, glm::vec4>::iterator it;
	for (it = mouse.begin(); it != mouse.end(); ++it)
	{
		int button = it->first;
		glm::vec4 position = it->second;

		if (getMouseState(button) == GLFW_PRESS)
		{
			if (!currentGui->mouseHeld(button, position.x, position.y, position.z, position.w))
			{
				mouse.erase(button);
			}
		}
		else
		{
			currentGui->mouseRelease(button, position.x, position.y, position.z, position.w);
			mouse.erase(button);
		}
	}
}

void Window::cursorMove(double mouseX, double mouseY)
{
	//updates mouse delta and position
	mousePosition.mouseDeltaX = (float)((mouseX - mousePosition.mouseX) * widthScaled());
	mousePosition.mouseDeltaY = (float)((mouseY - mousePosition.mouseY) * heightScaled());
	mousePosition.mouseX = (float)(mouseX * widthScaled());
	mousePosition.mouseY = (float)(mouseY * heightScaled());
}

void Window::mouseClick(int button, int action)
{
	if (action != GLFW_PRESS)
		return;

	if (mouse.find(button) != mouse.end())
	{
		mouse.erase(button);
	}

	if (currentGui->mouseClick(button, mousePosition.mouseX, mousePosition.mouseY))
	{
		glm::vec4 position(mousePosition.mouseX, mousePosition.mouseY, 0, 0);
		mouse[button] = position;
	}
}

void Window::mouseScroll(double xOffset, double yOffset)
{
	currentGui->mouseScroll((float)xOffset, (float)yOffset);
}

void Window::keyboardClick(int keyCode, int action)
{
	if (action != GLFW_PRESS)
		return;

	//if letter is between 'A' and 'Z', make sure that it is properly cased 
	//based on shift key or caps_lock
	if (keyCode >= 'A' && keyCode <= 'Z')
	{
		//shift towards caps if CAPS_LOCK is on, or shift is pressed
		keyCode = keyCode + 32 * !(currentModifierKeys & 16 || currentModifierKeys & 1);
	}
	if (!notModifierKey(keyCode))
	{
		if (keyCode == GLFW_KEY_CAPS_LOCK)
		{
			if ((currentModifierKeys & 16) == 1)
			{
				removeModifierKey(keyCode);
			}
			else
			{
				addModifierKey(keyCode);
			}
		}
		else
		{
			addModifierKey(keyCode);
		}
	}

	if (keyboard.find(keyCode) != keyboard.end())
	{
		keyboard.erase(keyCode);
	}

	float time = currentGui->keyPressed(keyCode, currentModifierKeys);

	if (time > 0.0001f)
	{
		glm::vec2 key(time, 0);
		keyboard[keyCode] = key;
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
		const GLFWvidmode *vidmode = glfwGetVideoMode(getMonitor());

		glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

		instance = glfwCreateWindow(vidmode->width, vidmode->height, getTitle(), getMonitor(), windowInstance);
	}
	//fullscreen
	else
	{
		const GLFWvidmode *vidmode = glfwGetVideoMode(getMonitor());
		instance = glfwCreateWindow(vidmode->width, vidmode->height,
			getTitle(), getMonitor(), windowInstance);
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
	windowWidthScale = (float)windowWidth / (float)defaultWindowWidth;
	windowHeightScale = (float)windowHeight / (float)defaultWindowHeight;
}

void Window::gl2d()
{
	glSetup2d(glm::vec4(0, 0, windowWidth, windowHeight),
		defaultWindowWidth, defaultWindowHeight,
		windowZScale);
}

void Window::gl3d(float fovy, float zNear, float zFar)
{
	glSetup3d(glm::vec4(0, 0, (float)windowWidth, (float)windowHeight),
		(float)windowWidth / (float)windowHeight,
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

GLFWwindow *Window::createAndCenter(int width, int height)
{
	GLFWwindow *instance = glfwCreateWindow(width, height, getTitle(), getMonitor(),
		!windowInstance ? nullptr : windowInstance);
	const GLFWvidmode *vidMode = glfwGetVideoMode(getMonitor());
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
	return currentModifierKeys;
}

int Window::getKeyState(int key)
{
	return glfwGetKey(windowInstance, key);
}

int Window::getKeyWithShift(int key)
{
	std::map<int, int>::iterator it = shiftKeys.find(key);
	return it != shiftKeys.end() ? it->second : key;
}

int Window::getMouseState(int button)
{
	return glfwGetMouseButton(windowInstance, button);
}

bool Window::notModifierKey(int key)
{
	return std::find(modifierKeys.begin(), modifierKeys.end(), key) == modifierKeys.end();
}

void Window::addModifierKey(int key)
{
	std::vector<int>::iterator it = std::find(modifierKeys.begin(), modifierKeys.end(), key);
	if (it != modifierKeys.end())
	{
		currentModifierKeys |= 1 << (it - modifierKeys.begin()) / 2;
	}
}

void Window::removeModifierKey(int key)
{
	std::vector<int>::iterator it = std::find(modifierKeys.begin(), modifierKeys.end(), key);
	if (it != modifierKeys.end())
	{
		currentModifierKeys &= ~(1 << (it - modifierKeys.begin()) / 2);
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
	modifierKeys.push_back(GLFW_KEY_LEFT_SHIFT);
	modifierKeys.push_back(GLFW_KEY_RIGHT_SHIFT);
	modifierKeys.push_back(GLFW_KEY_LEFT_CONTROL);
	modifierKeys.push_back(GLFW_KEY_RIGHT_CONTROL);
	modifierKeys.push_back(GLFW_KEY_LEFT_ALT);
	modifierKeys.push_back(GLFW_KEY_RIGHT_ALT);
	modifierKeys.push_back(GLFW_KEY_LEFT_SUPER);
	modifierKeys.push_back(GLFW_KEY_RIGHT_SUPER);
	modifierKeys.push_back(GLFW_KEY_CAPS_LOCK);
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

Window *getApplication(GLFWwindow *window)
{
	return static_cast<Window *>(glfwGetWindowUserPointer(window));
}

void glfwCursorBounds(GLFWwindow *window, int entered)
{
	getApplication(window)->cursorMoveBounds(entered == GL_TRUE);
}

void glfwCursorPos(GLFWwindow *window, double xpos, double ypos)
{
	getApplication(window)->cursorMove(xpos, ypos);
}

void glfwMouseButton(GLFWwindow *window, int button, int action, int mods)
{
	getApplication(window)->mouseClick(button, action);
}

void glfwMouseScroll(GLFWwindow *window, double xoffset, double yoffset)
{
	getApplication(window)->mouseScroll(xoffset, yoffset);
}

void glfwKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	getApplication(window)->keyboardClick(key, action);
}

void glfwWindowClose(GLFWwindow *window)
{
	getApplication(window)->windowClose();
}

void glfwWindowFocus(GLFWwindow *window, int focused)
{
	getApplication(window)->windowFocus(focused == GL_TRUE);
}

void glfwWindowIconify(GLFWwindow *window, int iconified)
{
	getApplication(window)->windowIconify(iconified == GL_TRUE);
}

void glfwWindowPos(GLFWwindow *window, int xpos, int ypos)
{
	getApplication(window)->windowPos(xpos, ypos);
}

void glfwWindowRefresh(GLFWwindow *window)
{
	getApplication(window)->windowRefresh();
}

void glfwWindowSize(GLFWwindow *window, int width, int height)
{
	getApplication(window)->windowSize(width, height);
}