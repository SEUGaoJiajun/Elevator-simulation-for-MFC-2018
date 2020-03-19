// ElevatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Elevator.h"
#include "ElevatorDlg.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//int curWidth=0;          //门开闭的尺度


//创建电梯窗体

//电梯窗体

CElevatorDlg::CElevatorDlg(CWnd* pParent)
	: CDialog(CElevatorDlg::IDD, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		 
	m_iMaxPassengerNum = 12;
	m_iCurPassengerNum = 0;
	m_iCurFloor = 1;
	m_iNextDestFloor = -1;
	m_eCurState = IDLE;
	m_isOpen=false;    //电梯门一开始闭合
	m_isOpening=false;
	m_isClosing=false;
	m_isEntering=false;
	m_isLeaving=false;

	m_curWidth=0;

	m_cUpWaitQueue =new CUpWaitQueue();
	m_cDownWaitQueue =new CDownWaitQueue();

}

void CElevatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_STATE, m_conState);
	DDX_Control(pDX, IDC_STATIC_PSG_NUM, m_conPsgNum);
	DDX_Control(pDX, IDC_STATIC_ELEVATOR1, m_ElevatorBox);
}

BEGIN_MESSAGE_MAP(CElevatorDlg, CDialog)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_OPEN_DOOR, openDoor)
	ON_BN_CLICKED(IDC_BTN_CLOSE_DOOR, closeDoor)
	ON_BN_CLICKED(IDC_BTN_CREATE_FAULT, OnBtnCreateFault)
	ON_BN_CLICKED(IDC_BTN_CORRECT_FAULT, OnBtnCorrectFault)
	ON_BN_CLICKED(IDC_BTN_PSG_ENTER, OnBtnPsgEnter)
	ON_BN_CLICKED(IDC_BTN_PSG_LEAVE, OnBtnPsgLeave)
	ON_WM_CTLCOLOR()
    ON_COMMAND_RANGE(IDC_MYBUTTONS,IDC_MYBUTTONS+10,OnInnerBtnClk)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElevatorDlg message handlers

BOOL CElevatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
		CString TempString;
	
	//创建电梯窗体中的1-10楼层按钮参数
	CString strCaption;
	int iPanelLeft = 9;
	int iPanelTop = 75;
	int iRowHeight = 75;
	int iColWidth = 45;

	int iBtnWidth = 27;
	int iBtnHeight = 45;
	int i;

	try{

	for(i=FLOOR_NUM;i>0;i--)
	{
		strCaption.Format("%d",i);
		m_pButton[i-1]=new CButton;
		//m_pButton[i-1]->LoadBitmaps(IDB_BITMAP_TEAMLOGO);
		
		if(i%2==0)
		{
		m_pButton[i-1]->Create(strCaption,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,\
			CRect(\
			iPanelLeft,\
			iPanelTop+(10-i)*iRowHeight/2,\
			iPanelLeft+iBtnWidth,\
			iPanelTop+(10-i)*iRowHeight/2+iBtnHeight),\
			this,IDC_MYBUTTONS+i-1);//left,top,right,bottom
		//m_pButton[i-1]->SetFaceColor(RGB(0,225,0));
	
		}
		else
		{
		m_pButton[i-1]->Create(strCaption,BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,\
			CRect(\
			iPanelLeft+iColWidth,\
			iPanelTop+(10-i-1)*iRowHeight/2,\
			iPanelLeft+iColWidth+iBtnWidth,\
			iPanelTop+(10-i-1)*iRowHeight/2+iBtnHeight),\
			this,IDC_MYBUTTONS+i-1);//left,top,right,bottom
		}
		
	}//for

	}catch(CException* e){
	AfxMessageBox("创建电梯按钮失败，程序将退出！");
	return FALSE;
	}

	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CORRECT_FAULT)->EnableWindow(FALSE);

//创建电梯窗体中1-10楼层编号
	iPanelLeft = 160;
	iPanelTop = 43;
	int iLabelWidth = 35;
	int iLabelHeight = 40;
	

	try{

	for(i=FLOOR_NUM;i>0;i--)
	{
		TempString.Format("%d",i);
		m_pLabel[i-1] = new CStatic;
		m_pLabel[i-1]->Create("L"+TempString,WS_CHILD|WS_VISIBLE|SS_CENTER,\
			CRect(\
			iPanelLeft,\
			iPanelTop+(10-i)*iLabelHeight,\
			iPanelLeft+iLabelWidth,\
			iPanelTop+(11-i)*iLabelHeight),\
			this,IDC_MYLABELS+i-1);
		
		
	}

	}catch(CException e){
	AfxMessageBox("创建楼层编号失败，程序将退出！");
	return FALSE;
	}

	CFont cFont;
	cFont.CreateFont(12, 10, 0, 0, FW_BOLD, FALSE, TRUE,0,0,0,0,0,0, "楷体");
	
	TempString.Format("%c",str_arrElevatorName[m_iElevatorNo-1]);
	((CButton* )GetDlgItem(IDC_STATIC_ELEVATOR))->SetFont(&cFont);	
	((CButton* )GetDlgItem(IDC_STATIC_ELEVATOR))->SetWindowText(TempString+"号梯");
	cFont.DeleteObject();

	m_ElevatorBox.SetWindowText("WAITING");
	m_ElevatorBox.SetBkColor(RGB(0,225,200));

//指示条参数
	m_ElevatorBox.MoveWindow(iPanelLeft-65,iPanelTop+(10-m_iCurFloor)*iLabelHeight,70,20);

	//m_ElevatorDoor.Create1(this);
	GetDlgItem(IDC_LEFTDOOR)->MoveWindow(112,450,30,45);
    GetDlgItem(IDC_RIGHTDOOR)->MoveWindow(142,450,30,45);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CElevatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

		CDialog::OnSysCommand(nID, lParam);

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CElevatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CElevatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if(nCtlColor==CTLCOLOR_DLG){
		pDC->SetBkColor (RGB(255,255,0));//EDIT控件文字背景为黄色
		return m_hBrush;
	}

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}*/

void CElevatorDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString tempStr="",tempStr1="";
		switch(nIDEvent)
		{
	     case 1://电梯运行控制时钟
		 if(m_eCurState==UP_RUN)
		 {
			if(m_iCurFloor < m_iNextDestFloor)
			{
				m_iCurFloor++;
				m_ElevatorBox.SetWindowText("UP");
	            m_ElevatorBox.SetBkColor(RGB(200,110,255));
				m_ElevatorBox.MoveWindow(95,36+(10-m_iCurFloor)*ELEVATOR_HEIGHT,70,20);						
			}
			else //到达目的楼层
			{
				KillTimer(1);
				buzz();
				m_ElevatorBox.SetWindowText("WAITING");
	            m_ElevatorBox.SetBkColor(RGB(0,225,200));
				openDoor();

			}
		}else if(m_eCurState==DOWN_RUN)
		{
			if(m_iCurFloor > m_iNextDestFloor)
			{
				m_iCurFloor--;
				m_ElevatorBox.SetWindowText("DOWN");
	            m_ElevatorBox.SetBkColor(RGB(255,200,110));
				m_ElevatorBox.MoveWindow(95,36+(10-m_iCurFloor)*ELEVATOR_HEIGHT,70,20);						
			}
			else //到达目的楼层
			{
				KillTimer(1);
				buzz();
				m_ElevatorBox.SetWindowText("WAITING");
	            m_ElevatorBox.SetBkColor(RGB(0,225,200));
				openDoor();
			}
		}
		break;

	    case 2://电梯开门超时控制时钟
		   KillTimer(2);
		   //GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE); 
		   //GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
		   //GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	       //GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
		   //m_isOpen=false;
           //gotoNextDest();
		   if(isOverWeight()) return;
		   closeDoor();
		   break;

		case 3://乘客进入控制行为
			KillTimer(3);
		    /*if(m_iCurPassengerNum==0)
			{
		     GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	    	 GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
			}*/
			SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//再开启开门超时计时时钟

			GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	    	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	    	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

			m_isEntering=false;

		    m_iCurPassengerNum++;
    
	       if(isOverWeight())
		   {
		    m_bCanSchedule=false;

		    GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);   //关门关不上
		    GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);    //人进不去
            buzz();
		    CString TempStr ="";
            TempStr.Format("%d",m_iCurPassengerNum);
            m_conPsgNum.SetWindowText("!超载!");
            Write2Log("超载情况下进1人");

            AfxMessageBox("本电梯超载，请乘客下梯");
               
		   }
          else{
	          if(isFull())
			  {
		       m_bCanSchedule=false;

		       m_conPsgNum.SetWindowText("!满载!"); 
		       AfxMessageBox("本电梯满载，请勿上梯");
		   
			  }
	          else{
		       //m_bCanSchedule=true;

		       CString TempStr ="";
               TempStr.Format("%d",m_iCurPassengerNum);
               m_conPsgNum.SetWindowText("本梯当前搭乘人数："+TempStr);
               Write2Log("进1人");
			  }
		  }
		  break;
		case 4://乘客离开控制行为
			KillTimer(4);

			SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//再开启开门超时计时时钟

            GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	    	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	    	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

			m_isLeaving=false;

			if(m_iCurPassengerNum==1)              //该乘客离开后无人，则梯内开关门按钮失效
			{
	         GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	         GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
			}

            m_iCurPassengerNum--;

	        if(isFull())
			{
             m_bCanSchedule=false;
			 GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);  //门可以关上
			 //GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);    //人不可以进入
             m_conPsgNum.SetWindowText("!满载!");
		     Write2Log("人出，摆脱超载状态");
             AfxMessageBox("本梯恢复正常，感谢您的配合");
			}
            else{
			//m_bCanSchedule=true;
			GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);  //门可以关上
			GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);    //人可以进入
			CString TempStr ="";
            TempStr.Format("%d",m_iCurPassengerNum);
            m_conPsgNum.SetWindowText("本梯当前搭载人数："+TempStr);
            Write2Log("出一人");
			}
	        break;
		case 5://门彻底打开后的行为
			KillTimer(5);
			KillTimer(8);
			GetDlgItem(IDC_LEFTDOOR)->MoveWindow(112,450,5,45);
            GetDlgItem(IDC_RIGHTDOOR)->MoveWindow(167,450,5,45);
			m_curWidth=0;
			//CString tempStr="",tempStr1="";

			m_bCanSchedule=false;                                 //门打开后由于有乘客进出，不予许被调度

			m_isOpening=false;

			SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//开启开门超时计时时钟
	
	if(m_eCurState==UP_RUN||m_eCurState==DOWN_RUN)
	{
	  GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	  GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	  GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

      if(m_iCurPassengerNum>0) GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	   else  GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);

	//电梯之前接受的是逆向请求，现在到达了目的楼层，转向（并解禁）
	if(m_eBackupDirection!=BAD_DIRE)
	{
		if(m_eBackupDirection==UP)
		{
			m_eCurState = UP_PAUSE;
			m_cDownWaitQueue->removeElement(m_iCurFloor);
		}else{
			m_eCurState = DOWN_PAUSE;
			m_cUpWaitQueue->removeElement(m_iCurFloor);
		}
		
		//m_bCanSchedule = TRUE;
		m_eBackupDirection = BAD_DIRE;

	}else{

	//从等待队列中移除当前楼层请求
	if(m_eCurState == UP_RUN){
		m_cUpWaitQueue->removeElement(m_iCurFloor);
		m_eCurState = UP_PAUSE;
	}
	else if(m_eCurState == DOWN_RUN){
		m_cDownWaitQueue->removeElement(m_iCurFloor);
		m_eCurState = DOWN_PAUSE;
	}
	}
	

	tempStr.Format("%d",m_iCurFloor);
	tempStr = "到达"+tempStr+"楼,门开";
	m_conState.SetWindowText(tempStr);
	tempStr1.Format("%d",m_iCurPassengerNum);
	Write2Log(tempStr+"("+tempStr1+"人)");//记录日志
	tempStr="";

	
	m_isOpen=true;
	enableRelateBtn(m_eCurState,m_iCurFloor);

    //开启开门超时计时时钟,无
	}
	else{

		GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	    GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	    GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	    GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

		if(m_isOpen==false&&m_eCurState==DOWN_PAUSE){
			m_isOpen=true;
			//setState(DOWN_PAUSE_OPEN);
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "在"+tempStr+"楼";
	        m_conState.SetWindowText(tempStr+"下行暂停,门重开一次");
	        Write2Log(tempStr+"门重开一次");//记录日志
	        tempStr="";
		}
		if(m_isOpen==false&&m_eCurState==UP_PAUSE){
			m_isOpen=true;
			//setState(UP_PAUSE_OPEN);
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "在"+tempStr+"楼";
	        m_conState.SetWindowText(tempStr+"上行暂停,门重开一次");
	        Write2Log(tempStr+"门重开一次");//记录日志
	        tempStr="";
		}
	}
	break;
		case 6://门彻底关闭后的行为
			KillTimer(6);
            //CString tempStr;
			KillTimer(9);
			GetDlgItem(IDC_LEFTDOOR)->MoveWindow(112,450,30,45);
            GetDlgItem(IDC_RIGHTDOOR)->MoveWindow(142,450,30,45);
			m_curWidth=0;

			SetTimer(7,DOOR_CLOSE_TIME*1000,NULL);//开启关门超时计时时钟

			m_isClosing=false;

			GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(TRUE);
	        GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	        GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	        GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	        if(m_isOpen==true&&m_eCurState==DOWN_PAUSE){
		         m_isOpen=false;
			     tempStr.Format("%d",m_iCurFloor);
	             tempStr = "在"+tempStr+"楼";
	             m_conState.SetWindowText(tempStr+"下行暂停,门关一次");
	             Write2Log(tempStr+"门关一次");//记录日志
	             tempStr="";
			}
	        if(m_isOpen==true&&m_eCurState==UP_PAUSE){
		         m_isOpen=false;
			     tempStr.Format("%d",m_iCurFloor);
	             tempStr = "在"+tempStr+"楼";
	             m_conState.SetWindowText(tempStr+"上行暂停，门关一次");
	             Write2Log(tempStr+"门关一次");//记录日志
	             tempStr="";
			}
	
	//前往下一楼层
	//gotoNextDest();
	break;
		case 7://电梯关门超时控制
		   KillTimer(7);
		   GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE); 
		   GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
		   GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	       GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
 
		   //到头后自动换向
		   if(m_eCurState==UP_PAUSE && m_iCurFloor==FLOOR_NUM) m_eCurState =DOWN_PAUSE;
	       if(m_eCurState==DOWN_PAUSE && m_iCurFloor==1) m_eCurState =UP_PAUSE;
		   
		   if(!isFull()&&!isOverWeight()) m_bCanSchedule=true;   //此时才可以被调度
           gotoNextDest();

		   break;
		case 8://开门处理动作
			if(m_curWidth>24){    //hhh,伪闭环
				KillTimer(8);
			}
			else{
				m_curWidth+=3;
				GetDlgItem(IDC_LEFTDOOR)->MoveWindow(112,450,30-m_curWidth,45);
                GetDlgItem(IDC_RIGHTDOOR)->MoveWindow(142+m_curWidth,450,30-m_curWidth,45);
			}            
			break;
		case 9://关门处理动作
			if(m_curWidth>24){
				KillTimer(9);
			}
			else{
            	m_curWidth+=3;
                GetDlgItem(IDC_LEFTDOOR)->MoveWindow(112,450,0+m_curWidth,45);
                GetDlgItem(IDC_RIGHTDOOR)->MoveWindow(172-m_curWidth,450,m_curWidth,45);
			}
			break;

	}



	CDialog::OnTimer(nIDEvent);
}

void CElevatorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	for(int i=0;i<FLOOR_NUM;i++)
	{
		delete m_pButton[i];
		delete m_pLabel[i];
	}

	try{
		m_cLogFile.Close();
	}catch(CException e){}
	

	KillTimer(1);KillTimer(2);
	KillTimer(3);KillTimer(4);
	KillTimer(5);KillTimer(6);
	KillTimer(7);
	
}

void CElevatorDlg::openDoor() 
{
	CString tempStr="",tempStr1="";
	// TODO: Add your control notification handler code here

	KillTimer(7);                                         //门打开时终止闭合超时控制

	m_bCanSchedule=false;                                 //门打开时不允许被调度

    GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);   //门打开时，开关门和乘客进出失效
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);

	m_isOpening=true;


	tempStr.Format("%d",m_iCurFloor);
	tempStr = "在"+tempStr+"楼";
	m_conState.SetWindowText(tempStr+"门正在开启");
	Write2Log(tempStr+"门正在开启");//记录日志
	tempStr="";

	SetTimer(5,DOOR_ONOFF_TIME*1000,NULL);

	SetTimer(8,250,NULL);
    

	/*SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//开启开门超时计时时钟
	
	if(m_eCurState==UP_RUN||m_eCurState==DOWN_RUN)
	{
	   GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	   GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	   GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

       if(m_iCurPassengerNum>0) GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	   else  GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);

	//电梯之前接受的是逆向请求，现在到达了目的楼层，转向并解禁
	if(m_eBackupDirection!=BAD_DIRE)
	{
		if(m_eBackupDirection==UP)
		{
			m_eCurState = UP_PAUSE;
			m_cDownWaitQueue->removeElement(m_iCurFloor);
		}else{
			m_eCurState = DOWN_PAUSE;
			m_cUpWaitQueue->removeElement(m_iCurFloor);
		}
		
		m_bCanSchedule = TRUE;
		m_eBackupDirection = BAD_DIRE;

	}else{

	//从等待队列中移除当前楼层请求
	if(m_eCurState == UP_RUN){
		m_cUpWaitQueue->removeElement(m_iCurFloor);
		m_eCurState = UP_PAUSE;
	}
	else if(m_eCurState == DOWN_RUN){
		m_cDownWaitQueue->removeElement(m_iCurFloor);
		m_eCurState = DOWN_PAUSE;
	}
	}
	

	tempStr.Format("%d",m_iCurFloor);
	tempStr = "到达"+tempStr+"楼,门开";
	m_conState.SetWindowText(tempStr);
	tempStr1.Format("%d",m_iCurPassengerNum);
	Write2Log(tempStr+"("+tempStr1+"人)");//记录日志
	tempStr="";

	
	//GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);
	
	m_isOpen=true;
	enableRelateBtn(m_eCurState,m_iCurFloor);

	//SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//开启开门超时计时时钟
	}
	else{

		GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	    GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	    GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	    GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

		if(m_isOpen==false&&m_eCurState==DOWN_PAUSE){
			m_isOpen=true;
			//setState(DOWN_PAUSE_OPEN);
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "在"+tempStr+"楼";
	        m_conState.SetWindowText(tempStr+"下行暂停,门重开一次");
	        Write2Log(tempStr+"门重开一次");//记录日志
	        tempStr="";
		}
		if(m_isOpen==false&&m_eCurState==UP_PAUSE){
			m_isOpen=true;
			//setState(UP_PAUSE_OPEN);
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "在"+tempStr+"楼";
	        m_conState.SetWindowText(tempStr+"上行暂停,门重开一次");
	        Write2Log(tempStr+"门重开一次");//记录日志
	        tempStr="";
		}
	}*/
}

void CElevatorDlg::closeDoor() 
{
	CString tempStr;
	//到头后自动换向
	if(m_eCurState==UP_PAUSE && m_iCurFloor==FLOOR_NUM) m_eCurState =DOWN_PAUSE;
	if(m_eCurState==DOWN_PAUSE && m_iCurFloor==1) m_eCurState =UP_PAUSE;

	KillTimer(2);                                         //门闭合时终止开门超时控制

	m_bCanSchedule=false;                                 //门闭合时不允许被调度

	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);   //门闭合时，开关门和乘客进出失效
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	m_isClosing=true;


    tempStr.Format("%d",m_iCurFloor);
	tempStr = "在"+tempStr+"楼";
	m_conState.SetWindowText(tempStr+"门正在闭合");
	Write2Log(tempStr+"门正在闭合"); //记录日志

	SetTimer(6,DOOR_ONOFF_TIME*1000,NULL);

	SetTimer(9,250,NULL);
	
	/*GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	if(m_isOpen==true&&m_eCurState==DOWN_PAUSE){
		    m_isOpen=false;
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "在"+tempStr+"楼";
	        m_conState.SetWindowText(tempStr+"下行暂停,门关一次");
	        Write2Log(tempStr+"门关一次");//记录日志
	        tempStr="";
	}
	if(m_isOpen==true&&m_eCurState==UP_PAUSE){
		    m_isOpen=false;
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "在"+tempStr+"楼";
	        m_conState.SetWindowText(tempStr+"上行暂停，门关一次");
	        Write2Log(tempStr+"门关一次");//记录日志
	        tempStr="";
	}
	
	//前往下一楼层
	gotoNextDest();*/
}

void CElevatorDlg::OnBtnCreateFault() 
{
	// TODO: Add your control notification handler code here
	if(m_eCurState==UP_RUN || m_eCurState==DOWN_RUN)
 	{
		AfxMessageBox("本部电梯正在运行中，仿真环境不允许出现人为故障！");
 		return;
 	}
 	if(m_iCurPassengerNum > 0)
 	{
 		AfxMessageBox("电梯当前有乘客，不允许出现故障！");
 		return;
 	}
 	
 	m_eOldState = m_eCurState;
 	m_eCurState =MAL_FUNCTION;
 	GetDlgItem(IDC_BTN_CREATE_FAULT)->EnableWindow(FALSE);
 	GetDlgItem(IDC_BTN_CORRECT_FAULT)->EnableWindow(TRUE);
 	m_conState.SetWindowText(stateDespArr[m_eCurState]);//改变电梯状态显示
 	Write2Log("产生故障！");//记录日志
}

void CElevatorDlg::OnBtnCorrectFault() 
{
	// TODO: Add your control notification handler code here
    m_eCurState =m_eOldState;
	GetDlgItem(IDC_BTN_CREATE_FAULT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CORRECT_FAULT)->EnableWindow(FALSE);
	m_conState.SetWindowText(stateDespArr[m_eCurState]);//改变电梯状态显示
	Write2Log("本部电梯故障已经修复，可以搭乘");//记录日志
	
}

void CElevatorDlg::OnBtnPsgEnter() 
{
	// TODO: Add your control notification handler code here

	CString TempStr ="";

    /*if(m_iCurPassengerNum==0){
		GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	}*/

	KillTimer(2);                                            //乘客出入时终止超时控制

	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);     //乘客出入时不允许开关门！
	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);      //一次只进或出一人
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	m_isEntering=true;


    TempStr.Format("%d",m_iCurPassengerNum+1);
    m_conPsgNum.SetWindowText("第"+TempStr+"名乘客入梯中...");
	Write2Log("第"+TempStr+"名乘客入梯中...");

	SetTimer(3,PSG_INOUT_TIME*1000,NULL);
	
	/*m_iCurPassengerNum++;
    
	if(isOverWeight())
	{
		m_bCanSchedule=false;

		GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);   //关门关不上
		GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);    //人进不去
        buzz();
		CString TempStr ="";
        TempStr.Format("%d",m_iCurPassengerNum);
        m_conPsgNum.SetWindowText("!超载");
        Write2Log("超载情况下进1人");

        AfxMessageBox("本电梯超载，请乘客下梯");
               
        //return;
	}
    else{
	   if(isFull())
	   {
		   m_bCanSchedule=false;
		   m_conPsgNum.SetWindowText("!满载"); 
		   AfxMessageBox("本电梯满载，请勿上梯");
		   
	   }
	   else{
		   m_bCanSchedule=true;
		   CString TempStr ="";
           TempStr.Format("%d",m_iCurPassengerNum);
           m_conPsgNum.SetWindowText("本梯当前搭乘人数："+TempStr);
           Write2Log("进1人");
	   }
	}*/
}

void CElevatorDlg::OnBtnPsgLeave() 
{
	// TODO: Add your control notification handler code here

    CString TempStr ="";

	if(m_iCurPassengerNum==0)
	{
     AfxMessageBox("本梯内当前无乘客!");
     return;
	}

    KillTimer(2);                                           //乘客出入时终止超时控制

	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);    //乘客出入时不允许开关门！
	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);      //一次只进或出一人
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	m_isLeaving=true;


	TempStr.Format("%d",m_iCurPassengerNum);
    m_conPsgNum.SetWindowText("第"+TempStr+"名乘客出梯中...");
	Write2Log("第"+TempStr+"名乘客出梯中...");

    SetTimer(4,PSG_INOUT_TIME*1000,NULL);

	/*if(m_iCurPassengerNum==1)
	{
	 GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	 GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	}*/

        /*m_iCurPassengerNum--;

	    if(isFull())
		{
          m_bCanSchedule=false;
          m_conPsgNum.SetWindowText("!满载");
		  Write2Log("人出，摆脱超载状态");
          AfxMessageBox("本梯恢复正常，感谢您的配合");
		}
        else{
			m_bCanSchedule=true;
			GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);    //人可以进入
			CString TempStr ="";
            TempStr.Format("%d",m_iCurPassengerNum);
            m_conPsgNum.SetWindowText("本梯当前搭载人数："+TempStr);
            Write2Log("出一人");
		}
	}*/
}

HBRUSH CElevatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CElevatorDlg::OnInnerBtnClk(UINT nID)
{
	if(m_iCurPassengerNum==0)
	{
		AfxMessageBox("请先按楼层按钮输入所去楼层！");
		return;
	}

	if(isOverWeight())    //超载时乘客点击按钮去其他层是不允许的
	{
		/*GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);     //人进不去
	    GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);    //关门关不上
		GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
		m_isOpen=true;*/
	    
       
        m_conPsgNum.SetWindowText("!超载!");
        AfxMessageBox("本电梯超载，请乘客下梯");

        return;
	}
	
	if(isMalFunction())
	{
		AfxMessageBox("本部电梯产生故障，请选择乘坐其他电梯！");
		return;
	}

	if(m_isOpening||m_isClosing||m_isEntering||m_isLeaving) return;

    if(m_isOpen==true){
		AfxMessageBox("请在门关后再按键");
		
		return;
	}

	int iReqFloor = nID-300+1;

	if((m_eCurState==UP_RUN && iReqFloor<=m_iCurFloor) || \
		(m_eCurState==UP_PAUSE && iReqFloor<m_iCurFloor))
	{
		AfxMessageBox("您的请求跟电梯当前运行方向不一致，如到达所需楼层，请乘坐其他电梯！");
		return;
	}else if((m_eCurState==DOWN_RUN && iReqFloor>=m_iCurFloor) || \
		(m_eCurState==DOWN_PAUSE && iReqFloor>m_iCurFloor))
	{
		AfxMessageBox("您的请求跟电梯当前运行方向不一致，如到达所需楼层，请乘坐其他电梯！");
		return;
	}

	//刚好电梯所停楼层有请求，此时所在楼层停靠的电梯直接开门
	if((m_eCurState==UP_PAUSE || m_eCurState==DOWN_PAUSE) && (iReqFloor==m_iCurFloor))
	{
		if(m_eCurState==UP_PAUSE) m_eCurState = UP_RUN;
		else m_eCurState = DOWN_RUN;
		
		buzz();
		openDoor();
		return;
	}

switch(m_eCurState)
{
case UP_PAUSE:
	m_iNextDestFloor = m_cUpWaitQueue->getNextAvail();
	if(m_iNextDestFloor==-1 || iReqFloor<m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cUpWaitQueue->addElement(iReqFloor);
	m_eCurState =UP_RUN;

    GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
	m_isOpen=false;

	KillTimer(1);		
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//启动电梯
	break;
	
case DOWN_PAUSE:
	m_iNextDestFloor = m_cDownWaitQueue->getNextAvail();
	if(m_iNextDestFloor==-1 || iReqFloor>m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cDownWaitQueue->addElement(iReqFloor);
	m_eCurState =DOWN_RUN;

    GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
	m_isOpen=false;

	KillTimer(1);		
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//启动电梯		
	break;
	
case UP_RUN:
	if(iReqFloor<m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cUpWaitQueue->addElement(iReqFloor);
	break;
	
case DOWN_RUN:
	if(iReqFloor>m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cDownWaitQueue->addElement(iReqFloor);
	break;
	
}

	m_conState.SetWindowText(stateDespArr[m_eCurState]);//改变电梯状态显示
	GetDlgItem(IDC_MYBUTTONS+iReqFloor-1)->EnableWindow(FALSE);

}

void CElevatorDlg::gotoNextDest()
{

  if(m_eCurState==UP_PAUSE) 
  {	
	if((m_iNextDestFloor = m_cUpWaitQueue->getNextAvail())==-1)//上行队列空，调整方向
	{

	if(m_iCurPassengerNum>0) 
	{
	//无运行前往楼层请求，但有乘客，进入暂停状态
	}
	else{
		m_eCurState =IDLE;
		Write2Log("空闲");//记录日志
	}
	
	}
	else{m_eCurState =UP_RUN;}

}
else if(m_eCurState==DOWN_PAUSE) 
{
	if((m_iNextDestFloor = m_cDownWaitQueue->getNextAvail())==-1)//下行队列空，调整方向
	{

	if(m_iCurPassengerNum>0) //无运行前往楼层请求，但有乘客，进入暂停状态
	{
	}else{
		m_eCurState =IDLE;
		Write2Log("空闲");//记录日志
	}
	
	}else{m_eCurState =DOWN_RUN;}
}

m_conState.SetWindowText(stateDespArr[m_eCurState]);//改变电梯状态显示

//找到了下一个请求 
  if(m_iNextDestFloor>0) SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//启动电梯


}

void CElevatorDlg::enableRelateBtn(enum state eCurState, int iFloorNo)
{
	//Enable当前楼层按钮
	GetDlgItem(IDC_MYBUTTONS+iFloorNo-1)->EnableWindow(TRUE);

	//通知父窗体Enable该楼层按钮
	int tarFloorBtnID = (eCurState==UP_PAUSE) ? (2*(iFloorNo-1)) : (2*(iFloorNo-1)+1);
	m_pParent->SendMessage(WM_ARRIVE_ONEFLOOR,(WPARAM)tarFloorBtnID);

}

void CElevatorDlg::Write2Log(CString content)
{
 CString tempStr;
 tempStr.Format("%d",m_iElevatorNo);

 CTime m_SysTime = CTime::GetCurrentTime();

 try{
    m_cLogFile.WriteString("电梯"+tempStr+" ["+content+"]\t("+m_SysTime.Format("%Y-%m-%d %H:%M:%S")+")\n");
    }catch(CException* e){}   
}

void CElevatorDlg::buzz()
{
MessageBeep(MB_ICONASTERISK);
}


CElevatorDlg::CElevatorDlg(int iElevatorNo, int iMaxPassengerNum, int iIniFloor, CWnd *pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iElevatorNo = iElevatorNo;
	m_iMaxPassengerNum = iMaxPassengerNum;
	m_iCurPassengerNum = 0;
	m_iCurFloor = iIniFloor;//电梯开始时所在楼层
	m_iNextDestFloor = -1;
	m_eCurState = IDLE;	
	m_eBackupDirection = BAD_DIRE;
	m_bCanSchedule = TRUE;
	m_isOpen=false;        //电梯门一开始闭合
	m_isOpening=false;
	m_isClosing=false;
	m_isEntering=false;
	m_isLeaving=false;

	m_curWidth=0;

	m_pParent=pParent;

	m_cUpWaitQueue =new CUpWaitQueue(FLOOR_NUM);
	m_cDownWaitQueue =new CDownWaitQueue(FLOOR_NUM);


	stateDespArr[0] = "电梯空闲，可以载人";
	stateDespArr[1] = "电梯下行运行中，请选择其他电梯或等待";
	stateDespArr[2] = "电梯上行运行中，请选择其他电梯或等待";
	stateDespArr[3] = "电梯下行暂停中";
	stateDespArr[4] = "电梯上行暂停中";
	stateDespArr[5] = "电梯开门，请乘客上下";
	stateDespArr[6] = "电梯故障！请选择其他电梯";	
	stateDespArr[7] = "";
    //stateDespArr[8] = "电梯下行暂停，开门中";
	//stateDespArr[9] = "电梯下行暂停，关门中";
	//stateDespArr[10] = "电梯上行暂停，开门中";
	//stateDespArr[11] = "电梯上行暂停，关门中";


	str_arrElevatorName[0]='1';
	str_arrElevatorName[1]='2';
	str_arrElevatorName[2]='3';
	str_arrElevatorName[3]='4';
	str_arrElevatorName[4]='5';
	str_arrElevatorName[5]='6';
	
	CString tempStr;
	tempStr.Format("%d",iElevatorNo);
	tempStr = "logs\\log"+tempStr+".txt";
//打开日志文件
	try{
			m_cLogFile.Open( tempStr, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite\
							| CFile::typeText , &m_Except);
			m_cLogFile.SeekToEnd();
			Write2Log("电梯空闲");

}catch(CException* e){}
}

void CElevatorDlg::acceptReq(sOuterRequest &tmpOuterRequest)
{
enum direction eReqDirection = tmpOuterRequest.eReqDirection;
int iReqFloor = tmpOuterRequest.iReqFloor;

//刚好电梯所停楼层有请求，直接开门
if((m_eCurState==IDLE || m_eCurState==UP_PAUSE || m_eCurState==DOWN_PAUSE) && iReqFloor == m_iCurFloor)
{
if(eReqDirection==UP) m_eCurState = UP_RUN;
else m_eCurState = DOWN_RUN;

buzz();
openDoor();
return;
}

enum direction realDire = (iReqFloor>m_iCurFloor) ? UP : DOWN; 

switch(m_eCurState)    //核心：顺带捎上与作比较，自由度从逻辑上越来越低
{
case IDLE:
	//记录用户请求方向与电梯应该运行方向不一致的情况，以便电梯到达后调整方向
	if(eReqDirection==UP && realDire==DOWN){
		m_eBackupDirection = UP;
		m_bCanSchedule = FALSE;//电梯在到达本请求楼层前不允许再被调度
	}else if(eReqDirection==DOWN && realDire==UP){
		m_eBackupDirection = DOWN;
		m_bCanSchedule = FALSE;//电梯在到达本请求楼层前不允许再被调度
	}
	
	if(realDire==UP)
	{
		m_eCurState =UP_RUN;
		m_cUpWaitQueue->addElement(iReqFloor);
	}else{
		m_eCurState =DOWN_RUN;
		m_cDownWaitQueue->addElement(iReqFloor);
	}

	m_conState.SetWindowText(stateDespArr[m_eCurState]);//改变电梯状态显示
	Write2Log(stateDespArr[m_eCurState]);//记录日志

	m_iNextDestFloor = iReqFloor;

	KillTimer(1);
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//启动电梯
	break;

case UP_PAUSE:
	m_iNextDestFloor = m_cUpWaitQueue->getNextAvail();
	if(m_iNextDestFloor==-1 || iReqFloor<m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cUpWaitQueue->addElement(iReqFloor);
	m_eCurState =UP_RUN;
	m_conState.SetWindowText(stateDespArr[m_eCurState]);//改变电梯状态显示

	KillTimer(1);		
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//启动电梯
	break;
	
case DOWN_PAUSE:
	m_iNextDestFloor = m_cDownWaitQueue->getNextAvail();
	if(m_iNextDestFloor==-1 || iReqFloor>m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cDownWaitQueue->addElement(iReqFloor);
	m_eCurState =DOWN_RUN;
	m_conState.SetWindowText(stateDespArr[m_eCurState]);//改变电梯状态显示

	KillTimer(1);		
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//启动电梯		
	break;
	
case UP_RUN:
	if(iReqFloor<m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cUpWaitQueue->addElement(iReqFloor);
	break;
	
case DOWN_RUN:
	if(iReqFloor>m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cDownWaitQueue->addElement(iReqFloor);
	break;
	
}

}


bool CElevatorDlg::isMalFunction()
{
 return m_eCurState==MAL_FUNCTION;
}


int CElevatorDlg::getCurPassengerNum()
{
 return m_iCurPassengerNum; 
}

int CElevatorDlg::getCurFloor()
{
 return m_iCurFloor;
}

int CElevatorDlg::getCurWeight()
{
 return m_iCurPassengerNum;
}

enum state CElevatorDlg::getState()
{
 return m_eCurState;
}

bool CElevatorDlg::canSchedule()
{
 return m_bCanSchedule;
}

void CElevatorDlg::setState(enum state eCurState)
{
 m_eCurState =eCurState;
}


int CElevatorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//CSplashWnd::ShowSplashScreen(this); //显示启动画面，丢人啊
	return 0;
}



void CElevatorDlg::arrivalAct()        //作废作废
{
	CString tempStr,tempStr1;
 	SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//开启开门超时计时时钟
	
	if(m_eCurState==UP_RUN||m_eCurState==DOWN_RUN)
	{
	   GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	   GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	   GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

       if(m_iCurPassengerNum>0) GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	   else  GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);

	//电梯之前接受的是逆向请求，现在到达了目的楼层，转向并解禁
	if(m_eBackupDirection!=BAD_DIRE)
	{
		if(m_eBackupDirection==UP)
		{
			m_eCurState = UP_PAUSE;
			m_cDownWaitQueue->removeElement(m_iCurFloor);
		}else{
			m_eCurState = DOWN_PAUSE;
			m_cUpWaitQueue->removeElement(m_iCurFloor);
		}
		
		m_bCanSchedule = TRUE;
		m_eBackupDirection = BAD_DIRE;         //这表示不再拧着来

	}else{

	//从等待队列中移除当前楼层请求
	if(m_eCurState == UP_RUN){
		m_cUpWaitQueue->removeElement(m_iCurFloor);
		m_eCurState = UP_PAUSE;
	}
	else if(m_eCurState == DOWN_RUN){
		m_cDownWaitQueue->removeElement(m_iCurFloor);
		m_eCurState = DOWN_PAUSE;
	}
	}
	

	tempStr.Format("%d",m_iCurFloor);
	tempStr = "到达"+tempStr+"楼,门开";
	m_conState.SetWindowText(tempStr);
	tempStr1.Format("%d",m_iCurPassengerNum);
	Write2Log(tempStr+"("+tempStr1+"人)");//记录日志
	tempStr="";
	
	
	m_isOpen=true;
	enableRelateBtn(m_eCurState,m_iCurFloor);      //楼层再次可用，并向主窗口发送消息
	}
}
