#pragma once
#include "AUIScreen.h"

class ProfileScreen : public AUIScreen
{
public:
	ProfileScreen();
	~ProfileScreen();

	virtual void drawUI() override;
	friend class UIManager;
};

