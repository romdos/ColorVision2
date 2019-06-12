#if !defined(AFX_GLOBALOBJECTSFRAME_H__2A633103_CCE6_43B8_81A7_32E8BCCE7F8D__INCLUDED_)
#define AFX_GLOBALOBJECTSFRAME_H__2A633103_CCE6_43B8_81A7_32E8BCCE7F8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobalObjectsFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsFrame frame

class CGlobalObjectsFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CGlobalObjectsFrame)
protected:
	CGlobalObjectsFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobalObjectsFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGlobalObjectsFrame();

	// Generated message map functions
	//{{AFX_MSG(CGlobalObjectsFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBALOBJECTSFRAME_H__2A633103_CCE6_43B8_81A7_32E8BCCE7F8D__INCLUDED_)
