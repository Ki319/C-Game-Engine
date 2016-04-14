#pragma once
class Gui
{
public:
	Gui();
	virtual ~Gui();

	virtual void init();

	virtual void update(float delta);
	virtual void render(float delta);

	virtual void mouseClick(int button);
	virtual void mouseHeld(int button);
	virtual void mouseRelease(int button);
	virtual void mouseScroll(float xOffset, float yOffset);

	virtual int keyPressed(int key, int keyMods);
	virtual int keyHeld(int key, int timesCalled, int keyMods);
	virtual void keyRelease(int key, int keyMods);
};

