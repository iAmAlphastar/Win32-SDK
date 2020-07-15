///////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name :Rohan Sataymurthy
//	Date :16 July 2020
//	Program : Timer
//
///////////////////////////////////////////////////////////////////////////////////////////////

#include<windows.h>
#include"Header.h"

//Macro definitions
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MYTIMER 108

//function prototype/declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//Variable declaration
HWND ghwnd;
int igPaintflag;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Timer_Demo");


	//For centering of window calcualtinf the X & Y of Screen
	int X = GetSystemMetrics(SM_CXSCREEN);
	int Y = GetSystemMetrics(SM_CYSCREEN);


	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//Rgistering your Class
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Color_Change"),
		WS_OVERLAPPEDWINDOW,
		(X / 2) - (WIN_WIDTH / 2),
		(Y / 2) - (WIN_HEIGHT / 2),
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL,0,0)!=0)
	{ 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//Local Variable
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR str[] = TEXT("It Simply Works !!!!");
	
	//Graphics graphics(hdc);


	switch (iMsg)
	{
	case WM_CREATE:
		static HBRUSH brush[9];

		brush[0] = CreateSolidBrush(RGB(255, 0, 0));
		brush[1] = CreateSolidBrush(RGB(0, 255, 0));
		brush[2] = CreateSolidBrush(RGB(0, 0, 255));
		brush[3] = CreateSolidBrush(RGB(0 ,0 ,255));
		brush[4] = CreateSolidBrush(RGB(255, 0, 255));
		brush[5] = CreateSolidBrush(RGB(255, 255, 0));
		brush[6] = CreateSolidBrush(RGB(0, 0, 0));
		brush[7] = CreateSolidBrush(RGB(255, 255, 255));
		brush[8] = CreateSolidBrush(RGB(163, 222, 27));
		brush[9] = CreateSolidBrush(RGB(130, 130, 75));

		SetTimer(hwnd, MYTIMER, 1000, NULL);
		break;

	case WM_TIMER:
		if (igPaintflag > 9)
		{
			igPaintflag = 0;
		}

		KillTimer(hwnd, MYTIMER);
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd,MYTIMER,500,NULL);
		igPaintflag++;
		break;

	case WM_PAINT:

		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		//RECT rect1(0, 0, 100, 200);
		SelectObject(hdc, brush[igPaintflag]);
		FillRect(hdc, &rc, brush[igPaintflag]);
		//Rectangle(hdc, (rc.right / 2 - 13), (rc.bottom / 2 + 113), (rc.right / 2 + 13), (rc.bottom / 2 + 50));
		SetBkColor(hdc, RGB(255, 78, 90));
		SetTextColor(hdc, RGB(13, 13, 13));
		DrawText(hdc,str,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'x':
		case 'X':
		case ' ':
			DestroyWindow(hwnd);
			break;
		
		default:
			break;
		}
		break;

	case WM_DESTROY:
		MessageBox(hwnd, TEXT("WM_DESTROY is clicked"), TEXT("WM_DESTROY"), MB_OK);
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
