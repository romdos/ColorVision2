//
//
//
//
//
//
//




#include "stdafx.h"


#include "ColorVision.h"
#include "BunchCountDlg.h"

#include "resource.h"
#include "afxdialogex.h"





IMPLEMENT_DYNAMIC(BunchCountDlg, CDialogEx)



BunchCountDlg::BunchCountDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BUNCH_SELECT, pParent)
{ 
	m_colorBunchNum = 0U;
	m_grayBunchNum  = 0U;
}



BunchCountDlg::~BunchCountDlg()
{}



void BunchCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_COLOR_BUNCH, m_editColorBunch);
	DDX_Control(pDX, IDC_EDIT_GRAY_BUNCH, m_editGrayBunch);
	
	DDX_Text(pDX, IDC_EDIT_COLOR_BUNCH, m_colorBunchNum);
	DDX_Text(pDX, IDC_EDIT_GRAY_BUNCH, m_grayBunchNum);

	DDX_Control(pDX, IDC_SPIN_GRAY_BUNCH, m_spinGrayBunch);
	DDX_Control(pDX, IDC_SPIN_COLORBUNCH, m_spinColorBunch);
	
	DDX_Control(pDX, IDC_RADIO_COLOR_BUNCH, radioBtnColorBunch);
	DDX_Control(pDX, IDC_RADIO_GRAY_BUNCH,  radioBtnGrayBunch);
}



BOOL BunchCountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CWnd* pWnd = GetDlgItem(IDC_EDIT_COLOR_BUNCH);

	m_spinColorBunch.SetBuddy(pWnd);
	m_spinColorBunch.SetRange(0, 100);
	m_spinColorBunch.SetPos(0); 

	pWnd = GetDlgItem(IDC_EDIT_GRAY_BUNCH);
	m_spinGrayBunch.SetBuddy(pWnd);
	m_spinGrayBunch.SetRange(0, 100);
	m_spinGrayBunch.SetPos(0); 


	radioBtnColorBunch.SetCheck(TRUE); 

	return 1;
}



BEGIN_MESSAGE_MAP(BunchCountDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_COLORBUNCH, OnDeltaposColorBunchSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_GRAY_BUNCH, OnDeltaposGrayBunchSpin)
	ON_BN_CLICKED(IDC_RADIO_COLOR_BUNCH, OnRadioBtnClicked)
	ON_BN_CLICKED(IDC_RADIO_GRAY_BUNCH, OnRadioBtnClicked)

END_MESSAGE_MAP()



void BunchCountDlg::OnDeltaposColorBunchSpin(NMHDR*   pNMHDR, 
											 LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	pNMUpDown->iPos = GetDlgItemInt(IDC_EDIT_COLOR_BUNCH);
	m_colorBunchNum = pNMUpDown->iPos + pNMUpDown->iDelta;
	
	SetDlgItemInt(IDC_EDIT_COLOR_BUNCH, m_colorBunchNum);
	 
	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp();
	pApp->pDocGrayscaleImage->UpdateAllViews(NULL);
	*pResult = 0; 
}



void BunchCountDlg::OnDeltaposGrayBunchSpin(NMHDR* pNMHDR,
											LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
 
	pNMUpDown->iPos = GetDlgItemInt(IDC_EDIT_GRAY_BUNCH);
 
	// TODO: in the future replace BURSTS_SIZE to BUNCHES_SIZE
	m_grayBunchNum = (pNMUpDown->iPos + pNMUpDown->iDelta) % BURSTS_SIZE; 
	SetDlgItemInt(IDC_EDIT_GRAY_BUNCH, m_grayBunchNum);
	 
	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp();
	pApp->pDocGrayscaleImage->UpdateAllViews(NULL);

	*pResult = 0; 
}



void BunchCountDlg::OnRadioBtnClicked()
{ 
	UpdateData(FALSE);
	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp();
	pApp->pDocGrayscaleImage->UpdateAllViews(NULL);
}
