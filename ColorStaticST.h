#if !defined(AFX_COLORSTATICST_H__CCEC6A0B_F217_41C0_9D2F_A6894F29A1D6__INCLUDED_)
#define AFX_COLORSTATICST_H__CCEC6A0B_F217_41C0_9D2F_A6894F29A1D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorStaticST.h : header file
//

#include "EleBasicData.h"
/////////////////////////////////////////////////////////////////////////////
// CColorStaticST window

class CColorStaticST : public CStatic
{
// Construction
public:
	CColorStaticST();
	/*enum{ST_FLS_SLOW,
		ST_FLS_NORMAL,
		ST_FLS_FAST};*/

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStaticST)
	//}}AFX_VIRTUAL

// Implementation
public:
	static const char* GetVersionC();
	static const short GetVersionI();
	void EnableNotify(CWnd* pParent, UINT nMsg);
	void StartBkBlink(BOOL bStart ,speed nElapse);
	void SetBlinkBkColors(COLORREF crBlinkBkColor1, COLORREF crBlinkBkColor2);
	void StartTextBlink(BOOL bStart , speed nElapse);
	void SetBlinkTextColors(COLORREF crBlinkTextColor1, COLORREF crBlinkTextColor2);
	COLORREF GetBkColor();
	void SetBkColor(COLORREF crBkColor = 0xffffffff);
	COLORREF GetTextColor();
	void SetTextColor(COLORREF crTextColor = 0xffffffff);
	virtual ~CColorStaticST();

	// Generated message map functions
protected:
	
	//{{AFX_MSG(CColorStaticST)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	UINT m_nMsg;
	CWnd* m_pParent;

	CBrush m_brBlinkBkgnd[2];
	CBrush m_brBkgnd;

	int m_nBkBlinkStep;
	BOOL m_bBkBlink;
	COLORREF m_crBlinkBkColors[2];
	COLORREF m_crBkColor;

	int m_nTextBlinkStep;
	BOOL m_bTextBlink;
	COLORREF m_crBlinkTextColors[2];
	COLORREF m_crTextColor;

	UINT m_nTimerId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATICST_H__CCEC6A0B_F217_41C0_9D2F_A6894F29A1D6__INCLUDED_)
