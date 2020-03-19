// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

/*#if !defined(AFX_INIFILE_H__8BFFDE3C_A93E_4EFD_A96E_866DE936E65E__INCLUDED_)
#define AFX_INIFILE_H__8BFFDE3C_A93E_4EFD_A96E_866DE936E65E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniFileException.h"

#define MAX_BUFFER_SIZE 2048;   //¼«´óÁ¿

class CIniFile  
{
public:
	void EraseSection(CString Section);
	void ReadSections(CStringArray &Strings);
	void ReadSection(CString Section, CStringArray &Strings);
	void WriteInteger(CString Section, CString Ident, int Value);
	int ReadInteger(CString Section, CString Ident, int Default);
	void WriteString(CString Section, CString Ident, CString Value);
	CString ReadString(CString Section, CString Ident, CString Default);
	bool SectionExists(CString Section);
	CIniFile(CString FileName);
	virtual ~CIniFile();

protected:
	CString m_strFileName;
};

#endif // !defined(AFX_INIFILE_H__8BFFDE3C_A93E_4EFD_A96E_866DE936E65E__INCLUDED_)*/
