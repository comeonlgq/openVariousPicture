// ShowDoc.h : interface of the CShowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWDOC_H__B55682E2_928E_456C_A42E_F00A51E3F132__INCLUDED_)
#define AFX_SHOWDOC_H__B55682E2_928E_456C_A42E_F00A51E3F132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShowDoc : public CDocument
{
protected: // create from serialization only
	CShowDoc();
	DECLARE_DYNCREATE(CShowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWDOC_H__B55682E2_928E_456C_A42E_F00A51E3F132__INCLUDED_)
