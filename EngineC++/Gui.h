#pragma once
#include "Window.h"

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

	virtual int keyPressed(int key, int keyMods) {}
	virtual int keyHeld(int key, int timesCalled, int keyMods) {}
	virtual void keyRelease(int key, int keyMods) {}

	virtual void reload() {}
protected:

	Window *window;
	Gui *parent;

	float ticksExisted;

	Gui *getParent();

	virtual void reinit() {}
};

