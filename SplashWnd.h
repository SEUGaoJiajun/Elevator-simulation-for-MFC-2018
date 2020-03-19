#if !defined(AFX_SPLASHWND_H__BD203F16_415D_44E5_AE57_D43B408290B8__INCLUDED_)
#define AFX_SPLASHWND_H__BD203F16_415D_44E5_AE57_D43B408290B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd window

class CSplashWnd : public CWnd
{
// Construction
public:

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashWnd)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	CSplashWnd();
	virtual void PostNcDestroy();
	static BOOL PreTranslateAppMessage(MSG* pMsg);
	static void ShowSplashScreen(CWnd* pParentWnd = NULL);
	static void EnableSplashScreen(BOOL bEnable = TRUE);
	CBitmap m_bitmap;
	virtual ~CSplashWnd();

	// Generated message map functions
protected:
	//CSplashWnd(){}
	void HideSplashScreen();
	BOOL Create(CWnd* pParentWnd = NULL);
	static CSplashWnd* c_pSplashWnd;
	static BOOL c_bShowSplashWnd;
	//{{AFX_MSG(CSplashWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHWND_H__BD203F16_415D_44E5_AE57_D43B408290B8__INCLUDED_)
