#include <Windows.h>
#include <tchar.h>

#pragma comment (lib, "dwmapi.lib")
#include <dwmapi.h>

#include <cstdlib>
#include <string>
#include <vector>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

DWORD WINAPI TurnPCOffTimeouted(LPVOID lpParam) {
	int* timeout = (int*)lpParam;
	Sleep(*timeout * 1000);
	SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);
	delete timeout;

	return 0;
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
		_T("Каркас Windows-приложения"), 		// Заголовок окна 
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

	case WM_LBUTTONDOWN: case WM_RBUTTONDOWN: {
		HWND secondhWnd;
		secondhWnd = FindWindow(NULL, _T("Second App"));
		if (secondhWnd == NULL) {
			int* timeout = new int(3);
			CreateThread(NULL, 0, TurnPCOffTimeouted, timeout, 0, NULL);
			messageString = "Second window not found";
		} else {
			if (message == WM_LBUTTONDOWN){
				SendMessage(secondhWnd, WM_USER+1, WPARAM(&hWnd), 0);
			}
			else {
				SendMessage(secondhWnd, WM_USER+2, WPARAM(&hWnd), 0);
			}
			messageString = "Sent window descriptor to second app";
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		if (messageString != "") {
			POINT cursorPos = { 0, 0 };
			GetCursorPos(&cursorPos);
			TextOut(hdc, cursorPos.x, cursorPos.y, s2ws(messageString).c_str(), messageString.length());
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
