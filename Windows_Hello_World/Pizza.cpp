#include "framework.h"
#include "Resource.h"
#include "Pizza.h"

#define CMD_BUTTON_START 3001
#define CMD_CHECKBOX 3002
#define CMD_RADIO_BUTTON1 3003
#define CMD_RADIO_BUTTON2 3004
#define CMD_RADIO_BUTTON3 3005
#define CMD_BUTTON_ORDER 3006


BOOL isPizzaReg = FALSE;
HINSTANCE hInstPizza;
LRESULT CALLBACK WndProcPizza(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND pizza;
HWND hwndCheckboxP;
HWND hwndRadio1;
HWND hwndRadio2;
HWND hwndRadio3;
HWND hwndComboboxPizza;
HWND hwndOrderPizza;
void DeliveryControls(HWND);

void showWindowPizza(HINSTANCE hInstsance, HWND mainWindow) {
	hInstPizza = hInstsance;
	if (!isPizzaReg) {
		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
		wcex.cbSize = sizeof(WNDCLASSEX);

		//  wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProcPizza;
		//  wcex.cbClsExtra = 0;
		//  wcex.cbWndExtra = 0;
		wcex.hInstance = hInstPizza;
		//   wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WINDOWSHELLOWORLD));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 22);
		//  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSHELLOWORLD);
		wcex.lpszClassName = L"PizzaWindow";
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		if (!RegisterClassExW(&wcex)) {
			MessageBoxW(NULL, L"Register class error", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		
		isPizzaReg = TRUE;
		
	}
	ShowWindow(CreateWindowW(L"PizzaWindow", L"Pizza", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 300, 600, mainWindow, 0, hInstPizza, 0)
		, SW_NORMAL);
};

LRESULT CALLBACK WndProcPizza(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CREATE:

		DeliveryControls(hWnd);
		break;

	
	

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		
		case CMD_CHECKBOX:
		{
			LRESULT state = SendMessageW(pizza, BM_GETCHECK, 0, 0);
			if (state == BST_CHECKED)

				SendMessage(pizza, BM_SETCHECK, BST_UNCHECKED, 0);
			else
				SendMessage(pizza, BM_SETCHECK, BST_CHECKED, 0);

			SendMessageW(pizza, WM_KILLFOCUS, 0, 0);
			break;
		}
		
	case CMD_RADIO_BUTTON1:
	{
		LRESULT state = SendMessageW(hwndRadio1, BM_GETCHECK, 0, 0);
		if (state == BST_CHECKED)

			SendMessage(hwndRadio1, BM_SETCHECK, BST_UNCHECKED, 0);
		else
			SendMessage(hwndRadio1, BM_SETCHECK, BST_CHECKED, 0);

		SendMessageW(pizza, WM_KILLFOCUS, 0, 0);
		break;
	}
	
	case CMD_RADIO_BUTTON2:
	{
		LRESULT state = SendMessageW(hwndRadio2, BM_GETCHECK, 0, 0);
		if (state == BST_CHECKED)

			SendMessage(hwndRadio2, BM_SETCHECK, BST_UNCHECKED, 0);
		else
			SendMessage(hwndRadio2, BM_SETCHECK, BST_CHECKED, 0);

		SendMessageW(pizza, WM_KILLFOCUS, 0, 0);
		break;
	}
	
	case CMD_RADIO_BUTTON3:
	{
		LRESULT state = SendMessageW(hwndRadio3, BM_GETCHECK, 0, 0);
		if (state == BST_CHECKED)

			SendMessage(hwndRadio3, BM_SETCHECK, BST_UNCHECKED, 0);
		else
			SendMessage(hwndRadio3, BM_SETCHECK, BST_CHECKED, 0);

		SendMessageW(pizza, WM_KILLFOCUS, 0, 0);
		break;
	}
	case CMD_BUTTON_ORDER:
	{
		MessageBox(pizza, L"Заказ оформлен!", L"Готово!", MB_OK);
		 
	
		
	}
	}

	}
	case WM_DESTROY:

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


void DeliveryControls(HWND pizza) {
	CreateWindowW(L"Delivery", L"	", WS_VISIBLE | WS_CHILD | DT_CENTER,
		200, 10, 75, 20, pizza, 0, hInstPizza, 0);
	CreateWindowW(L"Static", L"На кого: ", WS_CHILD | WS_VISIBLE | DT_CENTER,
		10, 100, 100, 23, pizza, 0, hInstPizza, NULL);
	CreateWindowW(L"Edit", L"Введите имя", WS_CHILD | WS_VISIBLE | DT_CENTER,
		100, 100, 130, 23, pizza, 0, hInstPizza, NULL);
	hwndCheckboxP = CreateWindowW(L"Button", L"Доставка", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | DT_CENTER,
		10, 130, 100, 23, pizza, (HMENU)CMD_CHECKBOX, hInstPizza, 0);
	hwndRadio1 = CreateWindowW(L"Button", L"30см", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		10, 160, 100, 23, pizza, (HMENU)CMD_RADIO_BUTTON1, hInstPizza, 0);
	hwndRadio2 = CreateWindowW(L"Button", L"40см", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		10, 190, 100, 23, pizza, (HMENU)CMD_RADIO_BUTTON2, hInstPizza, 0);
	hwndRadio3 = CreateWindowW(L"Button", L"50см", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		10, 220, 100, 23, pizza, (HMENU)CMD_RADIO_BUTTON3, hInstPizza, 0);

	CreateWindowW(L"Static", L"Выбор пиццы", WS_CHILD | WS_VISIBLE | DT_CENTER,
		10, 260, 100, 23, pizza, 0, hInstPizza, NULL);

	hwndComboboxPizza = CreateWindowW(L"Combobox", L"pizza", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
		10, 280, 150, 100, pizza, (HMENU)0, hInstPizza, 0);
	

	

	SendMessageW(hwndComboboxPizza, CB_ADDSTRING, 100, (LPARAM)L"Margherita");
	SendMessageW(hwndComboboxPizza, CB_ADDSTRING, 100, (LPARAM)L"Marinara");
	SendMessageW(hwndComboboxPizza, CB_ADDSTRING, 100, (LPARAM)L"Carbonara");
	SendMessageW(hwndComboboxPizza, CB_ADDSTRING, 100, (LPARAM)L"Quattro Formaggi");
	SendMessageW(hwndComboboxPizza, CB_ADDSTRING, 100, (LPARAM)L"Frutti di Mare");

	hwndOrderPizza = CreateWindowW(L"Button", L"Оформить заказ", WS_CHILD | WS_VISIBLE | DT_CENTER,
		10, 310, 150, 23, pizza, (HMENU)CMD_BUTTON_ORDER, hInstPizza, 0);
}