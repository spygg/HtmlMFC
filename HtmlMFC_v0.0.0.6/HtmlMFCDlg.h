// HtmlMFCDlg.h : header file
//

#if !defined(AFX_HTMLMFCDLG_H__49B8872E_88A2_4E5B_AA01_C63907DBA006__INCLUDED_)
#define AFX_HTMLMFCDLG_H__49B8872E_88A2_4E5B_AA01_C63907DBA006__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHtmlMFCDlg dialog
#include "MyHtmlView.h"

class CHtmlMFCDlg : public CDialog
{
// Construction
public:
	CHtmlMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHtmlMFCDlg)
	enum { IDD = IDD_HTMLMFC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlMFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHtmlMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnJSMoveWindow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnJsMinWindow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnJsMaxWindow(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMyHtmlView m_htmlView;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLMFCDLG_H__49B8872E_88A2_4E5B_AA01_C63907DBA006__INCLUDED_)
