#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CHtmlView。"
#endif 

// CBaseHtmlView Html 视图
#include<afxhtml.h>
#include <mshtml.h>
#include <atlbase.h>
#include <oleacc.h>
#include <comdef.h>
#include <io.h>

#define WM_HTML_LOAD_FINSH WM_USER + 1

#define CALL0(f) f()
#define CALL1(f, va1) f(va1)
#define CALL2(f, va1, va2) f(va1, va2)
#define CALL3(f, va1, va2, va3) f(va1, va2, va3)
#define CALL4(f, va1, va2, va3, va4) f(va1, va2, va3, va4)

void SystemLog(char *szLog);
void GetModulePath(char *szPath);

class CBaseHtmlView : public CHtmlView, public IDispatch  
{
	DECLARE_DYNCREATE(CBaseHtmlView)
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP() // 构建dispatch映射表以暴露方法或属性
public:
	CBaseHtmlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBaseHtmlView();

protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void PostNcDestroy();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual void OnDocumentComplete(LPCTSTR lpszURL);

private:
	char m_szUrl[255];
	CComPtr<IHTMLDocument2> m_spDoc;

public:
	BOOL CreateHtmlView(CWnd* pParent);
	void SetUrl(char *szUrl);

private:
	BOOL SetScriptDocument();
	BOOL GetJScript(CComPtr<IDispatch>& spDisp);
	const CString GetSystemErrorMessage(DWORD dwError);
	//将指针传给JS
	BOOL SetCppObjectForJavaScript();
	//一个variant调用
	BOOL CallJScriptV(const CString strFunc, _variant_t* pVarIn, _variant_t* pVarResult = NULL);

//JS 调用MFC要实现的函数
private:
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo);  
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);  


	
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);  	
	virtual ULONG STDMETHODCALLTYPE AddRef();  	
	virtual ULONG STDMETHODCALLTYPE Release();  

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid,
		LPOLESTR *rgszNames,
		UINT cNames,
		LCID lcid,
		DISPID *rgDispId){
		return E_NOTIMPL;
	};  

	virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, 
		REFIID riid,
		LCID lcid,
		WORD wFlags,
		DISPPARAMS *pDispParams,
		VARIANT *pVarResult,
		EXCEPINFO *pExcepInfo,
		UINT *puArgErr){
		return E_NOTIMPL;
	};

// MFC  调用JavaScript接口
public:
	//无参调用
	BOOL CallJScript(const CString strFunc, _variant_t* pVarResult = NULL);
	//一个CString参数的调用
	BOOL CallJScript(const CString strFunc, const CString strArg1, _variant_t* pVarResult = NULL);
	//两个CString参数的调用
	BOOL CallJScript(const CString strFunc, const CString strArg1, const CString strArg2, _variant_t* pVarResult = NULL);
	//三个CString参数的调用
	BOOL CallJScript(const CString strFunc, const CString strArg1, const CString strArg2, const CString strArg3, _variant_t* pVarResult = NULL);
	//真正的调用JavaScript方法
	BOOL CallJScript(const CString strFunc, const CStringArray& paramArray, _variant_t* pVarResult = NULL);
	
};

