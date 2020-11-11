#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class Window;

class EngineTime
{

public:
	static EngineTime* getInstance();
	static void initialize();
	static double getDeltaTime();
	static int getFramesPassed();

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;
	int frames = 0;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;
	friend class AppWindow;
	friend class SwapChain;
};

