// BunchNumDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ColorVision.h"
#include "BunchNumDialog.h"
#include ".\bunchnumdialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BunchNumDialog dialog


BunchNumDialog::BunchNumDialog(CWnd* pParent /*=NULL*/)
	: CDialog(BunchNumDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(BunchNumDialog)
	m_BunchNumber = 0;
	//}}AFX_DATA_INIT
//	icount=0;
}


void BunchNumDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BunchNumDialog)
	DDX_Control(pDX, IDC_EDIT1, m_BunchCtrlEdit);
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
	DDX_Text(pDX, IDC_EDIT1, m_BunchNumber);
	DDV_MinMaxInt(pDX, m_BunchNumber, 0, 63);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BunchNumDialog, CDialog)
	//{{AFX_MSG_MAP(BunchNumDialog)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
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
	/*int pos;
	pos=0;*/
    CRect m_DialogRect;

	//CenterWindow();
	MoveWindow(390,530,150,140,0);	//maxser
	m_BunchCtrlEdit.LimitText(2);
	/*CWnd* pDialog = this->GetWindow();
	pDialog->GetWindowRect( &m_DialogRect );
	
	pDialog->SetWindowPos( &wndBottom, m_DialogRect.left, m_DialogRect.top,
						 m_DialogRect.Width(), m_DialogRect.Height(), SWP_SHOWWINDOW );

	ScreenToClient( &m_EditRect );*/

	CWnd* pWnd = GetDlgItem( IDC_EDIT1 );
	/*CRect rect;
	pWnd->GetWindowRect( &rect );
	ScreenToClient( &rect );*/

	//m_Spin.Create( WS_VISIBLE|WS_CHILD|dwStyles, rect, this, IDC_SPIN );
	//m_Spin.SetRange( m_uiRangeFrom, m_uiRangeTo );  // Sends UDM_SETRANGE
	
    m_Spin.SetBuddy(pWnd);
	m_Spin.SetRange(0,63);
	m_Spin.SetPos(0);
	//pos=m_Spin.GetPos();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
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
	int Temp;
	int RealNumberOfBunches;
	int Numstrip;

	Temp = (int) GetDlgItemInt (IDC_EDIT1);
	if(Temp>=0 && Temp<64)
    {
     m_BunchNumber=Temp;
	 
	 CColorVisionApp *pApp;
pApp= (CColorVisionApp *)AfxGetApp ();
Numstrip=pApp->NumberStripClicked;
RealNumberOfBunches=
pApp->ColorImageProcess->ColorInt[Numstrip].RefinedNumberOfBunches;
if((m_BunchNumber!=62)&&(m_BunchNumber!=63)&&(m_BunchNumber>=RealNumberOfBunches))
	 {
		 m_BunchNumber=0;
		 m_Spin.SetPos(0);
	 }
	 pApp->NumberOfBunch=m_BunchNumber;
	    if(pApp->pDocs3!=NULL)
		{
	    pApp->pDocs3->UpdateAllViews(NULL);
		}
	        if(pApp->pDoci1!=NULL)
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
	UINT idFrom, code;
	idFrom=pNMHDR->idFrom;
	code=pNMHDR->code;

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

void BunchNumDialog::OnUpdateEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	//m_BunchCtrlEdit.
	return;
	CWnd* pm_buddy;
	pm_buddy=m_Spin.GetBuddy();
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
	int Temp;

	m_Spin.SetPos(62);
Temp = (int) GetDlgItemInt (IDC_EDIT1);
	CDialog::OnRButtonDown(nFlags, point);
}

void BunchNumDialog::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_Spin.SetPos(63);

	CDialog::OnRButtonDblClk(nFlags, point);
}


