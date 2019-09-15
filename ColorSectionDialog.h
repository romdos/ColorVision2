



#if !defined(AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_)
#define AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_





#if _MSC_VER > 1000
#pragma once
#endif






class ColorSectionDialog : public CDialog
{
	// Construction
public:
	ColorSectionDialog(CWnd* pParent = NULL);   // standard constructor


	enum { IDD = IDD_DIALOG3 };

	CSpinButtonCtrl	m_Spin;

	CEdit	m_SectionCtrl;

	int		m_SectionNumber;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:

	virtual BOOL OnInitDialog();



	afx_msg void OnChangeEdit2();


	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_)
