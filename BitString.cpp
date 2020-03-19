// BitString.cpp: implementation of the CBitString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Elevator.h"
#include "BitString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitString::CBitString()
{
	m_iStrLen = 10;
	m_wBitString = WORD(0);
}

CBitString::~CBitString()
{

}

CBitString::CBitString(int iStrlen)
{
	if(iStrlen>32) return;
	m_iStrLen = iStrlen;
	m_wBitString = WORD(0);
}



void CBitString::setBit(int index)
{
 if(index<1 || index>m_iStrLen) return;
 m_wBitString |= ((WORD)(1) <<index);
}

bool CBitString::getBit(int index)
{
 if(index<1 || index>m_iStrLen) return FALSE;
 return (m_wBitString & ((WORD)(1) <<index)) ? TRUE:FALSE;
}

void CBitString::clrBit(int index)
{
 if(index<1 || index>m_iStrLen) return;
 m_wBitString &= ~((WORD)(1) <<index);
}

CString CBitString::showBitMap()
{
 CString strTemp="";
 for(int i=m_iStrLen; i>0; i--) strTemp += (getBit(i) ? "1":"0");
 return strTemp;
}
