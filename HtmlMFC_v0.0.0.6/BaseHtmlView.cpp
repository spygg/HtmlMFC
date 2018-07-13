// BaseHtmlView.cpp : 实现文件
//

#include "stdafx.h"
#include "BaseHtmlView.h"


void GetModulePath(char *szPath)
{
	ASSERT(szPath != NULL);
	
	char szFileName[_MAX_PATH] = {0};
	char szDrive[_MAX_DRIVE] = {0};
	char szDir[_MAX_DIR] = {0};
	
	if (0 != ::GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle, szFileName, _MAX_PATH))
	{
		_tsplitpath(szFileName, szDrive, szDir, 0, 0);
		strcpy(szPath, szDrive);
		strcat(szPath, szDir);
	}
	else
	{
		GetCurrentDirectory(_MAX_PATH, szFileName);
		
		strcpy(szPath, szFileName);
	}
}


void SystemLog(char *szLog)
{
	TRACE("%s\n", szLog);
	
	char szFilePath[255] = {0};
	char szTmepPath[255] = {0};
	SYSTEMTIME tm;
	
	GetLocalTime(&tm);
	GetModulePath(szTmepPath);
	
	
	strcat(szTmepPath, "LogFile\\");
	
	if(_taccess(szTmepPath, 0) == -1)
	{
		CreateDirectory(szTmepPath, NULL);
	}
	sprintf(szFilePath, "%s%d%02d%02d.txt", szTmepPath, tm.wYear, tm.wMonth, tm.wDay);	
	
	FILE *fp = NULL;
	fp = fopen(szFilePath, "a+");
	
	if(fp)
	{
		fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] ", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
		fprintf(fp, "%s", szLog);
		if(szLog[strlen(szLog) - 1] != '\n')
		{
			fprintf(fp, "\n");
		}
		
		fclose(fp);
	}
	
}
// CBaseHtmlView

IMPLEMENT_DYNCREATE(CBaseHtmlView, CHtmlView)

CBaseHtmlView::CBaseHtmlView()
{
	memset(m_szUrl, 0, sizeof(m_szUrl));
}

CBaseHtmlView::~CBaseHtmlView()
{
}

void CBaseHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_DISPATCH_MAP(CBaseHtmlView, CHtmlView)

END_DISPATCH_MAP()

BEGIN_MESSAGE_MAP(CBaseHtmlView, CHtmlView)
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CBaseHtmlView 诊断

#ifdef _DEBUG
void CBaseHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBaseHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

#endif //_DEBUG


// CBaseHtmlView 消息处理程序


void CBaseHtmlView::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CWnd::PostNcDestroy();
}


int CBaseHtmlView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//return MA_ACTIVATE;
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CBaseHtmlView::OnDestroy()
{

	CWnd::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CBaseHtmlView::OnSize(UINT nType, int cx, int cy)
{
	CHtmlView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
// 	if (::IsWindow(m_wndBrowser.m_hWnd))
// 	{
// 		CRect rect;
// 		GetClientRect(rect);
// 		LONG lWindows = GetWindowLong(GetParent()->GetSafeHwnd(), GWL_EXSTYLE);
// 		//::AdjustWindowRectEx(rect, GetStyle(), FALSE, WS_CLIPSIBLINGS);
// 		//::AdjustWindowRectEx(rect, GetStyle(), FALSE, lWindows);
// 
// 		//m_wndBrowser.SetWindowPos(NULL, rect.left, rect.top, 962, 632, SWP_NOACTIVATE | SWP_NOZORDER);
// 
// 	}
}


void CBaseHtmlView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	char szHtml[255] = {0};
	
	if(strcmp(m_szUrl, "") == 0)
	{
		GetModulePath(szHtml);
		strcat(szHtml, "html\\index.html");
	}
	else
	{
		strcpy(szHtml, m_szUrl);
	}


	Navigate2(szHtml, NULL, NULL);
	SystemLog("Init\n");
}

//通过网址来判断
void CBaseHtmlView::OnDocumentComplete(LPCTSTR lpszURL)
{
	// TODO: 在此添加专用代码和/或调用基类
	//
//  	CString szUrl(lpszURL);
//  	if(szUrl.Find("index.html") != -1)
	{
		TRACE("%s\n", lpszURL);

		SetScriptDocument(); //初始化com组件 IID_IHTMLDocument2接口

		SetCppObjectForJavaScript();
	}
//	::SendMessage(GetParent()->GetSafeHwnd(), WM_HTML_LOAD_FINSH, NULL, NULL);
	CHtmlView::OnDocumentComplete(lpszURL);
}

BOOL CBaseHtmlView::CreateHtmlView(CWnd* pParent)
{

	CRect rc;
	pParent->GetClientRect(&rc);
	if (!Create(NULL, NULL, (WS_CHILD | WS_VISIBLE), rc, pParent, NULL, NULL))
		return FALSE;

	OnInitialUpdate();
	//SetSilent(TRUE);//add by wh ,bid pop script dlg  true表示允许界面弹出对话框
	return TRUE;
}

void CBaseHtmlView::SetUrl( char *szUrl )
{
	strcpy(m_szUrl, szUrl);
}



BOOL CBaseHtmlView::SetScriptDocument()
{
	CComPtr<IDispatch> spDisp = GetHtmlDocument(); //获取com 初始接口指针
	if (spDisp == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}
	
	m_spDoc = NULL;
	HRESULT hr = spDisp->QueryInterface(IID_IHTMLDocument2, (void **)&m_spDoc);
	if (FAILED(hr))
	{
		//MessageBox("Failed to get HTML document COM object");
		SystemLog("Failed to get HTML document COM object");
		return FALSE;
	}
	
	return TRUE;
}

BOOL CBaseHtmlView::GetJScript(CComPtr<IDispatch>& spDisp)
{
	if (m_spDoc == NULL)
		return FALSE;
	
	HRESULT hr = m_spDoc->get_Script(&spDisp); //获取Script接口

	//m_spDoc->put_bgColor( CComVariant("red") );

	ATLASSERT(SUCCEEDED(hr));
	return SUCCEEDED(hr);
}




const CString CBaseHtmlView::GetSystemErrorMessage(DWORD dwError)
{
	CString strError;
	LPTSTR lpBuffer;
	
	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
		(LPTSTR)&lpBuffer, 0, NULL))
	{
		strError = "FormatMessage Netive Error";
	}
	else
	{
		strError = lpBuffer;
		LocalFree(lpBuffer);
	}
	return strError;
}


BOOL CBaseHtmlView::CallJScript(const CString strFunc, const CStringArray& paramArray, _variant_t* pVarResult /*= NULL*/)
{
	CComPtr<IDispatch> spScript;
	if (!GetJScript(spScript))
	{
		SystemLog("函数GetJScrip调用失败！");
		return FALSE;
	}
	
	CComBSTR bstrFunc(strFunc);
	DISPID dispid = NULL;
	//根据名称strFunc 获取 ids
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL, &bstrFunc, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	if (FAILED(hr))
	{
		//MessageBox(GetSystemErrorMessage(hr));
		CString msg = GetSystemErrorMessage(hr);
		SystemLog(msg.GetBuffer(0));
		return FALSE;
	}
	
	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	
	INT_PTR arraySize = paramArray.GetSize();
	dispparams.cArgs = (UINT)arraySize; //参数个数
	dispparams.rgvarg = new VARIANT[dispparams.cArgs]; 
	
	for (int i = 0; i < arraySize; i++)
	{
		CComBSTR bstr = paramArray.GetAt(arraySize - 1 - i); // back reading
		bstr.CopyTo(&dispparams.rgvarg[i].bstrVal);
		dispparams.rgvarg[i].vt = VT_BSTR;
	}
	dispparams.cNamedArgs = 0;
	
 	EXCEPINFO excepInfo;
 	memset(&excepInfo, 0, sizeof excepInfo);
 	_variant_t vaResult;
 	UINT nArgErr = (UINT)-1;  // initialize to invalid arg
	
	//调用JaveScript接口
	hr = spScript->Invoke(dispid, IID_NULL, 0,
		DISPATCH_METHOD, &dispparams, &vaResult, &excepInfo, &nArgErr);
	
	delete[] dispparams.rgvarg;
	if (FAILED(hr))
	{
		//MessageBox(GetSystemErrorMessage(hr));
		CString msg = GetSystemErrorMessage(hr);
		SystemLog(msg.GetBuffer(0));
		return FALSE;
	}
	
	if (pVarResult)
	{
		*pVarResult = vaResult;
	}
	return TRUE;
}

BOOL CBaseHtmlView::SetCppObjectForJavaScript()
{
	_variant_t var(static_cast<IDispatch*>(this));
	CallJScriptV("SetCppObject", &var);

	return TRUE;
}

BOOL CBaseHtmlView::CallJScriptV(const CString strFunc, _variant_t* pVarIn, _variant_t* pVarResult /*= NULL*/)
{
	CComPtr<IDispatch> spScript;
	if (!GetJScript(spScript))
	{
		SystemLog("函数GetJScrip调用失败！");
		return FALSE;
	}
	
	CComBSTR bstrFunc(strFunc);
	DISPID dispid = NULL;
	//根据名称strFunc 获取 ids
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL, &bstrFunc, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	if (FAILED(hr))
	{
		CString msg = GetSystemErrorMessage(hr);
		SystemLog(msg.GetBuffer(0));
		return FALSE;
	}
	
	
	//调用JaveScript接口

	DISPPARAMS dispparams = { pVarIn, NULL, 1, 0};
	hr = spScript->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
		DISPATCH_METHOD, &dispparams, pVarResult, NULL, NULL);


	if (FAILED(hr))
	{
		//MessageBox(GetSystemErrorMessage(hr));
		CString msg = GetSystemErrorMessage(hr);
		SystemLog(msg.GetBuffer(0));
		return FALSE;
	}
	
	return TRUE;
}

BOOL CBaseHtmlView::CallJScript(const CString strFunc, _variant_t* pVarResult /*= NULL*/)
{
	CStringArray paramArray;
	return CallJScript(strFunc, paramArray, pVarResult);
}

BOOL CBaseHtmlView::CallJScript(const CString strFunc, const CString strArg1, _variant_t* pVarResult /*= NULL*/)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	return CallJScript(strFunc, paramArray, pVarResult);
}

BOOL CBaseHtmlView::CallJScript(const CString strFunc, const CString strArg1, const CString strArg2, _variant_t* pVarResult /*= NULL*/)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	paramArray.Add(strArg2);
	return CallJScript(strFunc, paramArray, pVarResult);
}

BOOL CBaseHtmlView::CallJScript(const CString strFunc, const CString strArg1, const CString strArg2, const CString strArg3, _variant_t* pVarResult /*= NULL*/)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	paramArray.Add(strArg2);
	paramArray.Add(strArg3);
	return CallJScript(strFunc, paramArray, pVarResult);
}


//不用实现，直接返回E_NOTIMPL
HRESULT STDMETHODCALLTYPE CBaseHtmlView::GetTypeInfoCount(UINT *pctinfo)
{
	return E_NOTIMPL;
}

//不用实现，直接返回E_NOTIMPL
HRESULT STDMETHODCALLTYPE CBaseHtmlView::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
	return E_NOTIMPL;
}


//JavaScript拿到我们传递给它的指针后，由于它不清楚我们的对象是什么东西，会调用QueryInterface来询问我们“你是什么鬼东西？”
//它会通过riid来问我们是什么东西，只有它问到我们是不是IID_IDispatch或我们是不是IID_IUnknown时，我们才能肯定的回答它S_OK
//因为我们的对象继承于IDispatch，而IDispatch又继承于IUnknown，我们只实现了这两个接口，所以只能这样来回答它的询问
HRESULT STDMETHODCALLTYPE CBaseHtmlView::QueryInterface(REFIID riid, void **ppvObject)
{
	if (riid == IID_IDispatch || riid == IID_IUnknown)
	{
		//对的，我是一个IDispatch，把我自己(this)交给你
		*ppvObject = static_cast<IDispatch*>(this);
		return S_OK;
	}
	else
		return E_NOINTERFACE;
}

//我们知道COM对象使用引用计数来管理对象生命周期，我们的CJsCallCppDlg对象的生命周期就是整个程序的生命周期
//我的这个对象不需要你JavaScript来管，我自己会管，所以我不用实现AddRef()和Release()，这里乱写一些。
//你要return 1;return 2;return 3;return 4;return 5;都可以
ULONG STDMETHODCALLTYPE CBaseHtmlView::AddRef()
{
	return 1;
}

//同上，不多说了
//题外话：当然如果你要new出一个c++对象来并扔给JavaScript来管，你就需要实现AddRef()和Release()，在引用计数归零时delete this;
ULONG STDMETHODCALLTYPE CBaseHtmlView::Release()
{
	return 1;
}



