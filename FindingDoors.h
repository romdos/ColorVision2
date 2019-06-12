/*
 * FindingDoors.h
 *
 *  Created on: 15.01.2014
 *      Author: randomind
 */


#ifndef FINDINGDOORS_H_
#define FINDINGDOORS_H_


//------------------------------------------------------
class CMyPoint
{
public:
	CMyPoint(void);
	virtual ~CMyPoint(void);
	int x;
	int y;
	bool contrast;

};
//------------------------------------------------------
class CMyLine
{
public:
	CMyLine(void);
	virtual ~CMyLine(void);
	// снизу вверх
	CMyPoint BegPoint;
	CMyPoint EndPoint;

};
//------------------------------------------------------
class CBunchPoint
{
public:
	CBunchPoint(void);
	virtual ~CBunchPoint(void);
	CMyPoint BegBunchPoint [95];
	CMyPoint EndBunchPoint [95];
	int FirstStrip;
	int LastStrip;
};
//------------------------------------------------------
class CFindRect
{
public:
	CFindRect(void);
	virtual ~CFindRect(void);

public:
	int left_bord_angl;
	int right_bord_angl;
	int num_strips;
	int count_sec;
	CMyPoint centr;
	int sat;
	int hue;
	int gray;
	int dlina;
	CMyPoint left_low_corn;
	CMyPoint right_low_corn;
	CMyPoint left_up_corn;
	CMyPoint right_up_corn;
};
//------------------------------------------------------
class CNStrip
{
public:
	CNStrip(void);
	virtual ~CNStrip(void);
	
public:
	CMyPoint Begin;
	CMyPoint End;
};
//------------------------------------------------------
class CNewBanch
{
public:
	CNewBanch(void);
	virtual ~CNewBanch(void);
public:
	CNStrip MasStrip [95];
	int FirstStrip;
	int LastStrip;
	int StripsNumb;
	CMyLine LeftBord;
	CMyLine RightBord;
	int AngleLeftBord;
	int AngleRightBord;
	int MeanGray;
	int MeanHue;
	int MeanSaturation;
};
#endif /* FINDINGDOORS_H_ */
