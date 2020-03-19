// SplashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Elevator.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd

BOOL CSplashWnd::c_bShowSplashWnd;
CSplashWnd* CSplashWnd::c_pSplashWnd;


CSplashWnd::~CSplashWnd()
{
    // Clear the static window pointer.
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}


BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplashWnd message handlers


int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	SetTimer(1, 2500, NULL);   //对画面的计时

	return 0;
}

void CSplashWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
	// Do not call CWnd::OnPaint() for painting messages
}

void CSplashWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	HideSplashScreen();
	//CWnd::OnTimer(nIDEvent);
}

BOOL CSplashWnd::Create(CWnd *pParentWnd)
{
 	if (!m_bitmap.LoadBitmap(IDB_SPLASH))
		return FALSE;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	CRect testRect;
    pParentWnd->GetWindowRect(testRect);

	return CreateEx(0,
		AfxRegisterWndClass(0, 
		AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE,
		testRect.left+40,testRect.top+750, bm.bmWidth, bm.bmHeight, 
		pParentWnd->GetSafeHwnd(), NULL);
}

void CSplashWnd::HideSplashScreen()
{
 	// 到达指定时间进行隐藏
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();
}

void CSplashWnd::EnableSplashScreen(BOOL bEnable)
{
 c_bShowSplashWnd = bEnable;
}

void CSplashWnd::ShowSplashScreen(CWnd *pParentWnd)
{
    //对外接口，显示 
    if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
    return;

   //创建新窗口
    c_pSplashWnd = new CSplashWnd;
    if (!c_pSplashWnd->Create(pParentWnd))
	   delete c_pSplashWnd;
    else
	   c_pSplashWnd->UpdateWindow();
}

BOOL CSplashWnd::PreTranslateAppMessage(MSG *pMsg)
{
 	if (c_pSplashWnd == NULL)
		return FALSE;

	// 有人工响应，立即隐藏
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
		return TRUE;	
	}

	return FALSE;	
}

void CSplashWnd::PostNcDestroy()
{ 
  delete this;       //显式撤销
}


CSplashWnd::CSplashWnd()
{

}
