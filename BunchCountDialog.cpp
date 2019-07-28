


/* To interact with color and gray bunches numbers via dialog */





// To get ColorVisionApp pointer 
#include "stdafx.h"

// Class definition
#include "BunchCountDialog.h"
 
// To change bunch number in App
#include "ColorVision.h"

// 
#include "afxdialogex.h"




IMPLEMENT_DYNAMIC(BunchCountDialog, CDialogEx)

 


BunchCountDialog::BunchCountDialog(CWnd* pParent)
				 :CDialogEx(IDD_DIALOG2, pParent)
{
	colorPicked = true;
	grayPicked = false;

	colorBunchNum = 0;
	grayBunchNum = 0;
}


 
// todo:  make default dtor
BunchCountDialog::~BunchCountDialog() {}



void BunchCountDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COLORBUNCH, editColor);
	DDX_Control(pDX, IDC_GRAYBUNCH, editGray);
	
	DDX_Control(pDX, IDC_SPIN_COLORBUNCH, spinColor);
	DDX_Control(pDX, IDC_SPIN_GRAYBUNCH, spinGray);

	DDX_Radio(pDX, IDC_RADIO1, colorPicked);
	DDX_Radio(pDX, IDC_RADIO2, grayPicked);

	DDX_CBIndex(pDX, IDC_COLORBUNCH, colorBunchNum);
	DDX_CBIndex(pDX, IDC_GRAYBUNCH,  grayBunchNum);
}



BEGIN_MESSAGE_MAP(BunchCountDialog, CDialogEx)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_COLORBUNCH, OnChangeEditColor)
	ON_EN_CHANGE(IDC_GRAYBUNCH, OnChangeEditGray)

END_MESSAGE_MAP()



BOOL BunchCountDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	spinColor.SetBuddy(&editColor);
	spinColor.SetRange(0, 23);
	spinColor.SetPos(0);
	 
	spinGray.SetBuddy(&editGray);
	spinGray.SetRange(0, 23);
	spinGray.SetPos(0);

	return TRUE;
}


 
void BunchCountDialog::OnChangeEditColor()
{
	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp();

	std::uint8_t Numstrip = pApp->NumberStripClicked;
	std::uint8_t bunchesNum = pApp->ColorImageProcess->ColorInt[Numstrip].RefinedNumberOfBunches; 

	colorBunchNum = GetDlgItemInt(IDC_COLORBUNCH);
	if ((colorBunchNum >= 0) && (colorBunchNum <= bunchesNum))
	{
		pApp->NumberOfBunch = colorBunchNum;
		pApp->pDoci0->UpdateAllViews(NULL); 
	}
}



void BunchCountDialog::OnChangeEditGray()
{
	CColorVisionApp* pApp = (CColorVisionApp*)AfxGetApp();
	
	std::uint8_t Numstrip = pApp->NumberStripClicked;
	std::uint8_t bunchesNum = pApp->ColorImageProcess->GrayBunches[Numstrip].bursts.size();

	grayBunchNum = GetDlgItemInt(IDC_GRAYBUNCH);
	
	if ((grayBunchNum >= 0) && (grayBunchNum <= bunchesNum))
	{
		pApp->grayBunchNumber = grayBunchNum;
		pApp->pDoci0->UpdateAllViews(NULL); 
	}
}
