// ShowDoc.cpp : implementation of the CShowDoc class
//

#include "stdafx.h"
#include "Show.h"

#include "ShowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowDoc

IMPLEMENT_DYNCREATE(CShowDoc, CDocument)

BEGIN_MESSAGE_MAP(CShowDoc, CDocument)
	//{{AFX_MSG_MAP(CShowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowDoc construction/destruction

CShowDoc::CShowDoc()
{
	// TODO: add one-time construction code here

}

CShowDoc::~CShowDoc()
{
}

BOOL CShowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CShowDoc serialization

void CShowDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CShowDoc diagnostics

#ifdef _DEBUG
void CShowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowDoc commands
