// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Elevator.h"
#include "MainDlg.h"
#include "math.h"
#include "SplashWnd.h"
#include "Mmsystem.h"    //ʹ�ñ�����������ͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//���ش�����벿��

//������


CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{

	//����ϵͳ��־Ŀ¼
	try
	{
		CreateDirectory("logs",NULL);
	}
		catch(CException* e)
		{
			AfxMessageBox("ϵͳ��־Ŀ¼����ʧ��");
		}

	//����־�ļ�
	try
	{
		m_cLogFile.Open("logs\\log_origin.txt", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite\
		| CFile::typeText , &m_Except);
		m_cLogFile.SeekToEnd();
	}catch(CException* e){}

	str_arrElevatorName[0]='1';
	str_arrElevatorName[1]='2';
	str_arrElevatorName[2]='3';
	str_arrElevatorName[3]='4';
    str_arrElevatorName[4]='5';
    str_arrElevatorName[5]='6';

	for(int i=0;i<ELEVATOR_NUM;i++)  m_elevatorArr[i]=0;

	iTotalFailTimes = 0;

}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)

	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_MESSAGE(WM_ARRIVE_ONEFLOOR,OnOneFloorArrived) //����ĳһ¥��Ķ�����Ϣ
	ON_WM_CLOSE()
    ON_COMMAND_RANGE(IDC_FLOORBUTTONS,IDC_FLOORBUTTONS+20,OnFloorBtnClk)
	ON_WM_MOVE()

END_MESSAGE_MAP()


// CMainDlg message handlers

void CMainDlg::OnDestroy()          //���ٸ����ݴ��塢¥���ⲿ��ť���رն�ʱ������յȴ�����
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	for(int i=0;i<ELEVATOR_NUM;i++)
	{
		delete m_elevatorArr[i];
	}

	for(i=0;i<FLOOR_NUM;i++)
	{
		delete m_pFloorButton[i][0];
		delete m_pFloorButton[i][1];
	}

	KillTimer(1);
	lWaitQueue.~CircleSingleLink();

	try{
		Write2Log("ϵͳ�ر�.");
		m_cLogFile.Close();
	}catch(CException* e){}

}


void CMainDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
		case 1:
			Schedule();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CenterWindow();
	// TODO: Add your specialized creation code here

	CSplashWnd::ShowSplashScreen(this); //��ʾ��������
	return 0;
}


LONG CMainDlg::OnOneFloorArrived(WPARAM wP, LPARAM lP)
{
	int iReqFloor=(int)wP;
	CString tempString;

	GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->EnableWindow(TRUE);
	GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->GetWindowText(tempString);

	if(tempString.GetLength() >4 )//����֮��ť�ָ�����
	{
	tempString = tempString.Mid(0,tempString.GetLength()-3);
	GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->SetWindowText(tempString);
	}
	return 0;
}


BOOL CMainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    HINSTANCE hinstance;
	hinstance=AfxGetApp()->m_hInstance;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1),hinstance,SND_RESOURCE|SND_ASYNC|SND_LOOP);
	CenterWindow();
	
	// TODO: Add extra initialization here
		//�����Ҳ�¥�����̨��ť
	CString strCaption;
	int iPanelLeft = 1350;     //������Ҷ����Լ����п��
	int iPanelTop = 135;
	int iColWidth = 90;
	int iRowHeight = 95;	

	int iBtnWidth = 50;
	int iBtnHeight = 35;
	int i;

	try
	{
		for(i=FLOOR_NUM;i>0;i--)
			{
				strCaption.Format("%d",i);
				m_pFloorButton[i-1][0]=new CButton;
				m_pFloorButton[i-1][1]=new CButton;
				m_pFloorButton[i-1][0]->Create(strCaption+"��",BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,\
					CRect(\
					iPanelLeft,\
					iPanelTop+(10-i)*iRowHeight/2,\
					iPanelLeft+iBtnWidth,\
					iPanelTop+(10-i)*iRowHeight/2+iBtnHeight),\
					this,IDC_FLOORBUTTONS+2*(i-1));

				m_pFloorButton[i-1][1]->Create(strCaption+"��",BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,\
					CRect(\
					iPanelLeft+iColWidth,\
					iPanelTop+(10-i)*iRowHeight/2,\
					iPanelLeft+iColWidth+iBtnWidth,\
					iPanelTop+(10-i)*iRowHeight/2+iBtnHeight),\
					this,IDC_FLOORBUTTONS+2*(i-1)+1);
			}

	}catch(CException* e)
			{
				AfxMessageBox("�����˳�");
				return FALSE;
			}

	//�����������ð�ť10���Ϻ�1����
	m_pFloorButton[9][0]->ShowWindow(FALSE);
	m_pFloorButton[0][1]->ShowWindow(FALSE);

	try
	{
		//��������ݵĳ�ʼ״̬����Ҫ��

       
        m_elevatorArr[0] = new CElevatorDlg(1,MAX_PASSENGER_NUM,1,this);
        m_elevatorArr[1] = new CElevatorDlg(2,MAX_PASSENGER_NUM,1,this);
        m_elevatorArr[2] = new CElevatorDlg(3,MAX_PASSENGER_NUM,FLOOR_NUM/2,this);
        m_elevatorArr[3] = new CElevatorDlg(4,MAX_PASSENGER_NUM,FLOOR_NUM/2,this);
        m_elevatorArr[4] = new CElevatorDlg(5,MAX_PASSENGER_NUM,FLOOR_NUM,this);
        m_elevatorArr[5] = new CElevatorDlg(6,MAX_PASSENGER_NUM,FLOOR_NUM,this);

        CRect testRect;
		this->GetWindowRect(testRect);

		for(i=0;i<ELEVATOR_NUM;i++)     //�ܹ���������
			{
				m_elevatorArr[i]->Create(IDD_ELEVATOR_DIALOG,this);
			    //m_elevatorArr[i]->Create(this,IDD_ELEVATOR_DIALOG);
			    /*m_elevatorArr[i]->Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,
					CRect(testRect.left+10+i*220,testRect.top+30,testRect.left+10+(i+1)*220,testRect.top+750),
					this,NULL,0,NULL);*/

				m_elevatorArr[i]->MoveWindow(CRect(testRect.left+10+i*220,testRect.top+30,testRect.left+10+(i+1)*220,testRect.top+750));

				//m_elevatorArr[i]->ShowWindow(WS_CHILD|WS_VISIBLE);
			}

	}
		catch(CException* e)
		{
			AfxMessageBox("���ݴ���ʧ�ܣ������˳���");
			return FALSE;
		}

	Write2Log("ϵͳ�Ѿ�������");	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CMainDlg::OnFloorBtnClk(UINT nID)
{
	int iReqFloor =nID-500+1;
	sOuterRequest tmpOuterRequest = No2ReqStruct(iReqFloor);

	if((lWaitQueue.searchNode(tmpOuterRequest))>0)
		{
			AfxMessageBox("���棬�ظ�����");
			return;
		}

	GetDlgItem(nID)->EnableWindow(FALSE);

	trytoSchedule(tmpOuterRequest);//����¥���������	
 
}

void CMainDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(IDYES==MessageBox("�Ƿ���ֹ���ε��ݷ���?","���ݷ���ϵͳ@2018.9",MB_YESNO))
	CDialog::OnClose();
}

sOuterRequest CMainDlg::No2ReqStruct(int iNo)   //������������ṹ��Ļ���
{
	sOuterRequest tempVal;
	if(iNo%2==0) 
		{
			tempVal.eReqDirection =DOWN;
		}
	else
		{
			tempVal.eReqDirection =UP;
			iNo++;
		}

	tempVal.iReqFloor = iNo/2;
	tempVal.iAge =0;
	tempVal.bReClaimed = FALSE;
	return tempVal;
}

int CMainDlg::ReqStruct2No(const sOuterRequest &tmpRequest)
{
 return (tmpRequest.eReqDirection==UP) ? (2*(tmpRequest.iReqFloor-1)) : (2*(tmpRequest.iReqFloor-1)+1);
}

int CMainDlg::Goodness(const sOuterRequest &tmpOuterRequest)   //Ѱ�����ŵ���
{
	int returnVal = -1;
	
//����������������ݵ�����״̬

	int tmpCurFloor;
	int tmpCurWeight;
	int tmpPrioValue;
	bool tmpCanSchedule;
	enum state tmpState;

	int iPrioValue = 8000;//��������������ԽС���ȼ�Խ��ȷ�����ŵ��ݣ����루��λʱ�䣩������������Ϊ��Ȩϵ��

	for(int i=0;i<ELEVATOR_NUM; i++)
	{
		tmpState = m_elevatorArr[i]->getState();
		tmpCurFloor = m_elevatorArr[i]->getCurFloor();
		tmpCurWeight = m_elevatorArr[i]->getCurWeight();
		tmpCanSchedule = m_elevatorArr[i]->canSchedule();

		if(tmpState!=MAL_FUNCTION && tmpCanSchedule)
			{
				if(tmpState==IDLE || \
				   (tmpOuterRequest.eReqDirection==UP && (tmpState==UP_RUN || tmpState==UP_PAUSE)) || \
				   (tmpOuterRequest.eReqDirection==DOWN && (tmpState==DOWN_RUN || tmpState==DOWN_PAUSE)) )
					{
					    if(tmpState==IDLE)
							{
							//����õ��ݵ�������
								tmpPrioValue = DIST_PRIO*abs(tmpOuterRequest.iReqFloor-tmpCurFloor)+\
												WEIGHT_PRIO*tmpCurWeight;
								if(tmpPrioValue<iPrioValue)
									{
										iPrioValue = tmpPrioValue;
										returnVal = i;
									}
							}
						if(tmpOuterRequest.eReqDirection==UP && tmpOuterRequest.iReqFloor>=tmpCurFloor)
							{
							//����õ��ݵ�������
								tmpPrioValue = DIST_PRIO*(tmpOuterRequest.iReqFloor-tmpCurFloor)+\
												WEIGHT_PRIO*tmpCurWeight;
								if(tmpPrioValue<iPrioValue)
									{
										iPrioValue = tmpPrioValue;
										returnVal = i;
									}
							}
						if(tmpOuterRequest.eReqDirection==DOWN && tmpOuterRequest.iReqFloor<=tmpCurFloor)
							{
							//����õ��ݵ�������
								tmpPrioValue = DIST_PRIO*(tmpCurFloor-tmpOuterRequest.iReqFloor)+\
									     		WEIGHT_PRIO*tmpCurWeight;
								if(tmpPrioValue<iPrioValue)
									{
										iPrioValue = tmpPrioValue;
										returnVal = i;
									}
							}
					}
			}
	}
    return returnVal;

}
//��ʱ�������������������������
// �ú����������Լ���Զ�ʱ�ַ���������е�����
// �ú����ڶ��п�ʱֹͣ��ʱ����ֱ�ӷ��أ�����
// ���ڵ�ǰ�ȴ������е�ÿ�������Էַ�
// ���ɹ��ַ���ȥ������ɾ����δ�ɹ��ַ������ñ�ǲ�������������·Żض���
// ����һ��ʱ����δ�õ����ɵ�������ֱ��ɾ��
//Schedule() trytoSchedule()����ƹ����

void CMainDlg::Schedule()
{
 	if(lWaitQueue.getLength() == 0)
		{
		   KillTimer(1);//����Ϊ��
		   return;
		}

	int iReqFloor;
	CString tempString,tempString1;
	sOuterRequest tmpOuterRequest;

	while(lWaitQueue.cutHead(tmpOuterRequest) && !tmpOuterRequest.bReClaimed)
		{
			if(tmpOuterRequest.iAge < BAD_REQUEST_AGE)//����ʱ��û�еõ����䣬ֱ��ɾ��
				{
					trytoSchedule(tmpOuterRequest);
				}
			else
				{
					iReqFloor = ReqStruct2No(tmpOuterRequest);//ת��������ť��
					GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->EnableWindow(TRUE);
					iTotalFailTimes++;//�����ܵ���ʧ�ܴ���
					tempString.Format("%d",tmpOuterRequest.iReqFloor);	
					tempString1 = (tmpOuterRequest.eReqDirection==UP) ? "��":"��";	
					AfxMessageBox("����ʱ��ȡ��,�����½�������\n"+tempString+tempString1);
				}
		}


//����׷�ӵ���β�������ʶλ�ָ�
	if(tmpOuterRequest.bReClaimed)
		{
			tmpOuterRequest.bReClaimed = FALSE;
			lWaitQueue.appendTail(tmpOuterRequest);
		}
	
	lWaitQueue.refreshLink();           //���µȴ�����

}

void CMainDlg::trytoSchedule(sOuterRequest &tmpRequest)
{
	int targetElevator=-1;
	int iReqFloor;
	CString tempString,tempString1;

	if((targetElevator = Goodness(tmpRequest))<0)//û���ҵ����ʵĽ����ߣ��ٷ���
		{
			tmpRequest.iAge++;
			tmpRequest.bReClaimed = TRUE;
			lWaitQueue.appendTail(tmpRequest);
		}
	else //����Ϣ���ݸ�Ŀ�����
		{

		//���ڵ��ݸպ��ڵ�ǰ¥�����������ݵķ�������������ĳ���λ�Ҫ�죡��Ѫ�Ľ�ѵ��
			tempString1.Format("%c",str_arrElevatorName[targetElevator]);	
			iReqFloor = ReqStruct2No(tmpRequest);//ת��������ť��
			GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->GetWindowText(tempString);	
			GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->SetWindowText(tempString+"("+tempString1+")");   //��ʾ�����ݶԸõ��Ƚ�����Ӧ

			m_elevatorArr[targetElevator]->acceptReq(tmpRequest);      //֪ͨ���������Ĺ����������ݴ���
		}

	KillTimer(1);
	SetTimer(1,SCHEDULE_INTERVAL*1000,NULL);//�����������ĵ��ȶ�ʱ��
}

void CMainDlg::Write2Log(const CString &content)
{
    if(content=="") return;
	
	CTime m_SysTime = CTime::GetCurrentTime();

	try
	{
		m_cLogFile.WriteString(content+"\t("+m_SysTime.Format("%Y-%m-%d %H:%M:%S")+")\n");
	}

		catch(CException* e){}
}

void CMainDlg::OnMove()
{
    CRect testRect;
	int i=0;
	this->GetWindowRect(testRect);

	for(i=0;i<ELEVATOR_NUM;i++)     //ELEVATOR_NUM-3��Ϊ��̨����
			{
				//m_elevatorArr[i]->Create(IDD_ELEVATOR_DIALOG,this);
			    //m_elevatorArr[i]->Create(this,IDD_ELEVATOR_DIALOG);
			    /*m_elevatorArr[i]->Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,
					CRect(testRect.left+10+i*220,testRect.top+30,testRect.left+10+(i+1)*220,testRect.top+750),
					this,NULL,0,NULL);*/
		if(m_elevatorArr[i]!=0){
				m_elevatorArr[i]->MoveWindow(CRect(testRect.left+10+i*220,testRect.top+30,testRect.left+10+(i+1)*220,testRect.top+750));
		}

				//m_elevatorArr[i]->ShowWindow(WS_CHILD|WS_VISIBLE);
			} 

}
