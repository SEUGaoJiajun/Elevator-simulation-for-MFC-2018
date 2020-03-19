// CircleLink.h: interface for the CCircleLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLELINK_H__3FB548B2_DC69_44FD_A9D0_05C491C0BD58__INCLUDED_)
#define AFX_CIRCLELINK_H__3FB548B2_DC69_44FD_A9D0_05C491C0BD58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream.h>        //存疑
#define NULL 0

//主控中心等待队列-链表

template <class T>
class CircleSingleLink;

// 链表节点类定义
template <class T>
class CircleSingleLinkNode
{
	friend CircleSingleLink<T>;
private:
	T data;
	CircleSingleLinkNode<T>* next;
};

// 链表定义
template <class T>
class CircleSingleLink 
{
public:
	CircleSingleLink();
	~CircleSingleLink();

	bool cutHead(T& x);
	bool appendTail(const T& x);
	int getLength();	
	int searchNode(const T& x);	
	void refreshLink();	

private:
	CircleSingleLinkNode<T>* pLinkTail;
	int iLinkLength;
private:
	bool isEmpty();
	void removeAll();
};


// 链表构造函数
template <class T>
CircleSingleLink<T>::CircleSingleLink()
{
	pLinkTail=NULL;
	iLinkLength=0;
}

// 链表析构函数
template <class T>
CircleSingleLink<T>::~CircleSingleLink()
{
	removeAll();
}


// 得到链表长度
template <class T>
int CircleSingleLink<T>::getLength()
{
return iLinkLength;
}

// 判断链表是否为空
template <class T>
bool CircleSingleLink<T>::isEmpty()
{
return getLength()==0;
}


// 得到链表长度
template <class T>
bool CircleSingleLink<T>::cutHead(T& x)
{

if(isEmpty()) return FALSE;


CircleSingleLinkNode<T>* tmpNode =NULL;
if(pLinkTail->next==pLinkTail)//如果只有一个节点
{
x = pLinkTail->data;
delete pLinkTail;
pLinkTail = NULL;
}
else
{
tmpNode = pLinkTail->next; //tmpNode指向队首节点
pLinkTail->next = tmpNode->next;

x = tmpNode->data;
delete tmpNode;
tmpNode = NULL;
}

iLinkLength--;
return TRUE;

}

// 向链表尾部加上一个元素
template <class T>
bool CircleSingleLink<T>::appendTail(const T& x)
{
	CircleSingleLinkNode<T>* newNode=new CircleSingleLinkNode<T>;	
	if(!newNode) return FALSE;

	newNode->data=x;

	if(isEmpty())
	{
		pLinkTail = newNode;
		pLinkTail->next = pLinkTail;
	}
	else
	{
		newNode->next = pLinkTail->next;
		pLinkTail->next = newNode;
		pLinkTail = newNode;
	}

	iLinkLength++;
	return TRUE;	
}


// 在链表中寻找值为x的节点，返回0表示没找到

template <class T>
int CircleSingleLink<T>::searchNode(const T& x) 
{

	if(isEmpty()) return 0;

	CircleSingleLinkNode<T>* current=pLinkTail->next;

	int nPos=0;
	for(int i=1; i<=iLinkLength; current=current->next,i++)
	{
		if((current->data).eReqDirection==x.eReqDirection && \
			(current->data).iReqFloor==x.iReqFloor)
		{
			nPos = i;
			break;
		}
	}

	nPos = ((nPos==iLinkLength+1) ?0:nPos);
	return nPos;
}



// 清空链表
template <class T>
void CircleSingleLink<T>::removeAll()
{
	if(isEmpty()) return;

	CircleSingleLinkNode<T>* curNode=pLinkTail->next;
	CircleSingleLinkNode<T>* tmpNode;
	while(curNode)
	{
		tmpNode = curNode;
		curNode=curNode->next;
		delete tmpNode;
	}
	tmpNode = NULL;

	pLinkTail = NULL;
	iLinkLength =0;
}


template <class T>
void CircleSingleLink<T>::refreshLink()
{

	if(isEmpty()) return;

	CircleSingleLinkNode<T>* curNode=pLinkTail->next;
	while(curNode && curNode->data.bReClaimed)
	{
		curNode->data.bReClaimed = FALSE;
		curNode=curNode->next;
	}

	return;
}
#endif // !defined(AFX_CIRCLELINK_H__3FB548B2_DC69_44FD_A9D0_05C491C0BD58__INCLUDED_)
