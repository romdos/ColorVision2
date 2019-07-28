
#pragma once
 

#include "ColorVision_cfg.h"


#include "Resource.h"


class BunchCountDialog: public CDialogEx
{
	DECLARE_DYNAMIC(BunchCountDialog)

public:
	BunchCountDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~BunchCountDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:

	// Buddy
	CEdit editColor;
	CEdit editGray;

	// Spin controls
	CSpinButtonCtrl spinColor;
	CSpinButtonCtrl spinGray;

	// Radio buttons
	BOOL colorPicked;
	BOOL grayPicked;

	std::int32_t colorBunchNum;
	std::int32_t grayBunchNum;

	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();

	afx_msg void OnChangeEditColor();
	afx_msg void OnChangeEditGray();

	DECLARE_MESSAGE_MAP()
};
