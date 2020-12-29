#include "PaintWin32Dlg.h"

//главная функция программы
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	HACCEL axe;                  //дескриптор акселлератора
	axe=LoadAccelerators (hInst, //дескриптор приложения
		MAKEINTRESOURCE(IDR_ACCELERATOR1));//загружаем акселлератор
	
	MSG msg;              //структура для сообщений
	CDlg dlg;
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE (IDD_DIALOG1),NULL,dlg.DlgProc);

	ShowWindow(hDialog,nCmdShow);

	//цикл обработки сообщений
	while(GetMessage(&msg,0,0,0))
	{
		if ( !TranslateAccelerator(hDialog,          //дескриптор окна
			axe,&msg) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
