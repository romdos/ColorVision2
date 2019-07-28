/*
 * A strip of an image. Contains all necessary data and methods
 * for building Geometrized Histogram.
 *
 *
 *
 *
 */



#if !defined(AFX_STRIP_H__5115FABA_2C3C_461B_95FE_071A46A2B06E__INCLUDED_)
#define AFX_STRIP_H__5115FABA_2C3C_461B_95FE_071A46A2B06E__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/*
*  Segments of Geometrized Histograms.
*
*
*/
#include "Geometry.h"



// This structure describes the geometry of the distribution of a particular intensity in the strip
struct TIntCharact       
{ 
	int MaxSize;
	int num_of_int;  // the total number of intervals in the structure
	
	int *BegInt;      // pointer to the beginning  of the current interval
	int *EndInt;      // pointer to the end  of the current interval
	
	int *Signif;      // significance (cardinality) of the current interval
	
	int *ColorPeak;  //the corresponding peak of the other opponent ratio
	int *PeakFraction;
	int *FirstOutlet;
	int *SecondOutlet;
	int *ColorPeak1;
	int *PeakFraction1;
	int *FirstOutlet1;

	int *SecondOutlet1;
	int *MainOpponentRatiosBalance;
	int *ZeroRatio;
	int *ZeroRatio1;
	int *PositiveFraction;
	int *NegativeFraction;
	int *PositiveFraction2;
	int *NeighborPosFraction;
	int *NeighborNegFraction;
	int *CenterOfMass;
	int *CenterOfMass1;
	int *LowerGrayScale;
	int *UpperGrayScale;
	int *GrayScaleMean;
	int *LowerMRatio;
	int *UpperMRatio;
	int *MeanMRatio;

	TIntCharact();
	~TIntCharact();
};



// This structure describes the geometry of the distribution of a particular intensity in the strip
struct TIntCharactGray       
{ 
	int MaxSize;
	int num_of_int;  // the total number of intervals in the structure
	int* BegInt;      // pointer to the beginning  of the current interval
	int* EndInt;      // pointer to the end  of the current interval
	int* Signif;      // significance (cardinality) of the current interval

	TIntCharactGray();
	~TIntCharactGray();
};



// This structure describes the colored intervals of strips
struct TIntColor 
{
	int num_of_int;  // the total number of intervals in the structure
	
	int* NumberOfColorBunch;      // pointer to the number of the color bunch
	int*  PosPeakHue; //the hue corresponding to the positive peak
	int*  TotCMHue;
	int*  NegPeakHue;
	int*  TotCMSat;
	int*  LeftHueValue;
	int*  RightHueValue;
	int*  LowerSatValue;
	int*  UpperSatValue;
	int*  TriangleHue;
	int*  TypeOfColor;
	 
	TIntColor();
	~TIntColor();
};




struct TIntColored //This structure describes the  integrated colored intervals of a strip
{ 
	int   num_of_int;  //the total number of integrated intervals in the structure
	int*  BegInterv;   //pointer to the interval beginnings
	int*  EndInterv;
	int*  GrainIntensity;
	int*  LowerIntensity;
	int*  UpperIntensity;
	int*  LowerGrayscale;
	int*  UpperGrayscale;
	int*  AverageGray;
	int*  LowerHueValue;
	int*  UpperHueValue;
	int*  AverageHue;
	int*  LowerSatValue;
	int*  UpperSatValue;
	int*  AverageSat;
	int*  Significance;
	int*  Cardinality;
	 
	TIntColored();
	~TIntColored();
};




struct TIntColorLessBack //This structure describes the  integrated background intervals of a strip
{ 
	int   num_of_int;  //the total number of integrated intervals in the structure
	int*  BegInterv;   //pointer to the interval beginnings
	int*  EndInterv;
	int*  GrainIntensity;
	int*  LowerIntensity;
	int*  UpperIntensity;
	int*  LowerGrayscale;
	int*  UpperGrayscale;
	int*  AverageGray;
	int*  AverageHue;
	int*  AverageSat;
	int*  Significance;
	int*  Cardinality;
	 
	TIntColorLessBack();
	~TIntColorLessBack();
};




struct TIntColoredCharacteristics //This structure describes the  characteristics of color bunches of strips
{ 
	int   Max_number;    //maximum number of intervals at a point of the strip middle line
	int   num_of_bunches;  //the total number of preliminary bunches in the structure
	int   num_of_refined_bunches;  //the total number of refined bunches in the structure
	int   num_of_contrast_intervals;  //the total number of bunches with contrast with adjacent bunches in the structure
	int*  bunch_blocking;   //pointer to blocked bunches
	int*  left_continuation;
	int*  right_continuation;
	int*  left_adjacent;
	int*  right_adjacent;
	int*  new_left_continuation;
	int*  new_right_continuation;
	int*  new_left_adjacent;
	int*  new_right_adjacent;
	int*  ordered_bunch_number;
	int*  old_ordered_bunch_number;
	int*  label_segments;
	int*  center_bunch_suitability;
	int*  new_bunch_number;
	int*  old_bunch_number;
	int*  visible_bunches;
	int*  length_of_trajectory;
	int*  shift_of_the_position;
	int*  total_shift;
	int*  previous_bunch_number;
	int*  right_length_of_trajectory;
	int*  right_shift_of_the_position;
	int*  right_total_shift;
	int*  right_previous_bunch_number; 

	TIntColoredCharacteristics();
	~TIntColoredCharacteristics();
};



struct TMotionShifts //This structure describes the  history of color bunch motion
{ 
	int* SeveralIntervalsMovements;

	TMotionShifts();
	~TMotionShifts();
};




class CMotion
{
public:
	CMotion();
	~CMotion();

	int NumberofFrames;
	int* permutation;
	TMotionShifts* SeveralIntervalsMotion;
};




class CStrip
{
public:
	CStrip();
	~CStrip();

public:

	// todo: rename according to camelCase. Remain only 'number'
	int num_strip; 

	int StripWidth;  
	int StripLength;

	int StripWidthPrev; // todo: delete

	int HorizontalVertical;

	BOOL GGBorGGR;

	int PressedLength;
	int NumLevels;   // number of values each pixel can take (e.g. 256)
	int NumbStr;  	  //number of strips
	int BitPerP;
	int TotalTime;

	int* correct_int;

	int DimX;        // width  of the image in pixels
	int Cor_Width; //correction to the width that takes into account the placement of the DIB
	int DimY;        // height of the image in pixels
	int Dimension;
	int DimDifference; //parameter that specifies the number of gradations of
							  //the difference between the opponent ratios
	int DimDifference1;
	int DimDifference2;
	int left_bound_of_color_resolution;
	int right_bound_of_color_resolution;
	int left_shift1[16];
	int left_shift2[16];
	int right_shift1[16];
	int right_shift2[16];
	int graygrades[16];
	int graygrades1[16];
	int graygrades2[16];

	uint8* intensi;
	//beginning parameters for analysis of a color ratio image
	int *hist_fun;  // number of lines where pixels of a particular intensity occur
	int *hist_sum;  // the value of the histogram function
	int *num_of_int;
	int *beg_point; // the beginning of lines  of fixed intensity
	int *end_point; // the end of lines  of fixed intensity
	int *thick_beg; //the beginning of the current interval
	int *thick_end; //the end of the current interval
	int *thick_stat;  //statistics corresponding to the interval
	int *thick_stat_input; //auxiliary information
	int *thick_break_beg;  //auxiliary information
	int *thick_break_end;  //auxiliary information
	int *thick_break_stat; //auxiliary information
	int *thick_prev_beg;   // previous interval information
	int *thick_prev_end;   // previous interval information
	int *thick_prev_stat;  // previous interval statistics
	int *thick_first;      // the first line of the collection of intervals
	int *thick_last;       // the last line of the collection of intervals
	int *jump_len;         // the maximal jump length
	int *jump_end;         // the maximal jump end
	int* import_beg;       //the most important interval for the particular value
	int* import_end;
	 
	int *gray_min;
	int *gray_max;
	float *gray_mean;
	int *opponent1_min;
	int *opponent1_max;
	float *opponent1_mean;

	uint8* valuable_intensity;  // flags for "visible" intensities
	int* bright_consistency; // array that describes the most visible intensities
	int* intensities_occurred;// array that describes the intensities at the
							  //particular point of the vertical axis
	int* interval_occurred;
	int* quantity_of_intensities;//rough texture characteristic;
	int* intervals_occurred;
	int* valuable_interval; //the best visible intervals of intensities.

	int* opponent_color_difference;
	int* invert_color_difference1;
	int* invert_color_difference2;
	 
	TIntCharact* IntAllInform; // Rough preliminary description of strip's geometry of
							   // intensity destribution for the G/(G +B) component

							   //parameters for analysis of a grayscale image
	int *hist_fung;  // number of lines where pixels of a particular intensity occur
	int *hist_sumg;  // the value of the histogram function
	int *num_of_intg;
	int *beg_pointg; // the beginning of lines  of fixed intensity
	int *end_pointg; // the end of lines  of fixed intensity
	int *thick_begg; //the beginning of the current interval
	int *thick_endg; //the end of the current interval
	int *thick_statg;  //statistics corresponding to the interval
	int *thick_stat_inputg; //auxiliary information
	int *thick_break_begg;  //auxiliary information
	int *thick_break_endg;  //auxiliary information
	int *thick_break_statg; //auxiliary information
	int *thick_prev_begg;   // previous interval information
	int *thick_prev_endg;   // previous interval information
	int *thick_prev_statg;  // previous interval statistics
	int *thick_firstg;      // the first line (or column) of the collection of intervals
	int *thick_lastg;       // the last line (or column) of the collection of intervals
	int *jump_leng;         // the maximal jump length
	int *jump_endg;         // the maximal jump end
	int* import_begg;       //the most important interval for the particular value
	int* import_endg;

	uint8* valuable_intensityg;  // flags for "visible" intensities
	
	
	
	int* bright_consistencyg; // array that describes the most visible intensities
	int* intensities_occurredg;// array that describes the intensities at the
							   //particular point of the vertical axis
	int* interval_occurredg;
	int* quantity_of_intensitiesg;//rough texture characteristic;
	int* intervals_occurredg;
	int* valuable_intervalg; //the best visible intervals of intensities.
	 

	TIntCharactGray* IntAllInformGray;// Rough preliminary description of strip's geometry of
									  // intensity destribution for the grayscale component

	unsigned int* signif_value; //Consistience of the intensity

public:
	void Loc_stat_geom_double(BOOL NumPair);
	// scans the strip and fills in the array AllIntens

	void Important_interval(int begin_interval, int end_interval, int min_val,
			int max_val, float mean_val, int min_opponent1, int max_opponent1, float mean_opponent1,
			unsigned char intensi, int signi, int* thick_be, int* thick_en, int* num_of_in,
			int* thick_sta, int* hist_fu, int* hist_su, int* thick_stat_inpu,
			int* thick_prev_be, int* thick_prev_en, int* thick_prev_sta,
			int* thick_break_be, int* thick_break_en, int* thick_break_sta, int num_comp);

	void Strip_value_painting(unsigned char intens, int beg_int, int end_int,
			int intens_consist, unsigned char*valuable_inten, int*bright_consist);

	void StripCharacteristicsFinding(unsigned char inten, int gray_intensity, int actual_opponent1, int* dif_int_count1,
			int coor1, int* hist_su, int* hist_fu, int* first_pi, int* last_pi, int* beg_poin,
			int* end_poin, int* thick_firs, int* thick_las, int* thick_stat_inpu,
			int* import_en, int* last_en, int* jump_le, int* jump_en, int* num_of_in,
			int* import_be, unsigned char* value_int, int* bright_cons, int* thick_be,
			int* thick_en, int* thick_sta, int* thick_prev_be, int* thick_prev_en,
			int* thick_prev_sta, int* thick_break_be, int* thick_break_en,
			int* thick_break_sta, int Coun, int color_balance,int saturation);

	void StripCharacteristicsFindingGray(std::uint8_t inten, std::uint16_t coord, std::uint16_t* last_pi, int* last_en);

	void FinalCorrectionGray();

	void FinalCorrection(int* thick_las, int* gray_mi, int* gray_ma, float* gray_mea,
			int *mratio_min, int *mratio_max, float *mratio_mean, int* thick_be, int* thick_en,
			int* import_be, int* import_en, int* thick_break_be, int* thick_break_en,
			int* thick_prev_be, int* thick_prev_en, int* thick_firs, int* num_of_in,
			int* hist_fu, int* hist_su, int* thick_sta, int* thick_stat_inpu, int* last_en,
			int* jump_le, int* jump_en, int* thick_break_sta, int* thick_prev_sta,
			unsigned char* value_int, int* bright_cons, int* diff_color,
			int Coun);

	void OpponentIntensityFinding(int* inten_opp_count, int start1,
			int bound1, int bound2, unsigned char inten_first, int signif, int coun,
			int num_opp);

	void Important_interval1(int begin_interval, int end_interval, unsigned char intensi, int signi);

	void Strip_value_painting1(std::uint8_t intens, std::int16_t beg, std::int16_t end, int consistency); 
};

 

#endif // !defined(AFX_STRIP_H__5115FABA_2C3C_461B_95FE_071A46A2B06E__INCLUDED_)
