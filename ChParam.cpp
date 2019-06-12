// ChParam.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "ChParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChParam dialog


CChParam::CChParam(CWnd* pParent /*=NULL*/)
	: CDialog(CChParam::IDD, pParent)
	, m_HorVert(TRUE)
	, NetworkDirect(TRUE)
	,m_NumStrips(24)
	, m_NumFrames(0)
	, m_straddr(_T("127.0.0.1"))
	, m_CameraNum(0)
	, m_GGBorGGR(FALSE)
{
	//{{AFX_DATA_INIT(CChParam)
	m_HorVert = TRUE;
	
	m_NumStrips = 0;
	m_straddr="127.0.0.1";
	m_CameraNum=0;
	//}}AFX_DATA_INIT
}


void CChParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChParam)
	DDX_Control(pDX, IDC_EDIT1, m_NumStripEdit);
	DDX_Check(pDX, IDC_CHECK1, m_HorVert);
	DDX_Text(pDX, IDC_EDIT1, m_NumStrips);
	DDV_MinMaxInt(pDX, m_NumStrips, 1, 99);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK2, NetworkDirect);
	DDX_Text(pDX, IDC_EDIT2, m_NumFrames);
	DDX_Control(pDX, IDC_EDIT2, m_EditF2);
	DDV_MinMaxInt(pDX, m_NumFrames, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT3, m_straddr);
	DDV_MaxChars(pDX, m_straddr, 100);
	DDX_Control(pDX, IDC_EDIT3, m_EditAddr);
	DDX_Control(pDX, IDC_EDIT4, m_CameraNumEdit);
	DDX_Text(pDX, IDC_EDIT4, m_CameraNum);
	DDV_MinMaxInt(pDX, m_CameraNum, 0, 20);
	DDX_Check(pDX, IDC_CHECK3, m_GGBorGGR);
}


BEGIN_MESSAGE_MAP(CChParam, CDialog)
	//{{AFX_MSG_MAP(CChParam)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK2, &CChParam::OnBnClickedCheck2)
	ON_EN_CHANGE(IDC_EDIT2, &CChParam::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CChParam::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CChParam::OnEnChangeEdit4)
	//ON_BN_CLICKED(IDC_RADIO1, &CChParam::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_CHECK3, &CChParam::OnBnClickedCheck3)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChParam message handlers

BOOL CChParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_NumStripEdit.LimitText(2);
	m_EditF2.LimitText(6);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChParam::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CChParam::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_HorVert = !m_HorVert;
}

void CChParam::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int Temp;

	Temp = (int) GetDlgItemInt (IDC_EDIT1);
	if(Temp>0 && Temp<100)
    {
     m_NumStrips=Temp;
	}
	
}

void CChParam::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here
NetworkDirect=!NetworkDirect;
}

void CChParam::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

int Temp;

	Temp = (int) GetDlgItemInt (IDC_EDIT2);
	if(Temp>=0)
    {
     m_NumFrames=Temp;
	}
}

void CChParam::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString Temp;
	if(GetDlgItemText(IDC_EDIT3,Temp))
	{
		m_straddr=Temp;
	}
 
}

void CChParam::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int Temp;
	Temp = (int) GetDlgItemInt (IDC_EDIT4);
	if(Temp>=0 && Temp<=20)
    {
     m_CameraNum=Temp;
	}
	/*if(GetDlgItemText(IDC_EDIT4,Temp))
	{
		m_CameraNum=Temp;
	}*/
}

/*void CChParam::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}*/

void CChParam::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here
	m_GGBorGGR = !m_GGBorGGR;
}
