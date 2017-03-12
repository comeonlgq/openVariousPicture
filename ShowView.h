// ShowView.h : interface of the CShowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWVIEW_H__AF2A63CD_365D_4200_8666_BFB4E2ABF23A__INCLUDED_)
#define AFX_SHOWVIEW_H__AF2A63CD_365D_4200_8666_BFB4E2ABF23A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShowView : public CView
{
protected: // create from serialization only
	CShowView();
	DECLARE_DYNCREATE(CShowView)

// Attributes
public:
	CShowDoc* GetDocument();

// Operations
public:
    // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetImageCLSID(const WCHAR *format, CLSID *pCLSID);
	WCHAR* ToWChar(char *str);
	CString strOpenFileName;
	virtual ~CShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShowView)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ShowView.cpp
inline CShowDoc* CShowView::GetDocument()
   { return (CShowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWVIEW_H__AF2A63CD_365D_4200_8666_BFB4E2ABF23A__INCLUDED_)
