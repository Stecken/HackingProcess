#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memoryapi.h>
#include <memory.h>
#include <vector>

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, 
	WPARAM wp, LPARAM lp) { // função que recebe os eventos da janela, e envia em forma de mensagem
	switch (msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;	
		default:
			return DefWindowProcW(hWnd, msg, wp, lp);
	}
	
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSW window = {0};
	window.hbrBackground = (HBRUSH) COLOR_WINDOW;
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hInstance = hInstance;
	window.lpszClassName = L"HackingWindowClass";
	window.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&window)) {
		return -1;
	}

	CreateWindowW(window.lpszClassName, L"teste", WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU, 100, 100, 
		500, 500, NULL, NULL, NULL, NULL);

	MSG msg = {0};

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}