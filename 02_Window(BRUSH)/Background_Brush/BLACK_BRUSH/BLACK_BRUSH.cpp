///////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name :Rohan Sataymurthy
//	Date :07 July 2020
//	Program : Background brush.
//
///////////////////////////////////////////////////////////////////////////////////////////////

//header file 

#include<windows.h>
#include<stdio.h>

/*
	******************Six Rules for CallBack function***********************

	1.Function should be declared globally
	2.Function's address should be kept in special area i.e. far memory.
	3.return value will be decided by O.S it will O.S type return value
	4.parameter will be decided by O.S , how many parameter and which type.
	5.Such function will be called by only O.S not anyone can call it.
	6.All Call back function must have O.S calling convention.

*/

//Global declaration because it is a call back function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration

	WNDCLASSEX wndclass;							//structure with 12member 
	HWND hwnd;										//handle to window
	MSG msg;										//6 member structure
	TCHAR szAppName[] = TEXT("MYAPP");				//TEXT is a MACRO , string passed in "double quote" that name is registered by OS,
													//as name of the application

	//code 

	//initialization of WNDCLASSEX

	wndclass.cbSize = sizeof(WNDCLASSEX);								//newly added
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (COLOR_MENU)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); 					//small icon (explorer/taskbar) newly added

	RegisterClassEx(&wndclass);

	//create window this window is only created in memory i.e. RAM
	
	hwnd = CreateWindow(szAppName,
		TEXT("BLACKBRUSH_DEMO"),
		WS_OVERLAPPEDWINDOW,		//MACRO made up of 6 different window style :: WS_CAPTION | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU | WS_THICKFRAME
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
		NULL, 					//HWND_DESKTOP , when this parameter is NULL we are telling the OS that make this window's parent DESKTOP
		NULL,					//class menu
		hInstance,				//1st parameter of WinMain()
		NULL);					//creation parameter LPVOID

	ShowWindow(hwnd, iCmdShow); 	//hwnd - HANDLE to window ,iCmdShow is 4th parameter of WinMain()
	UpdateWindow(hwnd);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	MessageBox(NULL, TEXT("Exiting.....Now....BYE"), TEXT("WinMain"), MB_OK);

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("WM_CREATE received"), TEXT("WM_Message"), MB_OK);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_LBUTTONDOWN received"), TEXT("WM_LBUTTONDOWN Message"), MB_OK);
		break;

	case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_RBUTTONDOWN received"), TEXT("WM_RBUTTONDOWN Message"), MB_OK);
		break;

	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("WM_KEYDOWN received"), TEXT("WM_KEYDOWN Message"), MB_OKCANCEL);
		break;

	case WM_DESTROY:
		MessageBox(NULL, TEXT("Exiting.....Now....BYE"), TEXT("WM_DESTROY"), MB_ABORTRETRYIGNORE);
		PostQuitMessage(0);		
		break;
	}//end of switch case

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
