// BitString.h: interface for the CBitString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITSTRING_H__E4A5980F_1EE9_4811_A0C3_D7C8964E1279__INCLUDED_)
#define AFX_BITSTRING_H__E4A5980F_1EE9_4811_A0C3_D7C8964E1279__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBitString  
{
public:
	CString showBitMap();
	void clrBit(int index);
	bool getBit(int index);
	void setBit(int index);
	CBitString(int iStrlen);
	CBitString();
	virtual ~CBitString();

private:
	WORD m_wBitString;
	int m_iStrLen;
};

#endif // !defined(AFX_BITSTRING_H__E4A5980F_1EE9_4811_A0C3_D7C8964E1279__INCLUDED_)
