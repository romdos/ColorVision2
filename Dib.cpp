// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ColorVision.h"
//#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib()
{
ds = NULL;
}


CDib::~CDib() 

{ 

DeleteObject(); 

} 


//////////////////////////////////////////////////////////////////////
BOOL 
CDib::LoadImageBMPFile(LPCTSTR lpszPathName)
{
int sign_attach;
int widt;
int heig;


	sign_attach=Attach(::LoadImage( NULL, lpszPathName, IMAGE_BITMAP, 0, 0,
               LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE ));
	if(!sign_attach)
	{
MessageBox(NULL, "Cannot read BMP file", 
		   NULL, MB_ICONINFORMATION | MB_OK);
        return FALSE;
    }

GetObject(sizeof(ds), ds);
if (!GetBitmap(&pBitmap)) // load BITMAP for speed 

return FALSE;
widt=pBitmap.bmWidth;
heig=pBitmap.bmHeight;

  if( ds == NULL )
    {
     return FALSE;
    }
	else
	{
	return TRUE;
    }

}

//////////////////////////////////////////////////////////////////////
BITMAP*

CDib::GetBitmapFile()
{
    return &pBitmap;
}
//////////////////////////////////////////////////////////////////////
void CDib::DeleteObject()
{
    if(ds != NULL)
	{
	::DeleteObject( ds );
	ds = NULL;
    } 
}	
//////////////////////////////////////////////////////////////////////
BOOL 

CDib::Draw(CDC* pDC)
{
	CDC MemDC;
	BITMAP BM;
		
	
MemDC.CreateCompatibleDC(NULL);
MemDC.SelectObject(this);
GetObject(sizeof(BITMAP),&BM);
pDC->BitBlt(10,20,BM.bmWidth,BM.bmHeight,&MemDC,0,0,SRCCOPY);

return TRUE;
}
