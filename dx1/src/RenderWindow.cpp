#include "WindowContainer.h"


bool RenderWindow::Initialize(
	WindowContainer* pWindowContainer,
	HINSTANCE hInstance,
	std::string window_title, std::string window_class,
	int width, int height
)
{
	this-> hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(window_class);
	this->RegisterWindowClass();
	 
	this->handle = CreateWindowEx(
		0,
		this->window_class_wide.c_str(),
		this->window_title_wide.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0,
		0,
		this->width,
		this->height,
		NULL,
		NULL,
		this->hInstance,
		pWindowContainer
	);

	if (this->handle == NULL)
	{
		ErrorLogger::Log(GetLastError(), "Failed to create windowEX  for: " + this->window_title);
		return false;
	}

	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;

}

bool RenderWindow::ProcessMessage()
{
	MSG msg; //handle messages
	ZeroMemory(&msg, sizeof(MSG)); //init mem structure 
    
	if (PeekMessage(
		&msg,
		this->handle,
		0,
		0,
		PM_REMOVE
	))
	{
		TranslateMessage(&msg); // WM_KEYDOWN, WM_CHAR (not only WM-KEYDOWN'S............)
		DispatchMessage(&msg);
	}
	//CHECK IF WND CLOSED
	if (msg.message != WM_NULL)
	{
		if (!IsWindow(this->handle))
		{
			this->handle = NULL;
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
		
	}
	return true;
}

RenderWindow::~RenderWindow()
{
	if (this->handle != NULL)
	{
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//all other mesgs
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
			return 0;
	}
	default:
		
	{
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>
		(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == false)
		{
			ErrorLogger::Log("ptr to the window is null at WM_NCCREATE");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);


		//WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>
			//(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	

	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}



void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->window_class_wide.c_str();
	
	RegisterClassEx(&wc);
}
