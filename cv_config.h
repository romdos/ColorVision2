//
// @Description:
//		
//



#ifndef COLORVISION_CV_CONFIG_H
#define COLORVISION_CV_CONFIG_H



#define		TRUE		1
#define		FALSE		0


#define		HORIZONTAL	0
#define		VERTICAL	1


#define		IMWIDTH		640U
#define		IMHEIGHT	480U


#define STRIPS_NUM  48

#define VIDEOWRITER OFF

  



#define PRESSING 1

 // Number of color segments
#define NUM_INTEN			136
// Number of grayscale segments
#define   NUM_INTEN1        64U
// Max number of colored intervals
#define   MAX_INT_NUMBER     32U


#define SEGMENTS_AND_INTENS_TOTAL_NUM  2048U 
#if (NUM_INTEN1 != 64)
#error recalculate SEGMENTS_AND_INTENS_TOTAL_NUM
#endif



#define MAX_COL_INT 96
#define MAX_COLLESS_INT 64

#define NUM_GRAINS 16
#define NUM_SECT 64

#define NUM_SECT1 256
#define NUM_HUES 48



#define RED_COEF    0.3  // 0.299
#define GREEN_COEF  0.59  // 0.587
#define BLUE_COEF   0.11  // 0.114

#define LOW_INTENSITY 12
#define LOW_INTENSITY1 33
#define LOW_INTENSITY2 46
#define LOW_INTENSITY3 23

#define NUM_YELLOW_WHITE_MARKING 32


#endif //COLORVISION_CV_CONFIG_H