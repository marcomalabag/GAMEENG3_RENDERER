#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::sharedInstance = NULL;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	POINT CurrentMousePosition = {};
	GetCursorPos(&CurrentMousePosition);

	if (this->FirstTime) {
		OldMousePosition = Point(CurrentMousePosition.x, CurrentMousePosition.y);
		this->FirstTime = false;
	}

	if (CurrentMousePosition.x != OldMousePosition.x || CurrentMousePosition.y != OldMousePosition.y) {
		std::unordered_set<InputListener*>::iterator iter = mapListeners.begin();

		while (iter != mapListeners.end()) {
			(*iter)->onMouseMove(Point(CurrentMousePosition.x - OldMousePosition.x, CurrentMousePosition.y - OldMousePosition.y));
		}
	}


	if (::GetKeyboardState(keys)) 
	{
		for (unsigned int i = 0; i < 256; i++) 
		{
			if (keys[i] & 0x80) 
			{
				std::unordered_set<InputListener*>::iterator it = mapListeners.begin();

				while(it != mapListeners.end()) {
					if (i == VK_LBUTTON) {
						if (keys[i] != oldkeys[i]) {
							(*it)->onLeftMouseDown(Point(CurrentMousePosition.x, CurrentMousePosition.y));
						}
					}
					else if (i == VK_RBUTTON) {
						if (keys[i] != oldkeys[i]) {
							(*it)->onRightMouseDown(Point(CurrentMousePosition.x, CurrentMousePosition.y));
						}
					}
					else {
						(*it)->onKeyDown(i);
					}
					it++;
				}
			}
			else 
			{
				if (keys[i] != oldkeys[i]) {
					std::unordered_set<InputListener*>::iterator it = mapListeners.begin();

					while (it != mapListeners.end()) {
						if (i == VK_LBUTTON) {
							(*it)->onLeftMouseUp(Point(CurrentMousePosition.x, CurrentMousePosition.y));
						}
						else if (i == VK_RBUTTON) {
							(*it)->onRightMouseUp(Point(CurrentMousePosition.x, CurrentMousePosition.y));
						}
						else {
							(*it)->onKeyUp(i);
						}
						++it;
					}

				}
			}
		}
		::memcpy(oldkeys, keys, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	mapListeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	mapListeners.erase(listener);
}

bool InputSystem::isKeyDown(int key)
{
	for (int j = 0; j < ARRAYSIZE(this->keys); j++) {
		if (!(this->keys[j] & 0x80) && j == key) {
			return true;
		}
		else if (j == key) {
			return false;
		}
	}

	return false;
}

bool InputSystem::isKeyUp(int key)
{
	for (int j = 0; j < ARRAYSIZE(this->keys); j++) {
		if (!(this->keys[j] & 0x80) && j == key) {
			return true;
		}
		else if (j == key) {
			return false;
		}
	}

	return false;
}

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	delete sharedInstance;
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}
