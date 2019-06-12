#pragma once

#include "Dib.h"
#include "DibGrayScale.h"

// CVideoImageInputDoc document

class CVideoImageInputDoc : public CDocument
{
	DECLARE_DYNCREATE(CVideoImageInputDoc)

public:
	CVideoImageInputDoc();
	virtual ~CVideoImageInputDoc();
// Attributes
public:
	CDib     *m_DibDoc;
	//CDibGrayScale *m_DibGrayScaleDoc;
	int VideoImageRepresentationType;

	//void InitializeGrayScale();
	//void CalculateGrayScale();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};