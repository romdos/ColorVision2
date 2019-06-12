// GlobalObjectsDoc.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "GlobalObjectsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsDoc

IMPLEMENT_DYNCREATE(CGlobalObjectsDoc, CDocument)

CGlobalObjectsDoc::CGlobalObjectsDoc()
{
	CColorVisionApp *pApp;
pApp= (CColorVisionApp *)AfxGetApp ();
	GlobalObjectsRepresentationType = pApp->GlobalObjectsRepresentationType;
}

BOOL CGlobalObjectsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CGlobalObjectsDoc::~CGlobalObjectsDoc()
{
}


BEGIN_MESSAGE_MAP(CGlobalObjectsDoc, CDocument)
	//{{AFX_MSG_MAP(CGlobalObjectsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsDoc diagnostics

#ifdef _DEBUG
void CGlobalObjectsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGlobalObjectsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsDoc serialization

void CGlobalObjectsDoc::Serialize(CArchive& ar)
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
// CGlobalObjectsDoc commands
