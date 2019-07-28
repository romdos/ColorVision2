


#if !defined(AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_)
#define AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorSectionDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ColorSectionDialog dialog

class ColorSectionDialog : public CDialog
{
	// Construction
public:
	ColorSectionDialog(CWnd* pParent = NULL);   // standard constructor

												// Dialog Data
												//{{AFX_DATA(ColorSectionDialog)
	enum { IDD = IDD_DIALOG3 };
	CSpinButtonCtrl	m_Spin;
	CEdit	m_SectionCtrl;
	int		m_SectionNumber;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorSectionDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ColorSectionDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit2();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_)
