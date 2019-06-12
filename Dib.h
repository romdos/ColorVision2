// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__C4B559F3_59DF_4184_9F3A_479582DA2A88__INCLUDED_)
#define AFX_DIB_H__C4B559F3_59DF_4184_9F3A_479582DA2A88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#endif // !defined(AFX_DIB_H__C4B559F3_59DF_4184_9F3A_479582DA2A88__INCLUDED_)



//---------------------------------------------------------

class CDib : public CBitmap 
{  

public:
	CDib();
	virtual ~CDib();
private:
DIBSECTION *ds;
//HBITMAP *phBitmap;
BITMAP pBitmap;

public:
	
	BOOL LoadImageBMPFile(LPCTSTR lpszPathName); 

    BOOL Draw(CDC* pDC);
	BITMAP *GetBitmapFile();
    void DeleteObject();

};

