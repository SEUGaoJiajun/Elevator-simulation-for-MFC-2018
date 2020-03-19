#if !defined(AFX_DOORST_H__E6004C6B_0558_4AD6_A406_BEFAC5829958__INCLUDED_)
#define AFX_DOORST_H__E6004C6B_0558_4AD6_A406_BEFAC5829958__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoorST.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoorST dialog

class CDoorST : public CDialog
{
// Construction
public:
	void close();
	void open();
	void setState(int stat);
	void Create1(CWnd*parent);
	bool stop;
	bool State;
	CWnd* Parent;
	int openTime;
	bool isOpen;
	CDoorST(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDoorST)
	enum { IDD = IDD_DOORST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoorST)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDoorST)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOORST_H__E6004C6B_0558_4AD6_A406_BEFAC5829958__INCLUDED_)
