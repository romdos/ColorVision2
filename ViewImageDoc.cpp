// ViewImageDoc.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
//#include "Dib.h"
#include "ViewImageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

/////////////////////////////////////////////////////////////////////////////
// CViewImageDoc

IMPLEMENT_DYNCREATE(CViewImageDoc, CDocument)

BEGIN_MESSAGE_MAP(CViewImageDoc, CDocument)
	//{{AFX_MSG_MAP(CViewImageDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateFileMruFile1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewImageDoc construction/destruction


CViewImageDoc::CViewImageDoc()
{
	m_DibGrayScaleDoc=NULL;
	m_DibDoc = NULL;
	m_DibTgaDoc = NULL;

	CColorVisionApp *pApp;
	pApp= (CColorVisionApp *)AfxGetApp ();
	ImageRepresentationType=pApp->ImageRepresentationType;
	if(ImageRepresentationType==0)
	{
	
	//m_hBitmap = NULL;
	m_it_is_nt = "it isn't either a BMP, or TGA, or JPG file";
	m_it_is_jpg = "it is a JPG file";
	OnlyTCU = "Only uncompressed true color images are processed";
	}
	
}

BOOL CViewImageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

if(ImageRepresentationType==1)
{
CallCalculateGrayScale();
}


	return TRUE;
}

CViewImageDoc::~CViewImageDoc()
{
	CColorVisionApp *pApp;
pApp= (CColorVisionApp *)AfxGetApp ();

	                     if(ImageRepresentationType==0)
						 {
							 pApp->pDoci0 = NULL;
							 /*if(pApp->ColorImageProcess!=NULL)
							 {
			 pApp->ColorImageProcess->DeleteTemporal();
							 }*/
	if(m_DibDoc!=NULL)
	{
	delete m_DibDoc;
    m_DibDoc=NULL;
	}
	if(m_DibTgaDoc!=NULL)
	{
	delete m_DibTgaDoc;
    m_DibTgaDoc=NULL;
	}

	if(pApp->pm_BunchNumDialog!=NULL)
	{
     pApp->pm_BunchNumDialog->DestroyWindow();
	 delete pApp->pm_BunchNumDialog;
     pApp->pm_BunchNumDialog = NULL;
	}

	if(pApp->pm_ColorSectNumDialog!=NULL)
	{
     pApp->pm_ColorSectNumDialog->DestroyWindow();
	 delete pApp->pm_ColorSectNumDialog;
     pApp->pm_ColorSectNumDialog = NULL;
	}
	// maxser
	
    // maxser end
if((pApp->m_ImageSegmented)&&((pApp->m_StripColorRepresentation)||
   (pApp->m_StripGrayRepresentation)||(pApp->m_ColorBunchRepresentation)
   ||(pApp->m_GrayScaleOpened)||(pApp->m_ColorSectionsRepresentation)))
{

	if(pApp->pDocs1 != NULL)
	{
		pApp->pDocs1->OnCloseDocument();
		pApp->pDocs1 = NULL;
	}
	if(pApp->pDocs2 != NULL)
	{
		pApp->pDocs2->OnCloseDocument();
		pApp->pDocs2 = NULL;
	}
	if(pApp->pDocs3 != NULL)
	{
		pApp->pDocs3->OnCloseDocument();
		pApp->pDocs3 = NULL;
	}
	if(pApp->pDoci1 != NULL)
	{
		pApp->pDoci1->OnCloseDocument();
		pApp->pDoci1 = NULL;
	}
	if(pApp->pDocColSec1 != NULL)
	{
		pApp->pDocColSec1->OnCloseDocument();
		pApp->pDocColSec1 = NULL;
	}
}
    pApp->m_ImageIsLoaded = FALSE;
    pApp->m_ImageSegmented = FALSE;
	pApp->m_GrayScaleOpened=FALSE;
	pApp->m_StripColorRepresentation=FALSE;
	pApp->m_StripGrayRepresentation=FALSE;
	pApp->m_ColorBunchRepresentation=FALSE;
	pApp->m_ColorSectionsRepresentation=FALSE;
    pApp->NumberStripClicked = 0;
    pApp->pm_BitmapApp=NULL;
	pApp->NumberOfDoc=0;
							  }
	                        if(ImageRepresentationType==1)
							  {
								  if(m_DibGrayScaleDoc!=NULL)
								  {
	                               delete m_DibGrayScaleDoc;
                                   m_DibGrayScaleDoc=NULL;
								  }
                               pApp->m_GrayScaleOpened=FALSE;
							   pApp->pDoci1=NULL;
							  }
							
}




// CViewImageDoc serialization

void CViewImageDoc::Serialize(CArchive& ar)
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
// CViewImageDoc commands

BOOL CViewImageDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CFile file;
	CFileException fe;
	CFileStatus status;
	CString m_FullName;
	CString FileExt;
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bminfHeader;
	DWORD dwBitsSize;
	DWORD dwStrcSize;
	DWORD Offset;
	DWORD Bsize;
	DWORD len;
    DWORD len1;
    DWORD len2;
	TARGAHeader tgaHeader;
	

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		ReportSaveLoadException(lpszPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}
	CFile::GetStatus( lpszPathName, status );
    m_FullName=status.m_szFullName;
	FileExt=m_FullName.Right(3);
if((FileExt.Compare("bmp"))&&(FileExt.Compare("BMP"))&&
		(FileExt.Compare("tga"))&&(FileExt.Compare("TGA"))&&
		(FileExt.Compare("jpg"))&&(FileExt.Compare("JPG")))
{
//MessageBox(NULL, "it isn't either a BMP, or TGA, or JPG file", NULL, MB_ICONINFORMATION | MB_OK);
MessageBox(NULL, m_it_is_nt, NULL, MB_ICONINFORMATION | MB_OK);
return FALSE;
}
if((!FileExt.Compare("jpg"))||(!FileExt.Compare("JPG")))
{
MessageBox(NULL, m_it_is_jpg, NULL, MB_ICONINFORMATION | MB_OK);

}
//MessageBox(NULL, m_FullName, NULL, MB_ICONINFORMATION | MB_OK);
	// replace calls to Serialize with ReadDIBFile function
dwBitsSize = file.GetLength();
CColorVisionApp *pApp;
pApp= (CColorVisionApp *)AfxGetApp ();
if((!FileExt.Compare("bmp"))||(!FileExt.Compare("BMP")))
{
	
m_DibDoc = new CDib;

	
	len = file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader));
	if (len != sizeof(bmfHeader))
		return FALSE;

	if (bmfHeader.bfType != DIB_HEADER_MARKER)
		return FALSE;

	Offset=bmfHeader.bfOffBits;
	Bsize=bmfHeader.bfSize;

len1 = file.Read((LPSTR)&bminfHeader, sizeof(bminfHeader));
if ((bminfHeader.biClrUsed)||(bminfHeader.biBitCount != 24)||(bminfHeader.biCompression))
{
MessageBox(NULL, "Only noncompressed true color images are processed", 
		   NULL, MB_ICONINFORMATION | MB_OK);
return FALSE;
}
dwStrcSize=bminfHeader.biSize;


file.Close();
	TRY
	{
		m_DibDoc->LoadImageBMPFile(lpszPathName);
		
	}
	CATCH (CFileException, eLoad)
	{
		file.Abort(); // will not throw an exception
		EndWaitCursor();
		ReportSaveLoadException(lpszPathName, eLoad,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			return FALSE;
	}
	END_CATCH
		(pApp->pm_BitmapApp)=m_DibDoc->GetBitmapFile();
		if(pApp->pm_BitmapApp==NULL)
		{
			return FALSE;
		}
		pApp->m_ImageIsLoaded=TRUE;
		return TRUE;
}
if((!FileExt.Compare("tga"))||(!FileExt.Compare("TGA")))
{
	len2=0;
len = file.Read((LPSTR)&tgaHeader.Offset, sizeof(tgaHeader.Offset));
	if (len != sizeof(tgaHeader.Offset))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.CmapType, sizeof(tgaHeader.CmapType));
	if (len != sizeof(tgaHeader.CmapType))
		return FALSE;
	len2+=len;
	len = file.Read((LPSTR)&tgaHeader.ImageType, sizeof(tgaHeader.ImageType));
	if (len != sizeof(tgaHeader.ImageType))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.CmapStart, sizeof(tgaHeader.CmapStart));
	if (len != sizeof(tgaHeader.CmapStart))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.CmapLength, sizeof(tgaHeader.CmapLength));
	if (len != sizeof(tgaHeader.CmapLength))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.CmapBits, sizeof(tgaHeader.CmapBits));
	if (len != sizeof(tgaHeader.CmapBits))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.Hoffset, sizeof(tgaHeader.Hoffset));
	if (len != sizeof(tgaHeader.Hoffset))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.Voffset, sizeof(tgaHeader.Hoffset));
	if (len != sizeof(tgaHeader.Hoffset))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.Width, sizeof(tgaHeader.Width));
	if (len != sizeof(tgaHeader.Width))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.Height, sizeof(tgaHeader.Height));
	if (len != sizeof(tgaHeader.Height))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.BitsPerPixel, sizeof(tgaHeader.BitsPerPixel));
	if (len != sizeof(tgaHeader.BitsPerPixel))
		return FALSE;
	len2+=len;
len = file.Read((LPSTR)&tgaHeader.Flags, sizeof(tgaHeader.Flags));
	if (len != sizeof(tgaHeader.Flags))
		return FALSE;
    len2+=len;
	if(((tgaHeader.BitsPerPixel!=16)&&(tgaHeader.BitsPerPixel!=24))||
		(tgaHeader.ImageType != 2))
	{
MessageBox(NULL, OnlyTCU, 
		   NULL, MB_ICONINFORMATION | MB_OK);
        return FALSE;
	}
	if(tgaHeader.Flags == 0x20)
	{
     pApp->m_ImageIsInverted=TRUE;
    }
	    m_DibTgaDoc= new CDibTga;
		dwBitsSize-=len2;
		m_DibTgaDoc->LoadImageTGAFile(file,&tgaHeader,dwBitsSize);
	    (pApp->pm_BitmapApp)=m_DibTgaDoc->GetBitmapFile();
		if(pApp->pm_BitmapApp==NULL)
		{
			return FALSE;
		}
		pApp->m_ImageIsLoaded=TRUE;
		return TRUE;
	
}
return TRUE;
}

void CViewImageDoc::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	CColorVisionApp *pApp = (CColorVisionApp *)AfxGetApp ();
	/*if(pApp->m_ImageIsLoaded)
	{
    AfxMessageBox ("A file has been already openned");
	}*/
	pCmdUI->Enable(!pApp->m_ImageIsLoaded);
	
}

void CViewImageDoc::OnUpdateFileMruFile1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CColorVisionApp *pApp = (CColorVisionApp *)AfxGetApp ();
	/*if(pApp->m_ImageIsLoaded)
	{
    AfxMessageBox ("A file has been already openned");
	}*/
	pCmdUI->Enable(!pApp->m_ImageIsLoaded);
	
}

/////////////////////////////////////////////////////////////////////////////
void

CViewImageDoc::CallCalculateGrayScale()
{
	CColorVisionApp *pApp = (CColorVisionApp *)AfxGetApp ();
	ImageRepresentationType=pApp->ImageRepresentationType;
	if(ImageRepresentationType==1)
	{
m_DibGrayScaleDoc = new CDibGrayScale;
m_DibGrayScaleDoc->CalculateGrayscale();
	}
	/*else
	{
		if(ImageRepresentationType==3)
		{
		if(pApp->VideoImageProcessedNumber==0)
		{
			m_DibGrayScaleDoc = new CDibGrayScale;
		}
		m_DibGrayScaleDoc->CalculateGrayscaleVideo();
		}
	}*/
	
}

/////////////////////////////////////////////////////////////////////////////
// CViewImageDoc diagnostics

#ifdef _DEBUG
void CViewImageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CViewImageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

/*void CViewImageDoc::OnVizStrips() 
{
	// TODO: Add your command handler code here
	CDocument::OnNewDocument();
		

	
}*/
