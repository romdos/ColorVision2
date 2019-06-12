#include "afxwin.h"
#if !defined(AFX_CHPARAM_H__CFC5C664_132D_4AA2_BEFE_479CDC99900F__INCLUDED_)
#define AFX_CHPARAM_H__CFC5C664_132D_4AA2_BEFE_479CDC99900F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChParam dialog

class CChParam : public CDialog
{
// Construction
public:
	CChParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChParam)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_NumStripEdit;
	BOOL	m_HorVert;
	int		m_NumStrips;
	//}}AFX_DATA

protected:

	RECT m_RectSample;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCheck1();
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck2();
public:
	bool NetDirect;
public:
	BOOL NetworkDirect;
public:
	int m_NumFrames;
public:
	CEdit m_EditF2;
public:
	afx_msg void OnEnChangeEdit2();
public:
	afx_msg void OnEnChangeEdit3();
public:
	CString m_straddr;
public:
	CEdit m_EditAddr;
public:
	CEdit m_CameraNumEdit;
public:
	int m_CameraNum;
public:
	afx_msg void OnEnChangeEdit4();
/*public:
	afx_msg void OnBnClickedRadio1();*/
public:
	afx_msg void OnBnClickedCheck3();
public:
	BOOL m_GGBorGGR;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHPARAM_H__CFC5C664_132D_4AA2_BEFE_479CDC99900F__INCLUDED_)
