#include "Engine.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
) 
{
	Engine engine;
	engine.Initialize(hInstance, "Title", "my wclass", 640, 480);

	while (engine.ProcessMessages()==true)
	{
		Sleep(50);
	}
}