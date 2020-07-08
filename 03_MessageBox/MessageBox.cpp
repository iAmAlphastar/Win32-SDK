///////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name :Rohan Sataymurthy
//	Date :09 July 2020
//	Program : Message Box
//
///////////////////////////////////////////////////////////////////////////////////////////////

//header file 

#include<windows.h>

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

/*

				WinMain()
					|
					v
			_WinMainCRTStartup (CRT-CRuntime)
					|
					v
				  main()
					|
					v
			_MainCRTStartup
					|
					v
				 _start

				 
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration

	WNDCLASSEX wndclass;							//structure with 12member 
	HWND hwnd;										//handle to window
	MSG msg;										//6 member structure
	TCHAR szAppName[] = TEXT("CustomMessageBox");	//TEXT is a MACRO , string passed in "double quote" that name is registered by OS,
													//as name of the application

	//code 

	//initialization of WNDCLASSEX

	wndclass.cbSize = sizeof(WNDCLASSEX);									//newly added  , cb Count of Byte
	wndclass.style = CS_HREDRAW | CS_VREDRAW;								//Vertical Redraw Or Horizontal Redraw
	wndclass.cbClsExtra = 0;												//Any Extra Info for this class regarding these 12 member specify here
	wndclass.cbWndExtra = 0;												//Any Extra Info for this window regarding these 12 member specify here
	wndclass.lpfnWndProc = WndProc;											//Registering out Call back function to WndProc function name
	wndclass.hInstance = hInstance;											//Handle to instance first parameter to our WinMain function
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);						//IDI - id to Icon  - hIcon - handle to icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);							//IDC - id to Cursor  hCursor - handle to cursor	
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);			//Which colour you want to give to our background of the window the return 
																			//Value GetStockObject = HGDIOBJ (handle to Graphics Device Interface Object)
	
	wndclass.lpszClassName = szAppName;										//Class name which is register to OS in szAppName
	wndclass.lpszMenuName = NULL;											//Menu for your window [File | Edit | Find | Tool | Help]
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); 					//small icon (explorer/taskbar) newly added

	//Register your wndclass structure return value of RegisterClassEx is ATOM
	RegisterClassEx(&wndclass);

	//create window this window is only created in memory i.e. RAM

	hwnd = CreateWindow(szAppName,	//Your registered class name in szAppName
		TEXT("MessageBox"),			//What title you want in your caption bar
		WS_OVERLAPPEDWINDOW,		//MACRO made up of 6 different window style :: WS_CAPTION | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU | WS_THICKFRAME
		CW_USEDEFAULT,				//Window position x axis horizontal position of window
		CW_USEDEFAULT,				//Window position y axis vertical position of window
		CW_USEDEFAULT,				//window width 
		CW_USEDEFAULT,				//window height
		NULL, 						//HWND_DESKTOP , when this parameter is NULL we are telling the OS that make this window's parent DESKTOP
		NULL,						//class menu
		hInstance,					//1st parameter of WinMain()
		NULL);						//creation parameter LPVOID and extra info for Create Window

	ShowWindow(hwnd, iCmdShow); 	//hwnd - HANDLE to window ,iCmdShow is 4th parameter of WinMain()
	UpdateWindow(hwnd);				//here your windows background gets painted to the colour of brush you have given in hbrBackground i.e GetStockObject


	while (GetMessage(&msg, NULL, 0, 0))		//msg structure which has 6 members hwnd,which msg,wparam,lparam,point,time. second parameter is null because there can be many other child window we need to catch and process their msg also so null or else you can pass hwnd there
	{
		TranslateMessage(&msg);		//Translate hardware message to low level message and then it is passed to dispatch message for further steps
		DispatchMessage(&msg);		//Its sends the message to our callback function i.e WndProc

	}

	MessageBox(NULL, TEXT("Exiting.....Now....BYE"), TEXT("WinMain"), MB_OK);

	return((int)msg.wParam);		//PostQuitMessage parameter is wParam so from msg strutcure we have accessed that msg and type casted it to int because wParam return value is DWORD
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	//code
	switch (iMsg)
	{
	case WM_CREATE:			//This msg is called before our window is created 
		MessageBox(hwnd, TEXT("WM_CREATE received"), TEXT("WM_Message"),MB_ICONASTERISK);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_LBUTTONDOWN received"), TEXT("WM_LBUTTONDOWN Message"),MB_ICONEXCLAMATION);
		break;

	case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_RBUTTONDOWN received"), TEXT("WM_RBUTTONDOWN Message"), MB_OK);
		break;

	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("WM_KEYDOWN received"), TEXT("WM_KEYDOWN Message"),MB_ICONHAND);
		break;

	case WM_DESTROY:
		MessageBox(NULL, TEXT("Exiting.....Now....BYE"), TEXT("WM_DESTROY"),MB_ICONERROR);
		PostQuitMessage(0);
		break;
	}//end of switch case

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));		//definition of window procdure
}
