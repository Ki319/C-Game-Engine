#include "Gui.h"

Gui::Gui(Window *application)
{
	window = application;
	parent = nullptr;
	ticksExisted = 0;
}

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