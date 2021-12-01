#include "Resource.h"
#include "framework.h"
#include "Calc.h"
#include "Pizza.h"


#define MAX_LOADSTRING 100
#define CMD_BUTTON_PRESS_ME 1001
#define CMD_BUTTON_INCREMENT 1002
#define CMD_BUTTON_DECREMENT 1003
#define CMD_BUTTON_PLUS_TEN 1004
#define CMD_BUTTON_MINUS_TEN 1005
#define CMD_BUTTON_RESET 1006
#define CMD_BUTTON_CONTROLS 1007    
#define CMD_CHECKBOX 2000
#define CMD_PUSHLIKE 2001
#define CMD_TEXT 2002
#define CMD_BUTTON_CALC 2003
#define CMD_BUTTON_DELIVERY 2004



// Global Variables:
HINSTANCE hInst; //Дескриптор экземпляра, который содержит оконную процедуру для класса.           
HWND mainWindow;
HWND hStatic1;
HWND hStatic2;
BOOL isControlsReg;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void                CreateExercise2();
void                processIncrement();
void                processDecrement();
void                processPlusTen();
void                processMinusTen();
void                processReset();
void                showWindowControls();



int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    isControlsReg = FALSE;
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_WINDOWSHELLOWORLD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    //MessageBoxA(NULL, (char*)((wchar_t*)"Are You Ready?"), (char*)(wchar_t*)"Welcome", MB_YESNO);

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
    wcex.cbSize = sizeof(WNDCLASSEX);
   
  //  wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
  //  wcex.cbClsExtra = 0;
  //  wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
 //   wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WINDOWSHELLOWORLD));
  //  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  //  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  //  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSHELLOWORLD);
    wcex.lpszClassName = L"BasicsWindow";
wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(   //  hWnd = new WinClass
        L"BasicsWindow",
        TEXT("Chess"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 640, 480,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

  

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:  // Window created - ready to append children
        mainWindow = hWnd;
        hStatic1 = CreateWindowW(
            L"Static",                 // class name
            L"Hello, world!",          // title
            WS_VISIBLE | WS_CHILD,     // style
            10, 10,                    // x, y (ref to parent)  
            200, 20,                   // width, height
            hWnd,                      // parent window handle
            0,                         // menu command - no
            hInst,                     // instance handle - global
            NULL                       // extra params
        );
        CreateWindowW(L"Button", L"Press me", WS_VISIBLE | WS_CHILD,
            10, 40, 75, 23,
            hWnd, (HMENU)1001, hInst, NULL);

        CreateExercise2();

        CreateWindowW(L"Button", L"Calc", WS_VISIBLE | WS_CHILD,
            30, 305, 75, 23, hWnd, (HMENU)CMD_BUTTON_CALC, hInst, NULL);

        CreateWindowW(L"Button", L"Delivery", WS_VISIBLE | WS_CHILD,
            150, 305, 105, 23, hWnd, (HMENU)CMD_BUTTON_DELIVERY, hInst, NULL);
      
        break;
    
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case CMD_BUTTON_CALC:
            showWindowCalc(hInst, mainWindow);
            break;

        case CMD_BUTTON_DELIVERY:
            showWindowPizza(hInst, mainWindow);
            break;
        case CMD_BUTTON_PRESS_ME:
            Beep(1000, 200);
            SendMessageW(hStatic1, WM_SETTEXT, 0, (LPARAM)L"Press one more time!");
            break;
        case CMD_BUTTON_INCREMENT:
            processIncrement();
            break;
        case CMD_BUTTON_DECREMENT:
            processDecrement();
            break;
        case CMD_BUTTON_PLUS_TEN:
            processPlusTen();
            break;
        case CMD_BUTTON_MINUS_TEN:
            processMinusTen();
            break;
        case CMD_BUTTON_RESET:
            processReset();
            break;
        case CMD_BUTTON_CONTROLS:
            showWindowControls();
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));
        
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void CreateExercise2() {
    hStatic2 = CreateWindowW(L"Static", L"0", WS_VISIBLE | WS_CHILD | DT_CENTER,
        100, 120, 75, 23, mainWindow, 0, hInst, NULL);

    CreateWindowW(L"Button", L"+", WS_VISIBLE | WS_CHILD,
        61, 120, 35, 23, mainWindow, (HMENU)CMD_BUTTON_INCREMENT, hInst, NULL);
    CreateWindowW(L"Button", L"-", WS_VISIBLE | WS_CHILD,
       180, 120, 35, 23, mainWindow, (HMENU)CMD_BUTTON_DECREMENT, hInst, NULL);
    CreateWindowW(L"Button", L"+10", WS_VISIBLE | WS_CHILD,
        20, 120, 35, 23, mainWindow, (HMENU)CMD_BUTTON_PLUS_TEN, hInst, NULL);
    CreateWindowW(L"Button", L"-10", WS_VISIBLE | WS_CHILD,
        220, 120, 35, 23, mainWindow, (HMENU)CMD_BUTTON_MINUS_TEN, hInst, NULL);
    CreateWindowW(L"Button", L"Reset", WS_VISIBLE | WS_CHILD | DT_CENTER,
        100, 150, 75, 23, mainWindow, (HMENU)CMD_BUTTON_RESET, hInst, NULL);

    CreateWindowW(L"Button", L"Controls", WS_VISIBLE | WS_CHILD | DT_CENTER,
       20, 200, 235, 23, mainWindow, (HMENU)CMD_BUTTON_CONTROLS, hInst, NULL);
}

void  processIncrement() {
    //Get text from the static
    WCHAR str[MAX_LOADSTRING];
    SendMessageW(hStatic2, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)str);
    //convert int
    int n = _wtoi(str);
    //increment
    Beep(500, 50);
    n++;
    //convert to WCHAR
    _itow_s(n, str, MAX_LOADSTRING, 10);
    //set to static2
    SendMessageW(hStatic2, WM_SETTEXT, 0, (LPARAM)str);
}

void processDecrement() {
    WCHAR str[MAX_LOADSTRING];
    SendMessageW(hStatic2, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)str);
    //convert int
    int n = _wtoi(str);
    //increment
    Beep(400,50);
    n--;
    //convert to WCHAR
    _itow_s(n, str, MAX_LOADSTRING, 10);
    //set to static2
    SendMessageW(hStatic2, WM_SETTEXT, 0, (LPARAM)str);
}

void processPlusTen() {
    WCHAR str[MAX_LOADSTRING];
    SendMessageW(hStatic2, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)str);
    //convert int
    int n = _wtoi(str);
    //increment
    Beep(500, 50);
    int pten = n + 10;
    //convert to WCHAR
    _itow_s(pten, str, MAX_LOADSTRING, 10);
    //set to static2
    SendMessageW(hStatic2, WM_SETTEXT, 0, (LPARAM)str);
}

void processMinusTen() {
    WCHAR str[MAX_LOADSTRING];
    SendMessageW(hStatic2, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)str);
    //convert int
    int n = _wtoi(str);
    //increment
    Beep(400, 50);
    int mten = n - 10;;
    //convert to WCHAR
    _itow_s(mten, str, MAX_LOADSTRING, 10);
    //set to static2
    SendMessageW(hStatic2, WM_SETTEXT, 0, (LPARAM)str);
}

void processReset() {
    WCHAR str[MAX_LOADSTRING];
    SendMessageW(hStatic2, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)str);
    //convert int
    int n = _wtoi(str);
    //increment
    Beep(200, 50);
    int reset = n = 0; 
    //convert to WCHAR
    _itow_s(reset, str, MAX_LOADSTRING, 10);
    //set to static2
    SendMessageW(hStatic2, WM_SETTEXT, 0, (LPARAM)str);
}

LRESULT CALLBACK WndProcControls(HWND, UINT, WPARAM, LPARAM);

void createControls(HWND);
HWND hwndCheckbox;
HWND hwndPushlike;
HWND hwndTEXT;


void showWindowControls() {
    if(!isControlsReg){
        WNDCLASSEXW wcex;
        ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
         wcex.cbSize = sizeof(WNDCLASSEX);
         wcex.lpfnWndProc = WndProcControls;
         wcex.hInstance = hInst;
         wcex.lpszClassName = L"ControlsWindow";
         wcex.hbrBackground = CreateSolidBrush(RGB(150,200,150));
         wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
         
             if (!RegisterClassExW(&wcex)) {
                  MessageBoxW(mainWindow, L"Reguster class error", 
                     L"Error",  MB_OK | MB_ICONERROR);
                    return;
              }
        isControlsReg = TRUE;
    }
   
    HWND contorlWindow = CreateWindowW(L"ControlsWindow", L"Controls",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 800, 600,
        mainWindow, NULL, hInst, 0);
    ShowWindow(contorlWindow, SW_NORMAL);
}

LRESULT CALLBACK WndProcControls(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch (message){
    case WM_CREATE:
        createControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case CMD_CHECKBOX:
        {
            LRESULT state = SendMessageW(hwndCheckbox, BM_GETCHECK, 0, 0);
            if(state == BST_CHECKED)
                 
            SendMessage(hwndCheckbox,  BM_SETCHECK, BST_UNCHECKED, 0);
            else
            SendMessage(hwndCheckbox, BM_SETCHECK, BST_CHECKED, 0);

            SendMessageW(hwndCheckbox, WM_KILLFOCUS, 0, 0);
            break;
        }
        case CMD_PUSHLIKE: 
        {
            
            LRESULT state = SendMessageW(hwndPushlike, BM_GETCHECK, 0, 0);
            if (state == BST_CHECKED)
                

            
            SendMessage(hwndPushlike, BM_SETCHECK, BST_UNCHECKED,0);
            
            else

                SendMessage(hwndPushlike, BM_SETCHECK, BST_CHECKED, 0);

            SendMessageW(hwndPushlike, WM_KILLFOCUS, 0, 0);
            break;
        }
       }
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);

    }
    return 0;
}


void createControls(HWND hWnd) {
    CreateWindowW(L"Button", L"Buttons", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        10, 10, 380, 200, hWnd, NULL, hInst, 0);
    CreateWindowW(L"Button", L"Push", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 40, 75, 23, hWnd, NULL, hInst, 0);
    CreateWindowW(L"Button", L"Def", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        20, 70, 75, 23, hWnd, NULL, hInst, 0);
    CreateWindowW(L"Button", L"Like", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE,
        20, 100, 75, 23, hWnd, NULL, hInst, 0);
 LPCWSTR lpWindowName;
   hwndCheckbox = CreateWindowW(L"Button", L"Checkbox", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
        20, 130, 75, 23, hWnd, (HMENU)CMD_CHECKBOX, hInst, 0);
    hwndPushlike = CreateWindowW(L"Button", L"Press", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_PUSHLIKE,
        20, 160, 75, 23, hWnd, (HMENU)CMD_PUSHLIKE, hInst, 0);

}