// VideoImageInputDoc.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "VideoImageInputDoc.h"


// CVideoImageInputDoc

IMPLEMENT_DYNCREATE(CVideoImageInputDoc, CDocument)

CVideoImageInputDoc::CVideoImageInputDoc()
{
	//m_DibGrayScaleDoc=NULL;
	m_DibDoc = NULL;
	/*CColorVisionApp *pApp;
	pApp= (CColorVisionApp *)AfxGetApp ();
	VideoImageRepresentationType=pApp->VideoImageRepresentationType;*/
}

BOOL CVideoImageInputDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	//if(VideoImageRepresentationType==1)
    //{
	//InitializeGrayScale();
	//}
	return TRUE;
}

CVideoImageInputDoc::~CVideoImageInputDoc()
{
	CColorVisionApp *pApp;
	pApp= (CColorVisionApp *)AfxGetApp ();
		
								//pApp->m_VideoCameraIsLoaded=FALSE;
							   pApp->pDoci2=NULL;
							   if((pApp->VideoImageProcessedNumber>0)&&
								   (pApp->ColorImageProcess!=NULL))
							   {
pApp->ColorImageProcess->DeleteTemporal();

							   pApp->VideoImageProcessedNumber=0;
							   }
							   
                               
							   pApp->m_Video_ImageSegmented=FALSE;

                             
	   
							 
}
/*void CVideoImageInputDoc::InitializeGrayScale()
{
	CColorVisionApp *pApp;
	pApp= (CColorVisionApp *)AfxGetApp ();
	
//if(VideoImageRepresentationType==1)
	//{
		if(pApp->VideoImageProcessedNumber==0)
		{
			m_DibGrayScaleDoc = new CDibGrayScale;
		}
		m_DibGrayScaleDoc->CalculateGrayscaleVideo();
		
		
	//}
}*/

BEGIN_MESSAGE_MAP(CVideoImageInputDoc, CDocument)
END_MESSAGE_MAP()


// CVideoImageInputDoc diagnostics

#ifdef _DEBUG
void CVideoImageInputDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CVideoImageInputDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CVideoImageInputDoc serialization

void CVideoImageInputDoc::Serialize(CArchive& ar)
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
#endif


// CVideoImageInputDoc commands

