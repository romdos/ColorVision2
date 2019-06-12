// olorSectionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "olorSectionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColorSectionDialog dialog


ColorSectionDialog::ColorSectionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ColorSectionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ColorSectionDialog)
	m_SectionNumber = 0;
	//}}AFX_DATA_INIT
}


void ColorSectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ColorSectionDialog)
	DDX_Control(pDX, IDC_SPIN2, m_Spin);
	DDX_Control(pDX, IDC_EDIT2, m_SectionCtrl);
	DDX_Text(pDX, IDC_EDIT2, m_SectionNumber);
	DDV_MinMaxInt(pDX, m_SectionNumber, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ColorSectionDialog, CDialog)
	//{{AFX_MSG_MAP(ColorSectionDialog)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorSectionDialog message handlers

BOOL ColorSectionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CRect m_DialogRect;

	CenterWindow();
	m_SectionCtrl.LimitText(3);

	CWnd* pWnd = GetDlgItem(IDC_EDIT2);

	m_Spin.SetBuddy(pWnd);
	m_Spin.SetRange(0, 255);
	m_Spin.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void ColorSectionDialog::OnChangeEdit2()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	int Temp;

	Temp = (int)GetDlgItemInt(IDC_EDIT2);
	if (Temp >= 0 && Temp<256)
	{
		m_SectionNumber = Temp;
		CColorVisionApp *pApp;
		pApp = (CColorVisionApp *)AfxGetApp();
		pApp->NumberOfColorSection = m_SectionNumber;
		if (pApp->pDocColSec1 != NULL)
		{
			pApp->pDocColSec1->UpdateAllViews(NULL);
			pApp->pDoci0->UpdateAllViews(NULL);
		}
		/*if(pApp->pDoci1!=NULL)
		{
		pApp->pDoci1->UpdateAllViews(NULL);
		}*/
	}

}

void ColorSectionDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_Spin.SetPos(0);
	CDialog::OnLButtonDblClk(nFlags, point);
}
