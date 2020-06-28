//Headers

#include<windows.h>

//global function declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{

	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWinApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = 0;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	//Register Class

	RegisterClassEx(&wndclass);

	//create window

	hwnd = CreateWindow(szAppName,
		TEXT("Win32 - SDK Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	//Message Loop

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return((int)msg.wParam);	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[100];
	int a, b, c;
	a = 10;
	b = 50;


	switch (iMsg)
	{		
		case WM_CREATE:
			c = a + b;
			wsprintf(str, TEXT("%d and %d is %d"), a, b, c);
			MessageBox(hwnd, str, TEXT("CreateAddition"), MB_OK);
			break;

		case WM_LBUTTONDOWN:
			MessageBox(hwnd, TEXT("L button Down is pressed"), TEXT("LBUTTON"), MB_OK);
			break;

		case WM_RBUTTONDOWN:
			MessageBox(hwnd, TEXT("R button Down is pressed"), TEXT("RBUTTON"), MB_ICONINFORMATION | MB_OK);
			break;

		case WM_KEYDOWN:
			MessageBox(hwnd, TEXT("You pressed a key"), TEXT("KEY BUTTON"), MB_OK);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
