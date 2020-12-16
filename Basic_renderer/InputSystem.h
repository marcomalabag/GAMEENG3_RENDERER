#pragma once
#include "InputListener.h"
#include <map>
#include <unordered_set>
#include "Point.h"

typedef std::vector<InputListener*> List;

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	bool isKeyDown(int key);
	bool isKeyUp(int key);

	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

public:
	static InputSystem* get();

private:
	std::unordered_set<InputListener*> mapListeners;
	List InputList;
	static InputSystem* sharedInstance;
	unsigned char keys[256] = {};
	unsigned char oldkeys[256] = {};
	Point OldMousePosition;
	bool FirstTime = true;
};

