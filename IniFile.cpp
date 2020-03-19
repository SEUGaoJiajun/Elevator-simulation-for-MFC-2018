// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

/*#include "stdafx.h"
#include "Elevator.h"
#include "IniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CIniFile::~CIniFile()
{

}

CIniFile::CIniFile(CString FileName)
{
  m_strFileName = FileName;
}

bool CIniFile::SectionExists(CString Section)
{
 	CStringArray Strings;
	ReadSection(Section, Strings);
	return Strings.GetSize()>0;
}

CString CIniFile::ReadString(CString Section, CString Ident, CString Default)
{
 	int nSize = 0, nLen = nSize-2;
	char *lpszReturnBuffer = 0;
	while(nLen==nSize-2)
	{
		nSize+=MAX_BUFFER_SIZE;
		if(lpszReturnBuffer) delete lpszReturnBuffer;
		lpszReturnBuffer = new char[nSize];
		nLen = GetPrivateProfileString(Section,Ident,Default,lpszReturnBuffer,//如果返回nSize-2
			nSize,m_strFileName);	//则表示缓冲区长度不足，递增MAX_BUFFER_SIZE
	}
	return lpszReturnBuffer;
}

void CIniFile::WriteString(CString Section, CString Ident, CString Value)
{
 	if(WritePrivateProfileString(Section,Ident,Value,m_strFileName)==0)
	throw CIniFileException();
}

int CIniFile::ReadInteger(CString Section, CString Ident, int Default)
{
  CString strInt = ReadString(Section,Ident,"");
  if (strInt.IsEmpty())
  {
   return Default;
  }
  else
  {
   return atoi(strInt);
  }
}

void CIniFile::WriteInteger(CString Section, CString Ident, int Value)
{
   char buffer[20];
   itoa(Value,buffer,10);
   WriteString(Section,Ident,buffer);
}

void CIniFile::ReadSection(CString Section, CStringArray &Strings)
{
 	Strings.RemoveAll();//清空字符串数组
	int nSize = 0, nLen = nSize-2;
	char *lpszReturnBuffer = 0;
	while(nLen==nSize-2)
	{
		nSize+=MAX_BUFFER_SIZE;
		if(lpszReturnBuffer) delete lpszReturnBuffer;
		lpszReturnBuffer = new char[nSize];
		nLen = GetPrivateProfileString(Section,NULL,NULL,lpszReturnBuffer,//如果返回nSize-2
			nSize,m_strFileName);	//则表示缓冲区长度不足，递增MAX_BUFFER_SIZE
	}
	char *pName = new char[MAX_PATH];
	char *pStart, *pEnd;
	pStart = lpszReturnBuffer;
	pEnd =0;
	while(pStart!=pEnd)
	{
		pEnd = strchr(pStart,0);
		nLen = pEnd-pStart;
		if(nLen==0) break;
		strncpy(pName,pStart,nLen);
		pName[nLen] = 0;
		Strings.Add(pName);
		pStart = pEnd+1;
	}	
	delete lpszReturnBuffer;
	delete pName;
}

void CIniFile::ReadSections(CStringArray &Strings)
{
 	Strings.RemoveAll();//清空字符串数组
	int nSize = 0, nLen = nSize-2;
	char *lpszReturnBuffer = 0;
	while(nLen==nSize-2)
	{
		nSize+=MAX_BUFFER_SIZE;
		if(lpszReturnBuffer) delete lpszReturnBuffer;
		lpszReturnBuffer = new char[nSize];
		nLen = GetPrivateProfileSectionNames(lpszReturnBuffer,nSize,//如果返回nSize-2则表示
			m_strFileName);	//缓冲区长度不足，递增MAX_BUFFER_SIZE
	}
	char *pName = new char[MAX_PATH];
	char *pStart, *pEnd;
	pStart = lpszReturnBuffer;
	pEnd =0;
	while(pStart!=pEnd)
	{
		pEnd = strchr(pStart,0);
		nLen = pEnd-pStart;
		if(nLen==0) break;
		strncpy(pName,pStart,nLen);
		pName[nLen] = 0;
		Strings.Add(pName);
		pStart = pEnd+1;
	}
	delete lpszReturnBuffer;
	delete pName;
}


void CIniFile::EraseSection(CString Section)
{
 	if(WritePrivateProfileString(Section,NULL,NULL,m_strFileName)==0)
		throw CIniFileException();
}
