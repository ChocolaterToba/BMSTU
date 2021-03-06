﻿#include <Windows.h>
#include <tchar.h>

#pragma comment (lib, "dwmapi.lib")
#include <dwmapi.h>

#include <cstdlib>
#include <string>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int RandTill(int max) {
	return std::rand() * max / RAND_MAX;
}

POINT RandomBetween(POINT* UL, POINT* BR) {
	return { UL->x + RandTill(BR->x - UL->x), UL->y + RandTill(BR->y - UL->y) };
}

void RandomShrink(POINT* UL, POINT* BR) {
	*UL = RandomBetween(UL, BR);
	*BR = RandomBetween(UL, BR);
}

void RandomShrink(RECT* rectangle) {
	POINT UL = { rectangle->left, rectangle->top };
	POINT BR = { rectangle->right, rectangle->bottom };
	RandomShrink(&UL, &BR);
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

typedef struct TimeoutInfo {
	TimeoutInfo(HWND hWnd, int timeout) : hWnd(hWnd) {
		if (timeout > 0) {
			this->timeout = timeout;
		}
		else {
			this->timeout = 0;
		}
	};

	HWND hWnd;  // handler of window to minimize
	int timeout;  // minimization timeout (seconds)
};

DWORD WINAPI MinimizeWindowTimeouted(LPVOID lpParam) {
	TimeoutInfo* info = (TimeoutInfo*) lpParam;

	Sleep(info->timeout * 1000);
	SendMessage(info->hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

	delete info;

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
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 255))); 	// Заполнение окна белым цветом 


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
	switch (message)		 // Обработчик сообщений
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы

	//case WM_PAINT:
	case WM_LBUTTONDOWN: {
		RECT rectangle;
		POINT ptClientUL;
		POINT ptClientBR;

		DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rectangle, sizeof(rectangle));
		RandomShrink(&rectangle);

 		HDC hdc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		FillRect(hdc, &rectangle, (HBRUSH)(CreateSolidBrush(RGB(RandTill(255), RandTill(255), RandTill(255)))));
		break;
	}

	case WM_RBUTTONDOWN: {
		POINT cursorPos = { 0, 0 };
		GetCursorPos(&cursorPos);

		HDC hdc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		TextOut(hdc, cursorPos.x, cursorPos.y, s2ws(std::string("Это окно закроется через 30 секунд")).c_str(), 35);

		TimeoutInfo* info = new TimeoutInfo(hWnd, 30);
		CreateThread(NULL, 0, MinimizeWindowTimeouted, info, 0, NULL);
	}

	default: 			// Обработка сообщения по умолчанию
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
