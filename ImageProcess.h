/**
 * Segmentation function.
 * 
 * 
 * 
 */ 





#include "Strip.h"
#include "BunchGray.h"
#include "ColorIntervalSelect.h"
#include "ColorSection.h"






#if !defined(AFX_IMAGEPROCESS_H__E888F34A_F0CC_4849_8D36_78C688F32ADE__INCLUDED_)
#define AFX_IMAGEPROCESS_H__E888F34A_F0CC_4849_8D36_78C688F32ADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CImageProcess
{
public:
	CImageProcess(int TotalNumberofFrames);
	~CImageProcess();
	 
	int DimX;        // width  of the image in pixels
	int DimY;        // height of the image in pixels

	int TotalNumFrame;
	int LengthofMotionAnalysisInterval;
	int TotalDisOrdering;
	
	bool FindLabels;
	
	int LabelCenterCoordinate;
	int LabelLeftCoordinate;
	int LabelRightCoordinate;
	int LabelCenterHue;
	int LabelHueZone;
	int LabelCenterSaturation;
	int LabelFirstStrip;
	int    LabelLastStrip;
	int    LabelCenterGray;
	int    LabelCenterOXTrajectory[16];
	int    LabelCenterOYTrajectory[16];
	int    LabelOXPermutation[16];
	int    LabelDeviation;
	int    LabelVelocity;
	int    LabelIsFound;
	int    LabelPresence;
	int    LabelFoundNumberOfFrame;
	int    FirstLabelCoordinate;
	int    LastLabelFoundNumberOfFrame;
	int    LastLabelCoordinate;
	int    NumberOflabels;
	int    LabelCost;
	int NumberOfCurrentFrame;
	int RedNumberOfCurrentFrame;
	int RedNumberOfPreviousFrame;
	BOOL VideoCameraIsLoaded;
	//finding sky
	BOOL SkyFinding;
	int SkyMainLeft;
	int SkyMainRight;
	int SkySaturatedLeft;
	int SkySaturatedRight;
	int MassiveGray;
	int MassiveGrayLow;
	int MassiveGrayTop;
	int MassiveGrayTopSection;
	int TotalUpWeight;
	int SkyLeftHueZone;
	int SkyRightHueZone;
	int NumberLeftSkyComp;
	int NumberRightSkyComp;
	int MaximumNumberOfCoveringElements;
	int* ColorOfBasicBunches;//last_cor07.12.16
	int* LeftSkyComp;
	int* RightSkyComp;
	int* LeftBunchesInTheSky;
	int* RightBunchesInTheSky;
	int LowerSkyFiber;
	int UpperSkyFiber;
	int UpperMeanGray;
	int LowerMeanGray;
	int GreenMainLeft;
	int GreenMainLeftLb;
	int GreenMainLeftRb;
	int GreenMainRight;
	int GreenMainRightLb;
	int GreenMainRightRb;
	int    execution_time;
	int* SkyBoundPoints;
	int* SkyStripsOfBoundaryPoints;
	int* SkyColumnsOfBoundaryPoints;
	int* SkyPixelsOfBoundaryPoints;
	int* SkyVisualization;
	int NumberOfSkyBoundaryPoints;
	int SkyComponents[32];
	int SkyBoundaries[1920];
	int paint[64];
	int* SkyGreenComponents;
	//finding sky
	BOOL GreenFinding;
	int UpperGreenBoundaryLeft;
	int UpperGreenBoundaryRight;
	int FinalGreenStripNearRoad;
	int* LeftGreenBoundary;
	int* LeftGreenBoundaryVert;
	int* LeftGreenBoundaryBunch;
	int* LeftGreenBoundarySection;
	int* LeftAdjacentNonGreenSectionMax;
	int* LeftAdjacentGreenSectionMax;//last_cor09.12.16
	int* RightGreenBoundary;
	int* RightGreenBoundaryBunch;
	int* RightGreenBoundarySection;
	int* RightAdjacentNonGreenSectionMax;
	int* RightAdjacentGreenSectionMax;//last_cor09.12.16
	int* LeftRightSectionNumberOfRightGreenBoundaryPoints;
	int* BoundarySections;
	int* LeftBounSecTrace;
	int* RightBounSecTrace;
	int* RoadLikeSections;

	int* StraightSections;
	int* VerticalComponent;
	int* InclinedComponent;
	int* InclineCurve;
	int* InclineLocal;
	int* InclineLocalFirst;
	int* InclineLocalLast;
	int* BestVertComponentStart;
	int* BestVertComponentBeg;
	int* BestVertComponentEnd;
	int* BestVertNumPoints;
	int* GlobalDeviation;
	int* RightLeftConnections;
	int* NumberOfLRConnections;
	BOOL VertFinding;
	int NumberOfVertLines;
	int NumberOfVertLinesCloseToSignals;
	int NumberOfVertLinesCloseToSignals1;
	int* VerticalContrastCurves;
	int* VerticalContrastCurvesClosedSignals;
	int  VerticalLinesLength[64];
	int  VertLineFirstStrip[64];
	int  ConnectedVertLines[64];
	int  ConnectedVertLinesRight[64];
	int ConnectedLeftBounVert[64];
	int BlockConnected[64];
	int RightBounVert[64];
	int* StripSignals;
	int SignalNumber[256];
	int* StripNewNumber;
	int* StripSignalsAdditional;
	int SignalNumberAdditional[256];
	int* StripNewNumberAdditional;
	int FirstConnectedVertline[64];
	int LastConnectedVertline[64];
	int LeftClosestLine[64];
	int RightClosestLine[64];
	int LeftClosestLineIntersecting[64];//last_cor26.03.18
	int RightClosestLineIntersecting[64];
	int UpperClosestLine[64];
	int LowerClosestLine[64];
	 
protected:
	int    Dimension;
	int    PressedLength;
	int    DimDifference;

	unsigned char *Im; // pixels of the image

public:
	int        NumLevels;   // range of values each pixel can take (e.g. 256)
							//int        ColorRatio;  // is TRUE if this MonoImage was constructed from one
							// of the color-ratio images G/(G+B), ...
	int        BitsPerPix;
	int       correct_intence[256];

	int  GetHeight() { return DimY; }
	int  GetWidth() { return DimX; }
	unsigned char *GetBits() { return Im; }

	int        NumStrips;      // number of vertical (horizontal) strips
	int        StripWidth;     // width of a strip (except for the last one) = DimX/NumStrips
	int        Residual;
	int        Residual1;
	int        StripLength;

	BOOL        HorizontalVertical;
	BOOL       GGBorGGR;
	int ImageRepresentationType;
	int        RealColorNumSect;
	CMotion*   MotionAnalysis;
	CStrip*     CurStrip;
	CBunchGray*     GrayBunches;
	int left_shift1[12];
	int left_shift2[12];
	int right_shift1[12];
	int right_shift2[12];
	int* opponent_color_difference;
	int* invert_color_difference1;
	int* invert_color_difference2;


	CColorIntervalSelect* ColorInt;
	TIntColored* IntegratedColorIntervals;
	TIntColoredCharacteristics* IntegratedColorBunchesCharacteristics;
	TIntColorLessBack* IntegratedColorlessBackIntervals;
	ColorSectionDescr* ColorDescrSect;
	CColorSection*   ColorSection;
	int* SectionTraceLeft;
	int* SectionTraceRight;
	int* LineVertTrace;
	int* SectionStraightSegments;//last_cor20.11.14
	int* NumberOfConnectionsLeftRight;
	int* SectionNeighborsLeftRight;
	int* SectionNeighborsLeftRightIteration;
	int number_of_section_left;
	int number_of_section_right;
	int number_of_sections;
	int maximum_number_of_ordered_bunches;

	void InitialConstructions();//memory allocation and object construction

	void SegmentImage(int CurrentNumofFrame);      // segments the image
	
	void DeleteTemporal();      // delete intermediate arrays;
	
	void ContrastBunchesMotion(int num_strips, int* bunches_location);
	// calculate contrasts motion
	int ExtensionOfLeftContrast(int number_of_strip, int bunch_number, int bunch_beg, int bunch_end, int bunch_hue, int bunch_lower_hue,
			int bunch_upper_hue, int bunch_gray, int bunch_lower_gray, int bunch_upper_gray, int bunch_saturation,
			int bunch_lower_saturation, int bunch_upper_saturation);
	int Test_Junction_Different_Strips(int next_bunch, int previous_bunch, int Intersection_Measure,
			int indic_length, int ratio_length, int ratio_length1, int strip_number, int previous_strip_number);
	int ExtensionOfRightContrast(int number_of_strip, int bunch_number, int bunch_beg, int bunch_end, int bunch_hue, int bunch_lower_hue,
			int bunch_upper_hue, int bunch_gray, int bunch_lower_gray, int bunch_upper_gray, int bunch_saturation,
			int bunch_lower_saturation, int bunch_upper_saturation);

	int LabelCoordinatesFinding(void);

	int FindingRightConectedSection(void);

	void PermutationFinding(int FrameNumber);

	void AnalyzingArray();

	int Finding_Best_Label(void);

	int LabelFiltering(void);

	int StraightLineHighObjectsTesting(void);

	int ConnectedSections(int* initial_matrix);

	int FindingConnectedLeftSections(int coun_row, int coun_column, int mat_entry);

	int FindingLineSegments(int sect_length, int section_num,
			int* node_coordinates, int* opp_nodes_coor, int* differ_array);

	int MaximumTripleMaximum(int* main_array, int* compl_array, int dimen, int* triple_max,
			int* max_value, int* triple_max_value, int* one_pix_max_neighb, int* two_pix_max_neighb,
			int* zero_two_pix);

	int CenterOfMass(int* main_array, int dimen, int* mass_center, int* mass_deviation, int* left_number,
			int* right_number, int* small_angle, int* big_angle, int* painting, int* new_array, int new_dim);

	int MaximumTripleMaximumReduced(int* main_array, int dimen, int* triple_max,
			int* max_value, int* triple_max_value, int* one_pix_max_neighb, int* two_pix_max_neighb,
			int* zero_two_pix, int* loc_max_positions, int* num_loc_maxim, int* second_maxim_pos,
			int* second_max_val, int* first_noticable, int* last_noticable, int* noticable_sum);
	
	int Longest_Straight_Comp(int* difference_components, int num_point, int start_point,
			int last_point, int scale, int* first_segment, int* last_segment, int* number_of_segments,
			int* dev_reduced, int* glob_dev, int* glob_dev_plus, int* end_coordinates);

	int InclineRefinement(int section_number, int* incl_right);

	int InclineHistogram(int* main_array, int* hust_plus, int* hist_minus,
			int first_incl, int last_incl, int* neg_count);

	int FindingMaxPosNegSegments(int sect_length, int* chain_array, int* max_start);


	void SkyIntencitiesDistributionFinding(int* sky_gray, int* section_weight,
			int left_right);

	int MaximumSky(int* sk_gray, int* sec_weight, int* intensity_last, int* max_saturated);

	void BelongsSkyTo(int* sky_gr, int first_section, int last_section);
	 

	void LabelingSkyBunches(int* bunch_matrix, int* sky_components, int comp_number);

	void LeftRightSkyAddition(void);
	 

	void FindingBoundaryChains(void);

	void PaintingBoundaryChains(int left_end, int right_end, int fiber_num, int bunch_num);

	void TranslationIntoBigDimension(void);

	int TestSection(int sect_candidate_number, int left_right_sec,
			int min_left, int min_right);

	int GreenSeparation(int sect_max_number, int sect_sat_number,
			int min_left, int max_right, int min_left_sat, int max_right_sat);

	int LocateOn(int sect_number, int* sect_under_number, int* sect_under_number_r);

	int LocateUnder(int sect_number, int* sect_over_number, int* sect_over_number_r, int opt_fiber);

	int MaximumGreenComp(int left_right);

	int OpposGreenComponents(int left_right, int section_number);
	 

	int NextGreenComponents(int left_right, int oppos_bunch_number, int strip_number,
			int start_bunch_old_num, int sec_num, int left_side_boun, int right_side_boun, int* first_green_neighbor, int* last_green_neighbor,
			int* maximum_non_green, int* non_gr_length, int* first_non_green, int* last_non_green,
			int* last_green_in_chain, int* first_green_length, int* max_green_section,
			int* max_green_section_bunch, int* max_green_oppos_section,
			int* max_green_oppos_section_bunch, int* max_weight_n_green_section,
			int* max_weight_n_green_section_bunch, int* max_weight_n_green_section_oppos,
			int* max_weight_n_green_section_oppos_bunch, int* gr_length_before, int shift_to_next);

	int

		CImageProcess::NonGreenSummation(int left_right, int first_bunch, int last_bunch, int strip_number);

	int

		CImageProcess::NearestGreenUnder(int sect_number, int first_sec_strip, int bunch_sec);

	int

		CImageProcess::SectionCorrespondence(int prev_sect_number, int next_sec_number);

	void

		CImageProcess::ColorShapeSectionClassification(void);

	int

		CImageProcess::SectionGeometry(int section_num, int* meam_l, int* mean_u);

	int

		CImageProcess::GreenStripDescription(int adjacent_bunch,
			int max_section_bunch, int strp_number, int left_r, int* last_green, int* tot_green_length, int* first_green,
			int* last_section_green_bunch, int* last_green_section, int* first_green_section_bunch,
			int* first_green_section);

	int

		CImageProcess::LongestPlusMinusChain(int section_number, int section_length, int* section_ends,
			int* next_member_appropriate, int* chains_appropriate, int* chain_first_member,
			int* number_of_ch, int sign);

	int

		CImageProcess::AppropriateChain(int first_appropriate, int shift_length, int* appropriate_numbers,
			int* chains_appropriate, int* chain_first, int* sect_ends, int sign, int chain_number);

	int

		CImageProcess::ChainLongest(int sec_length, int number_of_chains, int* coordinates, int* appropriate_numbers,
			int* chains_appropriate, int* chain_first, int* last_chain_last, int* chains_prolongation, int sign);

	int

		CImageProcess::StraightApproximation(int* array_elements, int* paint, int first_member,
			int last_member, int* reliability, int left_right);

	int

		CImageProcess::SequenceOfChainsLongest(int sec_length, int sect_num, int number_of_chains,
			int* section_array, int* chains_prolongated, int* chain_first, int* chains_appropriate,
			int* first_prolong, int* max_length);

	int

		CImageProcess::FindSignalZones(void);

	int

		CImageProcess::VerticalLinesConstruct(int first_strip,int last_strip,int first_line,int last_line);

	int

		CImageProcess::VerticalLinePassing(int count_bun, int next_str, int first_cl,
			int first_end, int v_line_number);

	int

		CImageProcess::ConnectedVerticalLines(void);

	int

		CImageProcess::IntersectingVerticalLines(void);

	int

		CImageProcess::BreakingVerticalLines(void);

	int

		CImageProcess::VerticalLinesSignalsConnected(void);

	int

		CImageProcess::VerticalPartsofGreenBoundary(void);

	void

		CImageProcess::FillingVerticalPartsofGreenBoundary(int first_step, int last_step);

	void

		CImageProcess::VerticalConnectedToBoundary(void);

	void

		CImageProcess::RoadComponents(void);

	int

		CImageProcess::VerticalComponentsInBoundary(int section_number, int* ends_coordinates,
			int* verticl_parts, int sign);

	int NextSection(int bunch_number, int strip_number, int* next_beg, int* next_end);
	int LineSigConnnectedCorrection(void);
};


#endif // !defined(AFX_IMAGEPROCESS_H__E888F34A_F0CC_4849_8D36_78C688F32ADE__INCLUDED_)
