// UpWaitQueue.cpp: implementation of the CUpWaitQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Elevator.h"
#include "UpWaitQueue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUpWaitQueue::CUpWaitQueue()
{

}

CUpWaitQueue::~CUpWaitQueue()
{

}

int CUpWaitQueue::getNextAvail()
{
 int result =-1;
 for(int i=1; i<=m_iMaxQueueLen; i++)
 {
	if(m_cBitString->getBit(i)) 
	{
		result = i;
		break;
	}
 }

 if(result>0) m_iCurPos= i+1;
 return result;
}

CUpWaitQueue::CUpWaitQueue(int iMaxQueueLen)
{
  m_iCurPos =1;
  m_iMaxQueueLen = iMaxQueueLen;
  m_cBitString = new CBitString(m_iMaxQueueLen);
}
