// UpWaitQueue.h: interface for the CUpWaitQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPWAITQUEUE_H__EE3915C1_C937_4EFE_9C69_9ECB59718D8F__INCLUDED_)
#define AFX_UPWAITQUEUE_H__EE3915C1_C937_4EFE_9C69_9ECB59718D8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WaitQueue.h"

class CUpWaitQueue : public CWaitQueue  
{
public:
	CUpWaitQueue(int iMaxQueueLen);
	int getNextAvail();
	CUpWaitQueue();
	virtual ~CUpWaitQueue();

};

#endif // !defined(AFX_UPWAITQUEUE_H__EE3915C1_C937_4EFE_9C69_9ECB59718D8F__INCLUDED_)
