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



#include "Config.h"
  

class Segment
{
public:
	Segment(std::int16_t begin, std::int16_t end);
	~Segment();

	std::int16_t beg;
	std::int16_t end;

	std::uint16_t length() { return end - beg + 1; }
};


std::uint8_t measure_intersection(Segment& s1,
                       Segment& s2,
					   std::uint16_t* ratio_1,
                       std::uint16_t* ratio_2);




#endif