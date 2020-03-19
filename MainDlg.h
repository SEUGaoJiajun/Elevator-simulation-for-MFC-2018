#if !defined(AFX_MAINDLG_H__F0B870D2_CE66_4881_99CA_4AA05C6274E7__INCLUDED_)
#define AFX_MAINDLG_H__F0B870D2_CE66_4881_99CA_4AA05C6274E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDlg.h : header file
//

#include "EleBasicData.h"
#include "ElevatorDlg.h"
#include "CircleLink.h"


//���ش���ͷ�ļ�

//������

class CMainDlg : public CDialog
{
//����
public:
	CMainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_MAINDLG };


// Overrides
	// ClassWizard generated virtual function overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
protected:
	afx_msg void OnMove();
	CElevatorDlg *m_elevatorArr[ELEVATOR_NUM];//�������飡
	afx_msg LONG OnOneFloorArrived(WPARAM wP,LPARAM lP);

	// Generated message map functions

	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
private:
	void Write2Log(const CString& content);
	void trytoSchedule(sOuterRequest& tmpRequest);
	void Schedule();
	int Goodness(const sOuterRequest& tmpOuterRequest);
	int ReqStruct2No(const sOuterRequest& tmpRequest);
	sOuterRequest No2ReqStruct(int iNo);
	void OnFloorBtnClk(UINT nID);

	int iTotalFailTimes;
	CircleSingleLink<sOuterRequest> lWaitQueue;      //ѭ����������������������
    CButton * m_pFloorButton[10][2];//¥�㰴ť
	CStdioFile m_cLogFile;//��־�ļ�
	CFileException m_Except;
	char str_arrElevatorName[ELEVATOR_NUM];//���ݱ�ʶ��


};

#endif 
