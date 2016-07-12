#pragma once

#include "pch.h"
#include "Settings.h"
#include "OpenGL.h"

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
	virtual void keyboardClick(int key, int action, int mods);

	
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
	void setToClose();
	
	//Called when the application is finally shutdown.
	void destroy();

	
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
	
	//Returns whether a key is being pressed (1) or not (0).
	int getKey(int key);
	
	//Returns the key that is given when the shift key has been pressed.
	int getKeyWithShift(int key);
	
	//Returns true if the key being pressed is not a modifier key.
	bool notModKey(int key);

	
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
	std::map<int, glm::vec2*> keyboardPress = std::map<int, glm::vec2*>();

	//the current gui that recieves calls for a variety of things including input, update,
	//and render
	Gui *currentGui;

	//settings that the game is based off.
	Settings *currentSettings;

	//position of the mouse
	Mouse mousePosition;

	//Called for initializing special details involved with the window.
	virtual void init() = 0;
	
	//Called for generating the windowed version of the application.
	virtual GLFWwindow *createWindow() = 0;

	
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
	void addModKey(int key);

	//Called for removing a mod key from the current list.
	void removeModKey(int key);


	//Called as an easy way to generate a centered window for the user.
	GLFWwindow *createAndCenter(int width, int height, GLFWmonitor *monitor);

private:

	//The list of all mod keys available on the keyboard.
	//These are shift, control, alt, and super (which I'm not exactly sure of).
	static std::vector<int> modKeys;

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
	int currentModKeys;

	//The current window mode, 0 -> windowed, 1 -> borderless, 2 -> fullscreen
	int currentWindowMode;


	//Called after the window mode is updated, transfers all textures and data that
	//are tied to the window to the next window.
	bool checkUpdateWindow();

	//Called from the run function to manage the keys that are currently being pressed.
	void handleKeyInput(float delta);

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

	virtual void mouseClick(int button) {}
	virtual void mouseHeld(int button) {}
	virtual void mouseRelease(int button) {}
	virtual void mouseScroll(float xOffset, float yOffset) {}

	virtual int keyPressed(int key, int keyMods) { return 0; }
	virtual int keyHeld(int key, int timesCalled, int keyMods) { return 0; }
	virtual void keyRelease(int key, int keyMods) {}

	virtual void reload() {}
protected:

	Window *window;
	Gui *parent;

	float ticksExisted;

	Gui *getParent();

	virtual void reinit() {}
};

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