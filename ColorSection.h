//
//
//
//





#if !defined(AFX_COLORSECTION_H__933D7686_AA52_44AC_88DE_E902CB908FCA__INCLUDED_)
#define AFX_COLORSECTION_H__933D7686_AA52_44AC_88DE_E902CB908FCA__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "StdTypes.h"

 


// Section of gray bunches (bunches built on grayscale image)
//
//
//
class GraySection
{
public:
	GraySection();
	~GraySection();

public:
	uint8 begStrip, endStrip;
	// element of this array is bunch number = bunchNumbers[strip], where strip in [beginStrip; endStrip]
	uint8 bunchNumbers[STRIPS_NUM];

public:
	uint16 length() const { return endStrip - begStrip + 1; }
};

 


struct ColorSectionDescr
{
public:
	//int Num_Strips;
	int* location_of_section; // the corresponding numbers of bunches
	int length_of_section;//the number of section fibres
	int base_first;    // the numbers (in accordance with the numeration of
	int base_last; //the strips) of the first and last fibres of the section
	int lower_hue;
	int upper_hue;
	int average_hue;
	int lower_sat;
	int upper_sat;
	int mean_sat;
	int lower_gray;
	int upper_gray;
	int mean_gray;

	ColorSectionDescr(void);
	~ColorSectionDescr(void);
};
//------------------------------------------------------




class CColorSection
{
public:
	CColorSection(int NumStrips, ColorSectionDescr* CurrentSecDes,
		CStrip* CurrentStrip, CColorIntervalSelect* ColorInterv);
	virtual ~CColorSection();

public:
	int Num_Strips;   //number of strips
	int DimX;
	int DimY;//sizes of the image
	int HorizontalVertical;
	//int Stwidth;
	int StripLength;
	int StripWidth;//last_cor15.05.14
	int NumStrips;//last_cor14.11.16
	int LeftRightBoundary;
	int TotalTime;
	int FirstGrain;
	int FirstStrip;
	int FirstHue;
	int FirstHueZone;
	int FirstSat;
	int FirstGray;
	int FirstGrayZone;
	int FirstBeg;
	int FirstEnd;
	int FirstLength;
	int FirstDensity;
	int FirstMarkingGrain;//last_cor29.04.19
	int FirstMarkingStrip;
	int FirstMarkingHue;
	int FirstMarkingHueZone;
	int FirstMarkingSat;
	int FirstMarkingGray;
	int FirstMarkingGrayZone;
	int FirstMarkingBeg;
	int FirstMarkingEnd;
	int FirstMarkingLength;
	int FirstMarkingDensity;
	int TotalShift;
	int TotalMarkingShift;
	int MeanSectionJump;//last_cor10.09.18
	int MeanMarkingJump;//last_cor29.04.19
	int TotalSectionJump;//last_cor10.09.18
	int TotalMarkingJump;//last_cor10.09.18
	int dev_mean[8];
	int NumMaxSection;  //maximal possible number of sections
	CStrip* StripCurrent; //pointer to classes CStrips
	ColorSectionDescr*  DescrSec;  //pointer to structure describing sections
	ColorSectionDescr*  DescrMarking;  //pointer to structure describing markings
	CColorIntervalSelect* ColorInterval;
	//TIntColored* ColoredIntervalsStructure;
	//TIntColored* ColoredIntervalsStructure1;
	int Number_of_sections; //the total number of sections constructed
	int Number_of_sections_left;//left boundary curves
	int Number_of_sections_right;//right boundary curves
	int Number_of_markings; //the total number of markings constructed
	int Number_of_white_markings; //the total number of white markings constructed
	int Number_of_white_markings_left;//left white marking boundary curves
	int Number_of_white_markings_right;//right white marking boundary curves
	int Number_of_yellow_markings; //the total number of yellow markings constructed
	int Number_of_yellow_markings_left;//left yellow marking boundary curves
	int Number_of_yellow_markings_right;//right yellow marking boundary curves
	int MaximalNumberOfBunches;
	int* section_fibre_first;  //beginning and end fibre of the section
	int* section_fibre_last;
	int* section_left_end;
	int* section_right_end;
	int* section_mean_hue;
	int* section_mean_saturation;
	int* section_mean_gray;
	int* section_out_connection;//arrays that describe connections of the
	int* root_section; //particular section
	int* section_point_cross;// with the others
	//int* marking_out_connection;//arrays that describe connections of the
	//int* root_marking; //particular marking
	//int* marking_point_cross;// with the others
	int* section_weight;//last_cor06.05.15
	int* section_fiber_max_length;//last_cor10.10.16
	int* section_upper_mean_length;//last_cor14.11.16
	int* section_lower_mean_length;//last_cor14.11.16
								   //data for classification
	int* trace_of_section;//one-dimensional collection of
						  //auxiliary arrays, showing that this particular grain
						  //has been already included in some section
	int* trace_of_section1;
	int* trace_of_marking;//one-dimensional collection of
						  //auxiliary arrays, showing that this particular grain
						  //has been already included in some marking
	int* trace_of_marking1;

	int* section_upper_hues;
	int* section_lower_hues;
	int* section_upper_saturations;
	int* section_lower_saturations;
	int* section_upper_grays;
	int* section_lower_grays;
	int* left_section_start_number;
	int* right_section_start_number;
	int* left_section_last_number;
	int* right_section_last_number;
	int* sections_under;

public:

	void

		CColorSection::SectionTracking(int left_right_boundary, int* section_trace);

	int

		CColorSection::Section_start(int strip_num, int *status_show, int *new_beg, int left_right_bound);

	int

		CColorSection::Continuation_of_section(int prev_corn, int *prolongation_grain,
			int previous_sec, int continuation_sec, int fiber_number);

	void

		CColorSection::Record_of_section(int current_fibre, int *trace,
			int current_grain, int old_current_grain, int number_of_section);

	void

		CColorSection::End_of_process(int first_strip, int first_grain,
			int section_numb, int last_strip, int count);

	int

		CColorSection::Measure1_of_proximity(int first_left, int first_right,
			int second_left, int second_right, int* proximity1, int* proximity2, int* left_shift, int* right_shift,
			int* ind_length, int* inter_length_ratio, int* inter_length_ratio1);

	void

		CColorSection::MeanCharacteristics(void);

	void

		CColorSection::ThreshodRecord(int* upp_hues, int* low_hues, int* upp_sats,
			int* low_sats, int* upp_grays, int* low_grays, int section_number);

	int

		CColorSection::Test_Junction_Different_Strips_Same_Image(int next_bunch, int previous_bunch,
			int Intersection_Measure, int indic_length, int ratio_length, int ratio_length1,
			int strip_number, int previous_strip_number, int *hue_close_r, int *sat_close_r, int* gray_close_r);

	int

		CColorSection::ColorJumpTesting(int first_fiber, int first_bunch, int second_fiber, int second_bunch,
			int place, int m_shift);

	int

		CColorSection::FindingLowerAdjacentSections(void);

	int

		CColorSection::WritingLowerAdjacentSections(int strip_number, int left_bunch, int right_bunch,
			int num_sect);
	int

		CColorSection::SectionGeometry(int section_num, int* meam_l, int* mean_u);

	void

		CColorSection::RoadMarkingSequences(int left_right_boundary, int* marking_trace,int color);

	int

		CColorSection::RoadMarking_start(int strip_num, int *status_show, int *new_beg, int left_right_bound, int color);

	int

		CColorSection::Continuation_of_roadmarking(int prev_corn, int *prolongation_grain,
		int* prolongation_step,	int previous_sec, int continuation_sec, int fiber_number, int color);

	void

		CColorSection::Record_of_marking(int current_fibre, int *trace,
		int old_current_grain, int grain_number, int number_of_section);

	void

		CColorSection::End_of_marking(int first_strip, int first_grain,
			int section_numb, int last_strip, int count);
	int Test_Suitability_White(int left_right, int continuation_strip, int beg_in, int end_in,
		int beg_in_new, int end_in_new, int beg_int_prev, int end_int_prev, int Intersect, int rat_length,
		int bunch_occur, int bunch_occur_new, int length_int_rat, int length_rat_prev, int incl_f_n_c_r, int incl_n_c_c_f_r,
		int den_rat, int den_rat_prev, int incl_c_f, int incl_n_f, int incl_p_c, int incl_c_n, int differ_sat, int differ_gray,
		int min_sa, int max_sa, int num_of_strips, int min_gr_z);
	int

		CColorSection::Test_Suitability_Yellow(int continuation_strip, int Intersect, int rat_length,
			int bunch_occur, int bunch_occur_new, int length_int_rat, int incl_f_n_c_r,
			int incl_n_c_c_f_r, int den_rat, int incl_c_f, int incl_n_f, int incl_p_c, int differ_sat, int differ_gray,
			int min_sa, int max_sa, int num_of_strips, int min_gr_z);

};

#endif // !defined(AFX_COLORSECTION_H__933D7686_AA52_44AC_88DE_E902CB908FCA__INCLUDED_)
