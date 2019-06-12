// GlobalObjectsFrame.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "GlobalObjectsFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsFrame

IMPLEMENT_DYNCREATE(CGlobalObjectsFrame, CMDIChildWnd)

CGlobalObjectsFrame::CGlobalObjectsFrame()
{
}

CGlobalObjectsFrame::~CGlobalObjectsFrame()
{
}


BEGIN_MESSAGE_MAP(CGlobalObjectsFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CGlobalObjectsFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsFrame message handlers

BOOL CGlobalObjectsFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

	cs.x=8+320+40;	//maxser +40
	cs.y=10-8;	//maxser -8
    cs.cx=320;
    cs.cy=280;
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
