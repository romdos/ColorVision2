//
//
//
//
//



#include "stdafx.h"
#include "ColorVision.h"
#include "RoadMarking.h"







#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define HORIZONT1 0
//#define LENGTH 16
#define TRUE 1



Marking::Marking()
{
	isValid = false;
}


Marking::~Marking()
{}



/*
 * @Description:
 *      Sum left deviations.
 * @Return value:
 *
 */
float Marking::left_curvature()
{
	// TODO: 
	return 0.0f;
}



/*
 * @Description:
 *      Sums 1+cos(xi), where xi -- angle between (xi-1, xi) and (xi, xi+1) vectors.
 * @Return value:
 *
 */
float Marking::right_curvature()
{
	// TODO: 
	return 0.0f;
}















static  int hue_zones[NUM_HUES] = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
5, 1, 1, 1, 1, 1 };
static  int dev_hue_zone[6] = { 2, 2, 2, 2, 2, 2 };
static  int dev_mean_sat[16] = { 1, 1, 1, 1, 1, 2, 3, 4, 4, 4, 4, 4, 3, 2, 1, 0 };
static  int dev_mean_sat1[16] = { 0, 1, 1, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4 };
static  int imp_dev_mean_sat[16] = { 3, 3, 3, 4, 5, 5, 6, 6, 6, 6, 6, 5, 4, 4, 4, 4 };
static  int imp_dev_mean_sat1[16] = { 1, 2, 2, 3, 3, 3, 3, 4, 5, 5, 5, 6, 6, 7, 6, 6 };

static  int gray_zones[NUM_INTEN1] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2,
2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7 };//last_cor05.06.15
																	  //0. 0-6, 1. 7-12, 2. 13-21, 3. 22-30, 4. 31-39, 5. 40-49, 6. 50-57, 7. 58-63

																	  //static  int dev_mean[8] = {5, 8, 8, 10, 10, 10, 12, 8};
static  int dev_mean[8] = { 5, 8, 8, 8, 8, 10, 12, 8 };

//static  int imp_dev_mean[8] = {14, 16, 18, 18, 16, 16, 14, 12};
static  int imp_dev_mean[8] = { 12, 12, 12, 12, 12, 12, 12, 12 };//last_cor03.12.14



void CColorSection::RoadMarkingSequences(int left_right_boundary, int* marking_trace,int color)
{
	int previous_strip, start_strip, nex_fibre;
	int mem_strip, mem_beg_grain;
	int new_mem_beg_grain;
	int new_beginning;
	int member;
	int next_value;
	int new_next_value;
	//int next_grain_inten;
	int gay, count_of_displacement;
	int counting_of_fibres, coun_strips, run_prev;
	int trace, new_trace;
	int NumberOfBunches;
	int num_strp;
	int bunch_signif;
	int beg_int;
	int end_int;
	int Strwidth;
	int first_signif;
	int prolong_step;
	int first_member_number;
	//int first_density;
	TIntColored* ColoredIntervalsStructure;


	new_mem_beg_grain = -1;
	first_member_number = -1;
	LeftRightBoundary = left_right_boundary;
	StripLength = ColorInterval[0].StripLength;
	StripWidth = ColorInterval[0].StripWidth;//last_cor15.05.14
	prolong_step = -1;


	trace_of_marking = marking_trace;
	if (!LeftRightBoundary)
	{
		trace_of_marking1 = trace_of_marking;
	}
	memset(trace_of_marking, (int) '\0', sizeof(int)*(Num_Strips)*16);
	
	start_strip = 0;
	gay = 0;
	next_value = -1;
	new_beginning = 0;
	
	while (TRUE)
	{
		if (Number_of_markings >= NUM_YELLOW_WHITE_MARKING)
		{
			goto wrap;
		}
		if (!color)
		{
			if (!LeftRightBoundary)
			{
				if (Number_of_yellow_markings_left >= NUM_YELLOW_WHITE_MARKING / 6)
				{
					goto wrap;
				}
			}
			else
			{
				if (Number_of_yellow_markings_right >= NUM_YELLOW_WHITE_MARKING / 6)
				{
					goto wrap;
				}
			}
		}
		else
		{

		}
		mem_strip = Num_Strips + 1;
		FirstMarkingHueZone = 0;
		FirstMarkingHue = -1;
		FirstMarkingSat = 0;
		FirstMarkingGray = -1;
		FirstMarkingGrayZone = -1;
		FirstMarkingDensity = -1;

		for (coun_strips = start_strip; coun_strips<Num_Strips - 1; coun_strips++)
		{//cs=strp
			
			first_member_number =
				RoadMarking_start(coun_strips, &trace_of_marking[coun_strips * 16],
					&new_beginning, LeftRightBoundary, color);
			if (first_member_number>=0)
			{//if
				mem_strip = coun_strips;
				mem_beg_grain = new_beginning;
				new_mem_beg_grain = ColorInterval[mem_strip].new_bunch_number[mem_beg_grain];
				FirstMarkingGrain = mem_beg_grain;
				FirstMarkingStrip = mem_strip;
				FirstMarkingHue = ColorInterval[mem_strip].ColoredIntervalsStructure->AverageHue[mem_beg_grain];
				FirstMarkingHueZone = hue_zones[FirstMarkingHue];
				FirstMarkingSat = ColorInterval[mem_strip].ColoredIntervalsStructure->AverageSat[mem_beg_grain];
				FirstMarkingGray = ColorInterval[mem_strip].ColoredIntervalsStructure->AverageGray[mem_beg_grain];
				FirstMarkingGrayZone = gray_zones[FirstMarkingGray];
				FirstMarkingBeg = ColorInterval[FirstMarkingStrip].ColoredIntervalsStructure->BegInterv[FirstMarkingGrain];//lc27.11.15
				FirstMarkingEnd = ColorInterval[FirstMarkingStrip].ColoredIntervalsStructure->EndInterv[FirstMarkingGrain];//lc27.11.15
				FirstMarkingLength = FirstMarkingEnd - FirstMarkingBeg + 1;
				first_signif = ColorInterval[FirstMarkingStrip].ColoredIntervalsStructure->Significance[FirstMarkingGrain];
				FirstMarkingDensity = (2 * first_signif) / FirstMarkingLength;
				TotalMarkingShift = 0;
				TotalMarkingJump = 0;
				MeanMarkingJump = 0;
				if ((mem_strip<(3 * Num_Strips) / 4) || (FirstMarkingDensity < StripWidth / 4))
					//if(mem_strip<(2*Num_Strips)/3)
				{//last_cor19.02.18
					break;
				}
				else
				{//last_cor27.03.17
					start_strip = mem_strip;
					goto conti;
				}//last_cor27.03.17
				break;
			}//if
			
		}//cs=strp
		/*if (first_member_number < 0)
		{
			goto wrap;
		}*/
		if (mem_strip>Num_Strips)
		{
			goto wrap;
		}

		nex_fibre = mem_strip + 1;
		previous_strip = mem_strip;
		counting_of_fibres = 1;
		count_of_displacement = 0;
		for (run_prev = 0; run_prev<Num_Strips - 1; run_prev++)
		{

			for (member = 0; member<Num_Strips; member++)
			{
				next_value = MaximalNumberOfBunches + 1;
				ColoredIntervalsStructure = ColorInterval[previous_strip].ColoredIntervalsStructure;
				Strwidth = ColorInterval[previous_strip].StripWidth;
				bunch_signif = ColoredIntervalsStructure->Significance[new_beginning];
				beg_int = ColoredIntervalsStructure->BegInterv[new_beginning];
				end_int = ColoredIntervalsStructure->EndInterv[new_beginning];
				bunch_signif = (2 * bunch_signif) / (end_int - beg_int + 1);
				gay = Continuation_of_roadmarking(new_beginning, &next_value, &prolong_step, previous_strip, nex_fibre, counting_of_fibres, color);

				if (gay>0)
				{//gay>0
					count_of_displacement = 0;
					trace = trace_of_marking[nex_fibre*16 + prolong_step];
					//trace=abs(trace);
					if (trace>0)
					{//tr>0
						new_trace = trace - 1;
						//new_trace = new_trace % 1000;//last_cor07.11.17
						//mrking_point_cross[Number_of_sections] = nex_fibre;
						//marking_out_connection[Number_of_sections] = trace;
						/*if (root_section[new_trace])
						{
							root_section[Number_of_sections] = root_section[new_trace];
						}
						else
						{
							root_section[Number_of_sections] = trace;
						}*/
						counting_of_fibres++;
						new_next_value = ColorInterval[nex_fibre].new_bunch_number[next_value];
Record_of_marking(nex_fibre,&trace_of_marking[nex_fibre*16],new_next_value, prolong_step, Number_of_markings);
End_of_marking(mem_strip, new_mem_beg_grain, Number_of_markings,
							nex_fibre, counting_of_fibres);
trace_of_marking[mem_strip * 16 + first_member_number] = Number_of_markings + 1;

						start_strip = mem_strip;
						Number_of_markings++;
						if (!color)
						{
							Number_of_yellow_markings++;
							if (!LeftRightBoundary)
							{
								Number_of_yellow_markings_left++;
							}
							else
							{
								Number_of_yellow_markings_right++;
							}
						}
						else
						{
							Number_of_white_markings++;
							if (!LeftRightBoundary)
							{
								Number_of_white_markings_left++;
							}
							else
							{
								Number_of_white_markings_right++;
							}
						}
						*(trace_of_marking + mem_strip*16 + prolong_step) =
							Number_of_markings;
						goto conti;
					}//tr>0
					counting_of_fibres++;
					new_next_value = ColorInterval[nex_fibre].new_bunch_number[next_value];
			Record_of_marking(nex_fibre,&trace_of_marking[nex_fibre*16],
			new_next_value, prolong_step, Number_of_markings);
					if ((nex_fibre + 1) >= Num_Strips)
					{//nf>=	
						if (new_mem_beg_grain >= 0)
						{
							End_of_marking(mem_strip, new_mem_beg_grain, Number_of_markings,
								nex_fibre, counting_of_fibres);
						}
			trace_of_marking[mem_strip * 16 + first_member_number] = Number_of_markings + 1;
						gay = 0;
						
						Number_of_markings++;
						if (!color)
						{
							Number_of_yellow_markings++;
							if (!LeftRightBoundary)
							{
								Number_of_yellow_markings_left++;
							}
							else
							{
								Number_of_yellow_markings_right++;
							}
						}
						else
						{
							Number_of_white_markings++;
							if (!LeftRightBoundary)
							{
								Number_of_white_markings_left++;
							}
							else
							{
								Number_of_white_markings_right++;
							}
						}
						
							*(trace_of_marking + mem_strip*16 + prolong_step) =
								Number_of_markings;

						start_strip = mem_strip;
						goto conti;
					}//nf>=
					previous_strip = nex_fibre;
					nex_fibre++;
					new_beginning = next_value;
					break;
				}//g>0
				else
				{
					ColoredIntervalsStructure = ColorInterval[previous_strip].ColoredIntervalsStructure;
					bunch_signif = ColoredIntervalsStructure->Significance[new_beginning];
					beg_int = ColoredIntervalsStructure->BegInterv[new_beginning];
					end_int = ColoredIntervalsStructure->EndInterv[new_beginning];
					bunch_signif = (2 * bunch_signif) / (end_int - beg_int + 1);
					if ((++nex_fibre >= Num_Strips) || (++count_of_displacement>HORIZONT1))
					{
						if (counting_of_fibres >= 2)
						{//cf
			End_of_marking(mem_strip, new_mem_beg_grain, Number_of_markings, previous_strip, counting_of_fibres);
			trace_of_marking[mem_strip * 16 + first_member_number] = Number_of_markings + 1;
							
			if (!color)
			{
				Number_of_yellow_markings++;
				if (!LeftRightBoundary)
				{
					Number_of_yellow_markings_left++;
				}
				else
				{
					Number_of_yellow_markings_right++;
				}
			}
			else
			{
				Number_of_white_markings++;
				if (!LeftRightBoundary)
				{
					Number_of_white_markings_left++;
				}
				else
				{
					Number_of_white_markings_right++;
				}
			}
							
							Number_of_markings++;
							
						}
						else
						{
							trace_of_marking[mem_strip * 16 + first_member_number] = -1;
						}
						start_strip = mem_strip;
						goto conti;
					}

				}
			}
		}
	conti:
		;
	}
wrap:;
}
/////////////////////////////////////////////////////////////////////////////////
int

CColorSection::RoadMarking_start(int strip_num, int *status_show, int *new_beg, int left_right_bound,int color)
{
	int foll;
	int foll_bunch;
	int success_of_seaching;
	int fibre_limit;
	//int left_cont;
	//int right_cont;
	//int direct_cont;
	//int beg;
	//int end;
	//int length;
	int left_right;
	//bool end_condition;
	//TIntColored* ColoredIntervalsStructure;

	//ColoredIntervalsStructure=ColorInterval[strip_num].ColoredIntervalsStructure;
	success_of_seaching = -1;
	left_right = left_right_bound;
	if (!color)
	{
	fibre_limit = min(ColorInterval[strip_num].NumberOfYellowMarkingCandidates,16);
	}
	else
	{
fibre_limit = min(ColorInterval[strip_num].NumberOfWhiteMarkingCandidates, 16);
	}

	for (foll = 0; foll<fibre_limit; foll++)
	{//follloop
		if (!color)
		{
foll_bunch = ColorInterval[strip_num].ListOfYellowMarking[foll];
		}
		else
		{
foll_bunch = ColorInterval[strip_num].ListOfWhiteMarking[foll];
		}
		if (foll_bunch > 0)
		{
			foll_bunch -= 1;
		}
		else
		{
			return(-1);
		}
			if (!*(status_show + foll))
			{
				*(status_show + foll) = -1;
					*new_beg = foll_bunch;
					success_of_seaching = foll;
					return(success_of_seaching);			
			}
	}//follloop
	return(success_of_seaching);
}
////////////////////////////////////////////////////////////////////////////////
int

CColorSection::Continuation_of_roadmarking(int prev_corn, int *prolongation_grain,
	int* prolongation_step, int previous_sec, int continuation_sec, int fiber_number, int color)
{
	int success_of_process;
	int number_bunches_continuations;
	int height_of_prolongation;
	int first_strip_ratio;
	int last_strip_ratio;
	int jump_sec;
	int beg_int;
	int end_int;
	int length_int;
	int strip_length;
	int number_of_fibers;
	int previous_fiber;
	int previous_bunch;
	int previous_bunch_beg;
	int previous_bunch_end;
	int signif_bunch;
	int density_bunch ;
	int bunch_mean_hue;
	int bunch_mean_hue_zone;
	int bunch_mean_sat;
	int bunch_mean_gray;
	int bunch_mean_zone;
	int bunch_occurrence;
	int bunch_new_occurrence;
	int occurrence_ratio;
	int bunch_ordered_number;
	int left_bunch_contrast;
	int right_bunch_contrast;
	int bunch_left_adjacent;
	int bunch_right_adjacent;
	int bunch_contrast;
	int bunch_opposite_contrast;
	int bunch_adjacent;
	int bunch_opposite_adjacent;
	int opposite_end_condition;
	int cycle_limit;
	int new_bunch;
	int signif_bunch_new;
	int density_bunch_new;
	int density_ratio;
	int density_ratio_first;
	int Intersection;
	int indic_length;
	int ratio_length, ratio_length1;
	int bunch_significance_ratio;
	int hue_new;
	int hue_zone_new;
	int sat_new;
	int gray_new;
	int gray_zone_new;
	int max_gray_zone;
	int difference_hue;
	int difference_gray;
	int difference_sat;
	int min_sat;
	int max_sat;
	int new_beg_int;
	int	new_end_int;
	int new_length_int;
	int length_int_ratio;
	int coinsidence; 
	int coinsidence1; 
	int shift_to_left; 
	int shift_to_right;
	int continuation_bunch;
	int continuation_bunch_beg;
	int continuation_bunch_end;
	int continuation_bunch_length;
	int continuation_bunch_sat;
	int continuation_bunch_hue;
	int continuation_bunch_gray;
	int continuation_bunch_density;
	int continuation_bunch_Intersection;
	int continuation_bunch_length_ratio;
	int continuation_bunch_length_ratio1;
	int continuation_bunch_n_f_incl;
	int continuation_bunch_n_c_incl;
	int continuation_bunch_n_f_c_f_ratio;
	int continuation_bunch_n_c_c_f_ratio;
	int inclination_current_first;
	int inclination_next_first;
	int inclination_current_next;
	int inclination_first_next_current_ratio;
	int	inclination_next_current_current_first_ratio;
	int trace;
	int continuation_step;
	int suitability_result;
	int min_gray_zone;
	int inclination_current_previous;
	int inclination_previous_first;
	int min_cont_ratio;
	int min_new_ratio;
	int continuation_bunch_length_int_ratio;
	int continuation_bunch_number;
	int Intersection1;
	int density_rat_prev;
	int length_rat_prev;
	int density_prev;
	int previous_bunch_length;
	int* bunch_new_visibility;
	int* bunch_visibility;
	TIntColored* ColoredIntervalsStructure;
	TIntColored* ColoredIntervalsStructure1;

	density_prev = 0;
	previous_bunch_length = 0;
	density_rat_prev = 0;
	length_rat_prev = 0;
	Intersection1 = -1;
	continuation_bunch_number = -1;
	continuation_bunch_length_int_ratio = -1;
	inclination_previous_first = 0;
	inclination_current_previous = 0;
	min_gray_zone = -1;
	inclination_current_first = 0;
	inclination_next_first = 0;
	continuation_bunch_n_f_incl=0;
	continuation_bunch_n_c_incl=0;
	continuation_bunch_n_f_c_f_ratio=0;
	continuation_bunch_n_c_c_f_ratio=0;
	suitability_result = -1;
	continuation_step = -1;
	inclination_first_next_current_ratio = -1;
	inclination_next_current_current_first_ratio = -1;
	continuation_bunch_Intersection = -1;
	continuation_bunch_length_ratio = -1;
	continuation_bunch_length_ratio1 = -1;
	continuation_bunch = -1;
	Intersection = -1;
	density_ratio_first = 0;
	new_bunch = -1;
	bunch_ordered_number= -1;
	left_bunch_contrast = 0;
	right_bunch_contrast = 0;
	bunch_left_adjacent = -1;
	bunch_right_adjacent = -1;
	bunch_contrast = 0;
	bunch_opposite_contrast = 0;
	bunch_adjacent = -1;
	bunch_opposite_adjacent = -1;
	previous_bunch_end = -1;
	previous_bunch_beg = -1;
	success_of_process = 0;
	if (!color)
	{
		number_bunches_continuations =
			ColorInterval[continuation_sec].NumberOfYellowMarkingCandidates;
	}
	else
	{
		number_bunches_continuations =
			ColorInterval[continuation_sec].NumberOfWhiteMarkingCandidates;
	}
	number_of_fibers = fiber_number;
	height_of_prolongation = (16 * continuation_sec) / Num_Strips;
	if (number_bunches_continuations == 0)
	{
		return(success_of_process);
	}
	first_strip_ratio = (16 * FirstMarkingStrip) / (Num_Strips + 1);
	last_strip_ratio = (16 * continuation_sec) / (Num_Strips + 1);
	jump_sec = continuation_sec - previous_sec;

	bunch_new_visibility = ColorInterval[continuation_sec].visible_bunches;
	bunch_visibility = ColorInterval[previous_sec].visible_bunches;
	ColoredIntervalsStructure = ColorInterval[previous_sec].ColoredIntervalsStructure;
	ColoredIntervalsStructure1 =
		ColorInterval[continuation_sec].ColoredIntervalsStructure;
	beg_int = ColoredIntervalsStructure->BegInterv[prev_corn];
	end_int = ColoredIntervalsStructure->EndInterv[prev_corn];
	length_int = end_int - beg_int + 1;
	strip_length = previous_sec - FirstMarkingStrip + 1;//last_cor03.02.17
	if (jump_sec>0)
	{//js
		if (number_of_fibers >= 2)
		{//>=2
			previous_fiber = previous_sec - 1;//!!!if jumps are not available
			if (number_of_fibers == 2)
			{
				previous_bunch = FirstMarkingGrain;
				previous_bunch =
	ColorInterval[previous_fiber].new_bunch_number[previous_bunch];
			}
			else
			{

previous_bunch = DescrMarking[Number_of_markings].location_of_section[previous_fiber];
				if (previous_bunch > 0)
				{
					previous_bunch -= 1;
				}

			}
			if (previous_bunch >= 0)
			{//last_cor10.09.18	
				if (number_of_fibers >= 2)
				{
					previous_bunch = ColorInterval[previous_fiber].old_bunch_number[previous_bunch];
				}
previous_bunch_beg =
ColorInterval[previous_fiber].ColoredIntervalsStructure->BegInterv[previous_bunch];
previous_bunch_end =
ColorInterval[previous_fiber].ColoredIntervalsStructure->EndInterv[previous_bunch];
previous_bunch_length = previous_bunch_end - previous_bunch_beg + 1;
density_prev = ColorInterval[previous_fiber].ColoredIntervalsStructure ->Significance[previous_bunch];
density_prev = (2*density_prev)/previous_bunch_length;
if (!LeftRightBoundary)
{
	inclination_previous_first =
		(previous_bunch_beg - FirstMarkingBeg);
}
else
{
	inclination_previous_first =
		(previous_bunch_end - FirstMarkingEnd);
}
			}//last_cor10.09.18
		}//n>=2
		}//js
	signif_bunch = ColoredIntervalsStructure->Significance[prev_corn];
	density_bunch = (2 * signif_bunch) / length_int;
	bunch_mean_hue = ColoredIntervalsStructure->AverageHue[prev_corn];
	bunch_mean_hue_zone = hue_zones[bunch_mean_hue];
	if (bunch_mean_hue >= NUM_HUES)
	{
		bunch_mean_hue -= NUM_HUES;
	}
	bunch_mean_sat = ColoredIntervalsStructure->AverageSat[prev_corn];
	bunch_mean_gray = ColoredIntervalsStructure->AverageGray[prev_corn];
	bunch_mean_zone = gray_zones[bunch_mean_gray];
	bunch_occurrence = *(bunch_visibility + prev_corn);
	if (bunch_occurrence > 0)
	{//bo>
		bunch_ordered_number = ColorInterval[previous_sec].ordered_bunch_number[prev_corn];
		left_bunch_contrast = ColorInterval[previous_sec].left_continuation[prev_corn];
		left_bunch_contrast = left_bunch_contrast % 10;
		right_bunch_contrast = ColorInterval[previous_sec].right_continuation[prev_corn];
		right_bunch_contrast = right_bunch_contrast % 10;
		bunch_left_adjacent = ColorInterval[previous_sec].left_adjacent[prev_corn];
		bunch_right_adjacent = ColorInterval[previous_sec].right_adjacent[prev_corn];

		if (!LeftRightBoundary)
		{
			bunch_contrast = left_bunch_contrast;
			bunch_opposite_contrast = right_bunch_contrast;
			bunch_adjacent = bunch_left_adjacent;
			bunch_opposite_adjacent = bunch_right_adjacent;
			if (end_int == (StripLength - 1))
			{
				opposite_end_condition = 0;
			}
		}
		else
		{
			bunch_contrast = right_bunch_contrast;
			bunch_opposite_contrast = left_bunch_contrast;
			bunch_adjacent = bunch_right_adjacent;
			bunch_opposite_adjacent = bunch_left_adjacent;
			if (!beg_int)
			{
				opposite_end_condition = 0;
			}
		}
	}//bo>
	cycle_limit = number_bunches_continuations;
	min_cont_ratio = -1;
	min_new_ratio = -1;
	for (int next_coun = 0; next_coun < cycle_limit; next_coun++)
	{//c1
		if (!color)
		{
			new_bunch = ColorInterval[continuation_sec].ListOfYellowMarking[next_coun];
		}
		else
		{
			new_bunch = ColorInterval[continuation_sec].ListOfWhiteMarking[next_coun];
		}
if (new_bunch > 0)
{//newf>
	new_bunch -= 1;
	trace = *(trace_of_marking + 16 * continuation_sec + next_coun);
	if (trace != 0)
	{
		goto L;
	}
	bunch_new_occurrence = *(bunch_new_visibility + new_bunch);
	hue_new = ColoredIntervalsStructure1->AverageHue[new_bunch];
	difference_hue = abs(hue_new - bunch_mean_hue);//last_cor03.02.17
	hue_zone_new = hue_zones[hue_new];
	gray_new = ColoredIntervalsStructure1->AverageGray[new_bunch];
	gray_zone_new = gray_zones[gray_new];
	max_gray_zone = max(gray_zone_new, bunch_mean_zone);
	min_gray_zone = min(gray_zone_new, bunch_mean_zone);
	sat_new = ColoredIntervalsStructure1->AverageSat[new_bunch];
	difference_gray = abs(gray_new- bunch_mean_gray);
	difference_sat = abs(sat_new - bunch_mean_sat);
	min_sat = min(bunch_mean_sat, sat_new);
	max_sat = max(bunch_mean_sat, sat_new);
	new_beg_int = ColoredIntervalsStructure1->BegInterv[new_bunch];
	new_end_int = ColoredIntervalsStructure1->EndInterv[new_bunch];
	new_length_int = new_end_int - new_beg_int + 1;
	if (continuation_bunch >= 0)
	{
		if ((new_beg_int >= continuation_bunch_beg) && (new_end_int <= continuation_bunch_end))
		{
			*(trace_of_marking + 16 * continuation_sec + next_coun) = Number_of_markings + 1;;
			goto L;
		}
		if (((new_beg_int > continuation_bunch_beg) && (new_beg_int < continuation_bunch_end)) ||
			((new_end_int > continuation_bunch_beg) && (new_end_int < continuation_bunch_end)))
		{
			Intersection1 = Measure1_of_proximity(new_beg_int, new_end_int, continuation_bunch_beg,
	continuation_bunch_end, &coinsidence, &coinsidence1, &shift_to_left, &shift_to_right, &indic_length,
				&ratio_length, &ratio_length1);
			if (((ratio_length >= 8) && (!indic_length)&&(ratio_length1<=5))||
				((!Intersection1)&&(ratio_length>=13)&&(ratio_length1>=13)))
			{
				*(trace_of_marking + 16 * continuation_sec + next_coun) = Number_of_markings + 1;;
				goto L;
			}
		}
	}
	length_int_ratio = (16 * new_length_int) / (new_length_int + length_int);
	signif_bunch_new = ColoredIntervalsStructure1->Significance[new_bunch];
	density_bunch_new = (2 * signif_bunch_new) / new_length_int;
	density_ratio = (16* density_bunch_new)/(density_bunch_new + density_bunch);
	Intersection = Measure1_of_proximity(beg_int, end_int, new_beg_int,
		new_end_int, &coinsidence, &coinsidence1, &shift_to_left, &shift_to_right, &indic_length,
		&ratio_length, &ratio_length1);
	
	if ((Intersection == 3)&&(ratio_length>2*StripWidth))
	{
		goto L;
	}
	if (!LeftRightBoundary)
	{
		inclination_current_next = new_beg_int - beg_int;
		inclination_next_first =
			(new_beg_int - FirstMarkingBeg);
		inclination_current_previous = -1000;
	}
	else
	{
		inclination_current_next = new_end_int - end_int;
		inclination_next_first =
			(new_end_int - FirstMarkingEnd);
		inclination_current_previous = -1000;
	}
	if ((density_bunch_new >= StripWidth) && (density_bunch <= StripWidth / 2))
	{
		if ((bunch_occurrence > 0) && (bunch_new_occurrence > 0) &&
(bunch_new_occurrence > 2 * bunch_occurrence)&&(bunch_new_occurrence>=10))
		{
			if (length_int_ratio >= 8)
			{
				if (continuation_sec >= NumStrips / 6)
				{
					goto L;
				}
			}
}
	}
	if (number_of_fibers >= 2)
	{//nf>=2
		density_ratio_first = 
			(16 * density_bunch_new) / (density_bunch_new + FirstMarkingDensity);
		if (!LeftRightBoundary)
		{
			inclination_current_first = 
				(beg_int - FirstMarkingBeg)/(number_of_fibers - 1);
			inclination_next_first =
				(new_beg_int - FirstMarkingBeg) / (number_of_fibers);
			inclination_current_previous =
				(beg_int - previous_bunch_beg);
			density_rat_prev = (16 * density_bunch_new) / (density_bunch_new + density_prev);
			length_rat_prev = (16 * new_length_int) / (new_length_int + previous_bunch_length);
			
		}
		else
		{
			inclination_current_first =
				(end_int - FirstMarkingEnd) / (number_of_fibers - 1);
			inclination_next_first =
				(new_end_int - FirstMarkingEnd) / (number_of_fibers);
			inclination_current_previous =
				(end_int - previous_bunch_end);
			
		}
		inclination_first_next_current_ratio = (16 * abs(inclination_next_first)) /
			(abs(inclination_current_first) + abs(inclination_next_first) + 1);
		inclination_next_current_current_first_ratio =
			(16 * abs(inclination_current_next)) /
			(abs(inclination_current_next) + abs(inclination_current_first) + 1);
		if ((abs(inclination_current_first) > StripWidth) &&
			((inclination_first_next_current_ratio >= 11) ||
			(inclination_first_next_current_ratio <= 5)))
		{
			goto L;
		}
	}//nf>=2
	
		if (continuation_bunch < 0)
		{//cb<
			if (!color)
			{
				
				suitability_result = 
					Test_Suitability_Yellow(continuation_sec, Intersection,
					ratio_length, bunch_occurrence, bunch_new_occurrence, length_int_ratio,
						inclination_first_next_current_ratio, inclination_next_current_current_first_ratio,
						density_ratio, inclination_current_first, inclination_next_first, inclination_current_previous,
						difference_sat, difference_gray, min_sat, max_sat, number_of_fibers, min_gray_zone);
				
			}
			else
			{
				
			suitability_result =
			Test_Suitability_White(LeftRightBoundary, continuation_sec, beg_int, end_int, new_beg_int, new_end_int,
			previous_bunch_beg, previous_bunch_end, Intersection, ratio_length, bunch_occurrence, 
			bunch_new_occurrence,length_int_ratio, length_rat_prev, inclination_first_next_current_ratio,
			inclination_next_current_current_first_ratio, density_ratio, density_rat_prev, 
			inclination_current_first, inclination_next_first, inclination_current_previous, inclination_current_next, 
			difference_sat, difference_gray, min_sat, max_sat, number_of_fibers, min_gray_zone);
				
			}

if (suitability_result > 0)
{
	continuation_bunch_number = next_coun;
	continuation_bunch = new_bunch;
	continuation_bunch_beg = new_beg_int;
	continuation_bunch_end = new_end_int;
	continuation_bunch_length = new_length_int;
	continuation_bunch_length_int_ratio = length_int_ratio;
	continuation_bunch_sat = sat_new;
	continuation_bunch_hue = hue_new;
	continuation_bunch_gray = gray_new;
	continuation_bunch_density = density_bunch_new;
	continuation_bunch_Intersection = Intersection;
	continuation_bunch_length_ratio = ratio_length;
	continuation_bunch_length_ratio1 = ratio_length1;
	min_cont_ratio = min(ratio_length, ratio_length1);
	continuation_step = next_coun;
	continuation_bunch_n_f_incl = inclination_next_first;
	continuation_bunch_n_c_incl = inclination_current_next;
	continuation_bunch_n_f_c_f_ratio = inclination_first_next_current_ratio;
	continuation_bunch_n_c_c_f_ratio = inclination_next_current_current_first_ratio;
	success_of_process = 1;
}
		}//cb<
		else
		{
			suitability_result =
				Test_Suitability_White(LeftRightBoundary, continuation_sec, beg_int, end_int, new_beg_int, new_end_int,
					previous_bunch_beg, previous_bunch_end, Intersection, ratio_length, bunch_occurrence,
					bunch_new_occurrence, length_int_ratio, length_rat_prev, inclination_first_next_current_ratio,
					inclination_next_current_current_first_ratio, density_ratio, density_rat_prev,
					inclination_current_first, inclination_next_first, inclination_current_previous, inclination_current_next,
					difference_sat, difference_gray, min_sat, max_sat, number_of_fibers, min_gray_zone);
			if (suitability_result > 0)
			{
				if ((continuation_bunch_n_c_c_f_ratio <= 4) && (inclination_next_current_current_first_ratio >= 7) &&
					(inclination_next_current_current_first_ratio <= 9))
				{
if((length_int_ratio >= 4) && (length_int_ratio <= 9))
{
	if ((density_ratio >= 5) && (density_ratio <= 9))
	{
		*(trace_of_marking + 16 * continuation_sec + continuation_bunch_number) = Number_of_markings + 1;
		continuation_bunch_number = next_coun;
		continuation_bunch = new_bunch;
		continuation_bunch_beg = new_beg_int;
		continuation_bunch_end = new_end_int;
		continuation_bunch_length = new_length_int;
		continuation_bunch_length_int_ratio = length_int_ratio;
		continuation_bunch_sat = sat_new;
		continuation_bunch_hue = hue_new;
		continuation_bunch_gray = gray_new;
		continuation_bunch_density = density_bunch_new;
		continuation_bunch_Intersection = Intersection;
		continuation_bunch_length_ratio = ratio_length;
		continuation_bunch_length_ratio1 = ratio_length1;
		min_cont_ratio = min(ratio_length, ratio_length1);
		continuation_step = next_coun;
		continuation_bunch_n_f_incl = inclination_next_first;
		continuation_bunch_n_c_incl = inclination_current_next;
		continuation_bunch_n_f_c_f_ratio = inclination_first_next_current_ratio;
		continuation_bunch_n_c_c_f_ratio = inclination_next_current_current_first_ratio;
		success_of_process = 1;
		goto L;
	}
}
				}
				min_new_ratio = min(ratio_length, ratio_length1);
				if (((continuation_bunch_Intersection >= 0) && (continuation_bunch_Intersection < 3) &&
					(Intersection >= 0) && (Intersection < 3))||
					((continuation_bunch_Intersection==3)&& (Intersection >= 0) && (Intersection < 3)))
				{
					if (min_new_ratio > min_cont_ratio)
					{
						if ((length_int_ratio >= 7) && (length_int_ratio <= 9) &&
							(length_int_ratio > continuation_bunch_length_int_ratio))
						{
							if ((density_ratio >= 6) && (density_ratio <= 11))
							{
								if (abs(continuation_bunch_n_c_c_f_ratio - 8) <= 2)
								{
									*(trace_of_marking + 16 * continuation_sec + continuation_bunch_number) = Number_of_markings + 1;
									continuation_bunch_number = next_coun;
									continuation_bunch = new_bunch;
									continuation_bunch_beg = new_beg_int;
									continuation_bunch_end = new_end_int;
									continuation_bunch_length = new_length_int;
									continuation_bunch_length_int_ratio = length_int_ratio;
									continuation_bunch_sat = sat_new;
									continuation_bunch_hue = hue_new;
									continuation_bunch_gray = gray_new;
									continuation_bunch_density = density_bunch_new;
									continuation_bunch_Intersection = Intersection;
									continuation_bunch_length_ratio = ratio_length;
									continuation_bunch_length_ratio1 = ratio_length1;
									min_cont_ratio = min(ratio_length, ratio_length1);
									continuation_step = next_coun;
									continuation_bunch_n_f_incl = inclination_next_first;
									continuation_bunch_n_c_incl = inclination_current_next;
									continuation_bunch_n_f_c_f_ratio = inclination_first_next_current_ratio;
									continuation_bunch_n_c_c_f_ratio = inclination_next_current_current_first_ratio;
									success_of_process = 1;
									goto L;
                                 }
							}
						}
						if ((difference_gray) <= (abs(continuation_bunch_gray - bunch_mean_gray)+4))
						{
							if ((length_int_ratio >= continuation_bunch_length_int_ratio)||
								((length_int_ratio>=7)&&(length_int_ratio<=9)&&(continuation_bunch_Intersection == 3))
								||((abs(inclination_next_current_current_first_ratio-8)<
								(abs(continuation_bunch_n_c_c_f_ratio-8)))))
							{
	*(trace_of_marking + 16 * continuation_sec + continuation_bunch_number) = Number_of_markings + 1;
	                            continuation_bunch_number = next_coun;
								continuation_bunch = new_bunch;
								continuation_bunch_beg = new_beg_int;
								continuation_bunch_end = new_end_int;
								continuation_bunch_length = new_length_int;
								continuation_bunch_length_int_ratio = length_int_ratio;
								continuation_bunch_sat = sat_new;
								continuation_bunch_hue = hue_new;
								continuation_bunch_gray = gray_new;
								continuation_bunch_density = density_bunch_new;
								continuation_bunch_Intersection = Intersection;
								continuation_bunch_length_ratio = ratio_length;
								continuation_bunch_length_ratio1 = ratio_length1;
								min_cont_ratio = min(ratio_length, ratio_length1);
								continuation_step = next_coun;
								continuation_bunch_n_f_incl = inclination_next_first;
								continuation_bunch_n_c_incl = inclination_current_next;
								continuation_bunch_n_f_c_f_ratio = inclination_first_next_current_ratio;
								continuation_bunch_n_c_c_f_ratio = inclination_next_current_current_first_ratio;
								success_of_process = 1;
								goto L;

							}

                        }
					}

				}
			}
		}

		
		
}//newf>
L:;
	}//c1
	if (success_of_process > 0)
	{
* prolongation_grain = continuation_bunch;
*prolongation_step = continuation_step;
	}
	else
	{
	*prolongation_grain = -1;
	*prolongation_step = -1;
	}
	return(success_of_process);
}
///////////////////////////////////////////////////////////////////////////
void

CColorSection::Record_of_marking(int current_fibre, int* trace,
	int old_current_grain, int grain_number, int number_of_section)
{
	DescrMarking[number_of_section].location_of_section[current_fibre] = old_current_grain + 1;
	if (!trace[grain_number])
	{
		*(trace + grain_number) = number_of_section + 1;
	}
	return;
}
//////////////////////////////////////////////////////////////////////////////
void

CColorSection::End_of_marking(int first_strip, int first_grain,
	int section_numb, int last_strip, int count)
{
	DescrMarking[section_numb].location_of_section[first_strip] = first_grain + 1;
	DescrMarking[section_numb].length_of_section = count;
	DescrMarking[section_numb].base_first = first_strip;
	DescrMarking[section_numb].base_last = last_strip;
	return;
}
////////////////////////////////////////////////////////////
int

CColorSection::Test_Suitability_White(int left_right, int continuation_strip, int beg_in, int end_in,
	int beg_in_new, int end_in_new, int beg_int_prev, int end_int_prev, int Intersect, int rat_length,
	int bunch_occur, int bunch_occur_new, int length_int_rat, int length_rat_prev, int incl_f_n_c_r, int incl_n_c_c_f_r,
	int den_rat, int den_rat_prev, int incl_c_f, int incl_n_f, int incl_p_c, int incl_c_n, int differ_sat, int differ_gray,
	int min_sa, int max_sa, int num_of_strips, int min_gr_z)
{
	int success_of_process;
	int next_current_distance;
	int previos_current_distance;
	int int_length;
	int int_length_new;
	int min_length;
	int max_length;
	int inclination_previous_first;
	int incl_ratio_first_p_p_c;
	int right_end;

	incl_ratio_first_p_p_c = 0;
	inclination_previous_first = 1000;
	success_of_process = 0;
	int_length = end_in - beg_in + 1;
	int_length_new = end_in_new - beg_in_new + 1;
	min_length = min(int_length, int_length_new);
	max_length = max(int_length, int_length_new);
	if (num_of_strips >= 2)
	{
		if ((abs(incl_c_n - incl_p_c) >= 2 * StripWidth)&&(num_of_strips>=4)&&(beg_int_prev>StripWidth))
		{
			return(success_of_process);
		}
	}

	if (beg_int_prev >= 0)
	{
		if (!left_right)
		{
			inclination_previous_first =
				(beg_int_prev - FirstMarkingBeg) / (continuation_strip - 1);

		}
		else
		{
			inclination_previous_first =
				(end_int_prev - FirstMarkingEnd) / (continuation_strip - 1);

		}
		if ((inclination_previous_first != 0) || (incl_p_c != 0))
		{
			incl_ratio_first_p_p_c = (32 * abs(inclination_previous_first)) /
				(abs(inclination_previous_first) + abs(incl_p_c));
		}
		else
		{
			incl_ratio_first_p_p_c = 16;
		}
	}
	if (!left_right)
	{
		next_current_distance = beg_in_new - beg_in;
		previos_current_distance = beg_in - beg_int_prev;
		right_end = beg_in;
	}
	else
	{
		next_current_distance = end_in_new - end_in;
		previos_current_distance = end_in - end_int_prev;
		right_end = end_in;
	}
	if (num_of_strips == 1)
	{
		if (right_end < DimX / 6)
		{
		if (incl_n_f < -StripWidth / 2)
		{
			return(success_of_process);
       }
       }
		if (right_end > (DimX - DimX / 6))
		{
		if (incl_n_f > StripWidth / 2)
		{
			return(success_of_process);
		}
	   }
		if (((right_end > StripWidth) &&(right_end < (DimX / 6)))||((right_end > (5*DimX) / 6)&&
			(right_end<(DimX-StripWidth))))
		{
			if (abs(incl_c_n) < StripWidth / 4)
			{
				return(success_of_process);
            }
		}
		if ((right_end < (DimX / 6)) && (continuation_strip >= NumStrips / 2)&&(right_end>StripWidth))
		{
			if (incl_c_n <= 0)
			{
				return(success_of_process);
			}
		}
		if ((right_end > (5*DimX) / 6) && (continuation_strip >= NumStrips / 2))
		{
			if (incl_c_n > 0)
			{
				return(success_of_process);
			}
		}
		if ((Intersect >= 0) && (Intersect < 3))
		{//bo2>
			if (bunch_occur > 0)
			{
				if (bunch_occur_new > 0)
				{
					if ((length_int_rat >= 5) && (length_int_rat <= 10))
					{
						if ((den_rat >= 6) && (den_rat <= 10))
						{
							success_of_process = 1;
							return(success_of_process);
						}
					}
				}
			}
		}//bo2>
		if ((Intersect >= 0) && (Intersect <= 2))
		{
			if ((length_int_rat >= 5) && (length_int_rat <= 10))
			{
				if ((den_rat >= 6) && (den_rat <= 10))
				{
					if (abs(incl_n_f) <= 4 * StripWidth)
					{
						success_of_process = 1;
						return(success_of_process);
					}
				}
			}
		}

	}
	else
	{
		if (num_of_strips >= 2)
		{//nf>=2
			if ((incl_p_c * incl_c_n) < 0)
			{
				if (beg_int_prev >= 0)
				{
					if ((previos_current_distance * incl_p_c) > 0)
					{
						if ((abs(previos_current_distance) >= StripWidth / 4)&&(abs(incl_p_c)>= StripWidth / 4))
						{

							if ((incl_ratio_first_p_p_c >= 13) && (incl_ratio_first_p_p_c <= 19))
							{
								success_of_process = -1;
								return(success_of_process);
                            }
                        }
                    }
				}
				if ((abs(next_current_distance) > max_length) && (Intersect == 3))
				{

					success_of_process = -1;
					return(success_of_process);

				}
			}
			if (((Intersect >= 0) && (Intersect < 3)) ||
				((incl_f_n_c_r >= 7) &&
				(incl_f_n_c_r <= 9)))
			{
				if (bunch_occur > 0)
				{//bo1>
					if (bunch_occur_new > 0)
					{//bo2>
						if ((length_int_rat >= 5) && (length_int_rat <= 10))
						{//lr
							if ((den_rat >= 4) && (den_rat <= 10))
							{
								if ((incl_c_f*incl_n_f > 0)&&(((incl_n_c_c_f_r>=6)&&(incl_n_c_c_f_r<=11))||
	((num_of_strips<=NumStrips/6)&&(Intersect >= 0) && (Intersect <= 1)&&(rat_length>=5))||
									((!Intersect)&&((incl_n_c_c_f_r >= 4) && (incl_n_c_c_f_r <= 12)))))
								{
									success_of_process = 1;
									return(success_of_process);
								}
								if ((!Intersect) && ((incl_c_f * incl_n_f > 0)))
								{
									if ((length_int_rat >= 6) && (length_int_rat <= 9))
									{//lr1
										if ((den_rat >= 7) && (den_rat <= 9))
										{
											if (differ_gray <= 4)
											{
												success_of_process = 1;
												return(success_of_process);
											}


										}
									}//lr1
								}
								if ((!Intersect) && (num_of_strips <= 4)&&
									(((incl_ratio_first_p_p_c>=14)&&(incl_ratio_first_p_p_c<=18))||
									(num_of_strips<=3)))
								{
									if ((length_int_rat >= 7) && (length_int_rat <= 9))
									{//lr1
										if ((den_rat >= 7) && (den_rat <= 9))
										{
											success_of_process = 1;
											return(success_of_process);
										}
									}//lr1
								}
								if ((Intersect>=0)&& (Intersect <=2) && (num_of_strips <= 4) &&
									(incl_ratio_first_p_p_c >= 14) && (incl_ratio_first_p_p_c <= 18))
								{
									if ((length_int_rat >= 7) && (length_int_rat <= 9))
									{//lr1
										if ((den_rat >= 7) && (den_rat <= 9))
										{
											success_of_process = 1;
											return(success_of_process);
										}
									}//lr1
								}

							}
						}//lr
						if ((incl_n_c_c_f_r >= 7) && (incl_n_c_c_f_r <= 9))
						{
							if ((Intersect >= 0) && (Intersect <= 2))
							{
								if ((length_int_rat >= 4) && (length_int_rat <= 11))
								{//lr
									if ((den_rat >= 3) && ((den_rat <= 11)||((Intersect >= 0) && (Intersect <= 1)&&
										(den_rat <= 12))))
									{
										success_of_process = 1;
										return(success_of_process);
									}
								}//lr
							}
						}
						if ((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9)&&(Intersect >= 0)&&(Intersect <= 2)&&
							(incl_n_c_c_f_r>=6)&&(incl_n_c_c_f_r<=10))
						{//incl
							if ((den_rat >= 3) && (den_rat <= 11))
							{
								if ((differ_sat <= 2) && ((min_sa <= 4) ||
									((max_sa <= 4) && (continuation_strip>Num_Strips / 6))))
								{
									if ((differ_gray <= 8)||(min_gr_z>=5))
									{
										if (incl_c_f*incl_n_f > 0)
										{
											success_of_process = 1;
											return(success_of_process);
										}
									}
								}
							}
						}//incl
					}//bo2>
					else
					{
						if ((incl_f_n_c_r == 8) ||
							((abs(incl_c_f - incl_n_f) <= StripWidth/2)) &&
							((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9))||
							((num_of_strips<=3)&&((length_int_rat>=7)&&
							(length_int_rat<=9)&&(den_rat>=7)&&(den_rat<=9))))
						{//incl1
							if (((incl_n_c_c_f_r >= 6) && (incl_n_c_c_f_r <= 10))||
								(abs(incl_c_f - incl_n_f) <=StripWidth))
							{
								if ((den_rat >= 4) && (den_rat <= 10))
								{
									if ((differ_sat <= 2) && ((min_sa <= 4) ||
										((max_sa <= 4) && (min_sa <= 2) &&
										(continuation_strip >= NumStrips / 6))))
									{//sat
										if ((differ_gray <= 8) || (min_gr_z >= 6))
										{
											if (incl_c_f*incl_c_n > 0)
											{
												success_of_process = 1;
												return(success_of_process);
											}
										}
									}//sat
								}
							}
						}//incl1
						if ((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9)&&(abs(incl_c_f - incl_n_f) <= StripWidth/4)&&
							((incl_ratio_first_p_p_c>=12)&&(incl_ratio_first_p_p_c<=19)))
						{
							if ((incl_n_c_c_f_r >= 6) && (incl_n_c_c_f_r <= 10) &&
								(abs(incl_c_f - incl_n_f) <= StripWidth / 4))
							{
								if ((Intersect >= 0) && (Intersect <= 2))
								{
									if ((den_rat >= 3) && (den_rat <= 12))
									{
										if ((differ_sat <= 1) && (min_sa <= 4))
										{
											if (incl_c_f * incl_c_n > 0)
											{
												success_of_process = 1;
												return(success_of_process);
											}
										}
									}

                                }
							}
						}
					}
				}//bo1>
				else
				{
				if ((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9))
				{
					if ((den_rat >= 7) && (den_rat <= 9))
					{
						if ((Intersect >= 0) && (Intersect < 2))
						{
							if ((differ_sat <= 2) && (min_sa <= 3))
							{//sat
								if ((differ_gray <= 8) || (min_gr_z >= 4))
								{
									if (incl_c_f * incl_n_f > 0)
									{
										if (incl_c_n * incl_c_f > 0)
										{
											success_of_process = 1;
											return(success_of_process);
										}
									}
								}
							}//sat
						}
					}
				}
				if ((incl_n_c_c_f_r >= 7) && (incl_n_c_c_f_r <= 9)&& (incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9))
				{
					if ((den_rat >= 5) && (den_rat <= 10)&& (length_int_rat >= 4) && (length_int_rat <= 11))
					{
						if (((Intersect >= 0) && (Intersect < 3))||
				((Intersect==3)&&((rat_length<StripWidth/4)||((rat_length<=max_length/2)&&(rat_length < StripWidth / 2)))))
						{
							if ((differ_sat <= 2) && (min_sa <= 3))
							{//sat
								if ((differ_gray <= 8) || (min_gr_z >= 4))
								{
									if (incl_c_f * incl_n_f > 0)
									{
										if (incl_c_n * incl_c_f > 0)
										{
											success_of_process = 1;
											return(success_of_process);
										}
									}
								}
							}//sat
						}
					}
					if ((abs(incl_c_f - incl_n_f) <= StripWidth / 4)&&(abs(incl_c_f - incl_n_f)<=2))
					{
						if (incl_c_f * incl_n_f > 0)
						{
							if (incl_c_n * incl_c_f > 0)
							{
								success_of_process = 1;
								return(success_of_process);
							}
						}
                    }
				}
					if ((!bunch_occur_new)||(((length_int_rat >= 7) && (length_int_rat <= 9))||
						((length_int_rat >= 4)&&(length_int_rat <= 11)&& (length_rat_prev >= 7) && (length_rat_prev <= 9))))
					{//bo20
						if (((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9)&& 
							((length_int_rat >= 5) && (length_int_rat <= 10))||
							((length_int_rat>=4)&&(length_int_rat<=12)&&(length_rat_prev>=7)&&(length_rat_prev<=9))))
						{//incl1))
							if (((Intersect >= 0) && (Intersect < 3)) || 
								((rat_length < StripWidth) && (Intersect == 3)&&(rat_length<max_length)))
							{
								if ((((den_rat >= 4) && (den_rat <= 10))||
									((den_rat >= 3) && (den_rat <= 12) && (den_rat_prev >= 7) && (den_rat_prev <= 9)))||
									((continuation_strip>=NumStrips/2)&&(Intersect >= 0) && (Intersect < 3)&&
									((den_rat >= 3) && (den_rat <= 12)||((den_rat_prev >= 7) && (den_rat_prev <= 9)))))
								{
									if ((differ_sat <= 2) && (min_sa <= 3))
									{//sat
										if ((differ_gray <= 12) || (min_gr_z >= 4))
										{
											if (incl_c_f*incl_n_f > 0)
											{
												if ((incl_c_n* incl_c_f>0)&&(incl_n_c_c_f_r >= 5) && (incl_n_c_c_f_r <= 12))
												{
													success_of_process = 1;
													return(success_of_process);
												}
											}
										}
									}//sat
								}
							}
							if (abs(incl_c_f) > 2 * StripWidth)
							{
								if (((Intersect >= 0) && (Intersect < 3)) ||
									((rat_length < (4 * StripWidth) / 3) && (Intersect == 3)))
								{
									if (((den_rat >= 4) && (den_rat <= 11)) ||
										((continuation_strip >= NumStrips / 2) && (Intersect >= 0) && (Intersect < 3) &&
										(den_rat >= 3) && (den_rat <= 12)))
									{
										if ((differ_sat <= 2) && (min_sa <= 3))
										{//sat
											if ((differ_gray <= 12) || (min_gr_z >= 5))
											{
												if (incl_c_f * incl_n_f > 0)
												{
													if ((incl_c_n * incl_c_f > 0) && (incl_n_c_c_f_r >= 5) && (incl_n_c_c_f_r <= 12))
													{
														success_of_process = 1;
														return(success_of_process);
													}
												}
											}
										}//sat
									}
								}
							}
						}//incl1
						if ((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9)&&(abs(incl_c_f - incl_n_f) <= StripWidth / 4))
						{
							if ((Intersect >= 0) && (Intersect <= 2))
							{
								if ((den_rat >= 4) && (den_rat <= 11))
								{
									if((incl_n_c_c_f_r >= 7)&&(incl_n_c_c_f_r<=9))
										if (incl_c_n * incl_c_f > 0)
										{
											success_of_process = 1;
											return(success_of_process);
										}
								}
							}
						}
						if ((Intersect >= 0) && (Intersect <= 1))
						{
							if ((length_int_rat >= 6) && (length_int_rat <= 10))
							{
								if ((den_rat >= 6) && (den_rat <= 11))
								{
									if (((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9))||
										(((incl_f_n_c_r >= 6) && (incl_f_n_c_r <= 10))&&(num_of_strips<=3)))
										if (incl_c_n * incl_c_f > 0)
										{
											success_of_process = 1;
											return(success_of_process);
										}
								}
							}
						}
					}//bo20
				}
			}
		}//nf>=2
	}
	return(success_of_process);

}
//////////////////////////////////////////////////////////////////
int

CColorSection::Test_Suitability_Yellow(int continuation_strip, int Intersect, int rat_length,
	int bunch_occur, int bunch_occur_new, int length_int_rat, int incl_f_n_c_r,
	int incl_n_c_c_f_r, int den_rat, int incl_c_f, int incl_n_f, int incl_p_c, int differ_sat, int differ_gray,
	int min_sa, int max_sa, int num_of_strips, int min_gr_z)
{
	int success_of_process;

	success_of_process = 0;
	if (num_of_strips == 1)
	{	
			if ((Intersect >= 0) && (Intersect < 3))
			{//bo2>
				if ((bunch_occur > 0) && (bunch_occur_new > 0))
				{
					if ((length_int_rat >= 5) && (length_int_rat <= 10))
					{
						if ((den_rat >= 5) && (den_rat <= 10))
						{
							success_of_process = 1;
							return(success_of_process);
						}
					}
				}
			}//bo2>
		
	}
	else
	{
		if (num_of_strips>=2)
		{//nf>=2
			if (((Intersect >= 0) && (Intersect < 3)) ||
				((incl_f_n_c_r >= 7) &&
				(incl_f_n_c_r <= 9)))
			{
				if (bunch_occur > 0)
				{//bo1>
					if (bunch_occur_new > 0)
					{//bo2>
						if ((length_int_rat >= 5) && (length_int_rat <= 10))
						{//lr
							if ((den_rat >= 6) && (den_rat <= 10))
							{
								if (incl_c_f*incl_n_f > 0)
								{
									success_of_process = 1;
									return(success_of_process);
								}

							}
						}//lr
						if ((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9))
						{//incl
							if ((den_rat >= 4) && (den_rat <= 10))
							{
								if ((differ_sat <= 2) && ((min_sa >= 3) ||
									((max_sa >= 3) && (continuation_strip>Num_Strips / 6))))
								{
									if (differ_gray <= 4)
									{
										if (incl_c_f*incl_n_f > 0)
										{
											success_of_process = 1;
											return(success_of_process);
										}
									}
								}
							}
						}//incl
					}//bo2>
					else
					{
						if ((incl_f_n_c_r == 8) ||
							((abs(incl_c_f - incl_n_f) <= num_of_strips)) &&
							((incl_f_n_c_r >= 7) &&	(incl_f_n_c_r <= 9)))
						{//incl1
							if ((incl_n_c_c_f_r >= 6) && (incl_n_c_c_f_r <= 10))
							{
								if ((den_rat >= 4) && (den_rat <= 10))
								{
									if ((differ_sat <= 2) && ((min_sa >= 3) ||
										((max_sa >= 3) && (min_sa >= 2) &&
										(continuation_strip >= NumStrips / 6))))
									{//sat
										if (differ_gray <= 6)
										{
											if (incl_c_f*incl_n_f > 0)
											{	
												success_of_process = 1;
												return(success_of_process);
											}
										}
									}//sat
								}
							}
						}//incl1
					}
				}//bo1>
				else
				{
					if (!bunch_occur_new)
					{//bo20
						if ((incl_f_n_c_r >= 7) && (incl_f_n_c_r <= 9))
						{//incl1))
							if (((Intersect >= 0) && (Intersect < 3)) || ((rat_length < StripWidth) && (Intersect == 3)))
							{
								if ((den_rat >= 6) && (den_rat <= 10))
								{
									if ((differ_sat <= 2) && ((max_sa >= 3) && (min_sa >= 2) &&
										(continuation_strip >= NumStrips / 6)))
									{//sat
										if (differ_gray <= 6)
										{
											if (incl_c_f*incl_n_f > 0)
											{
												
												success_of_process = 1;
												return(success_of_process);
											}
										}
									}//sat
								}
							}
						}//incl1
					}//bo20
				}
			}
		}//nf>=2
	}
	return(success_of_process);
}