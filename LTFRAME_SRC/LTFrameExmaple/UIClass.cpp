#include "stdafx.h"

#include "UIClass.h"
#include "SubWindow.h"
#include "Shellapi.h"
using namespace SubWindowSpace;

namespace UIClassSpace{

UIClass* UIClassC=0;
DEFINEFUNCTION DragWindowFun(LTExecState* es)
{
	UIClassC->DragWindow();
	return JsUndefined();
}

DEFINEFUNCTION QuitAppFun(LTExecState* es)
{
	UIClassC->QuitApp();
	return JsUndefined();
}
DEFINEFUNCTION MinWindowFun(LTExecState* es)
{
	UIClassC->MinWindow();
	return JsUndefined();
}
DEFINEFUNCTION  OpenSubWindowFun(LTExecState* es)
{
	UIClassC->OpenSubWindow();
	return JsUndefined();
}


DEFINEFUNCTION OpenApplactionFun(LTExecState* es)
{
	int size = JsValue2StringW(es,GetJsParameter(es,0),0);
	wchar_t* t = new wchar_t[size+1];
	JsValue2StringW(es,GetJsParameter(es,0),t);
	UIClassC->OpenNewApplaction(t);
	delete [] t;
	return JsUndefined();
}

DEFINEFUNCTION OpenTransparentWindowFun(LTExecState* es)
{
	int size = JsValue2StringW(es,GetJsParameter(es,0),0);
	wchar_t* t = new wchar_t[size+1];
	JsValue2StringW(es,GetJsParameter(es,0),t);
	wstring str = wstring(L"Transparent.exe");
	if (!wcscmp(L"undefined",t))
	{
		UIClassC->OpenNewApplaction((wchar_t*)str.c_str(),0);
	}
	else{
		UIClassC->OpenNewApplaction((wchar_t*)str.c_str(),t);
	}
	delete [] t;
	return JsUndefined();
}


RECT UIClass::CenterWindow(int w,int h)
{
	int scrWidth,scrHeight;
	RECT rect;
	scrWidth=GetSystemMetrics(SM_CXSCREEN);
	scrHeight=GetSystemMetrics(SM_CYSCREEN);
	rect.left=(scrWidth-w)/2;
	rect.top=(scrHeight-h)/2;
	return rect;
}

UIClass::UIClass()
{	
	HMODULE hModule = ::GetModuleHandle(0);
	applicationpath  = (wchar_t*)malloc((MAX_PATH+1)*sizeof(wchar_t)); 
	GetModuleFileName(NULL, applicationpath, MAX_PATH);
	(wcsrchr(applicationpath, '\\'))[1] = 0;
	int ww = 700,wh=500;
	RECT rect = CenterWindow(ww,wh);
	OleInitialize(0);
	ltskinview= new LTFrameView(this,L"LTFrame",NULL,WS_POPUP | WS_VISIBLE,rect.left,rect.top,ww,wh,0);
	UIClassC =this;
	ltskinview->BindUserFunction("DragWindow",DragWindowFun,0);
	ltskinview->BindUserFunction("QuitApp",QuitAppFun,0);
	ltskinview->BindUserFunction("MinWindow",MinWindowFun,0);
	ltskinview->BindUserFunction("OpenSubWindow",OpenSubWindowFun,0);
	ltskinview->BindUserFunction("OpenApplaction",OpenApplactionFun,0);
	ltskinview->BindUserFunction("OpenTransparentWindow",OpenTransparentWindowFun,1);
	SetWindowText(ltskinview->windowHandle(),L"LTFrame");
	wstring path = L"http://localhost:3333/1.php";
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

void UIClass::OpenSubWindow()
{
	new SubWindow(ltskinview->windowHandle());
}
void UIClass::DragWindow()
{
	ReleaseCapture();
	POINT DownPoint;
	GetCursorPos(&DownPoint);
	SendMessage(ltskinview->windowHandle(),WM_NCLBUTTONDOWN,HTCAPTION,MAKEWPARAM(DownPoint.x,DownPoint.y));
}
void UIClass::OpenNewApplaction(wchar_t* name,wchar_t* params)
{
	wstring path =wstring(applicationpath)+name;
	ShellExecute(0, L"open", path.c_str(),params, 0, SW_SHOWNORMAL);
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
	switch(uMsg)
	{

	}
	return ltskinview->HandleMessage(hwnd,uMsg,wParam,lParam);
}


LPCWSTR UIClass::GetWindowClassName()
{
	return L"INDEX";
}
}