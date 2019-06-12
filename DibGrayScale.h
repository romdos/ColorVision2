// DibGrayScale.h: interface for the CDibGrayScale class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBGRAYSCALE_H__6012F122_F751_4A64_ACE6_64BD60774180__INCLUDED_)
#define AFX_DIBGRAYSCALE_H__6012F122_F751_4A64_ACE6_64BD60774180__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDibGrayScale  : public CObject 
{
public:
	CDibGrayScale();
	virtual ~CDibGrayScale();
	BOOL Draw(CDC* pDC);
	void CalculateGrayscale();
	void CalculateGrayscaleVideo();

public:
	BITMAPINFOHEADER BmHeader;
     CString m_CannotDisp;
private:
	BITMAP pBitmap;
public:
	unsigned char *m_ImageBits;
	int ImageRepresentationType;

};

#endif // !defined(AFX_DIBGRAYSCALE_H__6012F122_F751_4A64_ACE6_64BD60774180__INCLUDED_)
