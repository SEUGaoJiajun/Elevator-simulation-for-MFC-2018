// WaitQueue.h: interface for the CWaitQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAITQUEUE_H__9F5B2477_39B9_4271_9C92_D85528CDC7FB__INCLUDED_)
#define AFX_WAITQUEUE_H__9F5B2477_39B9_4271_9C92_D85528CDC7FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EleBasicData.h"
#include "BitString.h"

//用位向量实现电梯窗体等待队列头文件
 

class CWaitQueue  
{
public:
	CWaitQueue(int iMaxQueueLen);
	void removeElement(int iDestFloor);
	void addElement(int iDestFloor);
	CWaitQueue();	
	virtual ~CWaitQueue();	
protected:
	CBitString* m_cBitString;
	int m_iMaxQueueLen;
	int m_iCurPos;
};


#endif // !defined(AFX_WAITQUEUE_H__9F5B2477_39B9_4271_9C92_D85528CDC7FB__INCLUDED_)
