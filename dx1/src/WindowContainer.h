#pragma once
#include "RenderWindow.h"
class WindowContainer
{
public:
	/*WindowProc()
	class Mouse;
	class Keyboard*/
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
protected:
	RenderWindow render_window;


private:


};