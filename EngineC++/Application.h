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
#define getWindowWidth Window::gww()
#define getWindowHeight Window::gwh()
#define getWindowWidthScale windowWidthScale / getWindowWidth
#define getWindowHeightScale windowHeightScale / getWindowHeight
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

static const int windowWidthScale = 1920;
static const int windowHeightScale = 1080;
static const int window2dZScale = 100;

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

class Window
{
public:
	static void swc();//setupWindowConsts
	static bool sw();//setupWindow
	static void swe();//setWindowEvents
	static bool sc();//shouldClose
	static void sb();//swapBuffers
	static void us();//updateSize
	static void d2();//gl2d
	static void d3(float fovy, float zNear, float zFar);//gl3d
	static void c();//close
	static void d();//destroy

	static GLFWwindow *cac(int width, int height, const char *title, GLFWmonitor *monitor);//createAndCenter

	static int gww();//getWindowWidth
	static int gwh();//getWindowHeight
	static int gmk();//getModKeys
	static int gk(int key);//getKey
	static int gsk(int key);//getShiftKey
	static bool nmk(int key);//notModKey
	static void amk(int key);//addModKey
	static void rmk(int key);//removeModKey

private:
	static bool isRunning;
	static int windowWidth;
	static int windowHeight;
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