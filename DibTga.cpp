// DibTga.cpp: implementation of the CDibTga class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ColorVision.h"
#include "DibTga.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDibTga::CDibTga()
{
m_ImageBits=NULL;
m_CannotDisp = "Cannot display TARGA file";
//m_hdd = NULL; 
}

CDibTga::~CDibTga()
{
	if(m_ImageBits != NULL)
	{
    delete [] m_ImageBits;
	}
}
//////////////////////////////////////////////////////////////////////
BOOL

CDibTga::LoadImageTGAFile(CFile& file,TARGAHeader* tgaHeader,DWORD BitsSize)
{
	DWORD Image_Size;
	//DWORD len;
	unsigned char* Buf;    // buffer for reading TARGA file
	unsigned short BytesPerLine, ActualBytesPerLine, DibBytesPerLine;
	unsigned short BytesPerPixel;
	signed   short LineAddrIncr;
	unsigned char Red, Green, Blue;
	BYTE BitsPerPixel;
	LPBYTE LineAddr;
	WORD     Pix;
//	DWORD pos;
	int i, j;
	
	
BitsPerPixel = tgaHeader->BitsPerPixel;
BytesPerPixel = BitsPerPixel/8;
BytesPerLine  = BytesPerPixel * tgaHeader->Width;
if(BytesPerLine % 4) BytesPerLine = 4 * (BytesPerLine/4 + 1);
DibBytesPerLine = 3*tgaHeader->Width;  // for 16-bit TARGA files DIB line is
											 // longer than TARGA line
if(DibBytesPerLine % 4) DibBytesPerLine = 4 * (DibBytesPerLine/4 + 1);
file.Seek ((long)(tgaHeader->Offset),CFile::current);

Buf = new unsigned char[BytesPerLine];
if(!Buf) 
       {
	MessageBox(NULL, "Cannot allocate buffer for reading TARGA file", 
		   NULL, MB_ICONINFORMATION | MB_OK);
        return FALSE;
	   }
Image_Size=DibBytesPerLine*tgaHeader->Height;
m_ImageBits = new unsigned char[Image_Size];

if(tgaHeader->Flags == 0x20) { // the upper line of the image goes first
	 LineAddr = m_ImageBits +	(unsigned long)(tgaHeader->Height-1) *
									(unsigned long)DibBytesPerLine;
	 LineAddrIncr = -DibBytesPerLine;
  }
  else { // the bottom line of the image goes first (as in BMP files)
	  LineAddr = m_ImageBits;
	 LineAddrIncr = DibBytesPerLine;
  }
  ActualBytesPerLine = BytesPerPixel * tgaHeader->Width;
  if(ActualBytesPerLine < BytesPerLine) {
	 for(i=ActualBytesPerLine; i<BytesPerLine; i++) Buf[i] = 0;
  }

  if(tgaHeader->BitsPerPixel ==24) {
	 for (i=0; i<tgaHeader->Height; i++) {
		file.Read(Buf, ActualBytesPerLine);
		//pos=file.GetPosition();
		
		for(j=0; j<ActualBytesPerLine; j++)
		{
			LineAddr[j] = Buf[j];
        }
		LineAddr+=LineAddrIncr;
	 }
  }
else if(tgaHeader->BitsPerPixel ==16) {
	 for (i=0; i<tgaHeader->Height; i++, LineAddr+=LineAddrIncr) {
		file.Read(Buf, ActualBytesPerLine);
		for(j=0; j<ActualBytesPerLine; j+=2) {
		  Pix = Buf[j+1];
		  Pix = Pix << 8;
		  Pix = Pix | Buf[j];
		  Red  = Pix & 0x1F;
		  Green= (Pix>>5) & 0x1F;
		  Blue = (Pix>>10)& 0x1F;

		  Red   = Red << 3;
		  Green = Green << 3;
		  Blue  = Blue << 3;

		  LineAddr[j+j/2]   = Red;
		  LineAddr[j+j/2+1] = Green;
		  LineAddr[j+j/2+2] = Blue;
		}
	 }
  }
 delete [] Buf;

	pBitmap.bmType = 0;
	pBitmap.bmWidth = (LONG)tgaHeader->Width;
	pBitmap.bmHeight = (LONG)tgaHeader->Height;
	pBitmap.bmBitsPixel = tgaHeader->BitsPerPixel;
	pBitmap.bmPlanes = 1;
	pBitmap.bmWidthBytes=(LONG)DibBytesPerLine;
	if(m_ImageBits == NULL)
	{
     return FALSE;
	}

    pBitmap.bmBits = (void *)m_ImageBits;
	BmHeader.biSize=40;
	BmHeader.biWidth=tgaHeader->Width;
    BmHeader.biHeight=tgaHeader->Height;
    BmHeader.biPlanes=1;
    BmHeader.biBitCount=24;
    BmHeader.biCompression=BI_RGB;
	BmHeader.biSizeImage=Image_Size;
	BmHeader.biXPelsPerMeter =(LONG)2834;
    BmHeader.biYPelsPerMeter =(LONG)2834;
    BmHeader.biClrUsed = 0;
    BmHeader.biClrImportant = 0;
	
return TRUE;
}
//////////////////////////////////////////////////////////////////////
BITMAP*

CDibTga::GetBitmapFile()
{
    return &pBitmap;
}

BOOL
 
CDibTga::Draw(CDC* pDC)
{

	HDC hDC;
	int bSuccess;

	if(m_ImageBits==NULL)
		return FALSE;
	hDC = pDC->m_hDC;
//m_Bitmap.CreateBitmapIndirect(&pBitmap);
//MemDC.CreateCompatibleDC(NULL);
//MemDC.SelectObject(this);
//Addr=(unsigned char *)pBitmap.bmBits;
//m_Bitmap.GetObject(sizeof(BITMAP),&BM);
//BM.bmBits=pBitmap.bmBits;
	bSuccess = ::SetDIBitsToDevice(hDC,                        // hDC
								   10,                          // DestX
								   20,                          // DestY
								   (int)BmHeader.biWidth,      // nDestWidth
								   (int)BmHeader.biHeight,     // nDestHeight
								   0,                          // SrcX
								   0,                          // SrcY
								   0,                          // nStartScan
								   (WORD)BmHeader.biHeight,    // nNumScans
								   m_ImageBits,                // lpBits
								   (LPBITMAPINFO)&BmHeader,     // lpBitsInfo
								   DIB_RGB_COLORS);            // wUsage
	//if(bSuccess != (int)BmHeader.biHeight)
    if(bSuccess == 0)
	{
MessageBox(NULL,m_CannotDisp, 
		   NULL, MB_ICONINFORMATION | MB_OK);
        return FALSE;
	}
//pDC->BitBlt(0,0,(int)BmHeader.biWidth,(int)BmHeader.biHeight,&MemDC,0,0,SRCCOPY);
/*	if (!m_hdd) 

VERIFY(m_hdd = DrawDibOpen());*/
	
/*CRect rc; 



rc.SetRect(0, 0, (int)BmHeader.biWidth, (int)BmHeader.biHeight);*/ 

/*return DrawDibDraw(m_hdd, (HDC)pDC, 

rc.left, rc.top, rc.Width(), rc.Height(), 

&BmHeader, pBitmap.bmBits,
rc.left, rc.top, rc.Width(), rc.Height(), 0); */
 


	
return TRUE;
}