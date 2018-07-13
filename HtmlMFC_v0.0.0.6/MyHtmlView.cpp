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


//JavaScript�����������ķ���ʱ����ѷ��������ŵ�rgszNames�У�������Ҫ������������ⶨһ��Ψһ������ID����rgDispId���ظ���
//ͬ��JavaScript��ȡ������������ʱ������������ŵ�rgszNames�У�������Ҫ������������ⶨһ��Ψһ������ID����rgDispId���ظ���
//������JavaScript�����Invoke���������ID��Ϊ�������ݽ���
HRESULT STDMETHODCALLTYPE CMyHtmlView::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	//rgszNames�Ǹ��ַ������飬cNamesָ������������м����ַ������������1���ַ�����������
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

//JavaScriptͨ��GetIDsOfNames�õ��ҵĶ���ķ�����ID�󣬻����Invoke��dispIdMember���Ǹղ��Ҹ����������Լ��ⶨ��ID
//wFlagsָ��JavaScript���ҵĶ������ʲô���飡
//�����DISPATCH_METHOD��˵��JavaScript�ڵ����������ķ���������cpp_object.ShowMessageBox();
//�����DISPATCH_PROPERTYGET��˵��JavaScript�ڻ�ȡ�����������ԣ�����var n = cpp_object.num;
//�����DISPATCH_PROPERTYPUT��˵��JavaScript���޸������������ԣ�����cpp_object.num = 10;
//�����DISPATCH_PROPERTYPUTREF��˵��JavaScript��ͨ�������޸�������󣬾�����Ҳ����
//ʾ�����벢û���漰��wFlags�Ͷ������Ե�ʹ�ã���Ҫ���������о����÷���һ����
//pDispParams����JavaScript�����ҵĶ���ķ���ʱ���ݽ����Ĳ�����������һ�����鱣�������в���
//pDispParams->cArgs�����������ж��ٸ�����
//pDispParams->rgvarg���Ǳ����Ų��������飬��ʹ��[]�±������ʣ�ÿ����������VARIANT���ͣ����Ա���������͵�ֵ
//������ʲô������VARIANT::vt���жϣ���������ˣ�VARIANT�ⶫ����Ҷ���
//pVarResult�������Ǹ�JavaScript�ķ���ֵ
//�������ù�
HRESULT STDMETHODCALLTYPE CMyHtmlView::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,
												WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	//ͨ��ID�Ҿ�֪��JavaScript������ĸ�����
	if (dispIdMember == FUNCTION_MinWindow)
	{
		//����Ƿ�ֻ��һ������
		// 		if (pDispParams->cArgs != 1)
		// 			return E_NOTIMPL;
		// 		//�����������Ƿ����ַ�������
		// 		if (pDispParams->rgvarg[0].vt != VT_BSTR)
		// 			return E_NOTIMPL;
		//���ĵ���
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
