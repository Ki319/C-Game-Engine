#pragma once

#include "stdafx.h"
#include "OpenGL.h"
#include "Textures.h"

using namespace Engine;

class Gui;

struct Mouse
{
	float mouseX;
	float mouseY;
	float mouseDeltaX;
	float mouseDeltaY;
};

class Window
{
public:

	//Function that initializes the games code
	void run();


	//Called for updating the games logic, this is on the base thread of the render function
	virtual void update(float delta);
	
	//Called for updating the games renders, this is on the base thread of the update function
	virtual void render(float delta);

	
	//Called when the cursor moves within the bounds of the application, and the application 
	//is focused on.
	virtual void cursorMove(double mouseX, double mouseY);
	
	//Called when the a click action on the application is performed.
	virtual void mouseClick(int button, int action);
	
	//Called when the mouse scrolls on the scroll wheel.
	virtual void mouseScroll(double xOffset, double yOffset);

	
	//Called when the keyboard is clicked.
	virtual void keyboardClick(int keyCode, int action);

	
	//Called anytime the windows size is adjusted.
	virtual void windowSize(int width, int height);

	
	//Called anytime the window is changed from windowed, or borderless, or fullscreen to
	//any of the other two described.
	bool setup();
	
	//Updates the windows variables measuring width and height.
	void updateSize();

	
	//Default way to setup a 2d rendering environment.
	void gl2d();
	
	//Default way to setup a 3d rendering environment.
	void gl3d(float fovy, float zNear, float zFar);

	
	//Called when one desires to shutdown the application.
	void close();
	
	//Changes the gui to a new one, if the newGui variable is a nullptr then the application
	//will set to close.
	void setGui(Gui *newGui);
	
	//Current gui.
	Gui *getCurrentScreen();

	
	//Width of the Window.
	int width();
	
	//Height of the Application.
	int height();
	
	//The ratio of the default width to the actual width.
	float widthScaled();
	
	//The ratio of the default height to the actual height.
	float heightScaled();
	
	//The 2d environment z scale max, allowing from -zscale to zscale layers.
	float zScale();

	
	//Gets all currently activated mod keys.
	int getModKeys();
	
	//Returns whether a key is being pressed (GLFW_PRESS) or not (GLFW_RELEASE).
	int getKeyState(int key);
	
	//Returns the key that is given when the shift key has been pressed.
	int getKeyWithShift(int key);

	//Returns whether a mouse button is being pressed (GLFW_PRESS) or not (GLFW_RELEASE).
	int getMouseState(int button);

	//Returns true if the key being pressed is not a modifier key.
	bool notModifierKey(int key);

	
	//Returns the x position of the mouse.
	float mouseX();
	
	//Returns the y position of the mouse.
	float mouseY();
	
	//Returns the change in the x position with the mouse since the last update.
	float mouseDeltaX();
	
	//Returns the change in the y position with the mouse since the last update.
	float mouseDeltaY();

	
	//Called when the cursor leaves the focused application and re-enters
	virtual void cursorMoveBounds(bool entered) {}

	
	//Called after a window has been closed.
	virtual void windowClose() {}

	//Called when the window changes focus.
	virtual void windowFocus(bool focused) {}

	//Called when the window changes iconification (minimized or not).
	virtual void windowIconify(bool iconified) {}

	//Called when the actual position of the window moves.
	virtual void windowPos(int xPos, int yPos) {}

	//Called whenever the window is refreshed.
	virtual void windowRefresh() {}

	//Title of the application.
	virtual const char *getTitle() = 0;

protected:

	//the map of all keys being pressed, the value returned from a key gives two values in
	//in vector format. First number is how long until the next call to the function
	//keyPressed in Gui. Second number is how many times the function keyPressed has been
	//called since the first time.
	std::map<int, glm::vec2> keyboard = std::map<int, glm::vec2>();

	//the map of all mouse button active, the value returned from a mouse button gives four
	//values in vector format. First number is the first x coordinate. The second number
	//is the first y coordinate.
	std::map<int, glm::vec2> mouse = std::map<int, glm::vec2>();

	//the current gui that recieves calls for a variety of things including input, update,
	//and render
	Gui *currentGui;

	//position of the mouse
	Mouse mousePosition;

	//Called for initializing special details involved with the window.
	virtual void init() = 0;
	
	virtual GLFWwindow* createDefaultWindow(int state);

	//Called for generating the windowed version of the application.
	virtual GLFWwindow *createWindow(int state) = 0;

	//Called as an easy way to generate a centered window for the user.
	GLFWwindow *createCenteredWindow(int width, int height);

	//Called for getting the monitor that the application.
	virtual GLFWmonitor* getMonitor();
	
	//Function that allows the user to change whether they want the default settings object,
	//or anything that is a sub class of it.
	virtual void loadSettings();

	
	//Called for changing the default width of the game.
	void setWidthScaled(int defaultWidth);
	
	//Called for changing the default height of the game.
	void setHeightScaled(int defaultHeight);

	//Called for changing the amount of layers in a 2d environment.
	void setZScale(float defaultZScale);


	//Called for adding a mod key to the current list.
	void addModifierKey(int key);

	//Called for removing a mod key from the current list.
	void removeModifierKey(int key);

	//Called when the application is finally shutdown.
	void destroy();

private:

	//The list of all mod keys available on the keyboard.
	//These are shift, control, alt, and super (which I'm not exactly sure of).
	static std::vector<int> modifierKeys;

	//The map of all keys and their appropriate keys that correspond with them
	//when the shift key is held down.
	static std::map<int, int> shiftKeys;

	//Used as a means to add all the mod keys to the static environment of a project.
	static void setupModKeys();

	//Used as a means to add all the shift keys to the static environment of a project.
	static void setupShiftKeys();


	//Instance of the window, non-static in case of the off chance a project needs two
	//windows open at the same time.
	GLFWwindow *windowInstance;

	//Whether the game should shut down or not.
	bool isRunning;


	//width of the window
	int windowWidth;

	//height of the window
	int windowHeight;

	//ratio of default width / width
	float windowWidthScale;

	//ratio of default height / height
	float windowHeightScale;

	//default width that the rendering environment is based on
	int defaultWindowWidth;

	//default height that the rendering environment is based on
	int defaultWindowHeight;

	//layers in a 2d environment, measured by windowZScale * 2 + 1
	float windowZScale;


	//The currently activated modifier keys that are being pressed down.
	int currentModifierKeys;

	//The current window mode, 0 -> windowed, 1 -> borderless, 2 -> fullscreen
	int currentWindowMode;

	//Called after the window mode is updated, transfers all textures and data that
	//are tied to the window to the next window.
	bool checkUpdateWindow();

	//Called from the run function to manage the keys that are currently being pressed.
	void handleKeyInput(float delta);

	//Called from the run function to manage the mouse buttons that are currently active.
	void handleMouseInput(float delta);

	//Sets the events needed to manage the window and input.
	void setEvents();
};

class Gui
{
public:

	Gui(Window *application);
	Gui(Gui *gui);

	virtual void update(float delta);

	~Gui() {}

	virtual void init() {}

	virtual void render(float delta) {}

	virtual bool mouseClick(int button, float x, float y) { return false; }
	virtual bool mouseHeld(int button, float x, float y, float deltaX, float deltaY) { return false; }
	virtual void mouseRelease(int button, float x, float y, float deltaX, float deltaY) {}
	virtual void mouseScroll(float xOffset, float yOffset) {}

	virtual float keyPressed(int key, int keyMods) { return 0.0f; }
	virtual float keyHeld(int key, int timesCalled, int keyMods) { return 120000.0f; }
	virtual void keyRelease(int key, int timesCalled, int keyMods) {}

	virtual void reload() {}
protected:

	Window *window;
	Gui *parent;

	float ticksExisted;

	Gui *getParent();

	virtual void reinit() {}
};

//Getting a window object from a GLFWwindow *instance
Window *getApplication(GLFWwindow *window);

//the really sketchy way to manipulate GLFW and make it do things my way.

void glfwCursorBounds(GLFWwindow *window, int entered);

void glfwCursorPos(GLFWwindow *window, double xpos, double ypos);

void glfwMouseButton(GLFWwindow *window, int button, int action, int mods);

void glfwMouseScroll(GLFWwindow *window, double xoffset, double yoffset);

void glfwKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods);

void glfwWindowClose(GLFWwindow *window);

void glfwWindowFocus(GLFWwindow *window, int focused);

void glfwWindowIconify(GLFWwindow *window, int iconified);

void glfwWindowPos(GLFWwindow *window, int xpos, int ypos);

void glfwWindowRefresh(GLFWwindow *window);

void glfwWindowSize(GLFWwindow *window, int width, int height);