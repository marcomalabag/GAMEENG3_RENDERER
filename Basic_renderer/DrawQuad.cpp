#include "DrawQuad.h"
#include "AppWindow.h"
#include <cstddef>


DrawQuad* DrawQuad::sharedInstance = nullptr;

DrawQuad* DrawQuad::getInstance()
{
	return sharedInstance;
}

void DrawQuad::initialize()
{
	sharedInstance = new DrawQuad();

}

void DrawQuad::destroy()
{
	if (sharedInstance != NULL) {
		delete sharedInstance;
	}
}

void DrawQuad::drawQuads()
{
}

DrawQuad::DrawQuad()
{
}

DrawQuad::~DrawQuad()
{
}
