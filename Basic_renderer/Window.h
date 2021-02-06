#pragma once
#define NOMINMAX
#include <Windows.h>

class Window
{
	public:
		Window();
		
	
		
		bool isRun();

		RECT getClientWindowRect();
		
		double deltaTime = 0.0;
		virtual void onCreate();
		virtual void onUpdate();
		virtual void onDestroy();
		virtual void onFocus();
		virtual void onDefocus();
		virtual void onKillFocus();

		~Window();
    private:
	   bool broadcast();

	protected:
		HWND m_hwnd;
		bool m_is_run;
		bool m_is_init = false;
};

