// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Elevator.h"
#include "MainDlg.h"
#include "math.h"
#include "SplashWnd.h"
#include "Mmsystem.h"    //使用背景音乐所需头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//主控窗体代码部分

//主窗体


CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{

	//创建系统日志目录
	try
	{
		CreateDirectory("logs",NULL);
	}
		catch(CException* e)
		{
			AfxMessageBox("系统日志目录创建失败");
		}

	//打开日志文件
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
	ON_MESSAGE(WM_ARRIVE_ONEFLOOR,OnOneFloorArrived) //到达某一楼层的定制消息
	ON_WM_CLOSE()
    ON_COMMAND_RANGE(IDC_FLOORBUTTONS,IDC_FLOORBUTTONS+20,OnFloorBtnClk)
	ON_WM_MOVE()

END_MESSAGE_MAP()


// CMainDlg message handlers

void CMainDlg::OnDestroy()          //销毁各电梯窗体、楼层外部按钮；关闭定时器；清空等待队列
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
		Write2Log("系统关闭.");
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

	CSplashWnd::ShowSplashScreen(this); //显示启动画面
	return 0;
}


LONG CMainDlg::OnOneFloorArrived(WPARAM wP, LPARAM lP)
{
	int iReqFloor=(int)wP;
	CString tempString;

	GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->EnableWindow(TRUE);
	GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->GetWindowText(tempString);

	if(tempString.GetLength() >4 )//到达之后按钮恢复正常
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
		//创建右侧楼层控制台按钮
	CString strCaption;
	int iPanelLeft = 1350;     //面板左右顶点以及行列宽度
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
				m_pFloorButton[i-1][0]->Create(strCaption+"↑",BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,\
					CRect(\
					iPanelLeft,\
					iPanelTop+(10-i)*iRowHeight/2,\
					iPanelLeft+iBtnWidth,\
					iPanelTop+(10-i)*iRowHeight/2+iBtnHeight),\
					this,IDC_FLOORBUTTONS+2*(i-1));

				m_pFloorButton[i-1][1]->Create(strCaption+"↓",BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,\
					CRect(\
					iPanelLeft+iColWidth,\
					iPanelTop+(10-i)*iRowHeight/2,\
					iPanelLeft+iColWidth+iBtnWidth,\
					iPanelTop+(10-i)*iRowHeight/2+iBtnHeight),\
					this,IDC_FLOORBUTTONS+2*(i-1)+1);
			}

	}catch(CException* e)
			{
				AfxMessageBox("程序退出");
				return FALSE;
			}

	//隐藏两个无用按钮10层上和1层下
	m_pFloorButton[9][0]->ShowWindow(FALSE);
	m_pFloorButton[0][1]->ShowWindow(FALSE);

	try
	{
		//对三组电梯的初始状态做出要求

       
        m_elevatorArr[0] = new CElevatorDlg(1,MAX_PASSENGER_NUM,1,this);
        m_elevatorArr[1] = new CElevatorDlg(2,MAX_PASSENGER_NUM,1,this);
        m_elevatorArr[2] = new CElevatorDlg(3,MAX_PASSENGER_NUM,FLOOR_NUM/2,this);
        m_elevatorArr[3] = new CElevatorDlg(4,MAX_PASSENGER_NUM,FLOOR_NUM/2,this);
        m_elevatorArr[4] = new CElevatorDlg(5,MAX_PASSENGER_NUM,FLOOR_NUM,this);
        m_elevatorArr[5] = new CElevatorDlg(6,MAX_PASSENGER_NUM,FLOOR_NUM,this);

        CRect testRect;
		this->GetWindowRect(testRect);

		for(i=0;i<ELEVATOR_NUM;i++)     //总共六部电梯
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
			AfxMessageBox("电梯创建失败，程序将退出！");
			return FALSE;
		}

	Write2Log("系统已经启动！");	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CMainDlg::OnFloorBtnClk(UINT nID)
{
	int iReqFloor =nID-500+1;
	sOuterRequest tmpOuterRequest = No2ReqStruct(iReqFloor);

	if((lWaitQueue.searchNode(tmpOuterRequest))>0)
		{
			AfxMessageBox("警告，重复请求！");
			return;
		}

	GetDlgItem(nID)->EnableWindow(FALSE);

	trytoSchedule(tmpOuterRequest);//接受楼层后分配电梯	
 
}

void CMainDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(IDYES==MessageBox("是否终止本次电梯仿真?","电梯仿真系统@2018.9",MB_YESNO))
	CDialog::OnClose();
}

sOuterRequest CMainDlg::No2ReqStruct(int iNo)   //标号与电梯请求结构体的互换
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

int CMainDlg::Goodness(const sOuterRequest &tmpOuterRequest)   //寻找最优电梯
{
	int returnVal = -1;
	
//逐个检查各个正常电梯的运行状态

	int tmpCurFloor;
	int tmpCurWeight;
	int tmpPrioValue;
	bool tmpCanSchedule;
	enum state tmpState;

	int iPrioValue = 8000;//优先数，优先数越小优先级越大，确定最优电梯，距离（单位时间）和梯内人数作为加权系数

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
							//计算该电梯的优先数
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
							//计算该电梯的优先数
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
							//计算该电梯的优先数
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
//定时处理主控中心请求队列中请求
// 该函数被周期性激活，以定时分发请求队列中的请求
// 该函数在队列空时停止定时器并直接返回，否则
// 对于当前等待队列中的每个请求尝试分发
// 将成功分发出去的请求删除，未成功分发的做好标记并增加年龄后重新放回队列
// 超过一定时间仍未得到分派的请求则直接删除
//Schedule() trytoSchedule()互打乒乓球

void CMainDlg::Schedule()
{
 	if(lWaitQueue.getLength() == 0)
		{
		   KillTimer(1);//队列为空
		   return;
		}

	int iReqFloor;
	CString tempString,tempString1;
	sOuterRequest tmpOuterRequest;

	while(lWaitQueue.cutHead(tmpOuterRequest) && !tmpOuterRequest.bReClaimed)
		{
			if(tmpOuterRequest.iAge < BAD_REQUEST_AGE)//若长时间没有得到分配，直接删除
				{
					trytoSchedule(tmpOuterRequest);
				}
			else
				{
					iReqFloor = ReqStruct2No(tmpOuterRequest);//转换成请求按钮号
					GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->EnableWindow(TRUE);
					iTotalFailTimes++;//递增总调度失败次数
					tempString.Format("%d",tmpOuterRequest.iReqFloor);	
					tempString1 = (tmpOuterRequest.eReqDirection==UP) ? "↑":"↓";	
					AfxMessageBox("请求超时被取消,请重新进行请求\n"+tempString+tempString1);
				}
		}


//本次追加到队尾的请求标识位恢复
	if(tmpOuterRequest.bReClaimed)
		{
			tmpOuterRequest.bReClaimed = FALSE;
			lWaitQueue.appendTail(tmpOuterRequest);
		}
	
	lWaitQueue.refreshLink();           //更新等待队列

}

void CMainDlg::trytoSchedule(sOuterRequest &tmpRequest)
{
	int targetElevator=-1;
	int iReqFloor;
	CString tempString,tempString1;

	if((targetElevator = Goodness(tmpRequest))<0)//没有找到合适的接受者，再放入
		{
			tmpRequest.iAge++;
			tmpRequest.bReClaimed = TRUE;
			lWaitQueue.appendTail(tmpRequest);
		}
	else //将消息传递给目标电梯
		{

		//对于电梯刚好在当前楼层的情况，电梯的返回往往比下面的程序段还要快！（血的教训）
			tempString1.Format("%c",str_arrElevatorName[targetElevator]);	
			iReqFloor = ReqStruct2No(tmpRequest);//转换成请求按钮号
			GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->GetWindowText(tempString);	
			GetDlgItem(IDC_FLOORBUTTONS+iReqFloor)->SetWindowText(tempString+"("+tempString1+")");   //显示几号梯对该调度进行响应

			m_elevatorArr[targetElevator]->acceptReq(tmpRequest);      //通知，接下来的工作交给电梯窗体
		}

	KillTimer(1);
	SetTimer(1,SCHEDULE_INTERVAL*1000,NULL);//启动主控中心调度定时器
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

	for(i=0;i<ELEVATOR_NUM;i++)     //ELEVATOR_NUM-3后即为三台电梯
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
