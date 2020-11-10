#include "logic.h"

#define START_HACKING 2

using namespace std;

void statusProcessAcessWrite();
void bateriaTestes();
bool processHunter();
bool verifyStatusGame();
void processModify();
void testProcessWrite();
void addButtons(HWND hWnd);
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

// Windows - Contem elementos da tela, como botões
HWND hGameProcess;
HWND textStatus;
HWND textStaticGame;
HWND textStatusGame;
HWND textStatusProcess;
//

bool status;
LPCTSTR text = L"Offline";
LPCTSTR textGame = text;
LPCTSTR textProcess = L"Impossível acessar!";
bool test;
HDC hdc;
HFONT hfont;
LOGFONT lf;

DWORD processID;
HANDLE handle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSW window = {0};
	window.hbrBackground = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 255));
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hInstance = hInstance;
	window.lpszClassName = L"HackingWindowClass";
	window.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&window)) {
		return -1;
	}

	HWND windwPrincipal = CreateWindowW(window.lpszClassName, L"Hacking Process", WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU, 100, 100, 
		500, 500, NULL, NULL, hInstance, NULL);
	ShowWindow(windwPrincipal, nCmdShow);              //display the window on the screen
	UpdateWindow(windwPrincipal);             //make sure the window is updated correctly
	MSG msg = {0};

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg,
	WPARAM wp, LPARAM lp) { // função que recebe os eventos da janela, e envia em forma de mensagem
	switch (msg) {
	case WM_COMMAND:
		switch (wp){
		case START_HACKING:
			status = !status;
			if (status == true) {
				text = L"Online";
				SendMessage(hWnd, WM_CTLCOLOREDIT, NULL, (LPARAM)textStatus);
				SendMessage(textStatus, WM_CTLCOLOREDIT, NULL, (LPARAM)textStatus);
				SendMessage(textStatus, WM_CTLCOLOREDIT, NULL, TRUE);
			}
			else {
				text = L"Offline";
			}
			SetWindowText(textStatus, text);
			break;
		default:
			break;
		}
	case WM_CREATE:
		addButtons(hWnd);
		break;

	case WM_SETTEXT:
		break;

	case WM_SETFONT:
		break;

	case WM_CTLCOLORSTATIC:
		if((HWND)lp == textStatus){
			SetTextColor((HDC)wp, RGB(255, 0, 0)); // red
			return (LRESULT)CreateSolidBrush(RGB(255, 0, 0)); // red
		}
		else{
			return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
		}
		break;
	
	case WM_CTLCOLOREDIT:
		if ((HWND)lp == textStatus) {
			if (status == true) {
				SetTextColor((HDC)wp, RGB(255, 0, 0)); // red
				return (LRESULT)((HBRUSH)GetStockObject(BLACK_BRUSH));
			}
			else {
				SetTextColor((HDC)wp, RGB(255, 0, 0)); // red
				return (LRESULT)CreateSolidBrush(RGB(255, 0, 0)); // red
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	case WM_ACTIVATE:
		bateriaTestes();
		processModify();
		break;

	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
		break;
	}
}

void addButtons(HWND hWnd) {
	textStaticGame = CreateWindowW(L"Static", L"Status:", WS_VISIBLE | WS_CHILD, 204, 150, 40, 15, hWnd, NULL, NULL, NULL); // texto
	textStatus = CreateWindowW(L"Static", text, WS_VISIBLE | WS_CHILD, 250, 150, 37, 15, hWnd, NULL, NULL, NULL); // texto
	CreateWindowW(L"Button", L"HACKING", WS_VISIBLE | WS_CHILD, 204, 194, 60, 40, hWnd, (HMENU) START_HACKING, NULL, NULL);
	CreateWindowW(L"Static", L"Status Game:", WS_VISIBLE | WS_CHILD, 170, 250, 87, 16, hWnd, NULL, NULL, NULL); // texto
	textStatusGame = CreateWindowW(L"Static", textGame, WS_VISIBLE | WS_CHILD, 280, 250, 50, 30, hWnd, NULL, NULL, NULL); // texto status game
	textStatusProcess = CreateWindowW(L"Static", textProcess, WS_VISIBLE | WS_CHILD, 170, 290, 150, 30, hWnd, NULL, NULL, NULL); // texto status Process
	GetObject(GetStockObject(LTGRAY_BRUSH | DC_BRUSH | BLACK_BRUSH | BLACK_PEN), sizeof(LOGFONT), &lf);
	hfont = CreateFont(lf.lfHeight, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, lf.lfWeight, lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily, lf.lfFaceName);
	SendMessage(textStaticGame, WM_SETFONT, (WPARAM)hfont, TRUE);
	SendMessage(textStatus, WM_SETFONT, (WPARAM)hfont, TRUE);
	SendMessage(textStatusGame, WM_SETFONT, (WPARAM)hfont, TRUE);
	SendMessage(textStatusProcess, WM_SETFONT, (WPARAM)hfont, TRUE);
}

bool verifyStatusGame(){
	hGameProcess = FindWindow(NULL, L"Counter-Strike"); // Processo que queremos usar para sobrescrever a memória
	if (hGameProcess != NULL) {
		return true;
	}
	return false;
}

void bateriaTestes() {
	testProcessWrite();
	statusProcessAcessWrite();
	Sleep(100);
}

void testProcessWrite() {
	if (verifyStatusGame()) {
		textGame = L"Online";
		test = true;
	}
	else {
		textGame = L"Offline";
		test = false;
	}
	SetWindowText(textStatusGame, textGame);
}

bool processHunter() {
	GetWindowThreadProcessId(hGameProcess, &processID);
	handle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);

	if (handle != NULL) {
		return true;
	}
	return false;
}

void statusProcessAcessWrite() {
	if (processHunter()) {
		textProcess = L"Acesso liberado ao Processo";
	}
	else {
		textProcess = L"Impossível acessar!";
	}
	SetWindowText(textStatusProcess, textProcess);
}

void processModify() {
	int valor = 70;
	if (status == true) {
		if (verifyStatusGame()) {
			if (processHunter()) {
				WriteProcessMemory(handle, (LPVOID)(0x01900000 + 0xF4B04), &valor, sizeof(int), 0);
				WriteProcessMemory(handle, (LPVOID)(0x01D00000 + 0x11FDAF0), &valor, sizeof(int), 0);
				WriteProcessMemory(handle, (LPVOID)(0x01D00000 + 0x10568EC), &valor, sizeof(int), 0);
			}
		}
	}
}

void HunterAdress(){
	//Get ProcId of the target process
	DWORD procId = GetProcId(L"Counter-Strike.exe");

	//Getmodulebaseaddress
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Counter-Strike.exe");

	//Get Handle to Process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	//Resolve base address of the pointer chain
	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x10f4f4;

	std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

	//Resolve our ammo pointer chain
	std::vector<unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };
	uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

	std::cout << "ammoAddr = " << "0x" << std::hex << ammoAddr << std::endl;

	//Read Ammo value
	int ammoValue = 0;

	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "Curent ammo = " << std::dec << ammoValue << std::endl;

	//Write to it
	int newAmmo = 1337;
	WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

	//Read out again
	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
}
