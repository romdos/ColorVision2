/*
 * Segments intersection measure and other useful functions.
 *
 *
 *
 *
 */






#ifndef GEOMETRY_H
#define GEOMETRY_H


 // For redefinition basic types(int, char etc.)
#include <cstdint>

// for abs
#include <cstdlib>

// Min and Max functions are contained here
#include <algorithm>

// To redefine basic types
#include "std_types.h"

#include "Config.h"
  

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