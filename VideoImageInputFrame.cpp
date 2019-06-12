// VideoImageInputFrame.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "VideoImageInputFrame.h"


// CVideoImageInputFrame

IMPLEMENT_DYNCREATE(CVideoImageInputFrame, CMDIChildWnd)

CVideoImageInputFrame::CVideoImageInputFrame()
{

}

CVideoImageInputFrame::~CVideoImageInputFrame()
{
}


BEGIN_MESSAGE_MAP(CVideoImageInputFrame, CMDIChildWnd)
END_MESSAGE_MAP()


// CVideoImageInputFrame message handlers
/////////////////////////////////////////////////////////////////////////////


BOOL CVideoImageInputFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	BITMAP m_Bitmap;
	int WMHeight;
	int WMWidth;

	CColorVisionApp *pApp= (CColorVisionApp *)AfxGetApp ();
	/*VideoImageRepresentationType=pApp->VideoImageRepresentationType;
	if(VideoImageRepresentationType==0)
	{*/
	m_Bitmap=pApp->m_BitmapApp;
	WMHeight=(int)m_Bitmap.bmHeight;
	WMWidth=(int)m_Bitmap.bmWidth;
	if(WMWidth>320)
	{
		WMWidth=min(WMWidth,640);
	}
	else
	{
		WMWidth=640;
	}
	if(WMHeight>240)
	{
	WMHeight=min(WMHeight,480);
	}
	else
	{
	WMHeight=240;
	}
	cs.x=2;
	cs.y=2;
    cs.cx=320+WMWidth+30;
    cs.cy=WMHeight+40;
	
	/*}
	if(VideoImageRepresentationType==1)
	{
	cs.x=2+340;
	cs.y=2;
    cs.cx=320;
    cs.cy=240;
	}*/
	if(CMDIChildWnd::PreCreateWindow(cs))
	{
return TRUE;
	}
	else
	{
		return FALSE;
	}
}
