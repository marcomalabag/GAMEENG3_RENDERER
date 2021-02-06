#pragma once
#include "InputListener.h"
#include <map>
#include <iostream>
#include <unordered_set>
#include <vector>
#include "Point.h"



class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

	bool isKeyDown(int key);
	bool isKeyUp(int key);

	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

public:
	static InputSystem* get();
	static void create();
	static void release();

private:
	std::unordered_set<InputListener*> mapListeners;
	
	static InputSystem* sharedInstance;
	unsigned char keys[256] = {};
	unsigned char oldkeys[256] = {};
	Point OldMousePosition;
	bool FirstTime = true;
	static InputSystem* Msystem;
};

