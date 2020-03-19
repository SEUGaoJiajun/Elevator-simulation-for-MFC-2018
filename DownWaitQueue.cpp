// DownWaitQueue.cpp: implementation of the CDownWaitQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Elevator.h"
#include "DownWaitQueue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDownWaitQueue::CDownWaitQueue()
{

}

CDownWaitQueue::~CDownWaitQueue()
{

}

int CDownWaitQueue::getNextAvail()
{
 int result =-1;
 for(int i=m_iMaxQueueLen; i>0; i--)
 {
	if(m_cBitString->getBit(i)) 
	{
		result = i;
		break;
	}
 }
 if(result>0) m_iCurPos= i-1;
 return result;
}

CDownWaitQueue::CDownWaitQueue(int iMaxQueueLen)
{
 m_iCurPos =1;
 m_iMaxQueueLen = iMaxQueueLen;
 m_cBitString = new CBitString(m_iMaxQueueLen);
}
