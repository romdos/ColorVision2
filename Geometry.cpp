/*
 * Useful functions for some intermediate calculations.
 *
 *
 *
 */





#include "StdAfx.h"


#include "Geometry.h"



Segment::Segment(sint16 a, sint16 b)
{
	beg = a;
	end = b;
}


Segment::~Segment() {}




/*  
*  @Description:
*	   Analyses intersection between 2 segments: s1 and s2.
*  @Parameters:
*      Ratio1 = intersection / first_interval_length;
*      Ratio2 = intersection / second_interval_length;
*	   if intervals are not intersecting, Ratio1 == distance between intervals
*	   and Ratio2 == 0.
*  @Return value: 
*	   0 - if intersection length is more than a half of a big interval, 
*	   1 - if intersection length is more than a half of a small interval, 
*	   2 - if intersection length is less than a half of a small interval, 
*	   3 - if intervals are not intersecting.                                                       
*/
uint8 measure_intersection(Segment& s1, Segment& s2,
                           uint16* Ratio1,
                           uint16* Ratio2)
{
	sint16 begIntersection = max(s1.beg, s2.beg);
    sint16 endIntersection = min(s1.end, s2.end);
	
	if (begIntersection > endIntersection + 5) // not intersecting
	{
		*Ratio1 = begIntersection - endIntersection;
		*Ratio2 = 0;
		return 3;
	}
	else
	{
		sint16 intersection = endIntersection - begIntersection + 1;

		uint16 firstLen = s1.end - s1.beg + 1;
        uint16 secondLen = s2.end - s2.beg + 1;

        uint16 minLen = min(firstLen, secondLen);
        uint16 maxLen = max(firstLen, secondLen);
		//  16 is for zero avoiding from division 
		*Ratio1 = (16 * intersection) / firstLen;
		*Ratio2 = (16 * intersection) / secondLen;

		if ((2 * intersection) > maxLen) // is it possible?
		{
			return 0;
		}
		else
		{
			if ((2 * intersection) > minLen)
			{
				return 1;
			}
			else
			{
				return 2;
			}
		}
	}
}



