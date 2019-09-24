//
// Dialog to list for color sections
//
//
//


#include "stdafx.h"



#include "ColorVision.h"
#include "ColorSectionDialog.h"




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
	m_SectionNumber = 0U;
	m_MarkingNumber = 0U;
}



void ColorSectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SPIN_COLOR_SECTION, m_SpinColorSection);
	DDX_Control(pDX, IDC_SPIN_MARKING, m_SpinMarking);

	DDX_Control(pDX, IDC_EDIT_COLOR_SECTION, m_ColorSectionEdit);
	DDX_Control(pDX, IDC_EDIT_MARKING, m_MarkingEdit);
	
	DDX_Control(pDX, IDC_RADIO_COLOR_SECTION, radioBtnColorSection);
	DDX_Control(pDX, IDC_RADIO_MARKING, radioBtnMarking);
	
	DDX_Text(pDX, IDC_EDIT_COLOR_SECTION, m_SectionNumber);
	DDX_Text(pDX, IDC_EDIT_MARKING, m_MarkingNumber);

	DDV_MinMaxInt(pDX, m_SectionNumber, 0, 255); 
	DDV_MinMaxInt(pDX, m_MarkingNumber, 0, 32);

}



BEGIN_MESSAGE_MAP(ColorSectionDialog, CDialog)
	//{{AFX_MSG_MAP(ColorSectionDialog) 
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP 
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MARKING, &ColorSectionDialog::OnDeltaposSpinMarkings)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_COLOR_SECTION, &ColorSectionDialog::OnDeltaposSpinColorSection)

	ON_BN_CLICKED(IDC_RADIO_MARKING, &ColorSectionDialog::OnBnClickedRadioMarkings)
	ON_BN_CLICKED(IDC_RADIO_COLOR_SECTION, &ColorSectionDialog::OnBnClickedRadioColorSection)
END_MESSAGE_MAP()




BOOL ColorSectionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow();


	m_ColorSectionEdit.LimitText(3);

	CWnd* pWnd = GetDlgItem(IDC_EDIT_COLOR_SECTION);

	m_SpinColorSection.SetBuddy(pWnd);
	m_SpinColorSection.SetRange(0, 255);
	m_SpinColorSection.SetPos(0);
	 

	pWnd = GetDlgItem(IDC_EDIT_MARKING);

	m_SpinMarking.SetBuddy(pWnd);
	m_SpinMarking.SetRange(0, 32);
	m_SpinMarking.SetPos(0);

	radioBtnColorSection.SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

 


void ColorSectionDialog::OnDeltaposSpinMarkings(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	pNMUpDown->iPos = GetDlgItemInt(IDC_EDIT_MARKING);
	 
	m_MarkingNumber = (pNMUpDown->iPos + pNMUpDown->iDelta) % MARKINGS_NUM;
	
	SetDlgItemInt(IDC_EDIT_MARKING, m_MarkingNumber);

	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp();
	pApp->pDocColorImage->UpdateAllViews(NULL);	
	
	*pResult = 0;
}



void ColorSectionDialog::OnDeltaposSpinColorSection(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	pNMUpDown->iPos = GetDlgItemInt(IDC_EDIT_COLOR_SECTION);

	m_SectionNumber = (pNMUpDown->iPos + pNMUpDown->iDelta) % 256;

	SetDlgItemInt(IDC_EDIT_COLOR_SECTION, m_SectionNumber);

	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp(); 
	
	pApp->pDocColorImage->UpdateAllViews(NULL);

	*pResult = 0;
}



void ColorSectionDialog::OnBnClickedRadioMarkings()
{
	UpdateData(FALSE);
	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp();
	pApp->pDocColorImage->UpdateAllViews(NULL);
}



void ColorSectionDialog::OnBnClickedRadioColorSection()
{
	UpdateData(FALSE);
	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp();
	pApp->pDocColorImage->UpdateAllViews(NULL);
}
