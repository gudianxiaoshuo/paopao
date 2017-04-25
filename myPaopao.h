// myPaopao.h : main header file for the MYPAOPAO application
//

#if !defined(AFX_MYPAOPAO_H__DA9B1FE2_8B82_417C_841C_D19906652427__INCLUDED_)
#define AFX_MYPAOPAO_H__DA9B1FE2_8B82_417C_841C_D19906652427__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyPaopaoApp:
// See myPaopao.cpp for the implementation of this class
//

class CMyPaopaoApp : public CWinApp
{
public:
	CMyPaopaoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPaopaoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyPaopaoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAOPAO_H__DA9B1FE2_8B82_417C_841C_D19906652427__INCLUDED_)
