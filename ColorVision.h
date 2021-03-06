//
//
//
//
//
//




#if !defined(AFX_COLORVISION_H__9489C2BE_B3C4_4822_A972_5786C7918411__INCLUDED_)
#define AFX_COLORVISION_H__9489C2BE_B3C4_4822_A972_5786C7918411__INCLUDED_




#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif



// main symbols
#include "resource.h"      


#include "Dib.h"
#include "DibTga.h"
#include "DibGrayScale.h"

#include "ImageProcess.h"
 
#include "BunchCountDlg.h"
#include "ColorSectionDialog.h" 




class CColorVisionApp : public CWinApp
{
public:
	BOOL m_ImageIsLoaded;
	
	
	BOOL m_VideoCameraIsLoaded;
	
	
	BOOL m_GrayScaleOpened;
	
	
	BOOL m_ImageSegmented;
	
	
	
	BOOL m_Video_ImageSegmented;
	
	
	
	BOOL m_ParamHaveBeenChanged;
	
	BOOL m_FindLabels;		// deprecated, used in Amur project

	BOOL m_FindSky;//last_cor27.05.15
	
	BOOL m_FindGreen;//last_cor08.02.16
	 

	int ColorNumber1;
	int ColorNumber2;
	int ColorNumber3; 
	
	BITMAPINFOHEADER info;
	BITMAP *pm_BitmapApp;
	BITMAP *pm_GrayBitmap;
	BITMAP m_BitmapApp;
	BITMAP m_GrayBitmap; 

	BOOL m_ImageIsInverted;
	BOOL m_StripColorRepresentation;
	BOOL m_StripGrayRepresentation;
	BOOL m_ColorBunchRepresentation;
	BOOL m_ColorSectionsRepresentation;
	
	
	BOOL m_VideoCameraInput;
	BOOL m_VideoCameraSequenceProcessing;
	BOOL m_NetworkDirectX;
	int NumberOfStrips;
	int CameraNumber;
	BOOL HorizontalVertical;
	BOOL PermuteRatios;
	
	
	int VideoImageProcessedNumber;
	int VideoInputLimit;
	int BitsPerPixel;
	
	int NumberStripClicked; 
	
	int ImageRepresentationType;
	int VideoImageRepresentationType;
	int StripRepresentationType;
	int GlobalObjectsRepresentationType;

	BunchCountDlg* m_pBunchCountDialog;
	ColorSectionDialog* m_pColorSectDialog;
	
	// todo: rename docs (reflect the role of each of them)
	CDocument* pDocColorImage;

	CDocument* pDocGrayscaleImage; // grayscale image
	CDocument* pDoci2;
	CDocument* pDoci3;
	CDocument* pDocs1;
	CDocument* pDocs2;
	CDocument* pDocs3;
	CDocument* pDocColSec1; 

	CImageProcess *ColorImageProcess;
	unsigned char* pBuffer; 
	char* buffer;
	BYTE* pData;
	
	CString strFail;
	CString strVideo;
	CString strVideoClose;
	CString strVideoClose1;
	CString strVideoClose2;
	CString strFailCrDialog;
	CString strErCrDiOb;
	CString m_CannotDisp;
	CString ServerAddress;
public:
	CColorVisionApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorVisionApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	// Implementation
	//{{AFX_MSG(CColorVisionApp)
	afx_msg void OnSegment();
	afx_msg void OnChangeParam();
	afx_msg void OnVizStrips();
	afx_msg void OnUpdateVizStrips(CCmdUI* pCmdUI);
	afx_msg void OnGrayStrips();
	afx_msg void OnUpdateGrayStrips(CCmdUI* pCmdUI);
	afx_msg void OnBunchDemo();
	afx_msg void OnUpdateBunchDemo(CCmdUI* pCmdUI);
	afx_msg void OnColorSections();
	afx_msg void OnUpdateColorSections(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() 
public:
	void OnSegmentInitialize(); 
	 
public:
	afx_msg void OnFileChangeparam();
public:
	afx_msg void OnUpdateFileChangeparam(CCmdUI *pCmdUI);
public:
	afx_msg void OnAppExit();  
public:
	afx_msg void OnUpdateChangeParam(CCmdUI *pCmdUI);
};


 
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORVISION_H__9489C2BE_B3C4_4822_A972_5786C7918411__INCLUDED_)
