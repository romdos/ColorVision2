//----------------------------------------------------------------------------
//Programmer:    K.I. Kiy                   File      MarkingSignalParts.cpp
//Last revision   26.10.18                            Creation  26.10.18
//Last printing  26.10.18
//----------------------------------------------------------------------------
#include "stdafx.h"
#include "ColorVision.h"
//#include "ColorIntervalSelect.h"
#include "ImageProcess.h"
//#include "Strip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


static  int hue_zones[NUM_HUES] = { 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
5, 1, 1, 1, 1, 1 };
static  int dev_hue_zone[6] = { 2, 2, 2, 2, 2, 2 };
static  int dev_mean_sat[16] = { 1, 1, 1, 1, 1, 2, 3, 4, 4, 4, 4, 4, 3, 2, 1, 0 };
static  int dev_mean_sat1[16] = { 0, 1, 1, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4 };
static  int imp_dev_mean_sat[16] = { 3, 3, 3, 3, 4, 5, 6, 6, 6, 6, 6, 5, 4, 4, 4, 4 };
static  int imp_dev_mean_sat1[16] = { 1, 2, 2, 3, 3, 3, 3, 4, 5, 5, 5, 6, 6, 7, 6, 6 };

static  int gray_zones[NUM_INTEN1] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2,
2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7 };
//0. 0-6, 1. 7-12, 2. 13-21, 3. 22-30, 4. 31-39, 5. 40-49, 6. 50-57, 7. 58-63
static  int dev_mean[8] = { 5, 8, 8, 10, 10, 10, 12, 8 };
static  int imp_dev_mean[8] = { 14, 16, 18, 18, 16, 16, 14, 12 };

//=========================================================
int

CColorIntervalSelect::MarkingSignalPartsFinding(void)
{
	int number_of_bunches;
	int number_of_covering_bunches;
	//int disordering;
	int prior;
	int bunch_old_number;
	int beg_int;
	int end_int;
	int int_length;
	int int_signif;
	int int_density;
	int bunch_occurrence;
	int bunch_hue;
	int bunch_sat;
	int bunch_gray;
	int bunch_hue_zone;
	int bunch_gray_zone;
	int first_in_ordering_old_number;
	int bunch_ordered_number;
	int residual;
	int strip_ratio;
	int shift;
	int  red_signal_car;
	int blue_signal_road_sign;
	int yellow_signal_road_marking;
	int white_signal_road_marking;
	int included_in_the_lattice;
	int comparison_result;
	int gray_mean_value;
	int center_coor;
	int bunch_inhabitant;
	int bunch_inhabitant_intensity;
	int bunch_inhabitant_beg;
	int bunch_inhabitant_end;
	int block;
	int bunch_inhabitant_length;
	int bunch_inhabitant_signif;
	int inhabitant_int_density;
	int bunch_inhabitant_satur;
	
	inhabitant_int_density = 0;
	bunch_inhabitant_signif = 0;
	bunch_inhabitant_length = 0;
	center_coor = 0;
	comparison_result = -1;
	included_in_the_lattice = 0;
	white_signal_road_marking = 0;
	yellow_signal_road_marking = 0;
	blue_signal_road_sign = 1;
	red_signal_car = 1;
	prior = -1;
	memset(painted_bunch_intensities, (int) '\0', sizeof(int)*(PressedLength));
	memset(painted_numbers_intensities, (int) '\0', sizeof(int)*(PressedLength));
	for (int coun_bunch = 0; coun_bunch<NumberOfColoredIntervals; coun_bunch++)
	{
		block = bunch_blocking[coun_bunch];
		if(!block)
		{
		beg_int = ColoredIntervalsStructure->BegInterv[coun_bunch];
		end_int = ColoredIntervalsStructure->EndInterv[coun_bunch];
		gray_mean_value = ColoredIntervalsStructure->AverageGray[coun_bunch];
		Strip_value_painting_bunch(coun_bunch, beg_int / 4, end_int / 4, gray_mean_value,
painted_bunch_intensities, painted_numbers_intensities, intensity_consistency, PressedLength);
		}
	}
		number_of_bunches = RefinedNumberOfBunches;
		shift = 0; //number_of_bunches*marking_signal;
		first_in_ordering_old_number = old_ordered_bunch_number[0];
		if (!Disordering)
		{
			number_of_covering_bunches = NumberOfIntervalsInCovering;
		}
		else
		{
			number_of_covering_bunches = -1;
			//goto L;
		}
		strip_ratio = 16 * strip_number / NumStrip;
		
		/*for (int count_bunch = 0; count_bunch<number_of_covering_bunches; count_bunch++)
		{//bunch_loop
			bunch_old_number = old_ordered_bunch_number[count_bunch];
			beg_int = ColoredIntervalsStructure->BegInterv[bunch_old_number];
			end_int = ColoredIntervalsStructure->EndInterv[bunch_old_number];
			int_length = end_int - beg_int + 1;
			int_signif = ColoredIntervalsStructure->Significance[bunch_old_number];
			int_density = (2 * int_signif) / int_length;
			bunch_occurrence = visible_bunches[bunch_old_number];//last_cor22.11.16
			bunch_hue = ColoredIntervalsStructure->AverageHue[bunch_old_number];
			bunch_sat = ColoredIntervalsStructure->AverageSat[bunch_old_number];
			bunch_gray = ColoredIntervalsStructure->AverageGray[bunch_old_number];
			bunch_hue_zone = hue_zones[bunch_hue];//last_cor01.10.18
			bunch_gray_zone = gray_zones[bunch_gray];
			if ((strip_ratio <= 2) && (int_length <= ((3 * StripWidth) / 2)) && (bunch_sat <= 3))
			{
				goto M;
			}
			if ((strip_ratio <= 5) && ((int_density <= StripWidth / 2) || ((bunch_sat <= 1) && (int_density <= 7))))
			{//error12.10.18
				goto M;
			}
			if ((strip_ratio <= 4) && (bunch_sat <= 1) && (bunch_gray_zone >= 2) && (bunch_gray_zone <= 4))
			{
				goto M;
			}
			
			if ((strip_ratio >= 7) && (int_length >= StripWidth) && (bunch_sat <= 1) && (bunch_gray_zone >= 2) &&
				(int_density >= StripWidth / 2))
			{
				goto M;
			}
			if ((strip_ratio >= 8) && (bunch_sat <= 2) && (bunch_gray_zone >= 2) && (bunch_gray_zone <= 4) &&
				(int_density >= (2 * StripWidth) / 3))
			{
				goto M;
			}

			if ((strip_ratio >= 7) && (bunch_sat <= 1) && (bunch_gray_zone >= 2) && (bunch_gray_zone <= 3) &&
				(int_density >= StripWidth))
			{
				goto M;
			}

			
			if (bunch_gray >= 6)
			{//bg4
				if (((bunch_hue_zone == 5) && (bunch_hue >= 40) && (bunch_sat >= 4) && (bunch_gray >= 10)) ||
					((bunch_hue_zone == 5) && (bunch_hue >= 41) && (bunch_sat >= 3) && (bunch_gray >= 15)) ||
					(bunch_hue_zone == 1) && ((bunch_sat >= 3)
						|| ((bunch_sat >= 2) && ((bunch_gray_zone >= 2) || (bunch_gray >= 8)))
						|| ((bunch_sat >= 1) && ((bunch_gray_zone >= 2) && (bunch_gray >= 16)))))
				{
					if ((int_length <= DimX / 16) && (beg_int>DimX / 8) && (end_int<(DimX - DimX / 8)))
					{
						if (!StripSignals[count_strip])
						{

							prior = 1;
							last_numbered_strip = count_strip;
							number_of_bunch_in_strip = 0;
							if (first_numbered_strip<0)
							{
								first_numbered_strip = count_strip;
							}
							if (number_of_strips_involved<16)
							{
								StripSignals[count_strip] += 1;
								SignalNumber[16 * number_of_strips_involved + number_of_bunch_in_strip] = count_bunch + 1;

							}
							StripNewNumber[count_strip] = number_of_strips_involved + 1;
							number_of_strips_involved++;
						}
						else
						{
							number_of_bunch_in_strip++;
							if ((number_of_bunch_in_strip<16) && (number_of_strips_involved<16))
							{
								StripSignals[count_strip] += 1;
								SignalNumber[16 * (number_of_strips_involved - 1) + number_of_bunch_in_strip] = count_bunch + 1;
							}

						}
					}
				}
			}//bg4
		M:;
		}//bunch_loop*/
	//L:;
		NumberOfRedFeaturesCandidates = 0;//last_cor27.02.19
		NumberOfYellowMarkingCandidates = 0;//last_cor27.02.19
		NumberOfWhiteMarkingCandidates = 0;
		for (int count_bunch1 = 0; count_bunch1 < number_of_bunches; count_bunch1++)
		{//bunch_loop1
			included_in_the_lattice = 0;
			bunch_old_number = old_bunch_number[count_bunch1];
			bunch_ordered_number = ordered_bunch_number[bunch_old_number];
			bunch_occurrence = visible_bunches[bunch_old_number];//last_cor22.11.16
			bunch_hue = ColoredIntervalsStructure->AverageHue[bunch_old_number];
			bunch_sat = ColoredIntervalsStructure->AverageSat[bunch_old_number];
			bunch_gray = ColoredIntervalsStructure->AverageGray[bunch_old_number];
			bunch_hue_zone = hue_zones[bunch_hue];
			bunch_gray_zone = gray_zones[bunch_gray];
			beg_int = ColoredIntervalsStructure->BegInterv[bunch_old_number];
			end_int = ColoredIntervalsStructure->EndInterv[bunch_old_number];
			center_coor = beg_int + (end_int - beg_int) / 2;
			int_length = end_int - beg_int + 1;
			int_signif = ColoredIntervalsStructure->Significance[bunch_old_number];
			int_density = (2 * int_signif) / int_length;
			residual = (2 * int_signif) % int_length;
			if (2 * residual > int_length)
			{
				int_density += 1;
			}
			bunch_inhabitant= painted_bunch_intensities[center_coor/4];
			bunch_inhabitant_intensity= intensity_consistency[center_coor / 4];
			if (bunch_inhabitant > 0)
			{
				bunch_inhabitant -= 1;
				bunch_inhabitant_beg = ColoredIntervalsStructure->BegInterv[bunch_inhabitant];
				bunch_inhabitant_end = ColoredIntervalsStructure->EndInterv[bunch_inhabitant];
				bunch_inhabitant_length = bunch_inhabitant_end - bunch_inhabitant_beg + 1;
				bunch_inhabitant_satur = ColoredIntervalsStructure ->AverageSat[bunch_inhabitant];
				bunch_inhabitant_signif= ColoredIntervalsStructure->Significance[bunch_inhabitant];
				inhabitant_int_density = (2 * bunch_inhabitant_signif) / int_length;
				residual = (2 * bunch_inhabitant_signif) % bunch_inhabitant_length;
				if (2 * residual > bunch_inhabitant_length)
				{
					inhabitant_int_density += 1;
				}
			}
			else
			{
				bunch_inhabitant = -1;
			}
			if (!Disordering)
			{
				if ((bunch_ordered_number) || (bunch_old_number == first_in_ordering_old_number))
				{//included in the lattice
					included_in_the_lattice = bunch_ordered_number+1;
				}//included in the lattice
			}
			if (!included_in_the_lattice)
			{//0

				if ((strip_ratio <= 2) && (int_length <= ((3 * StripWidth) / 2)) && (bunch_sat <= 3))
				{
					red_signal_car = -1;
				}
				if ((strip_ratio <= 6) && (int_length <= 6) && (bunch_sat <= 1) && (int_density <= 4))
				{
					red_signal_car = -1;
				}

				if ((strip_ratio <= 5) && ((int_density <= 3) || ((bunch_sat <= 1) &&
					(((int_density <= 7) && (int_length <= StripWidth / 2)) ||
					(int_density <= 6)))))
				{
					red_signal_car = -1;
				}

				if ((strip_ratio <= 9) && (int_length <= 6) && (bunch_sat <= 1) && (int_density <= 3) && (bunch_gray_zone >= 3))
				{
					red_signal_car = -1;
				}
				if ((strip_ratio <= 4) && (bunch_sat <= 1) && (bunch_gray_zone >= 2) && (bunch_gray_zone <= 4))
				{
					red_signal_car = -1;
				}
				if ((strip_ratio <= 5) && (bunch_sat <= 2) && (bunch_gray_zone <= 1))
				{
					red_signal_car = -1;
				}
				if ((strip_ratio <= 6) && (bunch_sat <= 2) && (bunch_gray_zone <= 1) && ((int_length <= 5)))
				{
					red_signal_car = -1;
				}
				if ((strip_ratio <= 6) && (bunch_sat <= 1) && (bunch_gray_zone >= 5) && (int_density <= 3))
				{
					red_signal_car = -1;
				}
				if ((bunch_gray <= 8) && (int_length <= 5) && (int_density <= 3) && (bunch_sat <= 4) && (bunch_hue_zone == 5))
				{
					red_signal_car = -1;
				}
				if ((bunch_gray >= 11) && (int_length <= 3) && (int_density <= 3) && (bunch_sat <= 4) && (bunch_hue_zone == 5))
				{//last_cor22.02.18
					red_signal_car = -1;
				}
				if ((bunch_gray >= 11) && (int_length <= 3) && (int_density <= 3) && (bunch_sat <= 1) && (bunch_hue_zone == 1))
				{//last_cor22.02.18
					red_signal_car = -1;
				}
				if (((bunch_hue_zone == 1) || (bunch_hue_zone == 5)) && (red_signal_car > 0))
				{//red
					if (bunch_gray >= 6)
					{//bg4
						if (((bunch_hue_zone == 5) && (bunch_hue >= 40) && (bunch_sat >= 4) && (bunch_gray >= 10)) ||
							((bunch_hue_zone == 5) && (bunch_hue >= 41) && (bunch_sat >= 3) && (bunch_gray >= 15)) ||
							(bunch_hue_zone == 1) && ((bunch_sat >= 3)
								|| ((bunch_sat >= 2) && ((bunch_gray_zone >= 2) || (bunch_gray >= 8)))
								|| ((bunch_sat >= 1) && ((bunch_gray_zone >= 2) && (bunch_gray >= 16)))))
						{
							if ((int_length <= (dimX / 16)) && (beg_int > dimX / 8) && (end_int < (dimX - dimX / 8)))
							{
								prior++;
								*(MarkingSignal + count_bunch1) = 1;
				if (NumberOfRedFeaturesCandidates < 16)
				{
				NumberOfSignals[NumberOfRedFeaturesCandidates] = bunch_old_number + 1;
				}
								NumberOfRedFeaturesCandidates++;
							}
						}
					}//bg4
				}//red

			}//0
			
				if (int_length <= (dimG / 10))
				{//roadMarking
					if (strip_number >= NumStrip / 6)
					{
						if ((end_int > dimG - StripWidth / 2) || (beg_int<StripWidth / 2))
						{
							if (int_length >= (dimG / 16))
							{
								goto K;
							}
						}
					}
					if ((bunch_sat <= 2)||((bunch_hue_zone==2)&&(bunch_sat >= 3)))
					{//white_yellow_road_marking
						if (!included_in_the_lattice)
						{//0
							if ((bunch_sat <= 2) && (bunch_inhabitant_satur <= 2)&&
								(bunch_inhabitant>=0))
							{
								if (bunch_old_number != bunch_inhabitant)
								{
if ((beg_int >= bunch_inhabitant_beg) && (end_int <= bunch_inhabitant_end)&&
(bunch_inhabitant_length<dimG/16))
{
	if (int_density < inhabitant_int_density)
	{
		goto K;
}
}
								}
							}
							if (!Disordering)
							{
comparison_result = ComparisonWithTheSurroundings(beg_int/4, end_int/4, 
	bunch_old_number,included_in_the_lattice);
if (comparison_result == 1)
{
	*(MarkingSignal + count_bunch1) = 2;
	
	if (NumberOfWhiteMarkingCandidates < 16)
	{
		ListOfWhiteMarking[NumberOfWhiteMarkingCandidates] = bunch_old_number+1;//last_cor27.02.19
	}
	NumberOfWhiteMarkingCandidates++;
}
else
{
	if (comparison_result == 2)
	{
		*(MarkingSignal + count_bunch1) = 3;
		if (NumberOfYellowMarkingCandidates < 16)
		{
			ListOfYellowMarking[NumberOfYellowMarkingCandidates] = bunch_old_number + 1;//last_cor27.02.19
		}
		NumberOfYellowMarkingCandidates++;
	}
}
							}
						}//0
						else
						{
							if (!Disordering)
							{
								
comparison_result = ComparisonWithTheSurroundings(beg_int / 4, end_int / 4,
									bunch_old_number, included_in_the_lattice);
if (comparison_result == 1)
{
	*(MarkingSignal + count_bunch1) = 2;
	if (NumberOfWhiteMarkingCandidates < 16)
	{
		ListOfWhiteMarking[NumberOfWhiteMarkingCandidates] = bunch_old_number + 1;//last_cor27.02.19
	}
	NumberOfWhiteMarkingCandidates++;
}
else
{
	if (comparison_result == 2)
	{
		*(MarkingSignal + count_bunch1) = 3;
		if (NumberOfYellowMarkingCandidates < 16)
		{
			ListOfYellowMarking[NumberOfYellowMarkingCandidates] = bunch_old_number + 1;//last_cor27.02.19
		}
		NumberOfYellowMarkingCandidates++;
	}
}
							}
						}
					}//white_road_marking
					/*if ((bunch_hue_zone >= 3) && (bunch_hue_zone <= 6))
					{//yellow_marking
						if (bunch_sat >= 3)
						{//bs
							if (bunch_gray_zone >= 2)
							{//bgz
								if (!included_in_the_lattice)
								{//0
									if (!Disordering)
									{
										;
									}
								}//0
								else
								{
									;
								}
							}//bgz
						}//bs
				}//yellow_marking*/
			}//roadMarking

		K:;
		}//bunch_loop1
	return(prior);
}
//===================================================
int

CColorIntervalSelect::ComparisonWithTheSurroundings(int beg_search, int end_search, 
	int bunch_number, int lattice_feature)
{
	int prior;
	int left_oppos_bound;
	int right_oppos_bound;
	int loop_first;
	int loop_last;
	int first_bunch_old_num;
	int old_count_bunch;
	int old_count_bunch_beg;
	int old_count_bunch_end;
	int old_count_bunch_length;
	int old_count_bunch_m_gray;
	int old_count_bunch_min_gray;
	int old_count_bunch_max_gray;
	int count_shift_gray;
	int old_count_bunch_min_gray_sim;
	int old_count_bunch_max_gray_sim;
	int old_count_bunch_m_hue;
	int old_count_bunch_m_sat;
	int old_count_bunch_hue_zone;
	int old_count_bunch_gray_zone;
	int bunch_hue;
	int bunch_sat;
	int bunch_gray;
	int bunch_l_gray;
	int bunch_m_gray;
	int bunch_hue_zone;
	int bunch_gray_zone;
	int beg_int;
	int end_int;
	int int_length;
	int shift_gray;
	int bunch_l_gray_sim;
	int bunch_m_gray_sim;
	int gray_intersection;
	int minimum_gray_intersection;
	int greater;
	int length_ratio;
	int minimum_length_ratio;
	int minimum_length_ratio1;
	int length_ratio1;
	int interval_intersection;
	int interv_greater;
	int interv_length_ratio;
	int interv_length_ratio1;
	int number_of_adjacent;
	int bunch_signif;
	int bunch_density;
	int count_bunch_signif;
	int count_bunch_density;
	int density_ratio;
	int number_of_covering_bunches;
	int length_ratio_of_intervals;
	int lattice_sign;
	int mean_gray_jump;
	int minimum_mean_gray_jump;
	int mean_hue_jump;
	int mean_sat_jump;
	int minumum_mean_hue_jump;
	int minumum_mean_sat_jump;
	int hue_zone_jump;
	int minumum_mean_hue_zone_jump;
	int min_gray_vicinity;
	int max_gray_vicinity;
	int min_gray_vicinity1;
	int max_gray_vicinity1;
	int maximum_density_ratio;
	int maximum_density_ratio1;
	int mean_gray_jump1;
	int minimum_mean_gray_jump1;
	int mean_hue_jump1;
	int mean_sat_jump1;
	int minumum_mean_hue_jump1;
	int minumum_mean_sat_jump1;
	int hue_zone_jump1;
	int minumum_mean_hue_zone_jump1;
	int distinction_left;
	int distinction_right;
	int minimum_gray_intersection1;

	minimum_mean_gray_jump1 = NUM_INTEN;
	maximum_density_ratio1 = 0;
	minimum_length_ratio1 = 0;
	minimum_gray_intersection1 = 0;
	distinction_left=0;
	distinction_right=0;
	maximum_density_ratio = 0;
	min_gray_vicinity = 64;
	max_gray_vicinity = 0;
	min_gray_vicinity1 = 64;
	max_gray_vicinity1 = 0;
	hue_zone_jump = 0;
	minumum_mean_hue_zone_jump = 0;
	minumum_mean_sat_jump = 16;
	minumum_mean_hue_jump = NUM_HUES;
	mean_sat_jump = 0;
	mean_hue_jump = 0;
	hue_zone_jump1 = 0;
	minumum_mean_hue_zone_jump1 = 0;
	minumum_mean_sat_jump1 = 16;
	minumum_mean_hue_jump1 = NUM_HUES;
	mean_sat_jump1 = 0;
	mean_hue_jump1 = 0;
	lattice_sign = -1;
	minimum_gray_intersection = 8;
	minimum_length_ratio = dimG;
	length_ratio_of_intervals = -1;
	length_ratio = -1;
	bunch_signif = 0;
	bunch_density = 0;
	count_bunch_signif = 0;
	count_bunch_density = 0;
	density_ratio= - 1;
	number_of_adjacent = 0;
	length_ratio = 0;
	length_ratio1 = 0;
	greater = -1;
		left_oppos_bound = -1;
	right_oppos_bound = -1;
	loop_first = -1;
	loop_last = -1;
	old_count_bunch = -1;
	prior = 0; 
	if (!Disordering)
	{
		number_of_covering_bunches = NumberOfIntervalsInCovering;
	}
	else
	{
		number_of_covering_bunches = -1;
	}
	if (!Disordering)
	{
		if (!lattice_feature)
		{//lf0
			first_bunch_old_num = old_ordered_bunch_number[0];
			left_oppos_bound = painted_strip_colored[beg_search];
			right_oppos_bound = painted_strip_colored[end_search];
			if (left_oppos_bound > 0)
			{
				left_oppos_bound -= 1;
			}
			else
			{
				left_oppos_bound = -1;
			}
			if (right_oppos_bound > 0)
			{
				right_oppos_bound -= 1;
			}
			else
			{
				right_oppos_bound = -1;
			}
			if ((left_oppos_bound >= 0) && (right_oppos_bound >= 0))
			{
				loop_first = ordered_bunch_number[left_oppos_bound];
				loop_last = ordered_bunch_number[right_oppos_bound];
			}
			if (!loop_first)
			{
				if (left_oppos_bound != first_bunch_old_num)
				{
					loop_first = -1;
				}
			}
			if (!loop_last)
			{
				if (right_oppos_bound != first_bunch_old_num)
				{
					loop_last = -1;
				}
			}
		}//lf0
		else
		{
			if (lattice_feature > 0)
			{
				lattice_feature -= 1;
				loop_last = min((number_of_covering_bunches - 1), (lattice_feature + 2));
				loop_first = max((lattice_feature - 2), 0);
				lattice_sign = 1;
			}
			else
			{
				lattice_sign = -1;
			}
		}
		if ((loop_first >= 0) && (loop_last >= 0))
		{//cond
			number_of_adjacent = loop_last - loop_first + 1;
			bunch_hue = ColoredIntervalsStructure->AverageHue[bunch_number];
			bunch_sat = ColoredIntervalsStructure->AverageSat[bunch_number];
			bunch_gray = ColoredIntervalsStructure->AverageGray[bunch_number];
			bunch_signif = ColoredIntervalsStructure->Significance[bunch_number];
			bunch_l_gray = ColoredIntervalsStructure->LowerGrayscale[bunch_number];
			bunch_m_gray = ColoredIntervalsStructure->UpperGrayscale[bunch_number];
			shift_gray = min((bunch_gray - bunch_l_gray), (bunch_m_gray - bunch_gray));
			bunch_l_gray_sim = bunch_gray - shift_gray;
			bunch_m_gray_sim = bunch_gray + shift_gray;
			bunch_hue_zone = hue_zones[bunch_hue];
			bunch_gray_zone = gray_zones[bunch_gray];
			beg_int = ColoredIntervalsStructure->BegInterv[bunch_number];
			end_int = ColoredIntervalsStructure->EndInterv[bunch_number];
			int_length = end_int - beg_int + 1;
			bunch_density = (bunch_signif << 2) / int_length;
			
			if ((bunch_density <= 6) && (strip_number <= NumStrip / 4) && (int_length < StripWidth))
			{
				return(prior);
			}
			if ((bunch_density > 12) && (strip_number >= NumStrip / 3) && (int_length > 8*StripWidth))
			{
				return(prior);
			}
	if ((bunch_density >= 12) && (strip_number <= NumStrip / 6)
				&& (int_length > 3 * StripWidth) && (bunch_sat <= 2) && (end_int >= (dimG - StripWidth) && (bunch_gray<45)))
			{
				return(prior);
			}
			minimum_mean_gray_jump = NUM_INTEN;
			minimum_mean_gray_jump1 = NUM_INTEN;
			hue_zone_jump = 0;
			minumum_mean_hue_zone_jump = 8;
			minumum_mean_sat_jump = 16;
			minumum_mean_hue_jump = NUM_HUES;
			mean_sat_jump = 16;
			mean_hue_jump = NUM_HUES;
			hue_zone_jump1 = 0;
			minumum_mean_hue_zone_jump1 = 8;
			minumum_mean_sat_jump1 = 16;
			minumum_mean_hue_jump1 = NUM_HUES;
			mean_sat_jump1 = 16;
			mean_hue_jump1 = NUM_HUES;
			if (lattice_sign < 0)
			{//ls<0
			for (int count_bunch = loop_first; count_bunch <= loop_last; count_bunch++)
			{//bunch_loop
				
				old_count_bunch = old_ordered_bunch_number[count_bunch];
				old_count_bunch_beg = ColoredIntervalsStructure->BegInterv[old_count_bunch];
				old_count_bunch_end = ColoredIntervalsStructure->EndInterv[old_count_bunch];
				old_count_bunch_length = old_count_bunch_end - old_count_bunch_beg + 1;
				length_ratio_of_intervals = (16 * int_length) / (int_length + old_count_bunch_length);
				old_count_bunch_m_gray = ColoredIntervalsStructure->AverageGray[old_count_bunch];
				count_bunch_signif = ColoredIntervalsStructure->Significance[old_count_bunch];
				count_bunch_density = (count_bunch_signif << 2) / old_count_bunch_length;
				density_ratio = (16 * bunch_density) / (bunch_density + count_bunch_density);
				if (density_ratio > maximum_density_ratio)
				{
					maximum_density_ratio = density_ratio;
				}
				old_count_bunch_min_gray = ColoredIntervalsStructure->LowerGrayscale[old_count_bunch];
				old_count_bunch_max_gray = ColoredIntervalsStructure->UpperGrayscale[old_count_bunch];
				count_shift_gray =
					min((old_count_bunch_m_gray - old_count_bunch_min_gray), (old_count_bunch_max_gray - old_count_bunch_m_gray));
				old_count_bunch_min_gray_sim = old_count_bunch_m_gray - count_shift_gray;
				old_count_bunch_max_gray_sim = old_count_bunch_m_gray + count_shift_gray;
				old_count_bunch_m_hue = ColoredIntervalsStructure->AverageHue[old_count_bunch];
				old_count_bunch_m_sat = ColoredIntervalsStructure->AverageSat[old_count_bunch];
				old_count_bunch_hue_zone = hue_zones[old_count_bunch_m_hue];
				old_count_bunch_gray_zone = gray_zones[old_count_bunch_m_gray];
				mean_hue_jump = abs(old_count_bunch_m_hue - bunch_hue);
				hue_zone_jump = abs(old_count_bunch_hue_zone - bunch_hue_zone);
				mean_sat_jump = bunch_sat - old_count_bunch_m_sat;
				mean_gray_jump = bunch_gray - old_count_bunch_m_gray;
				if (old_count_bunch_min_gray_sim < min_gray_vicinity)
				{
					min_gray_vicinity = old_count_bunch_min_gray_sim;
				}
				if (old_count_bunch_max_gray_sim > max_gray_vicinity)
				{
					max_gray_vicinity = old_count_bunch_max_gray_sim;
				}
				if (mean_gray_jump < minimum_mean_gray_jump)
				{
					minimum_mean_gray_jump = mean_gray_jump;
				}
				gray_intersection =
					Intersection_measure_ratios(bunch_l_gray_sim, bunch_m_gray_sim, old_count_bunch_min_gray_sim,
						old_count_bunch_max_gray_sim, &greater, &length_ratio, &length_ratio1);
				if (gray_intersection < minimum_gray_intersection)
				{
					minimum_gray_intersection = gray_intersection;
				}
				if (gray_intersection == 3)
				{
					if (length_ratio < minimum_length_ratio)
					{
						minimum_length_ratio = length_ratio;
					}
				}
				interval_intersection =
					Intersection_measure_ratios(old_count_bunch_beg, old_count_bunch_end,
						beg_int, end_int, &interv_greater, &interv_length_ratio, &interv_length_ratio1);
				if ((bunch_hue_zone == 2) && (bunch_sat >= 3))
				{
					if (mean_sat_jump < minumum_mean_sat_jump)
					{
						minumum_mean_sat_jump = mean_sat_jump;
					}
					if (mean_hue_jump < minumum_mean_hue_jump)
					{
						minumum_mean_hue_jump = mean_hue_jump;
					}
					if (hue_zone_jump < minumum_mean_hue_zone_jump)
					{
						minumum_mean_hue_zone_jump = hue_zone_jump;
					}
				}

			}//bunch_loop
			//if (lattice_sign < 0)
			//{//ls<0
				if (loop_first == loop_last)
				{//first=last
					if ((gray_intersection == 3) && (length_ratio >= 6) && (mean_gray_jump > 8))
					{
						if ((interv_length_ratio <= 4) && (interv_length_ratio1 >= 14))
						{
							if ((old_count_bunch_m_sat <= 2) && (bunch_sat <= 1) && (bunch_gray_zone >= 5))
							{
								prior = 1;
                            }
						}
					}
					if ((gray_intersection == 3) && (length_ratio >= 2) && (mean_gray_jump > 0))
					{
						if (((old_count_bunch_beg <= dimG / 4) ||
							(old_count_bunch_end > (dimG - dimG / 4))) ||
							((interv_length_ratio <= 1)) ||
							((old_count_bunch_length >= (dimG / 8)) && (interv_length_ratio <= 2)))
						{//lengthcond
							if (old_count_bunch_m_sat <= 3)
							{
								if (interv_length_ratio1 == 16)
								{
									if ((bunch_sat <= 2) && (bunch_gray_zone >= 4))
									{
										prior = 1;
									}

								}
							}
						}//lengthcond
					}
					if (((bunch_hue_zone == 2) || ((bunch_hue >= 6) && (bunch_hue <= 8) && (bunch_gray_zone >= 5))
						|| (bunch_hue == 2))
						&& (bunch_sat >= 3))
					{
						if (minumum_mean_sat_jump >= 2)
						{
							if ((minimum_mean_gray_jump >= 5) && (gray_intersection > 0))
							{
								if (((bunch_sat >= 4) && (bunch_gray_zone >= 3)) ||
									((bunch_sat >= 3) && (bunch_gray_zone >= 4)) ||
									((bunch_sat >= 6) && (bunch_gray_zone >= 2)))
								{
									prior = 2;
								}
							}
						}
						if (!prior)
						{
							if ((minumum_mean_hue_zone_jump >= 2) ||
								((minumum_mean_hue_jump > 2) && (minumum_mean_hue_zone_jump == 1)))
							{
								if (((bunch_sat >= 4) && (bunch_gray_zone >= 3)) ||
									((bunch_sat >= 3) && (bunch_gray_zone >= 4)) ||
									((bunch_sat >= 6) && (bunch_gray_zone >= 2)))
								{
									prior = 2;
								}
							}
						}
					}
				}//first=last
				else
				{
					if ((bunch_sat <= 1)&&(maximum_density_ratio<=4))
					{
						if ((minimum_gray_intersection >= 2) && (minimum_mean_gray_jump >= 4))
						{
							if (bunch_gray_zone >= 6)
							{
								prior = 1;
								return(prior);
							}
                        }
					}

					if (bunch_sat <= 2)
					{
						if ((minimum_gray_intersection == 3) && (minimum_mean_gray_jump > 0) &&
							(minimum_length_ratio >= 2))
						{
							if (bunch_gray_zone >= 4)
							{
								prior = 1;
								return(prior);
							}
						}
					}
					else
					{
						if (((bunch_hue_zone == 2) || ((bunch_hue > 6) && (bunch_hue <= 8) && (bunch_gray_zone >= 5))
							|| (bunch_hue == 2))
							&& (bunch_sat >= 3))
						{
							if (minumum_mean_sat_jump >= 2)
							{
								if (minimum_mean_gray_jump >= 3)
								{
									if (((bunch_sat >= 4) && (bunch_gray_zone >= 3)) ||
										((bunch_sat >= 3) && (bunch_gray_zone >= 4)) ||
										((bunch_sat >= 6) && (bunch_gray_zone >= 2)))
									{
										prior = 2;
										return(prior);
									}
								}
							}
							
								if ((minumum_mean_hue_zone_jump >= 2) ||
									((minumum_mean_hue_jump > 2) && (minumum_mean_hue_zone_jump == 1)))
								{
									if (((bunch_sat >= 4) && (bunch_gray_zone >= 3)) ||
										((bunch_sat >= 3) && (bunch_gray_zone >= 4)) ||
										((bunch_sat >= 6) && (bunch_gray_zone >= 2)))
									{
										prior = 2;
										return(prior);
									}
								}
							
						}
					}
				}
			}//ls<0
			else
			{//e<

				for (int count_bunch = lattice_feature -1; count_bunch >= loop_first; count_bunch--)
				{//bunch_loop					
					old_count_bunch = old_ordered_bunch_number[count_bunch];
					old_count_bunch_beg = ColoredIntervalsStructure->BegInterv[old_count_bunch];
					old_count_bunch_end = ColoredIntervalsStructure->EndInterv[old_count_bunch];
					old_count_bunch_length = old_count_bunch_end - old_count_bunch_beg + 1;
					length_ratio_of_intervals = (16 * int_length) / (int_length + old_count_bunch_length);
					old_count_bunch_m_gray = ColoredIntervalsStructure->AverageGray[old_count_bunch];
					count_bunch_signif = ColoredIntervalsStructure->Significance[old_count_bunch];
					count_bunch_density = (count_bunch_signif << 2) / old_count_bunch_length;
					density_ratio = (16 * bunch_density) / (bunch_density + count_bunch_density);
					if (density_ratio > maximum_density_ratio)
					{
						maximum_density_ratio = density_ratio;
					}
					old_count_bunch_min_gray = ColoredIntervalsStructure->LowerGrayscale[old_count_bunch];
					old_count_bunch_max_gray = ColoredIntervalsStructure->UpperGrayscale[old_count_bunch];
					count_shift_gray =
						min((old_count_bunch_m_gray - old_count_bunch_min_gray), (old_count_bunch_max_gray - old_count_bunch_m_gray));
					old_count_bunch_min_gray_sim = old_count_bunch_m_gray - count_shift_gray;
					old_count_bunch_max_gray_sim = old_count_bunch_m_gray + count_shift_gray;
					old_count_bunch_m_hue = ColoredIntervalsStructure->AverageHue[old_count_bunch];
					old_count_bunch_m_sat = ColoredIntervalsStructure->AverageSat[old_count_bunch];
					old_count_bunch_hue_zone = hue_zones[old_count_bunch_m_hue];
					old_count_bunch_gray_zone = gray_zones[old_count_bunch_m_gray];
					mean_hue_jump = abs(old_count_bunch_m_hue - bunch_hue);
					hue_zone_jump = abs(old_count_bunch_hue_zone - bunch_hue_zone);
					mean_sat_jump = bunch_sat - old_count_bunch_m_sat;
					mean_gray_jump = bunch_gray - old_count_bunch_m_gray;
					if (old_count_bunch_min_gray_sim < min_gray_vicinity)
					{
						min_gray_vicinity = old_count_bunch_min_gray_sim;
					}
					if (old_count_bunch_max_gray_sim > max_gray_vicinity)
					{
						max_gray_vicinity = old_count_bunch_max_gray_sim;
					}
					if (mean_gray_jump < minimum_mean_gray_jump)
					{
						minimum_mean_gray_jump = mean_gray_jump;
					}
					gray_intersection =
						Intersection_measure_ratios(bunch_l_gray_sim, bunch_m_gray_sim, old_count_bunch_min_gray_sim,
							old_count_bunch_max_gray_sim, &greater, &length_ratio, &length_ratio1);
					if (gray_intersection < minimum_gray_intersection)
					{
						minimum_gray_intersection = gray_intersection;
					}
					if (gray_intersection == 3)
					{
						if (length_ratio < minimum_length_ratio)
						{
							minimum_length_ratio = length_ratio;
						}
					}
					interval_intersection =
						Intersection_measure_ratios(old_count_bunch_beg, old_count_bunch_end,
							beg_int, end_int, &interv_greater, &interv_length_ratio, &interv_length_ratio1);
					if ((bunch_hue_zone == 2) && (bunch_sat >= 3))
					{
						if (mean_sat_jump < minumum_mean_sat_jump)
						{
							minumum_mean_sat_jump = mean_sat_jump;
						}
						if (mean_hue_jump < minumum_mean_hue_jump)
						{
							minumum_mean_hue_jump = mean_hue_jump;
						}
						if (hue_zone_jump < minumum_mean_hue_zone_jump)
						{
							minumum_mean_hue_zone_jump = hue_zone_jump;
						}
					}
					if ((hue_zone_jump) || ((!hue_zone_jump) && 
						(mean_sat_jump >= 2)&&(bunch_hue>=2)&&(bunch_hue<=7)))
					{
						if ((bunch_sat >= 2) && ((bunch_hue >= 2) && (bunch_hue <= 7)))
						{
							distinction_left = 1;
							break;
						}
					}
					if ((mean_gray_jump > 0)&&(bunch_sat <= 2)&&(bunch_gray_zone>=4))
					{
						distinction_left = 1;
						break;
					}
					if (length_ratio_of_intervals <= 5)
					{
						break;
					}
				}//bunch_loop
				for (int count_bunch = lattice_feature + 1; count_bunch <= loop_last; count_bunch++)
				{//bunch_loop					
					old_count_bunch = old_ordered_bunch_number[count_bunch];
					old_count_bunch_beg = ColoredIntervalsStructure->BegInterv[old_count_bunch];
					old_count_bunch_end = ColoredIntervalsStructure->EndInterv[old_count_bunch];
					old_count_bunch_length = old_count_bunch_end - old_count_bunch_beg + 1;
					length_ratio_of_intervals = (16 * int_length) / (int_length + old_count_bunch_length);
					old_count_bunch_m_gray = ColoredIntervalsStructure->AverageGray[old_count_bunch];
					count_bunch_signif = ColoredIntervalsStructure->Significance[old_count_bunch];
					count_bunch_density = (count_bunch_signif << 2) / old_count_bunch_length;
					density_ratio = (16 * bunch_density) / (bunch_density + count_bunch_density);
					if (density_ratio > maximum_density_ratio1)
					{
						maximum_density_ratio1 = density_ratio;
					}
					old_count_bunch_min_gray = ColoredIntervalsStructure->LowerGrayscale[old_count_bunch];
					old_count_bunch_max_gray = ColoredIntervalsStructure->UpperGrayscale[old_count_bunch];
					count_shift_gray =
						min((old_count_bunch_m_gray - old_count_bunch_min_gray), (old_count_bunch_max_gray - old_count_bunch_m_gray));
					old_count_bunch_min_gray_sim = old_count_bunch_m_gray - count_shift_gray;
					old_count_bunch_max_gray_sim = old_count_bunch_m_gray + count_shift_gray;
					old_count_bunch_m_hue = ColoredIntervalsStructure->AverageHue[old_count_bunch];
					old_count_bunch_m_sat = ColoredIntervalsStructure->AverageSat[old_count_bunch];
					old_count_bunch_hue_zone = hue_zones[old_count_bunch_m_hue];
					old_count_bunch_gray_zone = gray_zones[old_count_bunch_m_gray];
					mean_hue_jump1 = abs(old_count_bunch_m_hue - bunch_hue);
					hue_zone_jump1 = abs(old_count_bunch_hue_zone - bunch_hue_zone);
					mean_sat_jump1 = bunch_sat - old_count_bunch_m_sat;
					mean_gray_jump1 = bunch_gray - old_count_bunch_m_gray;
					if (old_count_bunch_min_gray_sim < min_gray_vicinity1)
					{
						min_gray_vicinity1 = old_count_bunch_min_gray_sim;
					}
					if (old_count_bunch_max_gray_sim > max_gray_vicinity1)
					{
						max_gray_vicinity1 = old_count_bunch_max_gray_sim;
					}
					if (mean_gray_jump1 < minimum_mean_gray_jump1)
					{
						minimum_mean_gray_jump1 = mean_gray_jump1;
					}
					gray_intersection =
						Intersection_measure_ratios(bunch_l_gray_sim, bunch_m_gray_sim, old_count_bunch_min_gray_sim,
							old_count_bunch_max_gray_sim, &greater, &length_ratio, &length_ratio1);
					if (gray_intersection < minimum_gray_intersection1)
					{
						minimum_gray_intersection1 = gray_intersection;
					}
					if (gray_intersection == 3)
					{
						if (length_ratio < minimum_length_ratio1)
						{
							minimum_length_ratio1 = length_ratio;
						}
					}
					interval_intersection =
						Intersection_measure_ratios(old_count_bunch_beg, old_count_bunch_end,
							beg_int, end_int, &interv_greater, &interv_length_ratio, &interv_length_ratio1);
					if ((bunch_hue_zone == 2) && (bunch_sat >= 3))
					{
						if (mean_sat_jump1 < minumum_mean_sat_jump1)
						{
							minumum_mean_sat_jump1 = mean_sat_jump1;
						}
						if (mean_hue_jump1 < minumum_mean_hue_jump1)
						{
							minumum_mean_hue_jump1 = mean_hue_jump1;
						}
						if (hue_zone_jump1 < minumum_mean_hue_zone_jump1)
						{
							minumum_mean_hue_zone_jump1 = hue_zone_jump1;
						}
					}
					if ((hue_zone_jump1) || ((!hue_zone_jump1) &&
						(mean_sat_jump1 >= 2) && (bunch_hue >= 2) && (bunch_hue <= 7)))
					{
						if ((bunch_sat >= 2) && ((bunch_hue >= 2) && (bunch_hue <= 7)))
						{
							distinction_right = 1;
							break;
						}
					}
					if ((mean_gray_jump1 > 0) && (bunch_sat <= 2) && (bunch_gray_zone >= 4))
					{
						distinction_right = 1;
						break;
					}
					if (length_ratio_of_intervals <= 5)
					{
						break;
					}
				}//bunch_loop
				if (bunch_sat <= 2)
				{
					if ((minimum_gray_intersection == 3) && (minimum_mean_gray_jump > 0) &&
						(minimum_length_ratio >= 2))
					{
						if (bunch_gray_zone >= 4)
						{
							prior = 1;
							return(prior);
						}
					}
				}
				else
				{
					if (minumum_mean_sat_jump >= 2)
					{
						if ((minimum_mean_gray_jump >= 3)||(minumum_mean_sat_jump>=3))
						{
							if (((bunch_sat >= 4) && (bunch_gray_zone >= 3)) ||
								((bunch_sat >= 3) && (bunch_gray_zone >= 4)) ||
								((bunch_sat >= 6) && (bunch_gray_zone >= 2)))
							{
								prior = 2;
								return(prior);
							}
						}
					}
					
						if (((bunch_hue_zone == 2) || ((bunch_hue >= 6) && (bunch_hue <= 8) && (bunch_gray_zone >= 5))
							|| (bunch_hue == 2))
							&& (bunch_sat >= 3))
						{
							if ((minumum_mean_hue_zone_jump >= 2) ||
								((minumum_mean_hue_jump > 2) && (minumum_mean_hue_zone_jump == 1)))
							{
								if (((bunch_sat >= 4) && (bunch_gray_zone >= 3)) ||
									((bunch_sat >= 3) && (bunch_gray_zone >= 4)) ||
									((bunch_sat >= 6) && (bunch_gray_zone >= 2)))
								{
									prior = 2;
									return(prior);
								}
							}
						}
					
				}
			}//e<
		}//cond
	}//!Disord
	else 
	{
		;
	}
	return(prior);
}
