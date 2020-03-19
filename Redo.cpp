// Redo.cpp : implementation file
//

#include "stdafx.h"
#include "Elevator.h"
#include "Redo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRedo dialog


void CRedo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRedo, CDialog)

   ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRedo message handlers

HBRUSH CRedo::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	if(nCtlColor==CTLCOLOR_DLG){
		pDC->SetBkColor (RGB(255,255,0));//EDIT控件文字背景为黄色
		return m_hBrush;
	}

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}


