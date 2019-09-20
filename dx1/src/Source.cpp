#include "ErrorLogger.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
) 
{
	HRESULT hr = S_OK;
	if (FAILED(hr))
		ErrorLogger::Log(hr, "Failure");
	else
		MessageBoxA(NULL, "SUCCESS", "SUCCESS", NULL);
}