#if !defined(AFX_VIZSTRIPFRAME_H__3F09B62B_4E3C_4C1D_A590_254BDB5A440D__INCLUDED_)
#define AFX_VIZSTRIPFRAME_H__3F09B62B_4E3C_4C1D_A590_254BDB5A440D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VizStripFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVizStripFrame frame

class CVizStripFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CVizStripFrame)
protected:
	CVizStripFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVizStripFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVizStripFrame();

	// Generated message map functions
	//{{AFX_MSG(CVizStripFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIZSTRIPFRAME_H__3F09B62B_4E3C_4C1D_A590_254BDB5A440D__INCLUDED_)
