#include "PaintWin32Dlg.h"

#include "time.h"

#define ID_EDIT_DELETE WM_USER+1
#define ID_FILE_NEW WM_USER+6
#define ID_FILE_OPEN WM_USER+7
#define ID_FILE_SAVE WM_USER+8
#define ID_EDIT_CUT WM_USER+13
#define ID_EDIT_COPY WM_USER+14
#define ID_EDIT_PASTE WM_USER+15


CDlg* CDlg::ptr = NULL;

BOOL fDraw = FALSE;
POINT ptPrevious = { 0 };
int	IsCLS = 0;
int	L100 = 0;
static int      cxClient, cyClient;
static POINT    ptCenter;
HDC             hdc;
PAINTSTRUCT     ps;
static HPEN		pen;
COLORREF pencolor;
COLORREF BCcolor;
const int MinY = 70;
//хэндлы текстовых полей дополнительного диалога
HWND hEDIT1, hBCOLOR, hSTATIC;

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, HPEN pen) {
	SelectObject(hdc, pen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

CDlg::CDlg(void)
{
	ptr = this;
}

void CDlg::Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
	PostQuitMessage(0);
}

void CDlg::Cls_OnLBUTTONDOWN(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
	if (y > MinY) {
		fDraw = TRUE;
		ptPrevious.x = x;
		ptPrevious.y = y;
	}
}

void CDlg::Cls_OnLBUTTONUP(HWND hWnd, int x, int y, UINT keyFlags){
	TCHAR buf[255];   //временный буффер для данных	
	GetWindowTextA(hEDIT1, (LPSTR)buf, 5);
	int w = atoi((char*)buf);
	
	if (fDraw && y > MinY + (w + 3) / 2) {
		hdc = GetDC(hWnd);
		MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
		pen = CreatePen(PS_SOLID, w, pencolor);
		SelectObject(hdc, pen);

		LineTo(hdc, x, y);
		ReleaseDC(hWnd, hdc);
		fDraw = FALSE;
	}
}

void CDlg::Cls_OnMOUSEMOVE(HWND hWnd, int x, int y, UINT keyFlags) {
	TCHAR buf[255];   //временный буффер для данных	
	GetWindowTextA(hEDIT1, (LPSTR)buf, 5);
	int w = atoi((char*)buf);

	if (fDraw && y > MinY + (w + 3) / 2) {
	
		hdc = GetDC(hWnd);
		MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
		pen = CreatePen(PS_SOLID, w, pencolor);
		SelectObject(hdc, pen);
		LineTo(hdc,	ptPrevious.x = x,	ptPrevious.y = y);
		/*if (pencolor = RGB(255, 255, 255)) {
			InvalidateRect(hSTATIC, NULL, FALSE);
		}*/
		ReleaseDC(hWnd, hdc);
	}

}
void CDlg::Cls_OnPaint(HWND hWnd) {
	hdc = BeginPaint(hWnd, &ps);
	if (IsCLS) {
		IsCLS = 0;  
	} 
	
	HDC dc = GetDC(hWnd); //Цепляемся к консольному окну
	//RECT window = {}; //Переменная window будет использована для получения ширины и высоты окна

	HBRUSH  hBrush = CreateSolidBrush(RGB(255, 255, 255)); // Создаём кисть определённого стиля и цвета
	SelectObject(dc, hBrush); //Выбираем кисть
	RECT WinCoord = {}; //Массив координат окна 
	GetWindowRect(hWnd, &WinCoord); //Узнаём координаты

	Rectangle(dc, 0, 0, WinCoord.right, WinCoord.bottom); //Нарисовали прямоугольник, закрашенный неким стилем		
	DeleteObject(hBrush); //Очищаем память от созданной, но уже ненужной кисти
	
	EndPaint(hWnd, &ps);
}

BOOL CDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;                            //сохраняем дескриптор окна

	RECT  rect;
	IsCLS = 0;
	GetWindowRect(hDialog, &rect);
	cxClient = rect.right - rect.left;
	cyClient = rect.bottom - rect.top;
	srand(time(NULL));        //сбрасываем таймер для генератора случайных чисел
	hEDIT1 = GetDlgItem(hDialog, IDC_EDIT1);
	hBCOLOR = GetDlgItem(hDialog, IDC_BCOLOR);
	hSTATIC = GetDlgItem(hDialog, IDC_STATIC);

	SetWindowText(hEDIT1, TEXT("2"));  //очищаем статик
	pencolor = RGB(0, 0, 255);
	//SetTextColor(hEDIT1, RGB(255, 0, 0));
	//HBRUSH oldbrush = (HBRUSH)GetClassLong(hwnd, GCL_HBRBACKGROUND);

	//HBRUSH brush = CreateSolidBrush(RGB(255,100,0));
	//SetClassLong(hwnd, GCL_HBRBACKGROUND, (long)brush);
	HBRUSH hBrush = (HBRUSH)GetClassLong(hwnd, GCL_HBRBACKGROUND);

	LOGBRUSH logBrush;                                    // объект, который хранит информацию о hBrush
	GetObject(hBrush, sizeof(LOGBRUSH), &logBrush);       // получаем logBrush

	BCcolor = logBrush.lbColor;                    // берём цвет
	hBrush = CreateSolidBrush(RGB(255, 100, 0));
	SetClassLong(hwnd, GCL_HBRBACKGROUND, (long)hBrush);


	HDC dc = GetDC(hwnd); //Цепляемся к консольному окну
	RECT window = {}; //Переменная window будет использована для получения ширины и высоты окна

	hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 255, 0)); // Создаём кисть определённого стиля и цвета
	SelectObject(dc, hBrush); //Выбираем кисть
	RECT WinCoord = {}; //Массив координат окна 
	GetWindowRect(hwnd, &WinCoord); //Узнаём координаты

	Rectangle(dc, 0, 0, WinCoord.right, WinCoord.bottom); //Нарисовали прямоугольник, закрашенный неким стилем		
	DeleteObject(hBrush); //Очищаем память от созданной, но уже ненужной кисти


	return TRUE;

}

//обработка событий от пунктов меню и от кнопок
void CDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify){
	COLORREF cust_colors[16] = { 0 };
	CHOOSECOLOR ch_color = { 0 };
	ch_color.lStructSize = sizeof(CHOOSECOLOR);
	ch_color.hwndOwner = hWnd;

	ch_color.lpCustColors = cust_colors;
	RECT w = {}; //Переменная window будет использована для получения ширины и высоты окна
	 switch(id)
	{
		case  ID_FILE_EXIT:   //выход из программы
		case  IDOK:
    		  Cls_OnClose(hWnd);	
			  break;

		case  IDM_LINE100:
			L100 = 1;
			//InvalidateRect(hWnd, NULL, false);
			hdc = GetDC(hWnd);

			for (int i = 0; i < 100; i++) {
				pen = CreatePen(PS_SOLID, rand() % 5, RGB(rand() % 170 + 85, rand() % 170 + 85, rand() % 170 + 85));
				//Формула генератора случайного числа в диапазоне от A до B : r= rand()%(B-A+1) + A
				int x1 = rand() % (cxClient - 100);
				int y1 = rand() % (cyClient - 100 - MinY + 1) + MinY;
				DrawLine(hdc, x1, y1, x1 + rand() % 65, y1 + rand() % 55, pen);
			}
			ReleaseDC(hWnd, hdc);
			break;

		case  IDM_CLEARALL:
			IsCLS = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDC_BCOLOR:
				if (ChooseColor(&ch_color)) {
					pencolor = ch_color.rgbResult;
				}
			  break;
		/*case IDC_BFILL:
			w.bottom = 75;
			w.top = 0;
			w.left = 1;
			w.right = cxClient - 1;
			//InvalidateRect(hSTATIC, &w, FALSE);
			//UpdateWindow(hSTATIC);
			//hdc = GetDC(hWnd);
			//ExtFloodFill(hdc, ptPrevious.x, ptPrevious.y, RGB(0, 255, 255), FLOODFILLSURFACE);
			//ReleaseDC(hWnd,  hdc);
			break;*/
		case IDC_BCLS: 
			pencolor = RGB(255, 255, 255);
			break;
			
		case IDC_BLINE:
			//pencolor = RGB(255, 255, 255);
			break;

	}
   
}

/*void QueueFill(HDC hdc, int xStart, int yStart)
{
	POINT pt = { xStart, yStart };
	std::queue <POINT> Pts;
	Pts.push(pt);
	while (!Pts.empty())
	{
		pt = Pts.front(); Pts.pop();
		switch (GetPixel(hdc, pt.x, pt.y))
		{
		case CLR_INVALID: case RGB(0, 0, 0): case RGB(255, 0, 0):
			break;
		default:
			SetPixel(hdc, pt.x, pt.y, RGB(0xFF, 0, 0));
			--pt.y;         Pts.push(pt);
			++pt.y; ++pt.y; Pts.push(pt);
			--pt.y; ++pt.x; Pts.push(pt);
			--pt.x; --pt.x; Pts.push(pt);
		}
	}
}*/

BOOL CALLBACK CDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_PAINT, ptr->Cls_OnPaint);
		//HANDLE_WM_LBUTTONDOWN(hwnd, wParam, lParam, ptr->Cls_OnLBUTTONDOWN);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, ptr->Cls_OnLBUTTONDOWN);
		HANDLE_MSG(hwnd, WM_LBUTTONUP,   ptr->Cls_OnLBUTTONUP);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE,   ptr->Cls_OnMOUSEMOVE);	
	}
	return FALSE;
}

/*
void col(HWND hwnd)
{
CHOOSECOLOR ch_color = { 0 };
ch_color.lStructSize = sizeof(CHOOSECOLOR);
ch_color.hwndOwner = hwnd;
COLORREF cust_colors[16] = { 0 };
ch_color.lpCustColors = cust_colors;
if(ChooseColor(&ch_color))
{
colClndr = ch_color.rgbResult;
}
}

// ...
case WM_CHAR:
col(hwnd); 
SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG) CreateSolidBrush(colClndr));
InvalidateRect(hwnd, 0, TRUE);
break;
*/