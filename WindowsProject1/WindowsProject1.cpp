// WindowsProject1.cpp : Определяет точку входа для приложения.
//
#include <math.h>
#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	wc.hbrBackground = CreateSolidBrush(RGB(127,255,0)); 	// Заполнение окна белым цветом 

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
	int wx, wy;
	switch (message)		 // Обработчик сообщений
	{
	/*case WM_SIZE:
	{
		wx = LOWORD(lParam);
		wy = HIWORD(lParam);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(hdc, hbrush);
		//Ellipse(hdc, wx/2-100, wy/2-100, wx/2+100, wy/2+100);
			
		DeleteObject(hbrush);
		EndPaint(hWnd, &ps);
		break;
	}*/
	case WM_NCLBUTTONDBLCLK:
	{
		wx = LOWORD(lParam);
		wy = HIWORD(lParam);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH hbrush = CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255));
		SelectObject(hdc, hbrush);
		//Pie(hdc, wx / 2 - 100, wy / 2 - 100, wx / 2 + 100, wy / 2 + 100, wx/2-rand()%100, wy / 2 - rand() % 100, wx / 2 + rand() % 100, wy / 2 + rand() % 100);
		int x1, x2, y1, y2;
		double p2 = 2 * 3.14159265359;
		int xw = 0, yw = 0;
		int r = 100;
		int i = 1, N = 10;
		x1 = (int)(xw + r * cos(p2 * i / N));
		y1 = (int)(yw - r * sin(p2 * i / N));
		x2 = (int)(xw + r * cos(p2 * (i + 1) / N));
		y2 = (int)(yw - r * sin(p2 * (i + 1) / N));
		Pie(hdc, 0,0 , 100, 100,x1, y1,x2,y2);
		ValidateRect(hWnd, 0);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}