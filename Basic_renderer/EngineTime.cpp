#include "EngineTime.h"
#include "AppWindow.h"

EngineTime* EngineTime::sharedInstance = NULL;

EngineTime* EngineTime::getInstance()
{
    return sharedInstance;
}

void EngineTime::initialize()
{
    sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
    return sharedInstance->deltaTime;
}

int EngineTime::getFramesPassed()
{
    return sharedInstance->frames;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
    sharedInstance->start = std::chrono::system_clock::now();
  
}

void EngineTime::LogFrameEnd()
{
    sharedInstance->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

    sharedInstance->deltaTime = elapsed_seconds.count();
    sharedInstance->frames += 1;

    std::cout << "Frame update finished in" << sharedInstance->deltaTime << "\n";
    std::cout << "Frames have passed:" << sharedInstance->frames << "\n";
}
