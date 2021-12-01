#include "framework.h"
#include "Resource.h"
#include "Calc.h"

#define CMD_BUTTON_1 4001

BOOL isCalcReg = FALSE;
HINSTANCE hInstCalc;
LRESULT CALLBACK WndProcCalc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void CalcControls(HWND);

void showWindowCalc(HINSTANCE hInstsance, HWND mainWindow){
	hInstCalc = hInstsance;
	if(!isCalcReg){
		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
		wcex.cbSize = sizeof(WNDCLASSEX);

		//  wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProcCalc;
		//  wcex.cbClsExtra = 0;
		//  wcex.cbWndExtra = 0;
		wcex.hInstance = hInstCalc;
		//   wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WINDOWSHELLOWORLD));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		//  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSHELLOWORLD);
		wcex.lpszClassName = L"CalcWindow";
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		if (!RegisterClassExW(&wcex)) {
			MessageBoxW(NULL, L"Register class error", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		isCalcReg = TRUE;
	}
	ShowWindow(
		CreateWindowW(L"CalcWindow", L"Calc", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 300, 600, mainWindow, 0 , hInstCalc, 0)
		,SW_NORMAL);
};

LRESULT CALLBACK WndProcCalc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CREATE:
		CalcControls(hWnd);
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case CMD_BUTTON_1:

			break;
		}
	}
	case WM_DESTROY:

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void CalcControls(HWND hWnd) {
	CreateWindowW(L"Static", L"	", WS_VISIBLE | WS_CHILD | DT_CENTER,
		10, 10, 260, 20, hWnd, 0, hInstCalc, 0);
	CreateWindowW(L"Edit", L"0", WS_VISIBLE | WS_CHILD | ES_RIGHT,
		10, 40, 260, 30, hWnd, 0, hInstCalc, 0);
}

	