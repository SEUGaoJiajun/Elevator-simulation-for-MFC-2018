// DoorST.cpp : implementation file
//

#include "stdafx.h"
#include "Elevator.h"
#include "DoorST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoorST dialog


CDoorST::CDoorST(CWnd* pParent /*=NULL*/)
	: CDialog(CDoorST::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDoorST)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDoorST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoorST)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	isOpen=FALSE;
	stop=TRUE;
	openTime=0;
	State=FALSE;
}


BEGIN_MESSAGE_MAP(CDoorST, CDialog)
	//{{AFX_MSG_MAP(CDoorST)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoorST message handlers

BOOL CDoorST::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetTimer(1,20,NULL);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDoorST::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    if(nIDEvent==1)
	{
	 if(stop==TRUE||(stop==FALSE&&State==FALSE))
	 {
		if(isOpen==TRUE)   open();
		else   close();
	    if(openTime==200)
		{
			openTime=0;
			isOpen=FALSE;
		}
	 }
	}
	CDialog::OnTimer(nIDEvent);
}

void CDoorST::Create1(CWnd *parent)
{
   Parent=parent;
   Create(IDD_DOORST_DIALOG,Parent);
   ShowWindow(SW_SHOW);
   //SetWindowPos(NULL,110,455,53,64,SWP_NOSIZE);  //需要改位置
}

void CDoorST::setState(int stat)
{
	if(stat==0)
		State=FALSE;
	else
		State=TRUE;
}

void CDoorST::open()
{
	stop=TRUE;
	CRect rect;
	GetDlgItem(IDC_STATIC_RIGHT)->GetWindowRect(&rect);
 	ScreenToClient(&rect);
	if(rect.TopLeft().x!=110)     //判坐标
	{
	 GetDlgItem(IDC_STATIC_RIGHT)->SetWindowPos(NULL,rect.TopLeft().x+1,rect.TopLeft().y,0,0,SWP_NOSIZE);
	 GetDlgItem(IDC_STATIC_LEFT)->GetWindowRect(&rect);
 	 ScreenToClient(&rect);
	 GetDlgItem(IDC_STATIC_LEFT)->SetWindowPos(NULL,rect.TopLeft().x-1,rect.TopLeft().y,0,0,SWP_NOSIZE);
	}
	else
	  openTime++;
}

void CDoorST::close()
{
    CRect rect;
	GetDlgItem(IDC_STATIC_LEFT)->GetWindowRect(&rect);
 	ScreenToClient(&rect);
	if(rect.TopLeft().x!=0)        //判坐标
	{
	 GetDlgItem(IDC_STATIC_LEFT)->SetWindowPos(NULL,rect.TopLeft().x+1,rect.TopLeft().y,0,0,SWP_NOSIZE);
	 GetDlgItem(IDC_STATIC_RIGHT)->GetWindowRect(&rect);
 	 ScreenToClient(&rect);
	 GetDlgItem(IDC_STATIC_RIGHT)->SetWindowPos(NULL,rect.TopLeft().x-1,rect.TopLeft().y,0,0,SWP_NOSIZE);
	}
	else stop=FALSE;
}
