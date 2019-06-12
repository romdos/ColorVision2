// MergedBunchDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "ColorVision.h"
#include "MergedBunchDialog.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// диалоговое окно MergedBunchDialog

IMPLEMENT_DYNAMIC(MergedBunchDialog, CDialog)

MergedBunchDialog::MergedBunchDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MergedBunchDialog::IDD, pParent)
{
	m_MB_number=0;
}

MergedBunchDialog::~MergedBunchDialog()
{
}

void MergedBunchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN3, m_Spin);
	DDX_Text(pDX, IDC_EDIT5, m_MB_number);
	DDV_MinMaxInt(pDX, m_MB_number, 0, 95);

}


BEGIN_MESSAGE_MAP(MergedBunchDialog, CDialog)
	ON_EN_CHANGE(IDC_EDIT5, &MergedBunchDialog::OnEnChangeEdit5)
END_MESSAGE_MAP()


// обработчики сообщений MergedBunchDialog
BOOL MergedBunchDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect m_DialogRect;

	//CenterWindow();
	MoveWindow(730,530,150,140,0);	//maxser
	m_MB_Edit.LimitText(3);

	CWnd* pWnd = GetDlgItem( IDC_EDIT2 );

	m_Spin.SetBuddy(pWnd);
	m_Spin.SetRange(0,95);
	m_Spin.SetPos(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MergedBunchDialog::OnEnChangeEdit5()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	int Temp;

	Temp = (int) GetDlgItemInt (IDC_EDIT5);
	if(Temp>=0 && Temp<96)
    {
		m_MB_number=Temp;
		CColorVisionApp *pApp;
		pApp= (CColorVisionApp *)AfxGetApp ();
		pApp->NumberOfColorSection=m_MB_number;
	    if(pApp->pDocColSec1!=NULL)
		{
	    pApp->pDocColSec1->UpdateAllViews(NULL);
		pApp->pDoci0->UpdateAllViews(NULL);
		}
	}


	// TODO:  Добавьте код элемента управления
}
