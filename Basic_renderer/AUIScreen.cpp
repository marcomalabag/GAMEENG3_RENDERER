#include "AUIScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

AUIScreen::AUIScreen()
{
}

AUIScreen::AUIScreen(String name)
{
    this->name = name;
}

AUIScreen::~AUIScreen()
{
}

String AUIScreen::getName()
{
    return this->name;
}

void AUIScreen::drawUI()
{
    
}
