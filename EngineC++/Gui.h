#pragma once
class Gui
{
public:
	Gui();
	virtual ~Gui();

	virtual void init();

	virtual void mouseClick(int button);
	virtual void mouseHeld(int button);
	virtual void mouseRelease(int button);

	virtual float keyHeld(int key, int timesCalled, int keyMods);
	virtual void keyRelease(int key, int keyMods);
};

