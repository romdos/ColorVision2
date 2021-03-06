//
//
//
//
//
//



#include "stdafx.h" 



#include "ColorVision.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#include "ViewImageDoc.h"
#include "ViewImageVw.h"

#include "VizStripDoc.h"
#include "VizStripFrame.h"
#include "VizStripView.h"


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
	NumberStripClicked = 0;

	m_ImageIsLoaded		  = FALSE;
	m_VideoCameraIsLoaded = FALSE;
	m_GrayScaleOpened	  = FALSE;
	m_ImageSegmented	  = FALSE;
	m_Video_ImageSegmented = FALSE;
	m_ImageIsInverted	   = TRUE;
	m_ParamHaveBeenChanged = FALSE;  

	m_FindSky   = TRUE;
	m_FindGreen = TRUE;
	
	ColorNumber1 = 4;
	ColorNumber2 = 1;
	ColorNumber3 = 0;
	
	m_StripColorRepresentation = FALSE;
	m_StripGrayRepresentation = FALSE;
	m_ColorBunchRepresentation = FALSE;
	m_ColorSectionsRepresentation = FALSE; 
	m_VideoCameraInput = FALSE;
	m_VideoCameraSequenceProcessing = FALSE;
	m_NetworkDirectX = FALSE; 
	
	pm_BitmapApp = NULL;
	pm_GrayBitmap = NULL;
	
	pBuffer = NULL;
	buffer = NULL;
	pData = NULL; 
	
	NumberOfStrips = 48;
	CameraNumber = 0;
	NumberStripClicked = 0; 
	VideoImageProcessedNumber = 0;
	VideoInputLimit = 1; 
	HorizontalVertical = FALSE;
	PermuteRatios = TRUE; 
	ColorImageProcess = NULL;
	StripRepresentationType = 0;
	ImageRepresentationType = 0;
	VideoImageRepresentationType = 0;
	GlobalObjectsRepresentationType = 0;  
	
	pDocColorImage = NULL;
	pDoci2 = NULL;
	pDoci3 = NULL;
	pDocs1 = NULL;
	pDocs2 = NULL;
	pDocs3 = NULL;
	pDocGrayscaleImage = NULL; 
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

	CMultiDocTemplate* pDocTemplate = new CMultiDocTemplate(
		IDR_COLORVTYPE,
		RUNTIME_CLASS(CViewImageDoc),
		RUNTIME_CLASS(CViewImageFrame), // custom MDI child frame
		RUNTIME_CLASS(CViewImageVw));
	AddDocTemplate(pDocTemplate);

	CMultiDocTemplate* pVizStripTemplate = new CMultiDocTemplate(
		IDR_COLORVTYPE,
		RUNTIME_CLASS(CVizStripDoc),
		RUNTIME_CLASS(CVizStripFrame), // custom MDI child frame
		RUNTIME_CLASS(CVizStripView));
	AddDocTemplate(pVizStripTemplate);


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
// CColorVisionApp message handlers


void CColorVisionApp::OnSegment()
{ 
	if (m_ImageIsLoaded)
	{
		int DimX = pm_BitmapApp->bmWidth;
		int DimY = pm_BitmapApp->bmHeight; 
		
		if ((NULL != ColorImageProcess) && (DimX == ColorImageProcess->DimX) && (DimY == ColorImageProcess->DimY) 
			&& (HorizontalVertical == ColorImageProcess->HorizontalVertical) &&
			(NumberOfStrips == ColorImageProcess->NumStrips))
		{
			ColorImageProcess->execution_time = 0;
			ColorImageProcess->DeleteTemporal();
			ColorImageProcess->SegmentImage(VideoImageProcessedNumber);
		}
		else
		{
			if (ColorImageProcess != NULL)
			{
				ColorImageProcess->DeleteTemporal();
				delete ColorImageProcess;
			}
			else
			{
				m_ParamHaveBeenChanged = FALSE;
			}

			ColorImageProcess = new CImageProcess(VideoInputLimit);
			ColorImageProcess->InitialConstructions();

			// Segmentation procedures are here
			ColorImageProcess->SegmentImage(VideoImageProcessedNumber);
		} 

		if (m_pColorSectDialog != NULL)
		{
			m_pColorSectDialog->DestroyWindow();
			delete m_pColorSectDialog;
			m_pColorSectDialog = NULL;
		}

		if (m_StripColorRepresentation || m_StripGrayRepresentation || m_ColorBunchRepresentation || m_GrayScaleOpened)
		{
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
			if (pDocGrayscaleImage != NULL)
			{
				pDocGrayscaleImage->OnCloseDocument();
				pDocGrayscaleImage = NULL;
			}

			if (pDocColSec1 != NULL)
			{
				pDocColSec1->OnCloseDocument();
				pDocColSec1 = NULL;
			}
		}

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
	if (m_ImageIsLoaded && m_ImageSegmented)
	{
		POSITION curTemplatePos = GetFirstDocTemplatePosition();

		int i = 0; 

		while (curTemplatePos != NULL)
		{ 
			CDocTemplate* curTemplate = GetNextDocTemplate(curTemplatePos);
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName); 
			if (i == 1)
			{
				StripRepresentationType = 1;
				curTemplate->OpenDocumentFile(NULL);
				m_StripColorRepresentation = TRUE; 
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
	if (m_ImageIsLoaded && m_ImageSegmented)
	{
		POSITION curTemplatePos = GetFirstDocTemplatePosition();

		int i = 0;

		while (curTemplatePos != NULL)
		{
			CDocTemplate* curTemplate = GetNextDocTemplate(curTemplatePos);
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName);
			if (i == 1)
			{
				StripRepresentationType = 2;
				curTemplate->OpenDocumentFile(NULL);
				m_StripGrayRepresentation = TRUE; 
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
	if (m_ImageIsLoaded && m_ImageSegmented)
	{
		// todo: try to not use member pointer of dialog, make local right here
		m_pBunchCountDialog = new BunchCountDlg;
		
		if (m_pBunchCountDialog != NULL)
		{ 
			if (!m_pBunchCountDialog->Create(IDD_DIALOG_BUNCH_SELECT, m_pMainWnd))
			{
				AfxMessageBox(strFailCrDialog);
			}
			m_pBunchCountDialog->ShowWindow(SW_SHOW);
		}
		else
		{
			AfxMessageBox(strFailCrDialog);
		}

		POSITION curTemplatePos = GetFirstDocTemplatePosition();
		  
		if (curTemplatePos != NULL)
		{ 
			CDocTemplate* curTemplate = GetNextDocTemplate(curTemplatePos);
			 
			ImageRepresentationType = GRAYSCALE;
			
			curTemplate->OpenDocumentFile(NULL);
			
			m_GrayScaleOpened = TRUE;
		 
			curTemplate = GetNextDocTemplate(curTemplatePos);
			
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName);

			// TODO: delete magic value
			StripRepresentationType = 3;
			
			curTemplate->OpenDocumentFile(NULL);
			
			m_ColorBunchRepresentation = TRUE; 
		}
	}
}



void CColorVisionApp::OnUpdateBunchDemo(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ImageSegmented && (!m_ColorBunchRepresentation) && m_StripColorRepresentation);
}



void CColorVisionApp::OnColorSections()
{
	// TODO: Add your command handler code here
	if (m_ImageIsLoaded && m_ImageSegmented)
	{
		m_pColorSectDialog = new ColorSectionDialog;
		if (m_pColorSectDialog != NULL)
		{ 
			if (!m_pColorSectDialog->Create(IDD_DIALOG2, m_pMainWnd))   //Create failed.
			{
				AfxMessageBox(strFailCrDialog);
			}
			m_pColorSectDialog->ShowWindow(SW_SHOW);
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
				return;
			}
			i++;

		}
		m_ColorSectionsRepresentation = TRUE;
	}
}



void CColorVisionApp::OnUpdateColorSections(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(m_ImageSegmented && (!m_ColorSectionsRepresentation) &&
		m_StripColorRepresentation);

}

 

void CColorVisionApp::OnSegmentInitialize()
{
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
			if (pDocColorImage != NULL)
			{
				pDocColorImage->OnCloseDocument();
				pDocColorImage = NULL;
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

	ParamDialog.m_HorVert = HorizontalVertical;
	ParamDialog.m_NumStrips = NumberOfStrips;
	ParamDialog.m_NumFrames = VideoInputLimit;
	ParamDialog.NetworkDirect = m_NetworkDirectX;
	
	int Numstr = NumberOfStrips;
	BOOL HorV = ParamDialog.m_HorVert; 

	if (ParamDialog.DoModal() == IDOK)
	{
		HorizontalVertical = ParamDialog.m_HorVert;
		NumberOfStrips     = ParamDialog.m_NumStrips;
		m_NetworkDirectX   = ParamDialog.NetworkDirect;
		VideoInputLimit    = ParamDialog.m_NumFrames;
		CameraNumber       = ParamDialog.m_CameraNum;

		if ((HorV != HorizontalVertical) || (Numstr != NumberOfStrips))   //fool proof
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
	if (pData != NULL)
	{
		delete pData;
		pData = NULL;
	}
	
	if (nullptr != m_pBunchCountDialog)
	{
		delete m_pBunchCountDialog;
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
	if (pDocColorImage != NULL)
	{
		pDocColorImage->OnCloseDocument();
		pDocColorImage = NULL;
	}
	CWinApp::OnAppExit();
}
 
 

void CColorVisionApp::OnUpdateChangeParam(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_VideoCameraIsLoaded);

}
