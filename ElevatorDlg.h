// ElevatorDlg.h : header file
//

#if !defined(AFX_ELEVATORDLG_H__7DA56847_41BB_4623_B02E_8F03D96C9AAD__INCLUDED_)
#define AFX_ELEVATORDLG_H__7DA56847_41BB_4623_B02E_8F03D96C9AAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "resource.h"		// main symbols
#include "EleBasicData.h"
#include "UpWaitQueue.h"
#include "DownWaitQueue.h"
//#include "WaitQueue.h"
#include "ColorStaticST.h"
//#include "DoorST.h"	// Added by ClassView

//发往父窗体的消息
#define WM_ARRIVE_ONEFLOOR		WM_USER+ 0X80

//电梯窗体

class CElevatorDlg : public CDialog
{
//构造
public:
	int m_curWidth;
	bool m_isClosing;
	bool m_isOpening;

	int getElevatorNo() { return m_iElevatorNo; }
	void setState(enum state eCurState);
	bool canSchedule();
	enum state getState();
	int getCurWeight();
	int getCurFloor();
	int getCurPassengerNum();
	bool isMalFunction();
	bool isOverWeight(){ return m_iCurPassengerNum > m_iMaxPassengerNum; }
	bool isFull(){ return m_iCurPassengerNum==m_iMaxPassengerNum; }
	void acceptReq(sOuterRequest& tmpOuterRequest);
	CElevatorDlg(int iElevatorNo, int iMaxPassengerNum, int iIniFloor, CWnd* pParent=NULL);
	CElevatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data

	enum { IDD = IDD_ELEVATOR_DIALOG };
	CStatic	m_conState;
	CStatic	m_conPsgNum;
	CColorStaticST	m_ElevatorBox;
	//CDoorST m_ElevatorDoor;


	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;
	CWnd* m_pParent;	
	CStdioFile m_cLogFile;   //日志文件
	CFileException m_Except;

protected:
	void arrivalAct();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void gotoNextDest();		

	// Generated message map functions

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void openDoor();
	afx_msg void closeDoor();
	afx_msg void OnBtnCreateFault();
	afx_msg void OnBtnCorrectFault();
	afx_msg void OnBtnPsgEnter();
	afx_msg void OnBtnPsgLeave();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnInnerBtnClk(UINT nID);

	DECLARE_MESSAGE_MAP()

private:

	//等待队列
	CDownWaitQueue* m_cDownWaitQueue;
	CUpWaitQueue* m_cUpWaitQueue;

    //窗体成员变量
	CString stateDespArr[12];
	CStatic* m_pLabel[FLOOR_NUM];
	CButton* m_pButton[FLOOR_NUM];

	char str_arrElevatorName[ELEVATOR_NUM];
	bool m_bCanSchedule;
	enum direction m_eBackupDirection;
	enum state m_eOldState;
	enum state m_eCurState;
	int m_iNextDestFloor;
	int m_iCurFloor;
	int m_iCurPassengerNum;
	int m_iMaxPassengerNum;
	int m_iElevatorNo;

private:
	bool m_isLeaving;
	bool m_isEntering;
	//bool m_isClosing;
	//bool m_isOpening;
	bool m_isOpen;    //电梯门是否开启
    void buzz();
	void Write2Log(CString content);
	void enableRelateBtn(enum state eCurState, int iFloorNo);
};


#endif 
