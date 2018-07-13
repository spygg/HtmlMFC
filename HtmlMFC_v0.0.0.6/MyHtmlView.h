// MyHtmlView.h: interface for the CMyHtmlView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYHTMLVIEW_H__15EBE886_2F97_4224_8073_A9DD0F3913E6__INCLUDED_)
#define AFX_MYHTMLVIEW_H__15EBE886_2F97_4224_8073_A9DD0F3913E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseHtmlView.h"



#define WM_MAINJS_MINIMIZE WM_USER + 2
#define WM_MAINJS_MAX WM_USER + 3
#define WM_MAINJS_MOVE WM_USER + 4

enum
{
	FUNCTION_MinWindow,
	FUNCTION_MaxWindow,
	FUNCTION_CloseWindow,
	FUNCTION_MoveWindowPos
};

class CMyHtmlView : public CBaseHtmlView  
{
public:
	CMyHtmlView();
	virtual ~CMyHtmlView();


	// JS ����MFC�Ľӿ�
	// ��Ҫע�����JS�Ĵ���˳���VC���Ƿ��ŵ�
private:
	void closeWindow();
	void MinWindow();
	void MaxWindow();
	void MoveWindowPos(CString x, CString y);
	// MFC  ����JavaScript�ӿ�
	//ֱ�Ӽ̳и���� CallJScript


//��ת����,����,
private:
	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember,
		REFIID riid,
		LCID lcid,
		WORD wFlags,
		DISPPARAMS *pDispParams,
		VARIANT *pVarResult,
		EXCEPINFO *pExcepInfo,
		UINT *puArgErr);

	HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid,
		LPOLESTR *rgszNames,
		UINT cNames,
		LCID lcid,
		DISPID *rgDispId);
};

#endif // !defined(AFX_MYHTMLVIEW_H__15EBE886_2F97_4224_8073_A9DD0F3913E6__INCLUDED_)
