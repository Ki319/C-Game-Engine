#include "pch.h"
#include "Settings.h"
#include "Gui.h"

//getting position and change in mouse position
#define mX App::getMouseX()
#define mY App::getMouseY()
#define mDX App::getMouseDeltaX()
#define mDY App::getMouseDeltaY()
#define setupWindowConsts Window::swc()
#define setupWindow Window::sw()
#define setWindowEvents Window::swe()
#define shouldClose Window::sc()
#define swapBuffers Window::sb()
#define updateSize Window::us()
#define setup2d Window::d2()
#define setup3d(fovy, zNear, zFar) Window::d3(fovy, zNear, zFar)
#define closeWindow Window::c()
#define destroyWindow Window::d()
#define createAndCenter(width, height, title, monitor) Window::cac(width, height, title, monitor);
#define windowWidth Window::ww()
#define windowHeight Window::wh()
#define windowWidthScaled Window::wws()
#define setWindowWidthScale(defaultWidth) Window::swws(defaultWidth)
#define windowHeightScaled Window::whs()
#define setWindowHeightScale(defaultHeight) Window::sww(defaultHeight)
#define window2dZScale Window::w2zs()
#define setWindow2dZScale(defaultZScale) Window::sw2zs(defaultZScale)
#define getModKeys Window::gmk()
#define getKey(key) Window::gk(key)
#define getShiftKey(key) Window::gsk(key)
#define notModKey(key) Window::nmk(key)
#define addModKey(key) Window::amk(key)
#define removeModKey(key) Window::rmk(key)
#define getTimer glfwGetTime()
#define resetTimer glfwSetTime(0)
#define pollEvents glfwPollEvents()

class App;

static App *application = nullptr;
static GLFWwindow *windowInstance = nullptr;
static Settings currentSettings;
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
	void run();
	void setGui(Gui *newGui);

	virtual void init() = 0;
	virtual GLFWwindow *createWindow() = 0;

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

	Gui *getCurrentScreen();

	static float getMouseX();
	static float getMouseY();
	static float getMouseDeltaX();
	static float getMouseDeltaY();
protected:
	static Mouse mousePosition;

	std::map<int, glm::vec2*> keyboardPress = std::map<int, glm::vec2*>();
	Gui *currentGui;

	virtual Settings getSettings()
	{
		return Settings();
	}

	virtual std::string getResourceLocation()
	{
		return "resources";
	}

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
	static void swc();
	//setupWindow
	static bool sw();
	//setWindowEvents
	static void swe();
	//shouldClose
	static bool sc();
	//swapBuffers
	static void sb();
	//updateSize
	static void us();
	//gl2d
	static void d2();
	//gl3d
	static void d3(float fovy, float zNear, float zFar);
	//close
	static void c();
	//destroy
	static void d();

	//createAndCenter
	static GLFWwindow *cac(int width, int height, const char *title, GLFWmonitor *monitor);

	//windowWidth
	static int ww();
	//windowHeight
	static int wh();
	//windowWidthScaled
	static float wws();
	//setWindowWidthScale
	static void swws(int defaultWindowWidth);
	//windowHeightScaled
	static float whs();
	//setWindowHeightScaled
	static void swhs(int defaultWindowHeight);
	//window2dZScaled
	static float w2zs();
	//setWindow2dZScaled
	static void sw2zs(int defaultZScale);
	//getModKeys
	static int gmk();
	//getKey
	static int gk(int key);
	//getShiftKey
	static int gsk(int key);
	//notModKey
	static bool nmk(int key);
	//addModKey
	static void amk(int key);
	//removeModKey
	static void rmk(int key);

private:
	static bool isRunning;
	//windowWidth
	static int wW;
	//windowHeight
	static int wH;
	//windowWidthScale
	static float wWS;
	//windowHeightScale
	static float wHS;
	//defaultWindowWidth
	static int dww;
	//defaultWindowHeight
	static int dwh;
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