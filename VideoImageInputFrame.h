#pragma once


// CVideoImageInputFrame frame

class CVideoImageInputFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CVideoImageInputFrame)
protected:
	CVideoImageInputFrame();           // protected constructor used by dynamic creation
	virtual ~CVideoImageInputFrame();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
public: 
	CColorVisionApp *pApp;
int VideoImageRepresentationType;
protected:
	DECLARE_MESSAGE_MAP()
};


