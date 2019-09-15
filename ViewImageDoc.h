// 
//
//
//
//
//
//








#if !defined(AFX_VIEWIMAGEDOC_H__7A3AF8B1_2F07_48CA_A3BC_E13D48652A28__INCLUDED_)
#define AFX_VIEWIMAGEDOC_H__7A3AF8B1_2F07_48CA_A3BC_E13D48652A28__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



 
#include "DibTga.h"
#include "Dib.h"
#include "DibGrayScale.h"




/////////////////////////////////////////////////////////////////////////////
// CViewImageDoc document

class CViewImageDoc : public CDocument
{
protected:
	CViewImageDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewImageDoc)


// Attributes
public:

	CDib     *m_DibDoc;
	//HBITMAP  *m_hBitmap;
	CDibTga  *m_DibTgaDoc;
	CDibGrayScale *m_DibGrayScaleDoc;
	//CFont     m_Font;
	CString    m_it_is_nt;
	CString    m_it_is_jpg;
	CString    OnlyTCU;
	int ImageRepresentationType; 

// Operations
public: 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewImageDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewImageDoc();

	void CallCalculateGrayScale();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewImageDoc)
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileMruFile1(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWIMAGEDOC_H__7A3AF8B1_2F07_48CA_A3BC_E13D48652A28__INCLUDED_)
