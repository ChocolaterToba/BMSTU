#include <Windows.h>
#include <tchar.h>

#pragma comment (lib, "dwmapi.lib")
#include <dwmapi.h>

#include <cstdlib>
#include <string>
#include <vector>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int RandTill(int max) {
	return std::rand() * max / RAND_MAX;
}

// Get random point inside rectangle made by Ul and BR points
POINT RandomBetween(POINT* UL, POINT* BR) {
	return { UL->x + RandTill(BR->x - UL->x), UL->y + RandTill(BR->y - UL->y) };
}

// Get random point anywhere on the screen
POINT RandomPoint() {
	return { RandTill(GetSystemMetrics(SM_CXSCREEN)), RandTill(GetSystemMetrics(SM_CYSCREEN)) };
}

// Change window size randomly (it will stay in current screen)
void RandomResize(POINT* UL, POINT* BR) {
	UL->x = 0;
	UL->y = 0;
	*BR = RandomPoint();
	*UL = RandomBetween(UL, BR);
}

void RandomResize(RECT* rectangle) {
	POINT UL = { rectangle->left, rectangle->top };
	POINT BR = { rectangle->right, rectangle->bottom };
	RandomResize(&UL, &BR);
	SetRect(rectangle, UL.x, UL.y, BR.x, BR.y);
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

// Center message string on window specified by hWnd with specified hdc
POINT CenterString(HWND hWnd, HDC hdc, std::string message) {
	RECT rectangle;
	GetClientRect(hWnd, &rectangle);
	SIZE messageSize;
	GetTextExtentPoint(hdc, s2ws(message).c_str(), message.length(), &messageSize);
	return POINT {
		(rectangle.right - rectangle.left - messageSize.cx) / 2,  // Centering message horizontally
		(rectangle.bottom - rectangle.top - messageSize.cy) / 2,  // Centering message vertically
	};
}

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255))); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Second App"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}


// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static std::string messageString = "";

	switch (message)		 // Обработчик сообщений
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы

	case WM_USER+1: case WM_LBUTTONDOWN: {
		messageString = "Received message from first app (left button pressed): ";
		messageString += std::to_string(*(int*)wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}

	case WM_USER + 2: case WM_RBUTTONDOWN: {
		RECT rectangle;
		GetClientRect(hWnd, &rectangle);
		RandomResize(&rectangle);
		SetWindowPos(hWnd, HWND_TOP, rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, SWP_DRAWFRAME);
		break;
	}

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		if (messageString != "") {
			POINT messageStartPos = CenterString(hWnd, hdc, messageString);
			TextOut(hdc, messageStartPos.x, messageStartPos.y, s2ws(messageString).c_str(), messageString.length());
			messageString = "";
		}
		EndPaint(hWnd, &ps);
		break;
	}

	default: 			// Обработка сообщения по умолчанию
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
