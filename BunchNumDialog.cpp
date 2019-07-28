




#include "stdafx.h"


// For reflecting bunch numbers into application
#include "ColorVision.h"
#include "BunchNumDialog.h" 




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// BunchNumDialog dialog


BunchNumDialog::BunchNumDialog(CWnd* pParent): CDialog(BunchNumDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(BunchNumDialog)
	m_BunchNumber = 0;
	//}}AFX_DATA_INIT
}



void BunchNumDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BunchNumDialog)
	DDX_Control(pDX, IDC_EDIT_VALUE_OLDBUNCH, m_BunchCtrlEdit);
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
	
	DDX_Text(pDX, IDC_EDIT_VALUE_OLDBUNCH, m_BunchNumber);
	
	DDV_MinMaxInt(pDX, m_BunchNumber, 0, 63);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(BunchNumDialog, CDialog)
	//{{AFX_MSG_MAP(BunchNumDialog)
	ON_WM_PAINT() 
	ON_EN_CHANGE(IDC_EDIT_VALUE_OLDBUNCH, OnChangeEdit1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_WM_RBUTTONDBLCLK()
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BunchNumDialog message handlers

BOOL BunchNumDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    CRect m_DialogRect;

	MoveWindow(390, 530, 150, 140, 0);	//maxser
	m_BunchCtrlEdit.LimitText(2);

	CWnd* pWnd = GetDlgItem(IDC_EDIT_VALUE_OLDBUNCH);

    m_Spin.SetBuddy(pWnd);
	m_Spin.SetRange(0, 63);
	m_Spin.SetPos(0);

	return TRUE;
}



void BunchNumDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}



void BunchNumDialog::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
 
	int Temp = (int) GetDlgItemInt (IDC_EDIT_VALUE_OLDBUNCH);
	
	if (Temp >= 0 && Temp < 64)
    {
		m_BunchNumber = Temp;
	 
		CColorVisionApp *pApp = (CColorVisionApp *)AfxGetApp ();
		
		int Numstrip = pApp->NumberStripClicked;
		int RealNumberOfBunches = pApp->ColorImageProcess->ColorInt[Numstrip].RefinedNumberOfBunches;

		if ((m_BunchNumber != 62) && (m_BunchNumber != 63) && (m_BunchNumber >= RealNumberOfBunches))
		{
			m_BunchNumber = 0;
			m_Spin.SetPos(0);
		}
		
		pApp->NumberOfBunch = m_BunchNumber;
	    
		if (pApp->pDocs3 != NULL)
		{
			pApp->pDocs3->UpdateAllViews(NULL);
		}
	    
		if (pApp->pDoci1 != NULL)
		{
			pApp->pDoci1->UpdateAllViews(NULL);
		}
	} 
}



void BunchNumDialog::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int pos;
	DWORD bound;
	CString buf1; 

	UINT idFrom = pNMHDR->idFrom;
	UINT code = pNMHDR->code;

	UpdateData();
	
	TCHAR buf[32];
	pos = m_Spin.GetPos();                      // Sends UDM_GETPOS
	bound= m_Spin.GetRange();
	wsprintf( buf, _T("%d"), pos );
	CWnd* pWnd = GetDlgItem( IDC_SPIN1 );
	pWnd = m_Spin.GetBuddy();                       // Sends UDM_GETBUDDY
	
	if (pWnd != NULL && HIWORD(pos) != 1)           // Check for error in high word
		pWnd->SetWindowText( buf );
	
	pWnd->GetWindowText(buf1);
	   
	*pResult = 0;
}



void BunchNumDialog::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_Spin.SetPos(0);	
	CDialog::OnLButtonDblClk(nFlags, point);
}



void BunchNumDialog::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_Spin.SetPos(62);
	int Temp = (int) GetDlgItemInt (IDC_EDIT_VALUE_OLDBUNCH);
	
	CDialog::OnRButtonDown(nFlags, point);
}



void BunchNumDialog::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_Spin.SetPos(63);

	CDialog::OnRButtonDblClk(nFlags, point);
}


