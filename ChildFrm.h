// ChildFrm.h : interface of the CViewImageFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__653BB159_8FB6_41B4_BBBA_1B713AA97BAA__INCLUDED_)
#define AFX_CHILDFRM_H__653BB159_8FB6_41B4_BBBA_1B713AA97BAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CViewImageFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CViewImageFrame)
public:
	CViewImageFrame();

// Attributes
public:
		
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewImageFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewImageFrame();



#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CViewImageFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__653BB159_8FB6_41B4_BBBA_1B713AA97BAA__INCLUDED_)
