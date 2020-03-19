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

//int curWidth=0;          //�ſ��յĳ߶�


//�������ݴ���

//���ݴ���

CElevatorDlg::CElevatorDlg(CWnd* pParent)
	: CDialog(CElevatorDlg::IDD, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		 
	m_iMaxPassengerNum = 12;
	m_iCurPassengerNum = 0;
	m_iCurFloor = 1;
	m_iNextDestFloor = -1;
	m_eCurState = IDLE;
	m_isOpen=false;    //������һ��ʼ�պ�
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
	
	//�������ݴ����е�1-10¥�㰴ť����
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
	AfxMessageBox("�������ݰ�ťʧ�ܣ������˳���");
	return FALSE;
	}

	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CORRECT_FAULT)->EnableWindow(FALSE);

//�������ݴ�����1-10¥����
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
	AfxMessageBox("����¥����ʧ�ܣ������˳���");
	return FALSE;
	}

	CFont cFont;
	cFont.CreateFont(12, 10, 0, 0, FW_BOLD, FALSE, TRUE,0,0,0,0,0,0, "����");
	
	TempString.Format("%c",str_arrElevatorName[m_iElevatorNo-1]);
	((CButton* )GetDlgItem(IDC_STATIC_ELEVATOR))->SetFont(&cFont);	
	((CButton* )GetDlgItem(IDC_STATIC_ELEVATOR))->SetWindowText(TempString+"����");
	cFont.DeleteObject();

	m_ElevatorBox.SetWindowText("WAITING");
	m_ElevatorBox.SetBkColor(RGB(0,225,200));

//ָʾ������
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
		pDC->SetBkColor (RGB(255,255,0));//EDIT�ؼ����ֱ���Ϊ��ɫ
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
	     case 1://�������п���ʱ��
		 if(m_eCurState==UP_RUN)
		 {
			if(m_iCurFloor < m_iNextDestFloor)
			{
				m_iCurFloor++;
				m_ElevatorBox.SetWindowText("UP");
	            m_ElevatorBox.SetBkColor(RGB(200,110,255));
				m_ElevatorBox.MoveWindow(95,36+(10-m_iCurFloor)*ELEVATOR_HEIGHT,70,20);						
			}
			else //����Ŀ��¥��
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
			else //����Ŀ��¥��
			{
				KillTimer(1);
				buzz();
				m_ElevatorBox.SetWindowText("WAITING");
	            m_ElevatorBox.SetBkColor(RGB(0,225,200));
				openDoor();
			}
		}
		break;

	    case 2://���ݿ��ų�ʱ����ʱ��
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

		case 3://�˿ͽ��������Ϊ
			KillTimer(3);
		    /*if(m_iCurPassengerNum==0)
			{
		     GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	    	 GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
			}*/
			SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//�ٿ������ų�ʱ��ʱʱ��

			GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	    	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	    	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

			m_isEntering=false;

		    m_iCurPassengerNum++;
    
	       if(isOverWeight())
		   {
		    m_bCanSchedule=false;

		    GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);   //���Źز���
		    GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);    //�˽���ȥ
            buzz();
		    CString TempStr ="";
            TempStr.Format("%d",m_iCurPassengerNum);
            m_conPsgNum.SetWindowText("!����!");
            Write2Log("��������½�1��");

            AfxMessageBox("�����ݳ��أ���˿�����");
               
		   }
          else{
	          if(isFull())
			  {
		       m_bCanSchedule=false;

		       m_conPsgNum.SetWindowText("!����!"); 
		       AfxMessageBox("���������أ���������");
		   
			  }
	          else{
		       //m_bCanSchedule=true;

		       CString TempStr ="";
               TempStr.Format("%d",m_iCurPassengerNum);
               m_conPsgNum.SetWindowText("���ݵ�ǰ���������"+TempStr);
               Write2Log("��1��");
			  }
		  }
		  break;
		case 4://�˿��뿪������Ϊ
			KillTimer(4);

			SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//�ٿ������ų�ʱ��ʱʱ��

            GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	    	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	    	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

			m_isLeaving=false;

			if(m_iCurPassengerNum==1)              //�ó˿��뿪�����ˣ������ڿ����Ű�ťʧЧ
			{
	         GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	         GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
			}

            m_iCurPassengerNum--;

	        if(isFull())
			{
             m_bCanSchedule=false;
			 GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);  //�ſ��Թ���
			 //GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);    //�˲����Խ���
             m_conPsgNum.SetWindowText("!����!");
		     Write2Log("�˳������ѳ���״̬");
             AfxMessageBox("���ݻָ���������л�������");
			}
            else{
			//m_bCanSchedule=true;
			GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);  //�ſ��Թ���
			GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);    //�˿��Խ���
			CString TempStr ="";
            TempStr.Format("%d",m_iCurPassengerNum);
            m_conPsgNum.SetWindowText("���ݵ�ǰ����������"+TempStr);
            Write2Log("��һ��");
			}
	        break;
		case 5://�ų��״򿪺����Ϊ
			KillTimer(5);
			KillTimer(8);
			GetDlgItem(IDC_LEFTDOOR)->MoveWindow(112,450,5,45);
            GetDlgItem(IDC_RIGHTDOOR)->MoveWindow(167,450,5,45);
			m_curWidth=0;
			//CString tempStr="",tempStr1="";

			m_bCanSchedule=false;                                 //�Ŵ򿪺������г˿ͽ���������������

			m_isOpening=false;

			SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//�������ų�ʱ��ʱʱ��
	
	if(m_eCurState==UP_RUN||m_eCurState==DOWN_RUN)
	{
	  GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	  GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	  GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

      if(m_iCurPassengerNum>0) GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	   else  GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);

	//����֮ǰ���ܵ��������������ڵ�����Ŀ��¥�㣬ת�򣨲������
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

	//�ӵȴ��������Ƴ���ǰ¥������
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
	tempStr = "����"+tempStr+"¥,�ſ�";
	m_conState.SetWindowText(tempStr);
	tempStr1.Format("%d",m_iCurPassengerNum);
	Write2Log(tempStr+"("+tempStr1+"��)");//��¼��־
	tempStr="";

	
	m_isOpen=true;
	enableRelateBtn(m_eCurState,m_iCurFloor);

    //�������ų�ʱ��ʱʱ��,��
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
	        tempStr = "��"+tempStr+"¥";
	        m_conState.SetWindowText(tempStr+"������ͣ,���ؿ�һ��");
	        Write2Log(tempStr+"���ؿ�һ��");//��¼��־
	        tempStr="";
		}
		if(m_isOpen==false&&m_eCurState==UP_PAUSE){
			m_isOpen=true;
			//setState(UP_PAUSE_OPEN);
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "��"+tempStr+"¥";
	        m_conState.SetWindowText(tempStr+"������ͣ,���ؿ�һ��");
	        Write2Log(tempStr+"���ؿ�һ��");//��¼��־
	        tempStr="";
		}
	}
	break;
		case 6://�ų��׹رպ����Ϊ
			KillTimer(6);
            //CString tempStr;
			KillTimer(9);
			GetDlgItem(IDC_LEFTDOOR)->MoveWindow(112,450,30,45);
            GetDlgItem(IDC_RIGHTDOOR)->MoveWindow(142,450,30,45);
			m_curWidth=0;

			SetTimer(7,DOOR_CLOSE_TIME*1000,NULL);//�������ų�ʱ��ʱʱ��

			m_isClosing=false;

			GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(TRUE);
	        GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	        GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	        GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	        if(m_isOpen==true&&m_eCurState==DOWN_PAUSE){
		         m_isOpen=false;
			     tempStr.Format("%d",m_iCurFloor);
	             tempStr = "��"+tempStr+"¥";
	             m_conState.SetWindowText(tempStr+"������ͣ,�Ź�һ��");
	             Write2Log(tempStr+"�Ź�һ��");//��¼��־
	             tempStr="";
			}
	        if(m_isOpen==true&&m_eCurState==UP_PAUSE){
		         m_isOpen=false;
			     tempStr.Format("%d",m_iCurFloor);
	             tempStr = "��"+tempStr+"¥";
	             m_conState.SetWindowText(tempStr+"������ͣ���Ź�һ��");
	             Write2Log(tempStr+"�Ź�һ��");//��¼��־
	             tempStr="";
			}
	
	//ǰ����һ¥��
	//gotoNextDest();
	break;
		case 7://���ݹ��ų�ʱ����
		   KillTimer(7);
		   GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE); 
		   GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
		   GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	       GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
 
		   //��ͷ���Զ�����
		   if(m_eCurState==UP_PAUSE && m_iCurFloor==FLOOR_NUM) m_eCurState =DOWN_PAUSE;
	       if(m_eCurState==DOWN_PAUSE && m_iCurFloor==1) m_eCurState =UP_PAUSE;
		   
		   if(!isFull()&&!isOverWeight()) m_bCanSchedule=true;   //��ʱ�ſ��Ա�����
           gotoNextDest();

		   break;
		case 8://���Ŵ�����
			if(m_curWidth>24){    //hhh,α�ջ�
				KillTimer(8);
			}
			else{
				m_curWidth+=3;
				GetDlgItem(IDC_LEFTDOOR)->MoveWindow(112,450,30-m_curWidth,45);
                GetDlgItem(IDC_RIGHTDOOR)->MoveWindow(142+m_curWidth,450,30-m_curWidth,45);
			}            
			break;
		case 9://���Ŵ�����
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

	KillTimer(7);                                         //�Ŵ�ʱ��ֹ�պϳ�ʱ����

	m_bCanSchedule=false;                                 //�Ŵ�ʱ����������

    GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);   //�Ŵ�ʱ�������źͳ˿ͽ���ʧЧ
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);

	m_isOpening=true;


	tempStr.Format("%d",m_iCurFloor);
	tempStr = "��"+tempStr+"¥";
	m_conState.SetWindowText(tempStr+"�����ڿ���");
	Write2Log(tempStr+"�����ڿ���");//��¼��־
	tempStr="";

	SetTimer(5,DOOR_ONOFF_TIME*1000,NULL);

	SetTimer(8,250,NULL);
    

	/*SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//�������ų�ʱ��ʱʱ��
	
	if(m_eCurState==UP_RUN||m_eCurState==DOWN_RUN)
	{
	   GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	   GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	   GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

       if(m_iCurPassengerNum>0) GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	   else  GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);

	//����֮ǰ���ܵ��������������ڵ�����Ŀ��¥�㣬ת�򲢽��
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

	//�ӵȴ��������Ƴ���ǰ¥������
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
	tempStr = "����"+tempStr+"¥,�ſ�";
	m_conState.SetWindowText(tempStr);
	tempStr1.Format("%d",m_iCurPassengerNum);
	Write2Log(tempStr+"("+tempStr1+"��)");//��¼��־
	tempStr="";

	
	//GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);
	
	m_isOpen=true;
	enableRelateBtn(m_eCurState,m_iCurFloor);

	//SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//�������ų�ʱ��ʱʱ��
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
	        tempStr = "��"+tempStr+"¥";
	        m_conState.SetWindowText(tempStr+"������ͣ,���ؿ�һ��");
	        Write2Log(tempStr+"���ؿ�һ��");//��¼��־
	        tempStr="";
		}
		if(m_isOpen==false&&m_eCurState==UP_PAUSE){
			m_isOpen=true;
			//setState(UP_PAUSE_OPEN);
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "��"+tempStr+"¥";
	        m_conState.SetWindowText(tempStr+"������ͣ,���ؿ�һ��");
	        Write2Log(tempStr+"���ؿ�һ��");//��¼��־
	        tempStr="";
		}
	}*/
}

void CElevatorDlg::closeDoor() 
{
	CString tempStr;
	//��ͷ���Զ�����
	if(m_eCurState==UP_PAUSE && m_iCurFloor==FLOOR_NUM) m_eCurState =DOWN_PAUSE;
	if(m_eCurState==DOWN_PAUSE && m_iCurFloor==1) m_eCurState =UP_PAUSE;

	KillTimer(2);                                         //�űպ�ʱ��ֹ���ų�ʱ����

	m_bCanSchedule=false;                                 //�űպ�ʱ����������

	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);   //�űպ�ʱ�������źͳ˿ͽ���ʧЧ
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	m_isClosing=true;


    tempStr.Format("%d",m_iCurFloor);
	tempStr = "��"+tempStr+"¥";
	m_conState.SetWindowText(tempStr+"�����ڱպ�");
	Write2Log(tempStr+"�����ڱպ�"); //��¼��־

	SetTimer(6,DOOR_ONOFF_TIME*1000,NULL);

	SetTimer(9,250,NULL);
	
	/*GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	if(m_isOpen==true&&m_eCurState==DOWN_PAUSE){
		    m_isOpen=false;
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "��"+tempStr+"¥";
	        m_conState.SetWindowText(tempStr+"������ͣ,�Ź�һ��");
	        Write2Log(tempStr+"�Ź�һ��");//��¼��־
	        tempStr="";
	}
	if(m_isOpen==true&&m_eCurState==UP_PAUSE){
		    m_isOpen=false;
			tempStr.Format("%d",m_iCurFloor);
	        tempStr = "��"+tempStr+"¥";
	        m_conState.SetWindowText(tempStr+"������ͣ���Ź�һ��");
	        Write2Log(tempStr+"�Ź�һ��");//��¼��־
	        tempStr="";
	}
	
	//ǰ����һ¥��
	gotoNextDest();*/
}

void CElevatorDlg::OnBtnCreateFault() 
{
	// TODO: Add your control notification handler code here
	if(m_eCurState==UP_RUN || m_eCurState==DOWN_RUN)
 	{
		AfxMessageBox("�����������������У����滷�������������Ϊ���ϣ�");
 		return;
 	}
 	if(m_iCurPassengerNum > 0)
 	{
 		AfxMessageBox("���ݵ�ǰ�г˿ͣ���������ֹ��ϣ�");
 		return;
 	}
 	
 	m_eOldState = m_eCurState;
 	m_eCurState =MAL_FUNCTION;
 	GetDlgItem(IDC_BTN_CREATE_FAULT)->EnableWindow(FALSE);
 	GetDlgItem(IDC_BTN_CORRECT_FAULT)->EnableWindow(TRUE);
 	m_conState.SetWindowText(stateDespArr[m_eCurState]);//�ı����״̬��ʾ
 	Write2Log("�������ϣ�");//��¼��־
}

void CElevatorDlg::OnBtnCorrectFault() 
{
	// TODO: Add your control notification handler code here
    m_eCurState =m_eOldState;
	GetDlgItem(IDC_BTN_CREATE_FAULT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CORRECT_FAULT)->EnableWindow(FALSE);
	m_conState.SetWindowText(stateDespArr[m_eCurState]);//�ı����״̬��ʾ
	Write2Log("�������ݹ����Ѿ��޸������Դ��");//��¼��־
	
}

void CElevatorDlg::OnBtnPsgEnter() 
{
	// TODO: Add your control notification handler code here

	CString TempStr ="";

    /*if(m_iCurPassengerNum==0){
		GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	}*/

	KillTimer(2);                                            //�˿ͳ���ʱ��ֹ��ʱ����

	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);     //�˿ͳ���ʱ���������ţ�
	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);      //һ��ֻ�����һ��
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	m_isEntering=true;


    TempStr.Format("%d",m_iCurPassengerNum+1);
    m_conPsgNum.SetWindowText("��"+TempStr+"���˿�������...");
	Write2Log("��"+TempStr+"���˿�������...");

	SetTimer(3,PSG_INOUT_TIME*1000,NULL);
	
	/*m_iCurPassengerNum++;
    
	if(isOverWeight())
	{
		m_bCanSchedule=false;

		GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);   //���Źز���
		GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);    //�˽���ȥ
        buzz();
		CString TempStr ="";
        TempStr.Format("%d",m_iCurPassengerNum);
        m_conPsgNum.SetWindowText("!����");
        Write2Log("��������½�1��");

        AfxMessageBox("�����ݳ��أ���˿�����");
               
        //return;
	}
    else{
	   if(isFull())
	   {
		   m_bCanSchedule=false;
		   m_conPsgNum.SetWindowText("!����"); 
		   AfxMessageBox("���������أ���������");
		   
	   }
	   else{
		   m_bCanSchedule=true;
		   CString TempStr ="";
           TempStr.Format("%d",m_iCurPassengerNum);
           m_conPsgNum.SetWindowText("���ݵ�ǰ���������"+TempStr);
           Write2Log("��1��");
	   }
	}*/
}

void CElevatorDlg::OnBtnPsgLeave() 
{
	// TODO: Add your control notification handler code here

    CString TempStr ="";

	if(m_iCurPassengerNum==0)
	{
     AfxMessageBox("�����ڵ�ǰ�޳˿�!");
     return;
	}

    KillTimer(2);                                           //�˿ͳ���ʱ��ֹ��ʱ����

	GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);    //�˿ͳ���ʱ���������ţ�
	GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);      //һ��ֻ�����һ��
	GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(FALSE);

	m_isLeaving=true;


	TempStr.Format("%d",m_iCurPassengerNum);
    m_conPsgNum.SetWindowText("��"+TempStr+"���˿ͳ�����...");
	Write2Log("��"+TempStr+"���˿ͳ�����...");

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
          m_conPsgNum.SetWindowText("!����");
		  Write2Log("�˳������ѳ���״̬");
          AfxMessageBox("���ݻָ���������л�������");
		}
        else{
			m_bCanSchedule=true;
			GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);    //�˿��Խ���
			CString TempStr ="";
            TempStr.Format("%d",m_iCurPassengerNum);
            m_conPsgNum.SetWindowText("���ݵ�ǰ����������"+TempStr);
            Write2Log("��һ��");
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
		AfxMessageBox("���Ȱ�¥�㰴ť������ȥ¥�㣡");
		return;
	}

	if(isOverWeight())    //����ʱ�˿͵����ťȥ�������ǲ������
	{
		/*GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(FALSE);     //�˽���ȥ
	    GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);    //���Źز���
		GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
		m_isOpen=true;*/
	    
       
        m_conPsgNum.SetWindowText("!����!");
        AfxMessageBox("�����ݳ��أ���˿�����");

        return;
	}
	
	if(isMalFunction())
	{
		AfxMessageBox("�������ݲ������ϣ���ѡ������������ݣ�");
		return;
	}

	if(m_isOpening||m_isClosing||m_isEntering||m_isLeaving) return;

    if(m_isOpen==true){
		AfxMessageBox("�����Źغ��ٰ���");
		
		return;
	}

	int iReqFloor = nID-300+1;

	if((m_eCurState==UP_RUN && iReqFloor<=m_iCurFloor) || \
		(m_eCurState==UP_PAUSE && iReqFloor<m_iCurFloor))
	{
		AfxMessageBox("������������ݵ�ǰ���з���һ�£��絽������¥�㣬������������ݣ�");
		return;
	}else if((m_eCurState==DOWN_RUN && iReqFloor>=m_iCurFloor) || \
		(m_eCurState==DOWN_PAUSE && iReqFloor>m_iCurFloor))
	{
		AfxMessageBox("������������ݵ�ǰ���з���һ�£��絽������¥�㣬������������ݣ�");
		return;
	}

	//�պõ�����ͣ¥�������󣬴�ʱ����¥��ͣ���ĵ���ֱ�ӿ���
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
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//��������
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
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//��������		
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

	m_conState.SetWindowText(stateDespArr[m_eCurState]);//�ı����״̬��ʾ
	GetDlgItem(IDC_MYBUTTONS+iReqFloor-1)->EnableWindow(FALSE);

}

void CElevatorDlg::gotoNextDest()
{

  if(m_eCurState==UP_PAUSE) 
  {	
	if((m_iNextDestFloor = m_cUpWaitQueue->getNextAvail())==-1)//���ж��пգ���������
	{

	if(m_iCurPassengerNum>0) 
	{
	//������ǰ��¥�����󣬵��г˿ͣ�������ͣ״̬
	}
	else{
		m_eCurState =IDLE;
		Write2Log("����");//��¼��־
	}
	
	}
	else{m_eCurState =UP_RUN;}

}
else if(m_eCurState==DOWN_PAUSE) 
{
	if((m_iNextDestFloor = m_cDownWaitQueue->getNextAvail())==-1)//���ж��пգ���������
	{

	if(m_iCurPassengerNum>0) //������ǰ��¥�����󣬵��г˿ͣ�������ͣ״̬
	{
	}else{
		m_eCurState =IDLE;
		Write2Log("����");//��¼��־
	}
	
	}else{m_eCurState =DOWN_RUN;}
}

m_conState.SetWindowText(stateDespArr[m_eCurState]);//�ı����״̬��ʾ

//�ҵ�����һ������ 
  if(m_iNextDestFloor>0) SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//��������


}

void CElevatorDlg::enableRelateBtn(enum state eCurState, int iFloorNo)
{
	//Enable��ǰ¥�㰴ť
	GetDlgItem(IDC_MYBUTTONS+iFloorNo-1)->EnableWindow(TRUE);

	//֪ͨ������Enable��¥�㰴ť
	int tarFloorBtnID = (eCurState==UP_PAUSE) ? (2*(iFloorNo-1)) : (2*(iFloorNo-1)+1);
	m_pParent->SendMessage(WM_ARRIVE_ONEFLOOR,(WPARAM)tarFloorBtnID);

}

void CElevatorDlg::Write2Log(CString content)
{
 CString tempStr;
 tempStr.Format("%d",m_iElevatorNo);

 CTime m_SysTime = CTime::GetCurrentTime();

 try{
    m_cLogFile.WriteString("����"+tempStr+" ["+content+"]\t("+m_SysTime.Format("%Y-%m-%d %H:%M:%S")+")\n");
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
	m_iCurFloor = iIniFloor;//���ݿ�ʼʱ����¥��
	m_iNextDestFloor = -1;
	m_eCurState = IDLE;	
	m_eBackupDirection = BAD_DIRE;
	m_bCanSchedule = TRUE;
	m_isOpen=false;        //������һ��ʼ�պ�
	m_isOpening=false;
	m_isClosing=false;
	m_isEntering=false;
	m_isLeaving=false;

	m_curWidth=0;

	m_pParent=pParent;

	m_cUpWaitQueue =new CUpWaitQueue(FLOOR_NUM);
	m_cDownWaitQueue =new CDownWaitQueue(FLOOR_NUM);


	stateDespArr[0] = "���ݿ��У���������";
	stateDespArr[1] = "�������������У���ѡ���������ݻ�ȴ�";
	stateDespArr[2] = "�������������У���ѡ���������ݻ�ȴ�";
	stateDespArr[3] = "����������ͣ��";
	stateDespArr[4] = "����������ͣ��";
	stateDespArr[5] = "���ݿ��ţ���˿�����";
	stateDespArr[6] = "���ݹ��ϣ���ѡ����������";	
	stateDespArr[7] = "";
    //stateDespArr[8] = "����������ͣ��������";
	//stateDespArr[9] = "����������ͣ��������";
	//stateDespArr[10] = "����������ͣ��������";
	//stateDespArr[11] = "����������ͣ��������";


	str_arrElevatorName[0]='1';
	str_arrElevatorName[1]='2';
	str_arrElevatorName[2]='3';
	str_arrElevatorName[3]='4';
	str_arrElevatorName[4]='5';
	str_arrElevatorName[5]='6';
	
	CString tempStr;
	tempStr.Format("%d",iElevatorNo);
	tempStr = "logs\\log"+tempStr+".txt";
//����־�ļ�
	try{
			m_cLogFile.Open( tempStr, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite\
							| CFile::typeText , &m_Except);
			m_cLogFile.SeekToEnd();
			Write2Log("���ݿ���");

}catch(CException* e){}
}

void CElevatorDlg::acceptReq(sOuterRequest &tmpOuterRequest)
{
enum direction eReqDirection = tmpOuterRequest.eReqDirection;
int iReqFloor = tmpOuterRequest.iReqFloor;

//�պõ�����ͣ¥��������ֱ�ӿ���
if((m_eCurState==IDLE || m_eCurState==UP_PAUSE || m_eCurState==DOWN_PAUSE) && iReqFloor == m_iCurFloor)
{
if(eReqDirection==UP) m_eCurState = UP_RUN;
else m_eCurState = DOWN_RUN;

buzz();
openDoor();
return;
}

enum direction realDire = (iReqFloor>m_iCurFloor) ? UP : DOWN; 

switch(m_eCurState)    //���ģ�˳�����������Ƚϣ����ɶȴ��߼���Խ��Խ��
{
case IDLE:
	//��¼�û������������Ӧ�����з���һ�µ�������Ա���ݵ�����������
	if(eReqDirection==UP && realDire==DOWN){
		m_eBackupDirection = UP;
		m_bCanSchedule = FALSE;//�����ڵ��ﱾ����¥��ǰ�������ٱ�����
	}else if(eReqDirection==DOWN && realDire==UP){
		m_eBackupDirection = DOWN;
		m_bCanSchedule = FALSE;//�����ڵ��ﱾ����¥��ǰ�������ٱ�����
	}
	
	if(realDire==UP)
	{
		m_eCurState =UP_RUN;
		m_cUpWaitQueue->addElement(iReqFloor);
	}else{
		m_eCurState =DOWN_RUN;
		m_cDownWaitQueue->addElement(iReqFloor);
	}

	m_conState.SetWindowText(stateDespArr[m_eCurState]);//�ı����״̬��ʾ
	Write2Log(stateDespArr[m_eCurState]);//��¼��־

	m_iNextDestFloor = iReqFloor;

	KillTimer(1);
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//��������
	break;

case UP_PAUSE:
	m_iNextDestFloor = m_cUpWaitQueue->getNextAvail();
	if(m_iNextDestFloor==-1 || iReqFloor<m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cUpWaitQueue->addElement(iReqFloor);
	m_eCurState =UP_RUN;
	m_conState.SetWindowText(stateDespArr[m_eCurState]);//�ı����״̬��ʾ

	KillTimer(1);		
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//��������
	break;
	
case DOWN_PAUSE:
	m_iNextDestFloor = m_cDownWaitQueue->getNextAvail();
	if(m_iNextDestFloor==-1 || iReqFloor>m_iNextDestFloor) m_iNextDestFloor = iReqFloor;
	m_cDownWaitQueue->addElement(iReqFloor);
	m_eCurState =DOWN_RUN;
	m_conState.SetWindowText(stateDespArr[m_eCurState]);//�ı����״̬��ʾ

	KillTimer(1);		
	SetTimer(1,ONE_FLOOR_TIME*1000,NULL);//��������		
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
	//CSplashWnd::ShowSplashScreen(this); //��ʾ�������棬���˰�
	return 0;
}



void CElevatorDlg::arrivalAct()        //��������
{
	CString tempStr,tempStr1;
 	SetTimer(2,DOOR_OPEN_TIME*1000,NULL);//�������ų�ʱ��ʱʱ��
	
	if(m_eCurState==UP_RUN||m_eCurState==DOWN_RUN)
	{
	   GetDlgItem(IDC_BTN_OPEN_DOOR)->EnableWindow(FALSE);
	   GetDlgItem(IDC_BTN_PSG_ENTER)->EnableWindow(TRUE);
	   GetDlgItem(IDC_BTN_PSG_LEAVE)->EnableWindow(TRUE);

       if(m_iCurPassengerNum>0) GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(TRUE);
	   else  GetDlgItem(IDC_BTN_CLOSE_DOOR)->EnableWindow(FALSE);

	//����֮ǰ���ܵ��������������ڵ�����Ŀ��¥�㣬ת�򲢽��
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
		m_eBackupDirection = BAD_DIRE;         //���ʾ����š����

	}else{

	//�ӵȴ��������Ƴ���ǰ¥������
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
	tempStr = "����"+tempStr+"¥,�ſ�";
	m_conState.SetWindowText(tempStr);
	tempStr1.Format("%d",m_iCurPassengerNum);
	Write2Log(tempStr+"("+tempStr1+"��)");//��¼��־
	tempStr="";
	
	
	m_isOpen=true;
	enableRelateBtn(m_eCurState,m_iCurFloor);      //¥���ٴο��ã����������ڷ�����Ϣ
	}
}
