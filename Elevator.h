// Elevator.h : main header file for the ELEVATOR application
//

#if !defined(AFX_ELEVATOR_H__FAD56847_70BA_422C_AC61_AA5464F43911__INCLUDED_)
#define AFX_ELEVATOR_H__FAD56847_70BA_422C_AC61_AA5464F43911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#define MB_USERDEFINE		0x10000000//为定制的AfxMessageBox


// CElevatorApp:
// See Elevator.cpp for the implementation of this class
//

class CElevatorApp : public CWinApp
{
public:
	CElevatorApp();
	~CElevatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
public:
	//virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
	virtual BOOL InitInstance();


// Implementation
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	DECLARE_MESSAGE_MAP()
private:
	//CString OSVer();
};


#endif 
