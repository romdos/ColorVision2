//
//
//
//
//
//


#pragma once



#include "Resource.h"



class BunchCountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BunchCountDlg)

public:
	BunchCountDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~BunchCountDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUNCHES_SELECT };
#endif

	CEdit m_editColorBunch;
	CEdit m_editGrayBunch; 

	CSpinButtonCtrl m_spinColorBunch;
	CSpinButtonCtrl m_spinGrayBunch;

	CButton radioBtnColorBunch;
	CButton radioBtnGrayBunch;

	UINT8 m_colorBunchNum;
	UINT8 m_grayBunchNum;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	 
	afx_msg void OnDeltaposColorBunchSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposGrayBunchSpin(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};
