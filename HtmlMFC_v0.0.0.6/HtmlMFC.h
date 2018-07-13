// HtmlMFC.h : main header file for the HTMLMFC application
//

#if !defined(AFX_HTMLMFC_H__13668E0B_8391_4F12_A11C_7283D61368F8__INCLUDED_)
#define AFX_HTMLMFC_H__13668E0B_8391_4F12_A11C_7283D61368F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHtmlMFCApp:
// See HtmlMFC.cpp for the implementation of this class
//

class CHtmlMFCApp : public CWinApp
{
public:
	CHtmlMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHtmlMFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLMFC_H__13668E0B_8391_4F12_A11C_7283D61368F8__INCLUDED_)
