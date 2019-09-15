//*************************************************************************************************  
// Interface for building grayscale bunches. 
//
//*************************************************************************************************

#pragma once

// To redefine basic types
#include "std_types.h"

// To store for bunches
#include <vector>




// created by K.I.
class CBunchGray
{
public:
	CBunchGray();
	~CBunchGray();

public:     
	int DimX;
	int DimY;
	int HorizontalVertical;
	int StripWidth; // width of a strip in pixels
    int StripWidthPrev; // width of the preceding strip
	int GapWidth;
	int MaxNumInt;
	int TotalNumInt;

	int PressedLength;
	int* IntervalIntensity;
	int* IntervalOldNumber;
	int* BackgroundClusters;
	int NumberOfBackgroundGrains;
	int* BackgroundGrains;
	int* BackgrGrainOldNumber;
	int NumberOflusters;
	int* ClusterGrains;
	int*  BegIntervOfClusters;   //pointer to the interval beginnings
    int*  EndIntervOfClusters;
    int*  GrainIntensityIntervalOfClusters;
    int*  LowerIntensityOfClusters;
    int*  UpperIntensityOfClusters;
    int*  AverageIntensityOfClusters;
    int*  SignificanceOfClusters;
    int*  CardinalityOfClusters;
		
	CStrip* StripCur; // pointer to the current strip

public:
	BOOL IntervalInteraction();

	void LimitIntervCalcFor(int* lower_int,int* upper_int,int* int_new_num);

	void LimitIntervCalcBack(int* lower_int,int* upper_int,int* int_new_num);

	void FindBoundaryIntervals(int* lower_int,int* upper_int,int n_fibre1,int n_fibre2,
int n_int1,int n_int2,int* int_new_num);

	void NegativeInitialization(int* lower_int,int* upper_int,int n_fibre,int n_int1,
int n_start,int* int_new_num);

	void BunchFinding();

	void Room_testing(int *IntervWeight,int* IntervNewNumber);

	void IntervalNumeration(int* IntervalNewNumber,int* IntervalIntensity,int* IntervalOldNumber);

	void ConnectedOrIsolated(int* con_isol,int* int_new_num);

	void LinkAdjacent(int* adjac_link,int* int_new_num,int* left_lower,int* left_upper,
int* right_lower,int* right_upper,int* inter_weight,int* inter_intens,int* inter_num,
int* con_isol,int* extended_signif);

	void IsolatedClustersLeft(int* cluster_number,int* int_properties,int* int_new_num,int* left_lower,int* left_upper,
int* right_lower,int* right_upper,int* inter_weight,int* inter_intens,int* inter_num);


    void ClusterizeRight(int inten,int num_interv,int new_number,int* int_properties,int* int_new_num,int* cluster_number,
int* right_lower,int* right_upper,int* inter_weight,int* inter_intens,int* inter_num,
int* continuation_num);

	int Intersection_measure(int beg_first,int end_first,int beg_second,int end_second,
int* greater,int* inter_compar1,int* inter_compar2,int* intersection_length);

	void ChainProcessing(int inten,int num_int,int num_steps,int* ListOfIntervals);

	void ClusterMembersAssignment(int num_clust,int number_of_members,int start_inten,int start_interval_number,
int start_new_nuw,int* ListOfIntervals,int* cluster_numbers,int* new_num);

	void LocalBackgroundFinding(int* interval_weigtht,int* lower_left,int* upper_left,
int* lower_right,int* upper_right,int* int_intensity,int* int_old_number,
int* interval_properties,int* new_num,int* local_signif_sum,int key);

	void LocalGrowing(int beg1,int end1,int dense1,int fibre,int lower_bound,int upper_bound,
int* best_fit,int* greater_adjacent,int* additional_signif);

	void ChainAssignment(int* record_list,int first_member,int chain_length);
	
	void FindingLocalBackgroundGrains(int* adjac_link,int* lower_left,int* upper_left,
int* lower_right,int* upper_right,int* int_intensity,int* int_old_number,
int* new_num,int* local_signif_sum,int* local_background,int* valuable_interv,int* value_of_place);
	
	void LocalComparison(int beg1,int end1,int signif,int fibre,int lower_bound,int upper_bound,
int* is_greater,int* new_num,int* exten_signif);
	
	void Strip_value_painting_secondary(int beg_int,int end_int,int num_int,int signif,
int* painted_strip_sc,int* intense_consistency_sc);
	


	void ArrangeIntervals(int* valuable_interval,int* visibility,int* local_signif_sum,
						int* local_background,int* interv_intensity,int* previous_number,int* lower_left,
						int* upper_left,int* lower_right,int* upper_right,int* adjac_link,int* new_number);



	int GrainsGrowing(int num_grain,int gr_intensity,int gr_prev_number,
						int adjacent_lower_interv,int adjacent_upper_interv,int beg_grain,int end_grain,
						int grain_dens0,int signif,int direct,int adj_link,int* new_num,int* local_signif_sum,
						int* added_signif,int* starting_cont_interv,int* finishing_cont_interv,
						int* joined_intervals,int* added_w_intens);



	int FindingIntervalsWithAdjacent(int last_member,int first_member,int direc, int* boundary_int);


	sint8 findBursts(uint16 max_length,
					uint8 depth);
};