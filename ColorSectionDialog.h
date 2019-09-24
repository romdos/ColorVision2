//
//
//
//
//





#if !defined(AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_)
#define AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_





#if _MSC_VER > 1000
#pragma once
#endif




class ColorSectionDialog : public CDialog
{ 
public:
	ColorSectionDialog(CWnd* pParent = NULL);   // standard constructor
	 
	enum { IDD = IDD_DIALOG2 };

	CSpinButtonCtrl	m_SpinColorSection;
	CSpinButtonCtrl	m_SpinMarking;
	 
	CButton radioBtnColorSection;
	CButton radioBtnMarking;
	 
	CEdit	m_ColorSectionEdit;
	CEdit	m_MarkingEdit;

	uint8		m_SectionNumber;
	uint8		m_MarkingNumber;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:

	virtual BOOL OnInitDialog();
	  
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: 
	afx_msg void OnDeltaposSpinMarkings(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinColorSection(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnBnClickedRadioMarkings();
	afx_msg void OnBnClickedRadioColorSection();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OLORSECTIONDIALOG_H__A837439D_29C0_42DA_87E9_4D23557C74C5__INCLUDED_)
