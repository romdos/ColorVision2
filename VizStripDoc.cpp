// VizStripDoc.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "VizStripDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVizStripDoc

IMPLEMENT_DYNCREATE(CVizStripDoc, CDocument)

CVizStripDoc::CVizStripDoc()
{
	CColorVisionApp *pApp;
pApp= (CColorVisionApp *)AfxGetApp ();

	StripRepresentationType=pApp->StripRepresentationType;
}

BOOL CVizStripDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	
	return TRUE;
}

CVizStripDoc::~CVizStripDoc()
{
	//CColorVisionApp *pApp;
//pApp= (CColorVisionApp *)AfxGetApp ();
//pApp->m_StripColorRepresentation=FALSE;
}


BEGIN_MESSAGE_MAP(CVizStripDoc, CDocument)
	//{{AFX_MSG_MAP(CVizStripDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CVizStripDoc diagnostics

#ifdef _DEBUG
void CVizStripDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVizStripDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVizStripDoc serialization

void CVizStripDoc::Serialize(CArchive& ar)
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
// CVizStripDoc commands
