// CircleLink.h: interface for the CCircleLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLELINK_H__3FB548B2_DC69_44FD_A9D0_05C491C0BD58__INCLUDED_)
#define AFX_CIRCLELINK_H__3FB548B2_DC69_44FD_A9D0_05C491C0BD58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream.h>        //����
#define NULL 0

//�������ĵȴ�����-����

template <class T>
class CircleSingleLink;

// ����ڵ��ඨ��
template <class T>
class CircleSingleLinkNode
{
	friend CircleSingleLink<T>;
private:
	T data;
	CircleSingleLinkNode<T>* next;
};

// ������
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


// �����캯��
template <class T>
CircleSingleLink<T>::CircleSingleLink()
{
	pLinkTail=NULL;
	iLinkLength=0;
}

// ������������
template <class T>
CircleSingleLink<T>::~CircleSingleLink()
{
	removeAll();
}


// �õ�������
template <class T>
int CircleSingleLink<T>::getLength()
{
return iLinkLength;
}

// �ж������Ƿ�Ϊ��
template <class T>
bool CircleSingleLink<T>::isEmpty()
{
return getLength()==0;
}


// �õ�������
template <class T>
bool CircleSingleLink<T>::cutHead(T& x)
{

if(isEmpty()) return FALSE;


CircleSingleLinkNode<T>* tmpNode =NULL;
if(pLinkTail->next==pLinkTail)//���ֻ��һ���ڵ�
{
x = pLinkTail->data;
delete pLinkTail;
pLinkTail = NULL;
}
else
{
tmpNode = pLinkTail->next; //tmpNodeָ����׽ڵ�
pLinkTail->next = tmpNode->next;

x = tmpNode->data;
delete tmpNode;
tmpNode = NULL;
}

iLinkLength--;
return TRUE;

}

// ������β������һ��Ԫ��
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


// ��������Ѱ��ֵΪx�Ľڵ㣬����0��ʾû�ҵ�

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



// �������
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
