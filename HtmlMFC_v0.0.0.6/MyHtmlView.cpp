// MyHtmlView.cpp: implementation of the CMyHtmlView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HtmlMFC.h"
#include "MyHtmlView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyHtmlView::CMyHtmlView()
{

}

CMyHtmlView::~CMyHtmlView()
{

}


//JavaScript调用这个对象的方法时，会把方法名，放到rgszNames中，我们需要给这个方法名拟定一个唯一的数字ID，用rgDispId传回给它
//同理JavaScript存取这个对象的属性时，会把属性名放到rgszNames中，我们需要给这个属性名拟定一个唯一的数字ID，用rgDispId传回给它
//紧接着JavaScript会调用Invoke，并把这个ID作为参数传递进来
HRESULT STDMETHODCALLTYPE CMyHtmlView::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	//rgszNames是个字符串数组，cNames指明这个数组中有几个字符串，如果不是1个字符串，忽略它
	if (cNames != 1)
		return E_NOTIMPL;

	if (wcscmp(rgszNames[0], L"CloseWindow") == 0)
	{
		*rgDispId = FUNCTION_CloseWindow;
		return S_OK;
	}
	else if (wcscmp(rgszNames[0], L"MinWindow") == 0)
	{
		*rgDispId = FUNCTION_MinWindow;
		return S_OK;
	}
	else if (wcscmp(rgszNames[0], L"MaxWindow") == 0)
	{
		*rgDispId = FUNCTION_MaxWindow;
		return S_OK;
	}
	else if (wcscmp(rgszNames[0], L"MoveWindowPos") == 0)
	{
		*rgDispId = FUNCTION_MoveWindowPos;
		return S_OK;
	}
	else
		return E_NOTIMPL;
}

//JavaScript通过GetIDsOfNames拿到我的对象的方法的ID后，会调用Invoke，dispIdMember就是刚才我告诉它的我自己拟定的ID
//wFlags指明JavaScript对我的对象干了什么事情！
//如果是DISPATCH_METHOD，说明JavaScript在调用这个对象的方法，比如cpp_object.ShowMessageBox();
//如果是DISPATCH_PROPERTYGET，说明JavaScript在获取这个对象的属性，比如var n = cpp_object.num;
//如果是DISPATCH_PROPERTYPUT，说明JavaScript在修改这个对象的属性，比如cpp_object.num = 10;
//如果是DISPATCH_PROPERTYPUTREF，说明JavaScript在通过引用修改这个对象，具体我也不懂
//示例代码并没有涉及到wFlags和对象属性的使用，需要的请自行研究，用法是一样的
//pDispParams就是JavaScript调用我的对象的方法时传递进来的参数，里面有一个数组保存着所有参数
//pDispParams->cArgs就是数组中有多少个参数
//pDispParams->rgvarg就是保存着参数的数组，请使用[]下标来访问，每个参数都是VARIANT类型，可以保存各种类型的值
//具体是什么类型用VARIANT::vt来判断，不多解释了，VARIANT这东西大家都懂
//pVarResult就是我们给JavaScript的返回值
//其它不用管
HRESULT STDMETHODCALLTYPE CMyHtmlView::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,
												WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	//通过ID我就知道JavaScript想调用哪个方法
	if (dispIdMember == FUNCTION_MinWindow)
	{
		//检查是否只有一个参数
		// 		if (pDispParams->cArgs != 1)
		// 			return E_NOTIMPL;
		// 		//检查这个参数是否是字符串类型
		// 		if (pDispParams->rgvarg[0].vt != VT_BSTR)
		// 			return E_NOTIMPL;
		//放心调用
		//ShowMessageBox(pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal);

		MinWindow();
		return S_OK;
	}
	else if (dispIdMember == FUNCTION_MaxWindow)
	{
// 		long id = GetProcessID();
// 		*pVarResult = CComVariant(id);
		MaxWindow();
		return S_OK;
	}
	else if (dispIdMember == FUNCTION_CloseWindow)
	{
		//DWORD id = test1();
		//		*pVarResult = CComVariant(id);

		closeWindow();
		return S_OK;
	}
	else if(dispIdMember == FUNCTION_MoveWindowPos)
	{
		MoveWindowPos(pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal);	
		return S_OK;
	}
	else
		return E_NOTIMPL;
}


void CMyHtmlView::closeWindow()
{
	::PostQuitMessage(0);
}

void CMyHtmlView::MaxWindow()
{
	::PostMessage(GetParent()->GetSafeHwnd(), WM_MAINJS_MAX, NULL, NULL);
}

void CMyHtmlView::MinWindow()
{

	::PostMessage(GetParent()->GetSafeHwnd(), WM_MAINJS_MINIMIZE, NULL, NULL);
}

void CMyHtmlView::MoveWindowPos(CString x, CString y)
{
	int iX = atoi(x);
	int iY = atoi(y);

	TRACE("%d, %d\n", iX, iY);
	::PostMessage(GetParent()->GetSafeHwnd(), WM_MAINJS_MOVE, (WPARAM)iX, (LPARAM)iY);
}



// void CDemoHtmlView::CloseWindow()
// {
// 	::PostMessage(GetParent()->GetSafeHwnd(), WM_MAINJS_CLOSE, NULL, NULL);
// 	return;
// }
// 
// void CDemoHtmlView::MinimizeWindow()
// {
// 	::PostMessage(GetParent()->GetSafeHwnd(), WM_MAINJS_MINIMIZE, NULL, NULL);
// 	return;
// }
// 
// void CDemoHtmlView::ClickCaption(LPCTSTR _bstr)
// {
// 	::PostMessage(GetParent()->GetSafeHwnd(), WM_MAINJS_MOVE, (WPARAM)_bstr, NULL);
// 	return;
// }
// 
// void CDemoHtmlView::SetSlideIn(short iShort)
// {
// 	::PostMessage(GetParent()->GetSafeHwnd(), WM_MAINJS_SLIDEIN, (WPARAM)iShort, NULL);
// 	return;
// }
