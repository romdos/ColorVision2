/* 
 *	Main file. 
*/








#include "stdafx.h" 
#include "ColorVision.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ViewImageDoc.h"
#include "ViewImageVw.h"

#include "VizStripDoc.h"
#include "VizStripFrame.h"
#include "VizStripView.h"

#include "GlobalObjectsDoc.h"
#include "GlobalObjectsFrame.h"
#include "GlobalObjectsView.h"

#include "VideoImageInputDoc.h"
#include "VideoImageInputFrame.h"
#include "VideoImageInputView.h"

#include "ChParam.h" 



 


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





/////////////////////////////////////////////////////////////////////////////
// CColorVisionApp

BEGIN_MESSAGE_MAP(CColorVisionApp, CWinApp)
	//{{AFX_MSG_MAP(CColorVisionApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_SEGMENT, OnSegment)
	ON_COMMAND(ID_CHANGE_PARAM, OnChangeParam)
	ON_COMMAND(ID_VIZ_STRIPS, OnVizStrips)
	ON_UPDATE_COMMAND_UI(ID_VIZ_STRIPS, OnUpdateVizStrips)
	ON_COMMAND(ID_GRAY_STRIPS, OnGrayStrips)
	ON_UPDATE_COMMAND_UI(ID_GRAY_STRIPS, OnUpdateGrayStrips)
	ON_COMMAND(ID_BUNCH_DEMO, OnBunchDemo)
	ON_UPDATE_COMMAND_UI(ID_BUNCH_DEMO, OnUpdateBunchDemo)
	ON_COMMAND(ID_COLOR_SECTIONS, OnColorSections)
	ON_UPDATE_COMMAND_UI(ID_COLOR_SECTIONS, OnUpdateColorSections)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen) 
	ON_COMMAND(ID_FILE_CHANGEPARAM, &CColorVisionApp::OnFileChangeparam)
	ON_UPDATE_COMMAND_UI(ID_FILE_CHANGEPARAM, &CColorVisionApp::OnUpdateFileChangeparam)
	ON_COMMAND(ID_APP_EXIT, &CColorVisionApp::OnAppExit) 
	ON_UPDATE_COMMAND_UI(ID_CHANGE_PARAM, &CColorVisionApp::OnUpdateChangeParam)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorVisionApp construction

CColorVisionApp::CColorVisionApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_ImageIsLoaded = FALSE;
	m_VideoCameraIsLoaded = FALSE;
	m_GrayScaleOpened = FALSE;
	m_ImageSegmented = FALSE;
	m_Video_ImageSegmented = FALSE;
	m_ImageIsInverted = TRUE;
	m_ParamHaveBeenChanged = FALSE;
	//m_FindLabels=TRUE;
	m_FindLabels = FALSE;
	m_FindSky = TRUE;
	m_FindGreen = TRUE;
	ColorNumber1 = 4;
	ColorNumber2 = 1;
	ColorNumber3 = 0;
	m_StripColorRepresentation = FALSE;
	m_StripGrayRepresentation = FALSE;
	m_ColorBunchRepresentation = FALSE;
	m_ColorSectionsRepresentation = FALSE;
	//m_CameraIsInitialized = FALSE;
	m_VideoCameraInput = FALSE;
	m_VideoCameraSequenceProcessing = FALSE;
	m_NetworkDirectX = FALSE;
	pm_inputbuffer = NULL;
	pm_BitmapApp = NULL;
	pm_GrayBitmap = NULL;
	pBuffer = NULL;
	buffer = NULL;
	pData = NULL;
	//pmListBunch = NULL;
	NumberOfStrips = 48;
	CameraNumber = 0;
	NumberStripClicked = 0;
	NumberOfBunch = 0;
	VideoImageProcessedNumber = 0;
	VideoInputLimit = 1;
	NumberOfColorSection = -1;
	HorizontalVertical = FALSE;
	PermuteRatios = TRUE;
	//printf("\n $%d",VideoInputLimit);
	ColorImageProcess = NULL;
	StripRepresentationType = 0;
	ImageRepresentationType = 0;
	VideoImageRepresentationType = 0;
	GlobalObjectsRepresentationType = 0;
	NumberOfDoc = 0;
	pm_BunchNumDialog = NULL;
	pDoci0 = NULL;
	pDoci2 = NULL;
	pDoci3 = NULL;
	pDocs1 = NULL;
	pDocs2 = NULL;
	pDocs3 = NULL;
	pDoci1 = NULL;
	pCamera = NULL; 
	pDocColSec1 = NULL;
	m_BitmapApp.bmBits = 0;
	m_BitmapApp.bmBitsPixel = 0;
	m_BitmapApp.bmHeight = 0;
	m_BitmapApp.bmPlanes = 0;
	m_BitmapApp.bmType = 0;
	m_BitmapApp.bmWidth = 0;
	m_BitmapApp.bmWidthBytes;
	m_GrayBitmap.bmBits = 0;
	m_GrayBitmap.bmBitsPixel = 0;
	m_GrayBitmap.bmHeight = 0;
	m_GrayBitmap.bmPlanes = 0;
	m_GrayBitmap.bmType = 0;
	m_GrayBitmap.bmWidth = 0;
	m_GrayBitmap.bmWidthBytes = 0;
	info.biBitCount = 0;
	info.biClrImportant = 0;
	info.biClrUsed = 0;
	info.biCompression = 0;
	info.biHeight = 0;
	info.biPlanes = 0;
	info.biSize = 0;
	info.biSizeImage = 0;
	info.biWidth = 0;
	info.biXPelsPerMeter = 0;
	info.biYPelsPerMeter = 0;
	strFail = "Cannot continue input";
	strVideo = "Net connection doesn't operate";
	strVideoClose = "Restart the program please!";
	strVideoClose1 = "Network is not avaiable!";
	strVideoClose2 = "Restart the program!";
	strFailCrDialog = "Error creating Dialog";
	strErCrDiOb = "Error Creating Dialog Object";
	m_CannotDisp = "Cannot display camera input";
	ServerAddress = "127.0.0.1";
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CColorVisionApp object

CColorVisionApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CColorVisionApp initialization

BOOL CColorVisionApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

								// Change the registry key under which our settings are stored.
								// TODO: You should modify this string to be something appropriate
								// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

							   // Register the application's document templates.  Document templates
							   //  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_COLORVTYPE,
		RUNTIME_CLASS(CViewImageDoc),
		RUNTIME_CLASS(CViewImageFrame), // custom MDI child frame
		RUNTIME_CLASS(CViewImageVw));
	AddDocTemplate(pDocTemplate);

	CMultiDocTemplate* pVizStripTemplate;
	pVizStripTemplate = new CMultiDocTemplate(
		IDR_COLORVTYPE,
		RUNTIME_CLASS(CVizStripDoc),
		RUNTIME_CLASS(CVizStripFrame), // custom MDI child frame
		RUNTIME_CLASS(CVizStripView));
	AddDocTemplate(pVizStripTemplate);

	CMultiDocTemplate* pGlobalObjectsTemplate;
	pGlobalObjectsTemplate = new CMultiDocTemplate(
		IDR_COLORVTYPE,
		RUNTIME_CLASS(CGlobalObjectsDoc),
		RUNTIME_CLASS(CGlobalObjectsFrame), // custom MDI child frame
		RUNTIME_CLASS(CGlobalObjectsView));
	AddDocTemplate(pGlobalObjectsTemplate);

	CMultiDocTemplate* pVideoImageInputTemplate;
	pVideoImageInputTemplate = new CMultiDocTemplate(
		IDR_COLORVTYPE,
		RUNTIME_CLASS(CVideoImageInputDoc),
		RUNTIME_CLASS(CVideoImageInputFrame), // custom MDI child frame
		RUNTIME_CLASS(CVideoImageInputView));
	AddDocTemplate(pVideoImageInputTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open


	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// No message handlers
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

// App command to run the dialog
void CColorVisionApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CColorVisionApp message handlers


void CColorVisionApp::OnSegment()
{
	int DimX;        // width  of the image in pixels
	int DimY;

	// TODO: Add your command handler code here
	if (m_ImageIsLoaded)
	{
		DimX = pm_BitmapApp->bmWidth;
		DimY = pm_BitmapApp->bmHeight;
		//printf("\n $%d",DimY);
		if ((ColorImageProcess) && (DimX == ColorImageProcess->DimX) &&
			(DimY == ColorImageProcess->DimY) && (HorizontalVertical == ColorImageProcess->HorizontalVertical) &&
			(NumberOfStrips == ColorImageProcess->NumStrips))
		{
			ColorImageProcess->execution_time = 0;
			ColorImageProcess->DeleteTemporal();
			ColorImageProcess->SegmentImage(VideoImageProcessedNumber);
		}
		else
		{
			if (ColorImageProcess == NULL)
			{
				ColorImageProcess = new CImageProcess(VideoInputLimit);
				ColorImageProcess->InitialConstructions();
				ColorImageProcess->SegmentImage(VideoImageProcessedNumber);
				m_ParamHaveBeenChanged = FALSE;
			}
			else
			{
				ColorImageProcess->DeleteTemporal();
				delete ColorImageProcess;
				ColorImageProcess = NULL;
				ColorImageProcess = new CImageProcess(VideoInputLimit);

				ColorImageProcess->InitialConstructions();
				ColorImageProcess->SegmentImage(VideoImageProcessedNumber);
				//m_ParamHaveBeenChanged =FALSE;

			}
		}

		if (pm_BunchNumDialog != NULL)
		{
			pm_BunchNumDialog->DestroyWindow();
			delete pm_BunchNumDialog;
			pm_BunchNumDialog = NULL;
		}

		if (pm_ColorSectNumDialog != NULL)
		{
			pm_ColorSectNumDialog->DestroyWindow();
			delete pm_ColorSectNumDialog;
			pm_ColorSectNumDialog = NULL;
		}
		/*pDocs1 = NULL;
		pDocs2 = NULL;
		pDocs3 = NULL;
		pDoci1 = NULL;*/
		if ((m_StripColorRepresentation) || (m_StripGrayRepresentation) || (m_ColorBunchRepresentation) ||
			(m_GrayScaleOpened))
		{

			/*POSITION curTemplatePos = this->GetFirstDocTemplatePosition();
			POSITION curDocPos,curDocPos1;
			int i=0;*/

			if (pDocs1 != NULL)
			{
				pDocs1->OnCloseDocument();
				pDocs1 = NULL;
			}

			if (pDocs2 != NULL)
			{
				pDocs2->OnCloseDocument();
				pDocs2 = NULL;
			}
			if (pDocs3 != NULL)
			{
				pDocs3->OnCloseDocument();
				pDocs3 = NULL;
			}
			if (pDoci1 != NULL)
			{
				pDoci1->OnCloseDocument();
				pDoci1 = NULL;
			}

			if (pDocColSec1 != NULL)
			{
				pDocColSec1->OnCloseDocument();
				pDocColSec1 = NULL;
			}
			/*while(curTemplatePos != NULL)
			{

			CDocTemplate* curTemplate =
			this->GetNextDocTemplate(curTemplatePos);

			if(i==0)
			{
			curDocPos1=curTemplate->GetFirstDocPosition();
			}

			if(i==1)
			{
			curDocPos=curTemplate->GetFirstDocPosition();
			if(curDocPos!=NULL)
			{
			CDocument* pDoc = curTemplate->GetNextDoc(curDocPos);
			if(pDoc!=NULL)
			{
			if(NumberOfDoc==3)
			{
			CDocument* pDoc1 = curTemplate->GetNextDoc(curDocPos);
			CDocument* pDoc2 = curTemplate->GetNextDoc(curDocPos);
			if((pDoc2!=NULL)&&(pDoc1!=NULL))
			{
			pDoc2->OnCloseDocument();
			pDoc1->OnCloseDocument();
			pDoc->OnCloseDocument();
			}
			else
			{
			if(pDoc1!=NULL)
			{
			pDoc1->OnCloseDocument();
			pDoc->OnCloseDocument();
			}
			if(pDoc2!=NULL)
			{
			pDoc2->OnCloseDocument();
			pDoc->OnCloseDocument();
			}

			}
			}

			if(NumberOfDoc==2)
			{
			CDocument* pDoc1 = curTemplate->GetNextDoc(curDocPos);

			if(pDoc1!=NULL)
			{
			pDoc1->OnCloseDocument();
			pDoc->OnCloseDocument();
			}
			}
			if(NumberOfDoc==1)
			{
			pDoc->OnCloseDocument();
			}
			}

			if((curDocPos1!=NULL)&&(m_GrayScaleOpened))
			{
			CDocument* pDoc3 = curTemplate->GetNextDoc(curDocPos1);
			CDocument* pDoc4 = curTemplate->GetNextDoc(curDocPos1);
			if(pDoc4!=NULL)
			{
			pDoc4->OnCloseDocument();
			}
			}



			}
			else
			{
			if((curDocPos1!=NULL)&&(m_GrayScaleOpened))
			{
			CDocument* pDoc3 = curTemplate->GetNextDoc(curDocPos1);
			CDocument* pDoc4 = curTemplate->GetNextDoc(curDocPos1);
			if(pDoc4!=NULL)
			{
			pDoc4->OnCloseDocument();
			}
			}
			}
			NumberStripClicked = 0;
			NumberOfDoc=0;
			goto L;
			}
			i++;

			}*/
		}
		//L:
		NumberStripClicked = 0;
		NumberOfDoc = 0;
		m_ImageSegmented = TRUE;

	}

}

void CColorVisionApp::OnChangeParam()
{
	// TODO: Add your command handler code here
	int NumStr;
	BOOL HorV;
	CChParam ParamDialog;

	NumStr = NumberOfStrips;
	HorV = HorizontalVertical;
	ParamDialog.m_HorVert = HorizontalVertical;
	ParamDialog.m_NumStrips = NumberOfStrips;
	ParamDialog.NetworkDirect = m_NetworkDirectX;
	ParamDialog.m_NumFrames = VideoInputLimit;
	ParamDialog.m_CameraNum = CameraNumber;
	ParamDialog.m_GGBorGGR = PermuteRatios;

	if (ParamDialog.DoModal() == IDOK)
	{
		HorizontalVertical = ParamDialog.m_HorVert;
		m_NetworkDirectX = ParamDialog.NetworkDirect;
		NumberOfStrips = ParamDialog.m_NumStrips;
		VideoInputLimit = ParamDialog.m_NumFrames;
		CameraNumber = ParamDialog.m_CameraNum;
		PermuteRatios = ParamDialog.m_GGBorGGR;
		if ((NumStr != NumberOfStrips) || (HorV != HorizontalVertical))//fool proof
		{
			m_ParamHaveBeenChanged = TRUE;
		}
	}

}



void CColorVisionApp::OnVizStrips()
{
	// TODO: Add your command handler code here
	if ((m_ImageIsLoaded) && (m_ImageSegmented))
	{
		POSITION curTemplatePos = GetFirstDocTemplatePosition();

		int i = 0;


		while (curTemplatePos != NULL)
		{

			CDocTemplate* curTemplate =
				GetNextDocTemplate(curTemplatePos);
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName);
			/*if(str == _T("Strip"))
			{
			curTemplate->OpenDocumentFile(NULL);
			return;
			}*/
			if (i == 1)
			{
				StripRepresentationType = 1;
				curTemplate->OpenDocumentFile(NULL);
				m_StripColorRepresentation = TRUE;
				NumberOfDoc++;
				return;
			}
			i++;

		}
		AfxMessageBox(IDS_COLORSTRIP);
	}

}

void CColorVisionApp::OnUpdateVizStrips(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable((m_ImageSegmented) && (!m_StripColorRepresentation));
}

void CColorVisionApp::OnGrayStrips()
{
	// TODO: Add your command handler code here
	if ((m_ImageIsLoaded) && (m_ImageSegmented))
	{
		POSITION curTemplatePos = GetFirstDocTemplatePosition();

		int i = 0;


		while (curTemplatePos != NULL)
		{

			CDocTemplate* curTemplate =
				GetNextDocTemplate(curTemplatePos);
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName);
			/*if(str == _T("Strip"))
			{
			curTemplate->OpenDocumentFile(NULL);
			return;
			}*/
			if (i == 1)
			{
				StripRepresentationType = 2;
				curTemplate->OpenDocumentFile(NULL);
				m_StripGrayRepresentation = TRUE;
				NumberOfDoc++;
				return;
			}
			i++;

		}
		AfxMessageBox(IDS_COLORSTRIP);
	}

}

void CColorVisionApp::OnUpdateGrayStrips(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_ImageSegmented) && (!m_StripGrayRepresentation));

}

void CColorVisionApp::OnBunchDemo()
{
	// TODO: Add your command handler code here
	if ((m_ImageIsLoaded) && (m_ImageSegmented))
	{

		/*CWnd* pMainWnd;
		pMainWnd=m_pMainWnd;
		pmListBunch= new CListBox;
		pmListBunch->Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD|WS_HSCROLL|LBS_NOTIFY|WS_CAPTION,
		CRect(310,310,500,500), pMainWnd, 1);
		pmListBunch->InitStorage(32,10);
		CString str;
		for (int j=0;j < 32;j++)
		{
		str.Format(_T("bunch %d"), j);
		pmListBunch->AddString( str );
		}*/
		pm_BunchNumDialog = new BunchNumDialog();
		if (pm_BunchNumDialog != NULL)
		{

			BOOL ret = pm_BunchNumDialog->Create(IDD_DIALOG2, m_pMainWnd);
			if (!ret)   //Create failed.
			{
				AfxMessageBox(strFailCrDialog);
			}
			pm_BunchNumDialog->ShowWindow(SW_SHOW);


		}
		else
		{
			AfxMessageBox(strFailCrDialog);
		}

		POSITION curTemplatePos = GetFirstDocTemplatePosition();

		int i = 0;

		while (curTemplatePos != NULL)
		{

			CDocTemplate* curTemplate =
				GetNextDocTemplate(curTemplatePos);
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName);
			/*if(str == _T("Strip"))
			{
			curTemplate->OpenDocumentFile(NULL);
			return;
			}*/
			if (i == 0)
			{
				ImageRepresentationType = 1;
				curTemplate->OpenDocumentFile(NULL);
				m_GrayScaleOpened = TRUE;
			}
			if (i == 1)
			{
				StripRepresentationType = 3;
				curTemplate->OpenDocumentFile(NULL);
				m_ColorBunchRepresentation = TRUE;
				NumberOfDoc++;
				return;
			}
			i++;

		}

	}

}

void CColorVisionApp::OnUpdateBunchDemo(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_ImageSegmented) && (!m_ColorBunchRepresentation) &&
		(m_StripColorRepresentation));

}

void CColorVisionApp::OnColorSections()
{
	// TODO: Add your command handler code here
	if ((m_ImageIsLoaded) && (m_ImageSegmented))
	{


		pm_ColorSectNumDialog = new ColorSectionDialog();
		if (pm_ColorSectNumDialog != NULL)
		{

			BOOL ret = pm_ColorSectNumDialog->Create(IDD_DIALOG3, m_pMainWnd);
			if (!ret)   //Create failed.
			{
				AfxMessageBox(strFailCrDialog);
			}
			pm_ColorSectNumDialog->ShowWindow(SW_SHOW);


		}
		else
		{
			AfxMessageBox(strErCrDiOb);
		}

		POSITION curTemplatePos = GetFirstDocTemplatePosition();

		int i = 0;

		while (curTemplatePos != NULL)
		{

			CDocTemplate* curTemplate =
				GetNextDocTemplate(curTemplatePos);
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName);
 

			if (i == 2)
			{
				GlobalObjectsRepresentationType = 1;
				curTemplate->OpenDocumentFile(NULL);
				m_ColorSectionsRepresentation = TRUE;
				NumberOfDoc++;
				return;
			}
			i++;

		}

	}


}

void CColorVisionApp::OnUpdateColorSections(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable((m_ImageSegmented) && (!m_ColorSectionsRepresentation) &&
		(m_StripColorRepresentation));

}

 

 
void CColorVisionApp::OnSegmentInitialize()
{
	/*int DimX;        // width  of the image in pixels
	int DimY;*/

	if (m_VideoCameraIsLoaded)
	{
		if (ColorImageProcess == NULL)
		{
			ColorImageProcess = new CImageProcess(VideoInputLimit);
			ColorImageProcess->InitialConstructions();
			//ColorImageProcess->SegmentImage();
			m_ParamHaveBeenChanged = FALSE;
		}
		else
		{
			delete ColorImageProcess;
			ColorImageProcess = NULL;
			if (pDoci0 != NULL)
			{
				pDoci0->OnCloseDocument();
				pDoci0 = NULL;
			}
			ColorImageProcess = new CImageProcess(VideoInputLimit);

			ColorImageProcess->InitialConstructions();

			m_ParamHaveBeenChanged = FALSE;

		}
	}
}
void CColorVisionApp::OnFileChangeparam()
{
	// TODO: Add your command handler code here
	CChParam ParamDialog;
	int Numstr;
	BOOL HorV;

	ParamDialog.m_HorVert = HorizontalVertical;
	ParamDialog.m_NumStrips = NumberOfStrips;
	ParamDialog.m_NumFrames = VideoInputLimit;
	ParamDialog.NetworkDirect = m_NetworkDirectX;
	Numstr = NumberOfStrips;
	HorV = ParamDialog.m_HorVert;
	//ParamDialog.m_CameraNum=CameraNumber;
	if (ParamDialog.DoModal() == IDOK)
	{
		HorizontalVertical = ParamDialog.m_HorVert;
		NumberOfStrips = ParamDialog.m_NumStrips;
		m_NetworkDirectX = ParamDialog.NetworkDirect;
		VideoInputLimit = ParamDialog.m_NumFrames;
		CameraNumber = ParamDialog.m_CameraNum;
		if ((HorV != HorizontalVertical) || (Numstr != NumberOfStrips))//fool proof
		{
			m_ParamHaveBeenChanged = TRUE;
		}
	}
}

void CColorVisionApp::OnUpdateFileChangeparam(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_VideoCameraIsLoaded);
} 

 


void CColorVisionApp::OnAppExit()
{
	// TODO: Add your command handler code here
	if (pDoci2 != NULL)
	{
		pDoci2->OnCloseDocument();
		pDoci2 = NULL;
	}
	if (pm_inputbuffer != NULL)
	{
		delete pm_inputbuffer;
	}
	if (pData != NULL)
	{
		delete pData;
		pData = NULL;
	}
	if (ColorImageProcess != NULL)
	{
		ColorImageProcess->DeleteTemporal();

		delete ColorImageProcess;
		ColorImageProcess = NULL;
	}

	if (pBuffer != NULL)
	{
		delete pBuffer;
		pBuffer = NULL;
	} 



	if (pDoci0 != NULL)
	{
		pDoci0->OnCloseDocument();
		pDoci0 = NULL;
	}
	CWinApp::OnAppExit();
}
 
 

void CColorVisionApp::DirectArrayDraw()
{
	POINT OrPoint;
	POINT EndPoint;
	POINT NewOrPoint;
	POINT NewEndPoint;
	POINT CnPoint;
	POINT New1CnPoint;
	POINT New2CnPoint;
	int NumStrips;
	int HorizVert;
	int StrWidthPrev;
	int StripWidth1;
	int StripWidthPrev1;
	int WMHeight;
	int WMWidth;
	int SideHue;
	int NumSideHues;
	int SideTriangle;
	int ratio_im;
	int Beg_bunch;
	int End_bunch;
	int Scoor1;
	int Scoor2;
	int Scoor3;
	int NScoor1;
	int NScoor2;
	int NScoor3;
	int BScoor1;
	int BScoor2;
	int BScoor3;
	int bunch_average_hue;
	int bunch_average_sat;
	int bunch_average_gray;
	int old_col_number;
	int old_col_num; 
	int bunch_number1;
	int bunch_occurrence;
	int left_contrast;
	int right_contrast;
	int label_sign;
	int trajectory_length;
	int motion_shift;
	int number_of_frame;
	int length_of_video_analysis;
	int reduced_current_frame_number;
	int right_trajectory_length;
	int right_motion_shift; 
	CStrip* CurrentStrip; 

	if ((m_VideoCameraIsLoaded) && (m_Video_ImageSegmented) &&
		(pBuffer != NULL))
	{
		number_of_frame = VideoImageProcessedNumber;
		length_of_video_analysis = ColorImageProcess->LengthofMotionAnalysisInterval;
		if (length_of_video_analysis)
		{
			reduced_current_frame_number = (number_of_frame) % length_of_video_analysis;
		}
		NumStrips = ColorImageProcess->NumStrips;
		HorizVert = ColorImageProcess->HorizontalVertical;
		StrWidthPrev = ColorImageProcess->CurStrip[0].StripWidthPrev;
		CurrentStrip = ColorImageProcess->CurStrip;
		WMHeight = (int)m_BitmapApp.bmHeight;
		WMWidth = (int)m_BitmapApp.bmWidth;
		 
		ratio_im = 1;
		for (int coun_strip1 = 0; coun_strip1<NumStrips; coun_strip1++) //draw bunches
		{
			old_col_number = ColorImageProcess->ColorInt[coun_strip1].NumberOfColoredIntervals;
			bunch_number1 = ColorImageProcess->ColorInt[coun_strip1].RefinedNumberOfBunches;
			StripWidth1 = CurrentStrip[coun_strip1].StripWidth;
			StripWidthPrev1 = CurrentStrip[coun_strip1].StripWidthPrev;
			if (ratio_im != 1)
			{
				StripWidth1 = StripWidth1 / ratio_im;
				StripWidthPrev1 = StripWidthPrev1 / ratio_im;
			}
			for (int coun_bunch2 = 0; coun_bunch2<bunch_number1; coun_bunch2++) //draw color bunches
			{
				old_col_num = ColorImageProcess->ColorInt[coun_strip1].old_bunch_number[coun_bunch2];
				if (old_col_num<old_col_number)
				{
					bunch_average_hue =
						ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->AverageHue[old_col_num];
					bunch_average_sat =
						ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->AverageSat[old_col_num];
					bunch_average_gray =
						ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->AverageGray[old_col_num];
					Beg_bunch =
						ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->BegInterv[old_col_num];
					End_bunch =
						ColorImageProcess->ColorInt[coun_strip1].ColoredIntervalsStructure->EndInterv[old_col_num];
					if (ratio_im != 1)
					{
						Beg_bunch = Beg_bunch / ratio_im;
						End_bunch = End_bunch / ratio_im;
					}
					bunch_occurrence = ColorImageProcess->ColorInt[coun_strip1].visible_bunches[old_col_num];
					left_contrast = ColorImageProcess->ColorInt[coun_strip1].left_continuation[old_col_num];
					right_contrast = ColorImageProcess->ColorInt[coun_strip1].right_continuation[old_col_num];
					label_sign = ColorImageProcess->ColorInt[coun_strip1].label_segments[old_col_num];
					if (VideoImageProcessedNumber >= 1)
					{
						trajectory_length =
							ColorImageProcess->IntegratedColorBunchesCharacteristics
							[coun_strip1 + reduced_current_frame_number*NumStrips].length_of_trajectory[old_col_num];
						motion_shift =
							ColorImageProcess->IntegratedColorBunchesCharacteristics
							[coun_strip1 + reduced_current_frame_number*NumStrips].shift_of_the_position[old_col_num];
						right_trajectory_length =
							ColorImageProcess->IntegratedColorBunchesCharacteristics
							[coun_strip1 + reduced_current_frame_number*NumStrips].right_length_of_trajectory[old_col_num];
						right_motion_shift =
							ColorImageProcess->IntegratedColorBunchesCharacteristics
							[coun_strip1 + reduced_current_frame_number*NumStrips].right_shift_of_the_position[old_col_num];
					}
					NumSideHues = (NUM_HUES / 3);
					if (bunch_average_hue >= NUM_HUES)
					{
						bunch_average_hue -= NUM_HUES;
					}
					SideTriangle = bunch_average_hue / NumSideHues;
					SideHue = bunch_average_hue - NumSideHues*SideTriangle;
					CalculateBrush(SideTriangle, SideHue, bunch_average_sat, bunch_average_gray,
						&Scoor1, &Scoor2, &Scoor3, &NScoor1, &NScoor2, &NScoor3);
					BScoor1 = 10;
					BScoor2 = 10;
					BScoor3 = 10;
					if (HorizVert)
					{
						OrPoint.y = Beg_bunch;
						if (bunch_occurrence>0)
						{
							OrPoint.x = (StripWidthPrev1*coun_strip1 + StripWidth1 / 2) - 1;
						}
						else
						{
							OrPoint.x = (StripWidthPrev1*coun_strip1 + StripWidth1 / 2) + min(3, StripWidth1 / 2);;
						}
						//OrPoint.x= StripWidthPrev1*coun_strip1 + StripWidth1/2;

						EndPoint.x = OrPoint.x;
						OrPoint.x -= 1;
						EndPoint.x -= 1;
						EndPoint.y = End_bunch;
						VerticalLine(OrPoint, EndPoint, NScoor1, NScoor2, NScoor3);
						OrPoint.x += 1;
						EndPoint.x += 1;
						VerticalLine(OrPoint, EndPoint, NScoor1, NScoor2, NScoor3);
						OrPoint.x += 1;
						EndPoint.x += 1;
						VerticalLine(OrPoint, EndPoint, NScoor1, NScoor2, NScoor3);
						if (right_contrast < 0)
						{
							NewOrPoint.x = max((EndPoint.x - 2), 0);
							NewOrPoint.y = EndPoint.y;
							NewEndPoint.x = max((EndPoint.x - 2 - min(5, StripWidthPrev1 / 2)), 0);
							NewEndPoint.y = EndPoint.y;
							HorizontalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							NewOrPoint.y -= 1;
							NewEndPoint.y -= 1;
							HorizontalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							NewOrPoint.y -= 1;
							NewEndPoint.y -= 1;
							HorizontalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
						}
						if (left_contrast < 0)
						{
							NewOrPoint.x = max((OrPoint.x - 2), 0);
							NewOrPoint.y = OrPoint.y;
							NewEndPoint.x = max((OrPoint.x - 2 - min(5, StripWidthPrev1 / 2)), 0);
							NewEndPoint.y = OrPoint.y;
							HorizontalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							NewOrPoint.y += 1;
							NewEndPoint.y += 1;
							HorizontalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							NewOrPoint.y += 1;
							NewEndPoint.y += 1;
							HorizontalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							if (VideoImageProcessedNumber >= 1)
							{//v>=1
								if (trajectory_length >= 2)
								{//tl
									if (!motion_shift)
									{

										NewOrPoint.x = max((OrPoint.x - 2), 0);
										NewOrPoint.y = max(NewOrPoint.y - 3, 0);
										NewEndPoint.y = NewOrPoint.y + 3;
										NewEndPoint.x = NewOrPoint.x;
										VerticalLine(NewOrPoint, NewEndPoint, BScoor1, BScoor2, BScoor3);
										NewOrPoint.x += 1;
										NewEndPoint.x += 1;
										VerticalLine(NewOrPoint, NewEndPoint, BScoor1, BScoor2, BScoor3);
										NewOrPoint.x += 1;
										NewEndPoint.x += 1;
										VerticalLine(NewOrPoint, NewEndPoint, BScoor1, BScoor2, BScoor3);
									}
									else
									{//e1
										if (motion_shift>0)
										{
											NewOrPoint.x = max((OrPoint.x - 2), 0);
											NewEndPoint.x = NewOrPoint.x;
											NewEndPoint.y = NewOrPoint.y + 5;
											VerticalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.x += 1;
											NewEndPoint.x += 1;
											VerticalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.x += 1;
											NewEndPoint.x += 1;
											VerticalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
										}
										else
										{
											NewOrPoint.x = max((OrPoint.x - 2), 0);
											NewEndPoint.x = NewOrPoint.x;
											NewOrPoint.y = max(NewOrPoint.y - 5, 0);
											VerticalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.x += 1;
											NewEndPoint.x += 1;
											VerticalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.x += 1;
											NewEndPoint.x += 1;
											VerticalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
										}

									}//e1
								}//tl
							}//v>=1
						}
						CnPoint.x = OrPoint.x;
						CnPoint.y = OrPoint.y + (EndPoint.y - OrPoint.y) / 2;
						New1CnPoint.y = CnPoint.y;
						New2CnPoint.y = CnPoint.y;
						New1CnPoint.x = CnPoint.x - min(10, StripWidth1 / 2);
						New2CnPoint.x = CnPoint.x + min(10, StripWidth1 / 2);
						if ((label_sign >= 3) && (label_sign <= 10) || ((label_sign >= 13) && (label_sign <= 20)))
						{
							New1CnPoint.y -= 1;
							New2CnPoint.y -= 1;
							HorizontalLine(New1CnPoint, New2CnPoint, NScoor1, NScoor2, NScoor3);
							New1CnPoint.y += 1;
							New2CnPoint.y += 1;
							HorizontalLine(New1CnPoint, New2CnPoint, NScoor1, NScoor2, NScoor3);
							New1CnPoint.y += 1;
							New2CnPoint.y += 1;
							HorizontalLine(New1CnPoint, New2CnPoint, NScoor1, NScoor2, NScoor3);
						}
					}
					else
					{
						OrPoint.x = Beg_bunch;
						//OrPoint.y = WMHeight/ratio_im - (StripWidthPrev1*coun_strip1 + StripWidth1/2);

						if (bunch_occurrence>0)
						{
							OrPoint.y = (StripWidthPrev1*coun_strip1 + StripWidth1 / 2) - 1;
							//OrPoint.y = WMHeight - (StripWidthPrev1*coun_strip1 + StripWidth1/2)-1;
						}
						else
						{
							OrPoint.y = (StripWidthPrev1*coun_strip1 + StripWidth1 / 2) + min(3, StripWidth1 / 2);
							//OrPoint.y = WMHeight - (StripWidthPrev1*coun_strip1 + StripWidth1/2)+3;
						}
						//OrPoint.y = (StripWidthPrev1*coun_strip1 + StripWidth1/2);

						EndPoint.x = End_bunch;
						EndPoint.y = OrPoint.y;
						OrPoint.y -= 1;
						EndPoint.y -= 1;
						HorizontalLine(OrPoint, EndPoint, NScoor1, NScoor2, NScoor3);
						OrPoint.y += 1;
						EndPoint.y += 1;
						HorizontalLine(OrPoint, EndPoint, NScoor1, NScoor2, NScoor3);
						OrPoint.y += 1;
						EndPoint.y += 1;
						HorizontalLine(OrPoint, EndPoint, NScoor1, NScoor2, NScoor3);
						if (right_contrast<0)
						{
							NewOrPoint.x = EndPoint.x;
							NewOrPoint.y = max((EndPoint.y - 2), 0);
							NewEndPoint.x = EndPoint.x;
							NewEndPoint.y = max((EndPoint.y - 2 - min(5, StripWidthPrev1 / 2)), 0);
							VerticalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							NewOrPoint.x -= 1;
							NewEndPoint.x -= 1;
							VerticalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							NewOrPoint.x -= 1;
							NewEndPoint.x -= 1;
							VerticalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							if (VideoImageProcessedNumber >= 1)
							{//v>=1
								if (right_trajectory_length >= 1)
								{//tl
									if (!right_motion_shift)
									{
										NewOrPoint.x = max(NewEndPoint.x - 5, 0);
										NewEndPoint.x = NewOrPoint.x + 7;
										NewOrPoint.y = NewEndPoint.y - 1;
										NewEndPoint.y = NewOrPoint.y;
										/*HorizontalLine(NewOrPoint,NewEndPoint, Scoor1, Scoor2, Scoor3);
										NewOrPoint.y+=1;
										NewEndPoint.y+=1;
										HorizontalLine(NewOrPoint,NewEndPoint, Scoor1, Scoor2, Scoor3);
										NewOrPoint.y+=1;
										NewEndPoint.y+=1;
										HorizontalLine(NewOrPoint,NewEndPoint, Scoor1, Scoor2, Scoor3);*/
									}
									else
									{//e1
										if (right_motion_shift>0)
										{
											NewOrPoint.x = NewEndPoint.x + 1;
											NewEndPoint.x = min(NewOrPoint.x + 5, WMWidth);
											NewOrPoint.y = max(NewEndPoint.y - 2, 0);
											NewEndPoint.y = NewOrPoint.y;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.y += 1;
											NewEndPoint.y += 1;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.y += 1;
											NewEndPoint.y += 1;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
										}
										else
										{
											NewOrPoint.x = max(NewEndPoint.x - 8, 0);
											NewEndPoint.x = min(NewOrPoint.x + 5, NewEndPoint.x - 1);
											NewOrPoint.y = max(NewEndPoint.y - 2, 0);
											NewEndPoint.y = NewOrPoint.y;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.y += 1;
											NewEndPoint.y += 1;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.y += 1;
											NewEndPoint.y += 1;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
										}
									}//e1
								}//tl
							}//v>=1
						}
						if (left_contrast<0)
						{
							NewOrPoint.x = OrPoint.x;
							NewOrPoint.y = max(OrPoint.y - 2, 0);
							NewEndPoint.x = OrPoint.x;
							NewEndPoint.y = max(OrPoint.y - 2 - min(5, StripWidthPrev1 / 2), 0);
							VerticalLine(NewOrPoint, NewEndPoint, NScoor1, NScoor2, NScoor3);
							NewOrPoint.x += 1;
							NewEndPoint.x += 1;
							VerticalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							NewOrPoint.x += 1;
							NewEndPoint.x += 1;
							VerticalLine(NewEndPoint, NewOrPoint, NScoor1, NScoor2, NScoor3);
							if (VideoImageProcessedNumber >= 1)
							{//v>=1
								if (trajectory_length >= 1)
								{//tl
									if (!motion_shift)
									{
										NewOrPoint.x = max(NewEndPoint.x - 5, 0);
										NewEndPoint.x = NewOrPoint.x + 7;
										NewOrPoint.y = NewEndPoint.y - 1;
										NewEndPoint.y = NewOrPoint.y;
										/*HorizontalLine(NewOrPoint,NewEndPoint, Scoor1, Scoor2, Scoor3);
										NewOrPoint.y+=1;
										NewEndPoint.y+=1;
										HorizontalLine(NewOrPoint,NewEndPoint, Scoor1, Scoor2, Scoor3);
										NewOrPoint.y+=1;
										NewEndPoint.y+=1;
										HorizontalLine(NewOrPoint,NewEndPoint, Scoor1, Scoor2, Scoor3);*/
									}
									else
									{//e1
										if (motion_shift>0)
										{
											NewOrPoint.x = NewEndPoint.x + 1;
											NewEndPoint.x = min(NewOrPoint.x + 5, WMWidth);
											NewOrPoint.y = max(NewEndPoint.y - 2, 0);
											NewEndPoint.y = NewOrPoint.y;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.y += 1;
											NewEndPoint.y += 1;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.y += 1;
											NewEndPoint.y += 1;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
										}
										else
										{
											NewOrPoint.x = max(NewEndPoint.x - 8, 0);
											NewEndPoint.x = min(NewOrPoint.x + 5, NewEndPoint.x - 1);
											NewOrPoint.y = max(NewEndPoint.y - 2, 0);
											NewEndPoint.y = NewOrPoint.y;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.y += 1;
											NewEndPoint.y += 1;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
											NewOrPoint.y += 1;
											NewEndPoint.y += 1;
											HorizontalLine(NewOrPoint, NewEndPoint, Scoor1, Scoor2, Scoor3);
										}
									}//e1
								}//tl
							}//v>=1
						}
						CnPoint.y = OrPoint.y;
						CnPoint.x = OrPoint.x + (EndPoint.x - OrPoint.x) / 2;
						New1CnPoint.x = CnPoint.x;
						New2CnPoint.x = CnPoint.x;
						New1CnPoint.y = CnPoint.y - min(10, StripWidth1 / 2);
						New2CnPoint.y = CnPoint.y + min(10, StripWidth1 / 2);
						if ((label_sign >= 3) && (label_sign <= 10) || ((label_sign >= 13) && (label_sign <= 20)))
						{
							New1CnPoint.x -= 1;
							New2CnPoint.x -= 1;
							VerticalLine(New1CnPoint, New2CnPoint, NScoor1, NScoor2, NScoor3);
							New1CnPoint.x += 1;
							New2CnPoint.x += 1;
							VerticalLine(New1CnPoint, New2CnPoint, NScoor1, NScoor2, NScoor3);
							New1CnPoint.x += 1;
							New2CnPoint.x += 1;
							VerticalLine(New1CnPoint, New2CnPoint, NScoor1, NScoor2, NScoor3);
						}
					}
				}
			}
		}
	}
}

void

CColorVisionApp::CalculateBrush(int side_triangle, int side_hue, int BunAverSat, int BunAverGr,
	int* scoor1, int* scoor2, int* scoor3, int* nscoor1, int* nscoor2, int* nscoor3)
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

	if (side_triangle == 0)
	{
		Coor1 = 255 - CoorHuPoints[side_hue];
		Coor2 = CoorHuPoints[side_hue];
		Scoor1 = 84 + (BunAverSat*(Coor1 - 84)) / 15;
		Scoor2 = 84 + (BunAverSat*(Coor2 - 84)) / 15;
		Scoor3 = (84 * (15 - BunAverSat)) / 15;
		Imax = max(Scoor1, max(Scoor2, Scoor3));
		Scoor1 = (Scoor1 * 255) / Imax;
		Scoor2 = (Scoor2 * 255) / Imax;
		Scoor3 = (Scoor3 * 255) / Imax;
		GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
		GrayLev = GrayLev / 4;
		if (GrayLev>BunAverGr)
		{

			NScoor1 = (Scoor1*BunAverGr) / GrayLev;
			NScoor2 = (Scoor2*BunAverGr) / GrayLev;
			NScoor3 = (Scoor3*BunAverGr) / GrayLev;
			NewGrayLev = int(0.3*((float)NScoor1) + 0.59*((float)NScoor2) + 0.11*((float)NScoor3));
			NewGrayLev = NewGrayLev / 4;
		}
		else
		{
			NScoor1 = Scoor1;
			NScoor2 = Scoor2;
			NScoor3 = Scoor3;
		}
	}
	if (side_triangle == 1)
	{
		Coor1 = 255 - CoorHuPoints[side_hue];
		Coor2 = CoorHuPoints[side_hue];
		Scoor1 = (84 * (15 - BunAverSat)) / 15;
		Scoor2 = 84 + (BunAverSat*(Coor1 - 84)) / 15;
		Scoor3 = 84 + (BunAverSat*(Coor2 - 84)) / 15;
		Imax = max(Scoor1, max(Scoor2, Scoor3));
		Scoor1 = (Scoor1 * 255) / Imax;
		Scoor2 = (Scoor2 * 255) / Imax;
		Scoor3 = (Scoor3 * 255) / Imax;

		GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
		GrayLev = GrayLev / 4;
		if (GrayLev>BunAverGr)
		{
			NScoor1 = (Scoor1*BunAverGr) / GrayLev;
			NScoor2 = (Scoor2*BunAverGr) / GrayLev;
			NScoor3 = (Scoor3*BunAverGr) / GrayLev;
			NewGrayLev = int(0.3*((float)NScoor1) + 0.59*((float)NScoor2) + 0.11*((float)NScoor3));
			NewGrayLev = NewGrayLev / 4;
		}
		else
		{
			NScoor1 = Scoor1;
			NScoor2 = Scoor2;
			NScoor3 = Scoor3;
		}

	}
	if (side_triangle == 2)
	{
		Coor1 = CoorHuPoints[side_hue];
		Coor2 = 255 - CoorHuPoints[side_hue];
		Scoor1 = 84 + (BunAverSat*(Coor1 - 84)) / 15;
		Scoor2 = (84 * (15 - BunAverSat)) / 15;
		Scoor3 = 84 + (BunAverSat*(Coor2 - 84)) / 15;
		Imax = max(Scoor1, max(Scoor2, Scoor3));
		Scoor1 = (Scoor1 * 255) / Imax;
		Scoor2 = (Scoor2 * 255) / Imax;
		Scoor3 = (Scoor3 * 255) / Imax;

		GrayLev = int(0.3*((float)Scoor1) + 0.59*((float)Scoor2) + 0.11*((float)Scoor3));
		GrayLev = GrayLev / 4;
		if (GrayLev>BunAverGr)
		{
			NScoor1 = (Scoor1*BunAverGr) / GrayLev;
			NScoor2 = (Scoor2*BunAverGr) / GrayLev;
			NScoor3 = (Scoor3*BunAverGr) / GrayLev;
			NewGrayLev = int(0.3*((float)NScoor1) + 0.59*((float)NScoor2) + 0.11*((float)NScoor3));
			NewGrayLev = NewGrayLev / 4;
		}
		else
		{
			NScoor1 = Scoor1;
			NScoor2 = Scoor2;
			NScoor3 = Scoor3;
		}

	}
	*scoor1 = Scoor1;
	*scoor2 = Scoor2;
	*scoor3 = Scoor3;
	*nscoor1 = NScoor1;
	*nscoor2 = NScoor2;
	*nscoor3 = NScoor3;
}

void

CColorVisionApp::HorizontalLine(POINT OrPoint, POINT EndPoint, int ACoor1, int ACoor2, int ACoor3)
{
	unsigned char *m_ImageBits;
	long int entry_point;
	long int coor2, coor3;
	int loop_limit;
	int WMHeight;
	int WMWidth;
	long int size;

	m_ImageBits = pBuffer;
	WMHeight = (int)m_BitmapApp.bmHeight;
	WMWidth = (int)m_BitmapApp.bmWidthBytes;
	size = ((long)WMHeight)*((long)(WMWidth));
	loop_limit = EndPoint.x - OrPoint.x + 1;
	entry_point = (3 * m_BitmapApp.bmWidth)*(long)OrPoint.y + (long)(3 * OrPoint.x);

	for (int Coun = 0; Coun<loop_limit; Coun++)
	{
		if (entry_point<(size - 1))
		{//cond1
			*(m_ImageBits + entry_point++) = ACoor3;
			coor2 = entry_point++;
			if (coor2<(size - 1))
			{//cond2
				*(m_ImageBits + coor2) = ACoor2;
				coor3 = entry_point++;
				if (coor3<(size - 1))
				{//cond3
					*(m_ImageBits + coor3) = ACoor1;
				}//cond3
			}//cond2
		}//cond1
		 //entry_point++;
	}
}

void CColorVisionApp::VerticalLine(POINT OrPoint, POINT EndPoint, int ACoor1, int ACoor2, int ACoor3)
{
	unsigned char *m_ImageBits;
	long int entry_point;
	long int coor2, coor3;
	int loop_limit;
	int WMHeight;
	int WMWidth;
	long int size;

	m_ImageBits = pBuffer;
	WMHeight = (int)m_BitmapApp.bmHeight;
	WMWidth = (int)m_BitmapApp.bmWidthBytes;
	size = ((long)WMHeight)*((long)(WMWidth));
	loop_limit = EndPoint.y - OrPoint.y + 1;
	entry_point = (3 * m_BitmapApp.bmWidth)*(long)OrPoint.y + (long)(3 * OrPoint.x);

	for (int Coun = 0; Coun<loop_limit; Coun++)
	{//cycle
		if (entry_point<(size - 1))
		{//cond1
			*(m_ImageBits + entry_point) = ACoor3;
			coor2 = entry_point + 1;
			if (coor2<(size - 1))
			{//cond2
				*(m_ImageBits + coor2) = ACoor2;
				coor3 = entry_point + 2;
				if (coor3<(size - 1))
				{//cond3
					*(m_ImageBits + coor3) = ACoor1;
				}//cond3   
			}//cond2
		}//cond1
		entry_point += 3 * m_BitmapApp.bmWidth;
	}//cycle
}
 


void CColorVisionApp::OnUpdateChangeParam(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_VideoCameraIsLoaded);

}
