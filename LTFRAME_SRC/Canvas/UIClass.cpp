#include "stdafx.h"

#include "UIClass.h"
#include <Psapi.h>






UIClass::UIClass()
{	
	HMODULE hModule = ::GetModuleHandle(0);
	applicationpath  = (wchar_t*)malloc((MAX_PATH+1)*sizeof(wchar_t)); 
	GetModuleFileName(NULL, applicationpath, MAX_PATH);
	(wcsrchr(applicationpath, '\\'))[1] = 0;
	int ww = 700,wh=500;
	OleInitialize(0);


	ltskinview= CreateLTFrameInstance(this,L"LTFrame-Canvas",NULL,WS_POPUP | WS_VISIBLE,0,0,ww,wh,0);


	LTNativeFunction p = (LTNativeFunction)(&UIClass::DragWindowFun);
	ltskinview->my("DragWindow",this,p,0);


	SetWindowText(ltskinview->windowHandle(),L"LTFrame-Canvas");	


	wstring path = L"D:\\WebKit\\LTFrame-exmaple\\Debug\\Template\\Canvas.html";
	ltskinview->loadFile(path.c_str());
	ltskinview->EnableDragFrameChangeSize(false);
	ltskinview->MessageLoop();
}


UIClass::~UIClass(void)
{
	OleUninitialize();
	free(applicationpath);
	delete ltskinview;
}

DEFINEFUNCTION UIClass::DragWindowFun(LTExecState* es)
{
DragWindow();
	return JsUndefined();
}


void UIClass::DragWindow()
{
	ReleaseCapture();
	POINT DownPoint;
	GetCursorPos(&DownPoint);
	SendMessage(ltskinview->windowHandle(),WM_NCLBUTTONDOWN,HTCAPTION,MAKEWPARAM(DownPoint.x,DownPoint.y));
}
void UIClass::QuitApp()
{
	ltskinview->QuitApp();
}
void UIClass::MinWindow()
{
	::ShowWindow(ltskinview->windowHandle(),SW_MINIMIZE);	
}
LRESULT UIClass::HandleUserMessage(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{

	return ltskinview->HandleMessage(hwnd,uMsg,wParam,lParam);

}
LPCWSTR UIClass::GetWindowClassName()
{
	return L"Canvas";
}
