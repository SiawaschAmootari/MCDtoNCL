
// MCDtoNCL.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
typedef CStringArray CStrArr;

// CMCDtoNCLApp:
// See MCDtoNCL.cpp for the implementation of this class
//

class CMCDtoNCLApp : public CWinApp
{
public:
	CMCDtoNCLApp();
	void	ArrToVal(const CStrArr& sValArr, CString& sVal);
	void	ArrToVal(const CString sDel, const CStrArr& sValArr, CString& sVal);

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMCDtoNCLApp theApp;
