// WaitQueue.cpp: implementation of the CWaitQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Elevator.h"
#include "WaitQueue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWaitQueue::CWaitQueue()
{
 m_iCurPos =1;
 m_iMaxQueueLen = FLOOR_NUM;
 m_cBitString = new CBitString(m_iMaxQueueLen);
}

CWaitQueue::~CWaitQueue()
{

}

void CWaitQueue::addElement(int iDestFloor)
{
 m_cBitString->setBit(iDestFloor);
}

void CWaitQueue::removeElement(int iDestFloor)
{
 m_cBitString->clrBit(iDestFloor);
}


CWaitQueue::CWaitQueue(int iMaxQueueLen)
{
 m_iCurPos =1;
 m_iMaxQueueLen = iMaxQueueLen;
 m_cBitString = new CBitString(m_iMaxQueueLen);
}
