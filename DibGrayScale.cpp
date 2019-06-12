// DibGrayScale.cpp: implementation of the CDibGrayScale class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ColorVision.h"
//#include "DibGrayScale.h"
#define RED_COEF    0.3  // 0.299
#define GREEN_COEF  0.59  // 0.587
#define BLUE_COEF   0.11  // 0.114

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDibGrayScale::CDibGrayScale()
{
m_ImageBits=NULL;
m_CannotDisp = "Cannot display GrayScale file";

}

CDibGrayScale::~CDibGrayScale()
{
	CColorVisionApp *pApp;
pApp= (CColorVisionApp *)AfxGetApp ();
ImageRepresentationType=pApp->ImageRepresentationType;

if(m_ImageBits != NULL)
	{
    delete [] m_ImageBits;

pApp->pm_GrayBitmap=NULL;
	
}
}

void CDibGrayScale::CalculateGrayscale()
{
	unsigned char gray_intense;
	unsigned char inten_red,inten_green,inten_blue;
	long int entry_point;
	long int shift;
	long int coor1,coor2,coor3;
	int DimX;
	int DimY;
	int dimX;
	int Res_Width;
	int Cor_Width;
BITMAP *pm_Color;
unsigned char *Im;
DWORD Image_Size;
int count_horiz;
int count_vert;

pm_Color=NULL;

CColorVisionApp *pApp;
pApp= (CColorVisionApp *)AfxGetApp ();
ImageRepresentationType=pApp->ImageRepresentationType;

pm_Color=pApp->pm_BitmapApp;

Im=(unsigned char *)pm_Color->bmBits;
dimX=pm_Color->bmWidth;
DimX=pm_Color->bmWidthBytes;
DimY=pm_Color->bmHeight;
Res_Width=(3*dimX)%4;
if(Res_Width)
{
Cor_Width=4-Res_Width;
}
else
{
Cor_Width=0;
}
      if(pm_Color)
	  {//pmc		  
      Image_Size=(DimX)*(DimY);
	  //word_size=(long int)(Image_Size/3);
	  m_ImageBits = new unsigned char[Image_Size];
	  BmHeader.biSize=40;
	BmHeader.biWidth=(LONG)pm_Color->bmWidth;
    BmHeader.biHeight=(LONG)pm_Color->bmHeight;
    BmHeader.biPlanes=1;
    BmHeader.biBitCount=24;
    BmHeader.biCompression=BI_RGB;
	BmHeader.biSizeImage=Image_Size;
	BmHeader.biXPelsPerMeter =(LONG)2834;
    BmHeader.biYPelsPerMeter =(LONG)2834;
    BmHeader.biClrUsed = 0;
    BmHeader.biClrImportant = 0;
	
	entry_point=0;
	for(count_vert=0;count_vert<DimY;count_vert++)
	{//vert cycle
		shift=((long)DimX)*((long)count_vert);
for(count_horiz=0;count_horiz<dimX;count_horiz++)
{//horiz cycle
entry_point=(long)(3*count_horiz)+shift;
coor1=entry_point;
inten_blue=*(Im+entry_point++);
coor2=entry_point;
     inten_green=*(Im+entry_point++);
coor3=entry_point;
     inten_red=*(Im+entry_point);
	 gray_intense=
(unsigned char)(BLUE_COEF*(float)inten_blue+GREEN_COEF*(float)inten_green+RED_COEF*(float)inten_red);
*(m_ImageBits+coor1)=gray_intense;
*(m_ImageBits+coor2)=gray_intense;
*(m_ImageBits+coor3)=gray_intense;
}//horiz cycle

	}//vert cycle
	  }//pmc	  
}

BOOL
 
CDibGrayScale::Draw(CDC* pDC)
{

	HDC hDC;
	int bSuccess;

	if(m_ImageBits==NULL)
		return FALSE;
	hDC = pDC->m_hDC;

	bSuccess = ::SetDIBitsToDevice(hDC,                        // hDC
								   0,                          // DestX
								   0,                          // DestY
								   (int)BmHeader.biWidth,      // nDestWidth
								   (int)BmHeader.biHeight,     // nDestHeight
								   0,                          // SrcX
								   0,                          // SrcY
								   0,                          // nStartScan
								   (WORD)BmHeader.biHeight,    // nNumScans
								   (void *)m_ImageBits,                // lpBits
								   (LPBITMAPINFO)&BmHeader,     // lpBitsInfo
								   DIB_RGB_COLORS);            // wUsage
	/*bSuccess = ::StretchDIBits(hDC,                        // hDC
								   0,                          // DestX
								   0,                          // DestY
								   320,
								   240,
								   0,                          // SrcX
								   0,                           // SrcY
								   (int)BmHeader.biWidth,      // nDestWidth
								   (int)BmHeader.biHeight,     // nDestHeight
								    (void *)m_ImageBits,                // lpBits
								   (LPBITMAPINFO)&BmHeader,     // lpBitsInfo
								   DIB_RGB_COLORS,
								   SRCCOPY);*/
	//if(bSuccess != (int)BmHeader.biHeight)
    if(bSuccess == 0)
	{
MessageBox(NULL,m_CannotDisp, 
		   NULL, MB_ICONINFORMATION | MB_OK);
        return FALSE;
	}
 

return TRUE;
}
void CDibGrayScale::CalculateGrayscaleVideo()
{
	unsigned char gray_intense;
	unsigned char inten_red,inten_green,inten_blue;
	long int entry_point;
	long int word_size;
	long int Coun;
	long int coor1,coor2,coor3;
BITMAP *pm_Color;
unsigned char *Im;
DWORD Image_Size;

pm_Color=NULL;

CColorVisionApp *pApp;
pApp= (CColorVisionApp *)AfxGetApp ();



pm_Color=(pApp->pm_BitmapApp);

Im=(unsigned char *)pm_Color->bmBits;

      if(pm_Color)
	  {
      Image_Size=(pm_Color->bmWidthBytes)*(pm_Color->bmHeight);
	  word_size=(long int)(Image_Size/3);
	  m_ImageBits = pApp->pBuffer;
BmHeader=pApp->info;
	/*  BmHeader.biSize=40;
	BmHeader.biWidth=(LONG)pm_Color->bmWidth;
    BmHeader.biHeight=(LONG)pm_Color->bmHeight;
    BmHeader.biPlanes=1;
    BmHeader.biBitCount=24;
    BmHeader.biCompression=BI_RGB;
	BmHeader.biSizeImage=Image_Size;
	BmHeader.biXPelsPerMeter =(LONG)2834;
    BmHeader.biYPelsPerMeter =(LONG)2834;
    BmHeader.biClrUsed = 0;
    BmHeader.biClrImportant = 0;*/
	 
	       for(Coun=0;Coun<word_size;Coun++)
		   {
entry_point=3*Coun;
coor1=entry_point;
inten_blue=*(Im+entry_point++);
coor2=entry_point;
     inten_green=*(Im+entry_point++);
coor3=entry_point;
     inten_red=*(Im+entry_point);
	 gray_intense=
(unsigned char)(BLUE_COEF*(float)inten_blue+GREEN_COEF*(float)inten_green+RED_COEF*(float)inten_red);
*(m_ImageBits+coor1)=gray_intense;
*(m_ImageBits+coor2)=gray_intense;
*(m_ImageBits+coor3)=gray_intense;
		   }
	  }
}