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
	int DimX;        // width  of the image in pixels
	int DimY;

	// TODO: Add your command handler code here
	if (m_ImageIsLoaded)
	{

		DimX = pm_BitmapApp->bmWidth;
		DimY = pm_BitmapApp->bmHeight;



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
			// Algorithm is here
			ColorImageProcess->SegmentImage(VideoImageProcessedNumber);
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
		}

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
	if (m_ImageIsLoaded && m_ImageSegmented)
	{
		POSITION curTemplatePos = GetFirstDocTemplatePosition();

		int i = 0;

		while (curTemplatePos != NULL)
		{
			CDocTemplate* curTemplate =
				GetNextDocTemplate(curTemplatePos);
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName);
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
	if (m_ImageIsLoaded && m_ImageSegmented)
	{
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
	if (m_ImageIsLoaded && m_ImageSegmented)
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

			CDocTemplate* curTemplate = GetNextDocTemplate(curTemplatePos);
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
 
 

void CColorVisionApp::OnUpdateChangeParam(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_VideoCameraIsLoaded);

}
