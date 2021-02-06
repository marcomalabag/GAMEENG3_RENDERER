#include "AppWindow.h"
#include "InputSystem.h"


int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::initialize();
	}
	catch (...) { return -1; }

	{
		try
		{
			AppWindow app;
			while (app.isRun());
		}
		catch (...) {
			InputSystem::getInstance()->destroy();
			GraphicsEngine::release();
			return -1;
		}
	}

	InputSystem::release();
	GraphicsEngine::release();

	return 0;
}