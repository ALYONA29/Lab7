#include "PaintWin32Dlg.h"

//������� ������� ���������
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	HACCEL axe;                  //���������� �������������
	axe=LoadAccelerators (hInst, //���������� ����������
		MAKEINTRESOURCE(IDR_ACCELERATOR1));//��������� ������������
	
	MSG msg;              //��������� ��� ���������
	CDlg dlg;
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE (IDD_DIALOG1),NULL,dlg.DlgProc);

	ShowWindow(hDialog,nCmdShow);

	//���� ��������� ���������
	while(GetMessage(&msg,0,0,0))
	{
		if ( !TranslateAccelerator(hDialog,          //���������� ����
			axe,&msg) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
