// Show.h : main header file for the SHOW application
//

#if !defined(AFX_SHOW_H__FC437033_9DCC_4FDC_A666_20C693380933__INCLUDED_)
#define AFX_SHOW_H__FC437033_9DCC_4FDC_A666_20C693380933__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CShowApp:
// See Show.cpp for the implementation of this class
//

class CShowApp : public CWinApp
{
public:
	CShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CShowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ULONG_PTR m_pGdiToken;
	GdiplusStartupInput m_gdiplusStartupInput;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOW_H__FC437033_9DCC_4FDC_A666_20C693380933__INCLUDED_)
