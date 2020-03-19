// DownWaitQueue.h: interface for the CDownWaitQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNWAITQUEUE_H__5338CBFA_88E6_45EF_9FDD_A0546540B96F__INCLUDED_)
#define AFX_DOWNWAITQUEUE_H__5338CBFA_88E6_45EF_9FDD_A0546540B96F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WaitQueue.h"

class CDownWaitQueue : public CWaitQueue  
{
public:
	CDownWaitQueue(int iMaxQueueLen);
	int getNextAvail();
	CDownWaitQueue();
	virtual ~CDownWaitQueue();

};

#endif // !defined(AFX_DOWNWAITQUEUE_H__5338CBFA_88E6_45EF_9FDD_A0546540B96F__INCLUDED_)
