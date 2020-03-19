#if !defined(AFX_REDO_H__44207F64_61D9_4277_A90F_5CF3F000EFE0__INCLUDED_)
#define AFX_REDO_H__44207F64_61D9_4277_A90F_5CF3F000EFE0__INCLUDED_

// Redo.h : header file
//


// CRedo ¶Ô»°¿ò
class CRedo : public CDialog
{
// Construction
public:


// Dialog Data

	enum { IDD = IDD_REDO_DIALOG };

	CRedo():CDialog(CRedo::IDD){}

	// ClassWizard generated virtual function overrides

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	

// Implementation
protected:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
    HBRUSH m_hBrush;
};


#endif 