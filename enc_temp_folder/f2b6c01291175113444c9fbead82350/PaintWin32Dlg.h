#pragma once
#include "header.h"

class CDlg
{
	static CDlg *ptr;

public:
	CDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnPaint(HWND hWnd);
	void Cls_OnLBUTTONDOWN(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
	void Cls_OnLBUTTONUP(HWND hWnd, int x, int y, UINT keyFlags);
	void Cls_OnMOUSEMOVE(HWND hWnd, int x, int y, UINT keyFlags);
	//объ€вление глобальных переменных
	HWND hDialog;
	};
