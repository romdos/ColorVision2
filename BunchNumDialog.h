#if !defined(AFX_BUNCHNUMDIALOG_H__A32E4F0C_F985_416F_9436_64D3991338BA__INCLUDED_)
#define AFX_BUNCHNUMDIALOG_H__A32E4F0C_F985_416F_9436_64D3991338BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BunchNumDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BunchNumDialog dialog

class BunchNumDialog : public CDialog
{
// Construction
public:
	BunchNumDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BunchNumDialog)
	enum { IDD = IDD_DIALOG2 };
	CEdit	m_BunchCtrlEdit;
	CSpinButtonCtrl	m_Spin;
	int		m_BunchNumber;
	//}}AFX_DATA
CRect           m_EditRect;
//int icount;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BunchNumDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BunchNumDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeEdit1();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEdit1();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUNCHNUMDIALOG_H__A32E4F0C_F985_416F_9436_64D3991338BA__INCLUDED_)
