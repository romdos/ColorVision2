// ColorVisionView.cpp : implementation of the CColorVisionView class
//

#include "stdafx.h"
#include "ColorVision.h"

#include "ColorVisionDoc.h"
#include "ColorVisionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorVisionView

IMPLEMENT_DYNCREATE(CColorVisionView, CScrollView)

BEGIN_MESSAGE_MAP(CColorVisionView, CScrollView)
	//{{AFX_MSG_MAP(CColorVisionView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorVisionView construction/destruction

CColorVisionView::CColorVisionView()
{
	// TODO: add construction code here

}

CColorVisionView::~CColorVisionView()
{
}

BOOL CColorVisionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CColorVisionView drawing

void CColorVisionView::OnDraw(CDC* pDC)
{
	CColorVisionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CColorVisionView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CColorVisionView diagnostics

#ifdef _DEBUG
void CColorVisionView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CColorVisionView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CColorVisionDoc* CColorVisionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorVisionDoc)));
	return (CColorVisionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColorVisionView message handlers
