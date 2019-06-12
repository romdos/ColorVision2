// ColorVisionDoc.cpp : implementation of the CColorVisionDoc class
//

#include "stdafx.h"
#include "ColorVision.h"

#include "ColorVisionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorVisionDoc

IMPLEMENT_DYNCREATE(CColorVisionDoc, CDocument)

BEGIN_MESSAGE_MAP(CColorVisionDoc, CDocument)
	//{{AFX_MSG_MAP(CColorVisionDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorVisionDoc construction/destruction

CColorVisionDoc::CColorVisionDoc()
{
	// TODO: add one-time construction code here

}

CColorVisionDoc::~CColorVisionDoc()
{
}

BOOL CColorVisionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CColorVisionDoc serialization

void CColorVisionDoc::Serialize(CArchive& ar)
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
// CColorVisionDoc diagnostics

#ifdef _DEBUG
void CColorVisionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorVisionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColorVisionDoc commands
