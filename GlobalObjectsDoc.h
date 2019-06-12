#if !defined(AFX_GLOBALOBJECTSDOC_H__F634721C_D0E4_4DB5_BA73_9A13D6E031FF__INCLUDED_)
#define AFX_GLOBALOBJECTSDOC_H__F634721C_D0E4_4DB5_BA73_9A13D6E031FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobalObjectsDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGlobalObjectsDoc document

class CGlobalObjectsDoc : public CDocument
{
protected:
	CGlobalObjectsDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGlobalObjectsDoc)

// Attributes
public:
	int GlobalObjectsRepresentationType;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobalObjectsDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGlobalObjectsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGlobalObjectsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBALOBJECTSDOC_H__F634721C_D0E4_4DB5_BA73_9A13D6E031FF__INCLUDED_)
