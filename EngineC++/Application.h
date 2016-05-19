#include "pch.h"
#include "Settings.h"
#include "Gui.h"

//getting position and change in mouse position
#define mX App::getMouseX()
#define mY App::getMouseY()
#define mDX App::getMouseDeltaX()
#define mDY App::getMouseDeltaY()
#define timer glfwGetTime()
#define resetTimer glfwSetTime(0)
#define pollEvents glfwPollEvents()

class App;

static App *application = nullptr;
static GLFWwindow *windowInstance = nullptr;
static Settings *currentSettings = nullptr;
static int currentWindowMode;

class Window;

struct Mouse
{
	float mouseX;
	float mouseY;
	float mouseDeltaX;
	float mouseDeltaY;
};

//main class that all applications must extend
class App
{
public:

	virtual GLFWwindow *createWindow() = 0;

	void run();
	void setGui(Gui *newGui);

	virtual void cursorMoveBounds(bool entered) {}
	virtual void cursorMove(double mouseX, double mouseY);
	virtual void cursorClick(int button, int action);
	virtual void cursorScroll(double xOffset, double yOffset);
	virtual void keyboardClick(int key, int action, int mods);
	virtual void windowClose();
	virtual void windowFocus(bool focused) {}
	virtual void windowIconify(bool iconified) {}
	virtual void windowPos(int xPos, int yPos) {}
	virtual void windowRefresh() {}
	virtual void windowSize(int width, int height);
	virtual void update(float delta);
	virtual void render(float delta);
	virtual void createSettings();

	Gui *getCurrentScreen();

	static float getMouseX();
	static float getMouseY();
	static float getMouseDeltaX();
	static float getMouseDeltaY();
protected:

	std::map<int, glm::vec2*> keyboardPress = std::map<int, glm::vec2*>();
	Gui *currentGui;

	virtual void init() = 0;

	static Mouse mousePosition;
	static boost::filesystem::path resourcePath;
private:

	bool checkUpdateWindow();
	void handleKeyInput(float delta);
};

/*
Just don't even bother really, this code is messy on purpose. You may ask why,
the reason is for the user to not have to type as much code out while perserving order.
This class is not to be called, the defines up top take care of it all and have proper naming.
Goal is to minimize the usage of <CLASSNAME>::<FUNCTION>(); and just have <FUNCTION>(); instead
*/
class Window
{
public:
	//setupWindowConsts
	static void setupConsts();
	//setupWindow
	static bool setup();
	//setWindowEvents
	static void setEvents();
	//shouldClose
	static bool shouldClose();
	//swapBuffers
	static void swapBuffers();
	//updateSize
	static void updateSize();
	//gl2d
	static void gl2d();
	//gl3d
	static void gl3d(float fovy, float zNear, float zFar);
	//close
	static void close();
	//destroy
	static void destroy();

	//createAndCenter
	static GLFWwindow *createAndCenter(int width, int height, const char *title, GLFWmonitor *monitor);

	//windowWidth
	static int width();
	//windowHeight
	static int height();
	//windowWidthScaled
	static float widthScaled();
	//setWindowWidthScale
	static void setWidthScaled(int defaultWidth);
	//windowHeightScaled
	static float heightScaled();
	//setWindowHeightScaled
	static void setHeightScaled(int defaultHeight);
	//window2dZScaled
	static float zLength();
	//setWindow2dZScaled
	static void setZLength(float defaultZScale);
	//getModKeys
	static int getModKeys();
	//getKey
	static int getKey(int key);
	//getShiftKey
	static int getKeyWithShift(int key);
	//notModKey
	static bool notModKey(int key);
	//addModKey
	static void addModKey(int key);
	//removeModKey
	static void removeModKey(int key);

private:
	static bool isRunning;
	//windowWidth
	static int windowWidth;
	//windowHeight
	static int windowHeight;
	//windowWidthScale
	static float windowWidthScale;
	//windowHeightScale
	static float windowHeightScale;
	//defaultWindowWidth
	static int defaultWindowWidth;
	//defaultWindowHeight
	static int defaultWindowHeight;
	//window2dZScaled
	static float windowZScale;

	static std::vector<int> modKeys;
	static std::map<int, int> shiftKeys;
	static int currentModKeys;

	static void cursorBounds(GLFWwindow *window, int entered)
	{
		application->cursorMoveBounds(entered == GL_TRUE);
	}

	static void cursorPos(GLFWwindow *window, double xpos, double ypos)
	{
		application->cursorMove(xpos, ypos);
	}

	static void cursorButton(GLFWwindow *window, int button, int action, int mods)
	{
		application->cursorClick(button, action);
	}

	static void cursorScroll(GLFWwindow *window, double xoffset, double yoffset)
	{
		application->cursorScroll(xoffset, yoffset);
	}

	static void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		application->keyboardClick(key, action, mods);
	}

	static void windowClose(GLFWwindow *window)
	{
		application->windowClose();
	}

	static void windowFocus(GLFWwindow *window, int focused)
	{
		application->windowFocus(focused == GL_TRUE);
	}

	static void windowIconify(GLFWwindow *window, int iconified)
	{
		application->windowIconify(iconified == GL_TRUE);
	}

	static void windowPos(GLFWwindow *window, int xpos, int ypos)
	{
		application->windowPos(xpos, ypos);
	}

	static void windowRefresh(GLFWwindow *window)
	{
		application->windowRefresh();
	}

	static void windowSize(GLFWwindow *window, int width, int height)
	{
		application->windowSize(width, height);
	}
};