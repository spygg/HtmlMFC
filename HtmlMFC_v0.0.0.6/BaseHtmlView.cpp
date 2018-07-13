// BaseHtmlView.cpp : ʵ���ļ�
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


// CBaseHtmlView ���

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


// CBaseHtmlView ��Ϣ�������


void CBaseHtmlView::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CWnd::PostNcDestroy();
}


int CBaseHtmlView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return MA_ACTIVATE;
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CBaseHtmlView::OnDestroy()
{

	CWnd::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}


void CBaseHtmlView::OnSize(UINT nType, int cx, int cy)
{
	CHtmlView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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

//ͨ����ַ���ж�
void CBaseHtmlView::OnDocumentComplete(LPCTSTR lpszURL)
{
	// TODO: �ڴ����ר�ô����/����û���
	//
//  	CString szUrl(lpszURL);
//  	if(szUrl.Find("index.html") != -1)
	{
		TRACE("%s\n", lpszURL);

		SetScriptDocument(); //��ʼ��com��� IID_IHTMLDocument2�ӿ�

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
	//SetSilent(TRUE);//add by wh ,bid pop script dlg  true��ʾ������浯���Ի���
	return TRUE;
}

void CBaseHtmlView::SetUrl( char *szUrl )
{
	strcpy(m_szUrl, szUrl);
}



BOOL CBaseHtmlView::SetScriptDocument()
{
	CComPtr<IDispatch> spDisp = GetHtmlDocument(); //��ȡcom ��ʼ�ӿ�ָ��
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
	
	HRESULT hr = m_spDoc->get_Script(&spDisp); //��ȡScript�ӿ�

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
		SystemLog("����GetJScrip����ʧ�ܣ�");
		return FALSE;
	}
	
	CComBSTR bstrFunc(strFunc);
	DISPID dispid = NULL;
	//��������strFunc ��ȡ ids
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
	dispparams.cArgs = (UINT)arraySize; //��������
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
	
	//����JaveScript�ӿ�
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
		SystemLog("����GetJScrip����ʧ�ܣ�");
		return FALSE;
	}
	
	CComBSTR bstrFunc(strFunc);
	DISPID dispid = NULL;
	//��������strFunc ��ȡ ids
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL, &bstrFunc, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	if (FAILED(hr))
	{
		CString msg = GetSystemErrorMessage(hr);
		SystemLog(msg.GetBuffer(0));
		return FALSE;
	}
	
	
	//����JaveScript�ӿ�

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


//����ʵ�֣�ֱ�ӷ���E_NOTIMPL
HRESULT STDMETHODCALLTYPE CBaseHtmlView::GetTypeInfoCount(UINT *pctinfo)
{
	return E_NOTIMPL;
}

//����ʵ�֣�ֱ�ӷ���E_NOTIMPL
HRESULT STDMETHODCALLTYPE CBaseHtmlView::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
	return E_NOTIMPL;
}


//JavaScript�õ����Ǵ��ݸ�����ָ�����������������ǵĶ�����ʲô�����������QueryInterface��ѯ�����ǡ�����ʲô��������
//����ͨ��riid����������ʲô������ֻ�����ʵ������ǲ���IID_IDispatch�������ǲ���IID_IUnknownʱ�����ǲ��ܿ϶��Ļش���S_OK
//��Ϊ���ǵĶ���̳���IDispatch����IDispatch�ּ̳���IUnknown������ֻʵ�����������ӿڣ�����ֻ���������ش�����ѯ��
HRESULT STDMETHODCALLTYPE CBaseHtmlView::QueryInterface(REFIID riid, void **ppvObject)
{
	if (riid == IID_IDispatch || riid == IID_IUnknown)
	{
		//�Եģ�����һ��IDispatch�������Լ�(this)������
		*ppvObject = static_cast<IDispatch*>(this);
		return S_OK;
	}
	else
		return E_NOINTERFACE;
}

//����֪��COM����ʹ�����ü�������������������ڣ����ǵ�CJsCallCppDlg������������ھ��������������������
//�ҵ����������Ҫ��JavaScript���ܣ����Լ���ܣ������Ҳ���ʵ��AddRef()��Release()��������дһЩ��
//��Ҫreturn 1;return 2;return 3;return 4;return 5;������
ULONG STDMETHODCALLTYPE CBaseHtmlView::AddRef()
{
	return 1;
}

//ͬ�ϣ�����˵��
//���⻰����Ȼ�����Ҫnew��һ��c++���������Ӹ�JavaScript���ܣ������Ҫʵ��AddRef()��Release()�������ü�������ʱdelete this;
ULONG STDMETHODCALLTYPE CBaseHtmlView::Release()
{
	return 1;
}



