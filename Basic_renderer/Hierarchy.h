#pragma once
#include "AUIScreen.h"

class Hierarchy : public AUIScreen
{
public:
	Hierarchy();
	~Hierarchy();

	void drawUI();
	void updateObjectList() const;
	friend class UIManager;
};

