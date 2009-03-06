// NetBox2.h : main header file for the NetBox2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "BoxObject.h"
#include "BoxService.h"
#include "BoxApplication.h"
#include "SSLContext.h"

#include "BoxSystem.h"

#include <BArguments.h>
#include <BConsole.h>

// CNetBox2App:
// See NetBox2.cpp for the implementation of this class
//

class CNetBox2App : public CWinApp
{
public:
	CNetBox2App();
	~CNetBox2App();

// Overrides
public:
	virtual BOOL InitInstance();

#ifdef _DEBUG
	CMemoryState msCheck;
#endif

public:

	CBoxObject<CBoxSystem> m_pSystem;
//	int m_DevIDS[4096];
//	int m_nDevCount;

public:
	afx_msg LPDISPATCH get_Console(void);
	afx_msg LPDISPATCH get_Service(void);
	afx_msg LPDISPATCH get_Arguments(void);

	afx_msg void Beep(void);
	afx_msg void Quit(long nErrorCode);
	afx_msg void Halt(long nErrorCode);
	afx_msg long MsgBox(LPCTSTR pstrText, LPCTSTR pstrTitle, VARIANT* varType);
	afx_msg long Execute(LPCTSTR pstrName, VARIANT* varCmdShow);
	afx_msg void Shutdown(BOOL bReboot);

	afx_msg void AppActivate(LPCTSTR pstrTitle);

	afx_msg void RegisterServer(LPCTSTR pstrName);
	afx_msg void UnregisterServer(LPCTSTR pstrName);

	afx_msg void SendMessage(LPCTSTR pstrSendTo, LPCTSTR pstrMessage);

	afx_msg void Command(void);

	afx_msg BSTR OpenFileDialog(VARIANT* initFile, VARIANT* initDir, VARIANT* filter, VARIANT* title);
	afx_msg BSTR SaveFileDialog(VARIANT* initFile, VARIANT* initDir, VARIANT* filter, VARIANT* title);
	afx_msg BSTR BrowseForFolder(VARIANT* initDir, VARIANT* title, VARIANT* varDescription, VARIANT* varNew);

	afx_msg void DoEvents(void);

	afx_msg long LoadPrivateKey(LPCTSTR PrivateKey, LPCTSTR pstrCertificate);

	DECLARE_DISPATCH_MAP()

public:
	void SetThreadName(LPCTSTR strName);

	static UINT staticStart(void* p);
	static UINT staticStartService(void* p);
	void Start(void);
	CString GetContentTypeFromFileName(LPCTSTR szFileName);
	CSSLContext& getSSL_CTX(void)
	{
		return *m_pSSL_CTX;
	}

	CBComPtr<CBArguments> m_pArguments;
	CBComPtr<CBConsole> m_pConsole;
	CBoxObject<CBoxService> m_pService;

	BOOL m_bIsShell;
	BOOL m_bRunSelfAtExit;

	void CallProc(void (*proc)(void*), void* pParam, BOOL AsynCall = FALSE);

private:
	BSTR DoFileDialog(VARIANT* initFile, VARIANT* initDir, VARIANT* filter, VARIANT* title, BOOL bOpen = TRUE);

	CSSLContext *m_pSSL_CTX;

	CCriticalSection m_csMime;
	CMapStringToString m_mapMimeType;

	HANDLE m_hCallProc;
	CCriticalSection m_csCallProc;

	BOOL m_bStep;
	long m_nErrorCode;

public:
	BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety)
		STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
		STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
	END_INTERFACE_PART(ObjectSafety)

protected:
	DECLARE_INTERFACE_MAP()
};

extern CNetBox2App theApp;
