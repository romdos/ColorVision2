#pragma once


#include "ColorSection.h"


#define		MARKINGS_NUM	2U



class Marking: public GraySection
{
public:
	Marking();
	~Marking();

public:
	// detected or not
	bool isValid; 

public:
	uint16 length() const { return endStrip - begStrip + 1; }
	float left_curvature();
	float right_curvature();
};