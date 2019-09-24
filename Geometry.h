/*
 * Segments intersection measure and other useful functions.
 *
 *
 *
 *
 */




#ifndef GEOMETRY_H
#define GEOMETRY_H



// To redefine basic types
#include "StdTypes.h"
 
#include "cv_config.h"
  

#define MAX(x, y) (x) > (y)? (x): (y)

#define MIN(x, y) (x) < (y)? (x): (y)

#define ABS(x) (x) < 0? -(x): (x)

 


class Segment
{
public:
	Segment(sint16 begin, sint16 end);
	~Segment();

	sint16 beg;
	sint16 end;

	uint16 length() { return end - beg + 1; }
};


uint8 measure_intersection(Segment& s1,
						   Segment& s2,
						   uint16* ratio_1,
						   uint16* ratio_2);




#endif