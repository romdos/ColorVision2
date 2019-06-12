#if !defined(AFX_VIZSTRIPDOC_H__49D84222_2824_4238_9592_A49A72239DDF__INCLUDED_)
#define AFX_VIZSTRIPDOC_H__49D84222_2824_4238_9592_A49A72239DDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VizStripDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVizStripDoc document

class CVizStripDoc : public CDocument
{
protected:
	CVizStripDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVizStripDoc)

// Attributes
public:

	int StripRepresentationType;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVizStripDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVizStripDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CVizStripDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIZSTRIPDOC_H__49D84222_2824_4238_9592_A49A72239DDF__INCLUDED_)
