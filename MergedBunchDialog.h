#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ���������� ���� MergedBunchDialog

class MergedBunchDialog : public CDialog
{
	DECLARE_DYNAMIC(MergedBunchDialog)

public:
	MergedBunchDialog(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~MergedBunchDialog();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG4 };
	CEdit m_MB_Edit;
	CSpinButtonCtrl	m_Spin;
	int	m_MB_number;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit1();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit5();
};
