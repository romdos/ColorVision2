// VideoImageInputView.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"

#include "VideoImageInputView.h"
#include <math.h>

// CVideoImageInputView

IMPLEMENT_DYNCREATE(CVideoImageInputView, CView)


#ifndef _DEBUG
CVideoImageInputDoc* CVideoImageInputView::GetDocument(){
	return (CVideoImageInputDoc*) m_pDocument;
};
#endif

CVideoImageInputView::CVideoImageInputView()
{
	pApp= (CColorVisionApp *)AfxGetApp ();
	VideoImageRepresentationType=pApp->VideoImageRepresentationType;
	VideoImageProcessedNumber=pApp->VideoImageProcessedNumber;
if(VideoImageRepresentationType==0)
	{
	strTitle = "Video Input & The Results of Video Input Processing";
	m_CannotDisp = "Cannot display camera input";
	m_CannotDispOut ="Cannot display the processing of camera input";
	}
	/*if(VideoImageRepresentationType==1)
	{
	strTitle = "Processing of Video Input";
	m_CannotDisp = "Cannot display camera input";
	m_CannotDispOut ="Cannot display the processing of camera input"; 
	}*/
}

CVideoImageInputView::~CVideoImageInputView()
{
}

BEGIN_MESSAGE_MAP(CVideoImageInputView, CView)
END_MESSAGE_MAP()

void CVideoImageInputView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	pApp= (CColorVisionApp *)AfxGetApp ();
	pDoc = GetDocument();

	pDoc->SetTitle((LPCTSTR) strTitle);

	if(VideoImageRepresentationType==0)
	{	
pApp->pDoci2 = pDoc;
	}
if(VideoImageRepresentationType==1)
	{	
pApp->pDoci3 = pDoc;
	}
/*if(VideoImageRepresentationType==0)
	{
		CameraInputDraw();
	}*/
}

/*void 

CVideoImageInputView::OnUpdate(CView* pSender,LPARAM lHint,CObject* pHint)
{
	/*if((VideoImageRepresentationType==0)&&(VideoImageProcessedNumber!=0))
	{
		CameraInputDraw();
	}
	CView::OnUpdate(NULL,0L,0);
}*/
// CVideoImageInputView drawing

void CVideoImageInputView::OnDraw(CDC* pDC)
{
	pDoc = GetDocument();
	pApp= (CColorVisionApp *)AfxGetApp ();
	// TODO: add draw code here
	//VideoImageRepresentationType=pDoc->VideoImageRepresentationType;
	//if(VideoImageRepresentationType==0)
	//{
		CameraInputDraw(pDC);
	//}
	//if(VideoImageRepresentationType==1)
	//{
		if(pApp->VideoImageProcessedNumber!=0)
		{
		CameraOutputDraw(pDC);
		}
	//}


}


/////////////////////////////////////////////////////////////////////////////
void

CVideoImageInputView::CalculateBrush(int side_triangle,int side_hue,int BunAverSat,int BunAverGr,
int* scoor1,int* scoor2,int* scoor3,int* nscoor1,int* nscoor2,int* nscoor3)
{
	int Coor1;
	int Coor2;
	int Scoor1;
	int Scoor2;
	int Scoor3;
	int NScoor1;
	int NScoor2;
	int NScoor3;
	int GrayLev;
	int NewGrayLev;
	int Imax;

	if(side_triangle==0)
				{
                 Coor1=255-CoorHuPoints[side_hue];
				 Coor2=CoorHuPoints[side_hue];
				 Scoor1=84+(BunAverSat*(Coor1-84))/15;
				 Scoor2=84+(BunAverSat*(Coor2-84))/15;
				 Scoor3=(84*(15-BunAverSat))/15;
				 Imax=max(Scoor1,max(Scoor2,Scoor3));
                 Scoor1=(Scoor1*255)/Imax;
				 Scoor2=(Scoor2*255)/Imax;
				 Scoor3=(Scoor3*255)/Imax;
				 GrayLev=int(0.3*((float)Scoor1) +0.59*((float)Scoor2)+0.11*((float)Scoor3));
				 GrayLev=GrayLev/4;
				 if(GrayLev>BunAverGr)
					   {
				        
                        NScoor1=(Scoor1*BunAverGr)/GrayLev;
				        NScoor2=(Scoor2*BunAverGr)/GrayLev;
				        NScoor3=(Scoor3*BunAverGr)/GrayLev;
		NewGrayLev=int(0.3*((float)NScoor1) +0.59*((float)NScoor2)+0.11*((float)NScoor3));
		NewGrayLev=NewGrayLev/4;
					   }
				       else
					   {
                       NScoor1=Scoor1;
				       NScoor2=Scoor2;
				       NScoor3=Scoor3;
					   }
				      }
if(side_triangle==1)
		  {
		   Coor1=255-CoorHuPoints[side_hue];
		   Coor2=CoorHuPoints[side_hue];
		         Scoor1=(84*(15-BunAverSat))/15;
				 Scoor2=84+(BunAverSat*(Coor1-84))/15;
				 Scoor3=84+(BunAverSat*(Coor2-84))/15;
				 Imax=max(Scoor1,max(Scoor2,Scoor3));
                 Scoor1=(Scoor1*255)/Imax;
				 Scoor2=(Scoor2*255)/Imax;
				 Scoor3=(Scoor3*255)/Imax;
		  
GrayLev=int(0.3*((float)Scoor1) +0.59*((float)Scoor2)+0.11*((float)Scoor3));
				 GrayLev=GrayLev/4;
				 if(GrayLev>BunAverGr)
				 {
                 NScoor1=(Scoor1*BunAverGr)/GrayLev;
				 NScoor2=(Scoor2*BunAverGr)/GrayLev;
				 NScoor3=(Scoor3*BunAverGr)/GrayLev;
				 NewGrayLev=int(0.3*((float)NScoor1) +0.59*((float)NScoor2)+0.11*((float)NScoor3));
		NewGrayLev=NewGrayLev/4;
				 }
				 else
				 {
                 NScoor1=Scoor1;
				 NScoor2=Scoor2;
				 NScoor3=Scoor3;
				 }
				 
		  }
if(side_triangle==2)
					 {
					  Coor1=CoorHuPoints[side_hue];
					  Coor2=255-CoorHuPoints[side_hue];
					  Scoor1=84+(BunAverSat*(Coor1-84))/15;
				      Scoor2=(84*(15-BunAverSat))/15;
				      Scoor3=84+(BunAverSat*(Coor2-84))/15;
				      Imax=max(Scoor1,max(Scoor2,Scoor3));
                 Scoor1=(Scoor1*255)/Imax;
				 Scoor2=(Scoor2*255)/Imax;
				 Scoor3=(Scoor3*255)/Imax;
		  
		  GrayLev=int(0.3*((float)Scoor1) +0.59*((float)Scoor2)+0.11*((float)Scoor3));
				 GrayLev=GrayLev/4;
				 if(GrayLev>BunAverGr)
				 {
                 NScoor1=(Scoor1*BunAverGr)/GrayLev;
				 NScoor2=(Scoor2*BunAverGr)/GrayLev;
				 NScoor3=(Scoor3*BunAverGr)/GrayLev;
				 NewGrayLev=int(0.3*((float)NScoor1) +0.59*((float)NScoor2)+0.11*((float)NScoor3));
		NewGrayLev=NewGrayLev/4;
				 }
				 else
				 {
				 NScoor1=Scoor1;
				 NScoor2=Scoor2;
				 NScoor3=Scoor3;
				 }
					 
					 }
*scoor1=Scoor1;
*scoor2=Scoor2;
*scoor3=Scoor3;
*nscoor1=NScoor1;
*nscoor2=NScoor2;
*nscoor3=NScoor3;
}
/////////////////////////////////////////////////////////////////////////////
BOOL
  
CVideoImageInputView::CameraInputDraw(CDC* pDC)
//CVideoImageInputView::CameraInputDraw()
{
	HDC hDC;
	int bSuccess;
	BITMAPINFOHEADER BmHeader;
	BITMAP *pm_Bitmap;
	BITMAP m_Bitmap;
	//unsigned char *m_ImageBits;

	//CRect rect;
	//CClientDC dc(this);
           

	//hDC = dc.m_hDC;
    
	pApp= (CColorVisionApp *)AfxGetApp ();


	pm_Bitmap=pApp->pm_BitmapApp;
	m_Bitmap=pApp->m_BitmapApp;
	//m_ImageBits=(unsigned char*)m_Bitmap.bmBits;
	BmHeader=pApp->info;

	hDC = pDC->m_hDC;
	

	
	bSuccess = ::StretchDIBits(hDC,                        // hDC
								   0,                          // DestX
								   0,                          // DestY
								   320,
								   240,
								   0,                          // SrcX
								   0,                           // SrcY
								   (int)pm_Bitmap->bmWidth,      // nDestWidth
								   (int)pm_Bitmap->bmHeight,     // nDestHeight
								    pm_Bitmap->bmBits,                // lpBits
								   (LPBITMAPINFO)&BmHeader,     // lpBitsInfo
								   DIB_RGB_COLORS,
								   SRCCOPY);
	 if(bSuccess == 0)
	{
		::MessageBox(NULL,m_CannotDisp, 
		   NULL, MB_ICONINFORMATION | MB_OK);
        return FALSE;
	}
	
return TRUE;
}
BOOL
 
CVideoImageInputView::CameraOutputDraw(CDC* pDC)
{
	HDC hDC;
	int bSuccess;
	BITMAPINFOHEADER BmHeader;
	BITMAP m_Bitmap;
	int BMWidth;
	int BMHeight;

	pDoc = GetDocument();
		          // TODO: add draw code here

pApp= (CColorVisionApp *)AfxGetApp ();
	                      if(pDoc)
						  {
		//if(pDoc->m_DibGrayScaleDoc)
		//{
	    //pDoc->m_DibGrayScaleDoc->Draw(pDC);
m_Bitmap=pApp->m_GrayBitmap;
BMWidth=(int)m_Bitmap.bmWidth;
BMHeight=(int)m_Bitmap.bmHeight;
BmHeader=pApp->info;
//pDoc->m_DibGrayScaleDoc->CalculateGrayscaleVideo();
m_Bitmap.bmBits=(void *) (pApp->pBuffer);
hDC = pDC->m_hDC;
	

	if((BMWidth>640)||(BMHeight>480))
	{
		bSuccess = ::StretchDIBits(hDC,                        // hDC
								   330,                          // DestX
								   0,                          // DestY
								   640,
								   480,
								   0,                          // SrcX
								   0,                           // SrcY
								   BMWidth,      // nDestWidth
								   BMHeight,     // nDestHeight
								    m_Bitmap.bmBits,                // lpBits
								   (LPBITMAPINFO)&BmHeader,     // lpBitsInfo
								   DIB_RGB_COLORS,
								   SRCCOPY);
	}
	else
	{
      bSuccess = ::SetDIBitsToDevice(hDC,                        // hDC
								   0,                          // DestX
								   0,                          // DestY
								   BMWidth,      // nDestWidth
								   BMHeight,     // nDestHeight
								   0,                          // SrcX
								   0,                          // SrcY
								   0,                          // nStartScan
								   (WORD)BmHeader.biHeight,    // nNumScans
								   m_Bitmap.bmBits,                // lpBits
								   (LPBITMAPINFO)&BmHeader,     // lpBitsInfo
								   DIB_RGB_COLORS); 
	}
	/*bSuccess = ::StretchDIBits(hDC,                        // hDC
								   330,                          // DestX
								   0,                          // DestY
								   320,
								   240,
								   0,                          // SrcX
								   0,                           // SrcY
								   BMWidth,      // nDestWidth
								   BMHeight,     // nDestHeight
								    m_Bitmap.bmBits,                // lpBits
								   (LPBITMAPINFO)&BmHeader,     // lpBitsInfo
								   DIB_RGB_COLORS,
								   SRCCOPY);*/
	 if(bSuccess == 0)
	{
		::MessageBox(NULL,m_CannotDispOut, 
		   NULL, MB_ICONINFORMATION | MB_OK);
        return FALSE;
	}
		
		//}
						  }
return TRUE;
}

// CVideoImageInputView diagnostics

#ifdef _DEBUG
void CVideoImageInputView::AssertValid() const
{
	CView::AssertValid();
}
CVideoImageInputDoc* CVideoImageInputView::GetDocument ()
{
ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVideoImageInputDoc)));
return (CVideoImageInputDoc*)m_pDocument;
}


#ifndef _WIN32_WCE
void CVideoImageInputView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVideoImageInputView message handlers
