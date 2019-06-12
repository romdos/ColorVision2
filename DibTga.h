// DibTga.h: interface for the CDibTga class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBTGA_H__95987CFB_7F1C_48F9_B71C_734B7493A6A2__INCLUDED_)
#define AFX_DIBTGA_H__95987CFB_7F1C_48F9_B71C_734B7493A6A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#endif // !defined(AFX_DIBTGA_H__95987CFB_7F1C_48F9_B71C_734B7493A6A2__INCLUDED_)
//#include "Vfw.h"
//--------------------------------------------------------------------
struct TARGAHeader {
  BYTE            Offset;
  BYTE            CmapType;   // Palette type. =0 for True color images (16- and 24-bits)
  BYTE            ImageType;  // =2 for uncompressed files
  WORD            CmapStart;  // define palette
  WORD            CmapLength; //                for paletted
  BYTE            CmapBits;   //                             images
  WORD            Hoffset;
  WORD            Voffset;
  WORD            Width;
  WORD            Height;
  BYTE            BitsPerPixel;
  BYTE            Flags;      // = 0x20 if the top line of the image goes first
										// = 0 if the bottom line goes first as in BMP files
};

//--------------------------------------------------------------------

class CDibTga : public CObject  
{
private:
BITMAP pBitmap;
unsigned char *m_ImageBits;

public:
	CDibTga();
	virtual ~CDibTga();
    BOOL LoadImageTGAFile(CFile& file,TARGAHeader* tgaHeader,DWORD BitsSize);
	BITMAP *GetBitmapFile();
	//HDRAWDIB m_hdd;
	BITMAPINFOHEADER BmHeader;
	CString m_CannotDisp;

   BOOL Draw(CDC* pDC);
};
