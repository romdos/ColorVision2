/*
 * Finds large bunches based only on intensity. It is not supposed to be used for road marking
 * finding because it finds only large objects (e.g. road).
 *
 *
 *
 *
 *
*/








#include "stdafx.h"
#include "ColorVision.h"
#include "Strip.h"
#include "BunchGray.h"




CBunchGray::CBunchGray()
{
	GapWidth = 2;
	BackgroundClusters = NULL;
	IntervalIntensity = NULL;
	IntervalOldNumber = NULL;
	BackgroundGrains = NULL;
}

CBunchGray::~CBunchGray()
{
	if(BackgroundClusters!=NULL)
	{
		delete [] BackgroundClusters;
	}
	if(IntervalIntensity!=NULL)
	{
delete [] IntervalIntensity;
	}
	if(IntervalOldNumber!=NULL)
	{
delete [] IntervalOldNumber;
	}
	if(BackgroundGrains!=NULL)
	{
delete [] BackgroundGrains;
	}
if(NumberOfBackgroundGrains!=0)
{
delete [] ClusterGrains;
delete [] BegIntervOfClusters;
delete [] EndIntervOfClusters;
delete [] GrainIntensityIntervalOfClusters;
delete [] LowerIntensityOfClusters;
delete [] UpperIntensityOfClusters;
delete [] AverageIntensityOfClusters;
delete [] SignificanceOfClusters;
delete [] CardinalityOfClusters;

}
}
BOOL

CBunchGray::IntervalInteraction()
{

int NumInt;

int* LeftLowerInterval;
int* LeftUpperInterval;
int* RightLowerInterval;
int* RightUpperInterval;
int* ClusterNumber;
int* IntervalWeight;


int* IntervalNewNumber;
int* IntervalProperties;
int* AdjacentLinked;
int* LocalSignifSum;
int* LocalOptimalBackground;
int* valuable_intervalb;
int* signif_of_intervalb;
int* IntervalVisibility;


TotalNumInt=0;
MaxNumInt=0; 
for(int inu=0;inu<NUM_INTEN1;inu++)
{
NumInt=StripCur->num_of_intg[inu];
   if(NumInt)
   {
      TotalNumInt+=NumInt;
      if(NumInt>MaxNumInt)
	  {
       MaxNumInt=NumInt;
	  }
   }
}
   if(MaxNumInt)
   {
	NumberOfBackgroundGrains=0;
    valuable_intervalb=new int[PressedLength];
    signif_of_intervalb=new int[PressedLength];
    LeftLowerInterval=new int[TotalNumInt];
	LeftUpperInterval=new int[TotalNumInt];
	RightLowerInterval=new int[TotalNumInt];
	RightUpperInterval=new int[TotalNumInt];
	ClusterNumber=new int[TotalNumInt];
	IntervalIntensity=new int[TotalNumInt];
	IntervalOldNumber=new int[TotalNumInt];
	IntervalProperties=new int[TotalNumInt];
	IntervalWeight=new int[TotalNumInt];
	IntervalVisibility=new int[TotalNumInt];
	AdjacentLinked=new int[TotalNumInt];
	LocalSignifSum=new int[TotalNumInt];
	LocalOptimalBackground=new int[TotalNumInt];
	BackgroundClusters=new int[TotalNumInt];
	BackgroundGrains=new int[TotalNumInt];
	BackgrGrainOldNumber=new int[TotalNumInt];
	IntervalNewNumber=new int[NUM_INTEN1*MaxNumInt];
	memset(IntervalWeight,(int) '\0',sizeof(int)*TotalNumInt);
	memset(IntervalVisibility,(int) '\0',sizeof(int)*TotalNumInt);
	memset(AdjacentLinked,(int) '\0',sizeof(int)*TotalNumInt);
	memset(ClusterNumber,(int) '\0',sizeof(int)*TotalNumInt);
	memset(LocalSignifSum,(int) '\0',sizeof(int)*TotalNumInt);
	memset(LocalOptimalBackground,(int) '\0',sizeof(int)*TotalNumInt);
	memset(BackgroundClusters,(int) '\0',sizeof(int)*TotalNumInt);
	memset(valuable_intervalb,(int) '\0',sizeof(int)*PressedLength);
	     IntervalNumeration(IntervalNewNumber,IntervalIntensity,IntervalOldNumber);
Room_testing(IntervalWeight,IntervalNewNumber);
      LimitIntervCalcFor(RightLowerInterval,RightUpperInterval,IntervalNewNumber);
LimitIntervCalcBack(LeftLowerInterval,LeftUpperInterval,IntervalNewNumber);
        ConnectedOrIsolated(IntervalProperties,IntervalNewNumber);

IsolatedClustersLeft(ClusterNumber,IntervalProperties,IntervalNewNumber,LeftLowerInterval,
LeftUpperInterval,RightLowerInterval,RightUpperInterval,IntervalWeight,IntervalIntensity,
IntervalOldNumber);

LocalBackgroundFinding(IntervalWeight,LeftLowerInterval,LeftUpperInterval,
RightLowerInterval,RightUpperInterval,IntervalIntensity,IntervalOldNumber,
IntervalProperties,IntervalNewNumber,LocalSignifSum,0);
        LocalBackgroundFinding(IntervalWeight,LeftLowerInterval,LeftUpperInterval,
        RightLowerInterval,RightUpperInterval,IntervalIntensity,IntervalOldNumber,
        IntervalProperties,IntervalNewNumber,LocalSignifSum,1);

LinkAdjacent(AdjacentLinked,IntervalNewNumber,LeftLowerInterval,LeftUpperInterval,
RightLowerInterval,RightUpperInterval,IntervalWeight,IntervalIntensity,IntervalOldNumber,
IntervalProperties,LocalSignifSum);
FindingLocalBackgroundGrains(AdjacentLinked,LeftLowerInterval,LeftUpperInterval,
RightLowerInterval,RightUpperInterval,IntervalIntensity,IntervalOldNumber,
IntervalNewNumber,LocalSignifSum,LocalOptimalBackground,valuable_intervalb,
signif_of_intervalb);
ArrangeIntervals(valuable_intervalb,IntervalVisibility,LocalSignifSum,
LocalOptimalBackground,IntervalIntensity,IntervalOldNumber,LeftLowerInterval,
LeftUpperInterval,RightLowerInterval,RightUpperInterval,AdjacentLinked,IntervalNewNumber);
   }
   else
   {
   return FALSE;
   }


delete [] LeftLowerInterval;
delete [] LeftUpperInterval;
delete [] RightLowerInterval;
delete [] RightUpperInterval;
delete [] ClusterNumber;
delete [] IntervalWeight;


delete [] IntervalNewNumber;
delete [] IntervalProperties;
delete [] AdjacentLinked;
delete [] LocalSignifSum;
delete [] valuable_intervalb;
delete [] signif_of_intervalb;
delete [] IntervalVisibility;

delete [] BackgrGrainOldNumber;
delete [] LocalOptimalBackground;

return TRUE;
}
//////////////////////////////////////////////////////////////////////
void

CBunchGray::LimitIntervCalcFor(int* lower_int,int* upper_int,int* int_new_num)
{
	int inu;
	int num_int1,num_int2;

	num_int1=StripCur->num_of_intg[NUM_INTEN1-1];
	     if(num_int1>0)
	      {
          NegativeInitialization(lower_int,upper_int,NUM_INTEN1-1,num_int1,0,int_new_num);
		  }
	for(inu=0;inu<NUM_INTEN1-1;inu++)
	{
    num_int1=StripCur->num_of_intg[inu];
	    if(num_int1)
		{
	
      	num_int2=StripCur->num_of_intg[inu+1];
		    if(num_int2)
			{
FindBoundaryIntervals(lower_int,upper_int,inu,inu+1,
num_int1,num_int2,int_new_num);

			}
			else
			{
				NegativeInitialization(lower_int,upper_int,inu,num_int1,0,int_new_num);
			}
    
			
		}
	}
return;
}

//////////////////////////////////////////////////////////////////////
void

CBunchGray::FindBoundaryIntervals(int* lower_int,int* upper_int,int n_fibre1,int n_fibre2,
int n_int1,int n_int2,int* int_new_num)
{
	int int_f,int_s;
	int num_int1,num_int2;
	int beg1,end1,beg2,end2;
	int bot_int_num,top_int_num;
	int int_start;
	int num_prev;
	int new_number;
	
	
	num_int1=n_int1;
    num_int2=n_int2;
	int_start=0;
//!eliminate singular cases to reduce the computations
for(int_f=0;int_f<num_int1;int_f++)
	{
    beg1=StripCur->IntAllInformGray[n_fibre1].BegInt[int_f];
	end1=StripCur->IntAllInformGray[n_fibre1].EndInt[int_f];
	num_prev=-1;
	
	
	bot_int_num=-1;
    top_int_num=-1;
	beg2=StripCur->IntAllInformGray[n_fibre2].BegInt[num_int2-1];
	end2=StripCur->IntAllInformGray[n_fibre2].EndInt[num_int2-1];
	if(end2<beg1)
		{
			NegativeInitialization(lower_int,upper_int,n_fibre1,num_int1,int_f,int_new_num);
			return;

		}
	beg2=StripCur->IntAllInformGray[n_fibre2].BegInt[0];
	end2=StripCur->IntAllInformGray[n_fibre2].EndInt[0];
		if(beg2>end1)
		{
			new_number=*(int_new_num+n_fibre1*MaxNumInt+int_f);
*(lower_int+new_number)=bot_int_num;
*(upper_int+new_number)=top_int_num;
goto L;
		}
		
		
      for(int_s=int_start;int_s<num_int2;int_s++)
			  {
      beg2=StripCur->IntAllInformGray[n_fibre2].BegInt[int_s];
	  end2=StripCur->IntAllInformGray[n_fibre2].EndInt[int_s];
	    if(beg2>end1)
		{
			if(num_prev>=0)
			{
				top_int_num=num_prev;
			}
			
			break;
		}
		if(((beg2>=beg1)&&(beg2<=end1))||((beg1>=beg2)&&(beg1<=end2)))
		{
			if(num_prev<0)
			{
			bot_int_num=int_s;
             
			}
			 top_int_num=int_s;
			 num_prev=int_s;
		}
	  }
new_number=*(int_new_num+n_fibre1*MaxNumInt+int_f);
*(lower_int+new_number)=bot_int_num;
*(upper_int+new_number)=top_int_num;
if(top_int_num>0)
{
int_start=top_int_num;
}
L:;
    }

}
//////////////////////////////////////////////////////////////////////
void

CBunchGray::LimitIntervCalcBack(int* lower_int,int* upper_int,int* int_new_num)
{
	int inu;
	int num_int1,num_int2;
	
        num_int1=StripCur->num_of_intg[0];
	     if(num_int1>0)
	      {
	    NegativeInitialization(lower_int,upper_int,0,num_int1,0,int_new_num);
		  }
	for(inu=NUM_INTEN1-1;inu>0;inu--)
	{
    num_int1=StripCur->num_of_intg[inu];
	    if(num_int1)
		{
	     num_int2=StripCur->num_of_intg[inu-1];
		    if(num_int2)
			{
FindBoundaryIntervals(lower_int,upper_int,inu,inu-1,
num_int1,num_int2,int_new_num);

			}
			else
			{
			NegativeInitialization(lower_int,upper_int,inu,num_int1,0,int_new_num);
			}
    
			
		}
	}
return;
}
//////////////////////////////////////////////////////////////////////
void

CBunchGray::NegativeInitialization(int* lower_int,int* upper_int,int n_fibre,int n_int1,
int n_start,int* int_new_num)
{
	int new_num;

	for(int int_f=n_start;int_f<n_int1;int_f++)
	{
		new_num=*(int_new_num+n_fibre*MaxNumInt+int_f);
*(lower_int+new_num)=-1;
*(upper_int+new_num)=-1;
	}

}
//////////////////////////////////////////////////////////////////////
void

CBunchGray::BunchFinding()
{


}
//----------------------------------------------------------------------------
	void
CBunchGray::Room_testing(int* IntervWeight,int* IntervNewNumber)
{

unsigned char corn_presense;
//int inten_go;
//int test_inten;
int num_int;
int new_num;

 for(int space_go=0;space_go<PressedLength;space_go++)
  {
	corn_presense=*(StripCur->valuable_intensityg+space_go);
	if(corn_presense)
	 {
	num_int=*(StripCur->valuable_intervalg+space_go);
	new_num=IntervNewNumber[(corn_presense-1)*MaxNumInt + num_int]; 
	(*(IntervWeight+new_num))++;

	 }
	  
  }
	 

}
//----------------------------------------------------------------------------
	void

CBunchGray::IntervalNumeration(int* IntervalNewNumber,int* IntervalIntensity,int* IntervalOldNumber)
{
		int NumInt;
		int IntervNum;
		

		IntervNum=0;

for(int inu=0;inu<NUM_INTEN1;inu++)
{
NumInt=StripCur->num_of_intg[inu];
   if(NumInt)
   {
	          
	   for(int inu_int=0;inu_int<NumInt;inu_int++)
	   {
		*(IntervalNewNumber + MaxNumInt*inu +inu_int)=IntervNum;
	    *(IntervalIntensity + IntervNum)=inu;
	    *(IntervalOldNumber + IntervNum)=inu_int;
		  IntervNum++;   
    
	   }
   }
}
}
//----------------------------------------------------------------------------
	void

CBunchGray::ConnectedOrIsolated(int* con_isol,int* int_new_num)
	{
		int NumInt;
		int beg1, end1, beg2, end2;
		int length1, length2, gap_length;
		int NewIntNum;
		int mi_length, ma_length;
		int signif1,signif2;
		int signif_ratio;

for(int inu=0;inu<NUM_INTEN1;inu++)
{
NumInt=StripCur->num_of_intg[inu];
   if(NumInt)
   {
	   if(NumInt==1)
			  {
			  NewIntNum=*(int_new_num + MaxNumInt*inu);
              *(con_isol + NewIntNum)=2;
			  //must be refined
			  goto M;
			  }
	   else
	   {
		   NewIntNum=*(int_new_num + MaxNumInt*inu+NumInt-1);
           *(con_isol + NewIntNum)=2;
	   }
	   for(int inu_int=0;inu_int<NumInt-1;inu_int++)
	   {
		beg1=StripCur->IntAllInformGray[inu].BegInt[inu_int];
	    end1=StripCur->IntAllInformGray[inu].EndInt[inu_int];
		signif1=StripCur->IntAllInformGray[inu].Signif[inu_int];
		
	    beg2=StripCur->IntAllInformGray[inu].BegInt[inu_int+1];
	    end2=StripCur->IntAllInformGray[inu].EndInt[inu_int+1];
		signif2=StripCur->IntAllInformGray[inu].Signif[inu_int+1];
		
           gap_length=beg2-end1+1;
	       length1=end1-beg1+1;
		   signif1=(4*signif1)/length1;
	       length2=end2-beg2+1;
		   signif2=(4*signif2)/length2;
		   signif_ratio=(16*signif2)/(signif2+signif1);
		   mi_length=min(length1,length2);
		   ma_length=max(length1,length2);
		   NewIntNum=*(int_new_num + MaxNumInt*inu+inu_int);
if(ma_length>StripWidthPrev)
{
  if((mi_length+gap_length)>ma_length)
  {
	if(gap_length>mi_length)
	{
	*(con_isol + NewIntNum)=1;
	}
	else
	{
		if(((3*gap_length<mi_length)&&(4*gap_length<ma_length))||
	 ((gap_length<StripWidthPrev)&&(gap_length<mi_length)&&(4*gap_length<ma_length)))
				{
			if(abs(signif_ratio-8)<=1)
			{
		         *(con_isol + NewIntNum)=0;
			}
				}
		else
		{
     *(con_isol + NewIntNum)=-1;
		}
	}
  }
  else
  {
   if((4*(gap_length+mi_length)>ma_length)&&((gap_length>2*mi_length)))
	{
	*(con_isol + NewIntNum)=1;
	}
	else
	{
	/*	if(4*gap_length<mi_length)
		{
		*(con_isol + NewIntNum)=0;
		}
		else
		{
     *(con_isol + NewIntNum)=-1;
		}*/
		*(con_isol + NewIntNum)=-1;
		                            

	}
	           if(((3*gap_length<mi_length)&&(4*gap_length<ma_length))||
	 ((gap_length<StripWidthPrev)&&(gap_length<mi_length)&&(4*gap_length<ma_length)))
				{
			 if(abs(signif_ratio-8)<=1)
			{
		    *(con_isol + NewIntNum)=0;
			}
				}
  }
}
else
{

if(gap_length>(ma_length+mi_length))
	{
	*(con_isol + NewIntNum)=1;
	}
	else
	{
     *(con_isol + NewIntNum)=-2;
	}
}


	   }

   }
   M:;
}
	}
//----------------------------------------------------------------------------
	void

CBunchGray::LinkAdjacent(int* adjac_link,int* int_new_num,int* left_lower,int* left_upper,
int* right_lower,int* right_upper,int* inter_weight,int* inter_intens,int* inter_num,
int* con_isol,int* extended_signif)
{
int test_inten1,test_inten2,test_inten3,test_inten4;
int beg1,end1,beg2,end2,beg3,end3;
int inter_number;
int interval_intensity;
int number_of_int;
int new_num,new_num1;
int signif1;
int dense1;
int ext_signif1;
int ext_dense1;
int ext_signif2;
int ext_dense2;
int length1;
int signif2;
int signif3;
int dense2,dense3,dense4;
int length2,length3;
int low_left1,up_left1;
int low_right1,up_right1;
int low_left2,up_left2;
int low_right2,up_right2;
int was_linked1;
int num_step;
int number_of_successful_steps;
int comp_density1,comp_density2,comp_density3,comp_density4;
int index_of_step;
int previous_intensity;
int next_intensity;
int total_signif;


for(int inter_go=0;inter_go<TotalNumInt;inter_go++)
	 {
	 test_inten1=*(inter_weight+inter_go);
     was_linked1=*(adjac_link+inter_go);
		if((test_inten1>0)&&(!was_linked1))
		{
			total_signif=0;
		interval_intensity=*(inter_intens+inter_go);
		inter_number=*(inter_num+inter_go);
		number_of_int=StripCur->num_of_intg[interval_intensity];
		num_step=number_of_int-1-inter_number;
   if(num_step>0)
   {
	   beg1=StripCur->IntAllInformGray[interval_intensity].BegInt[inter_number];
	   end1=StripCur->IntAllInformGray[interval_intensity].EndInt[inter_number];
	   signif1=StripCur->IntAllInformGray[interval_intensity].Signif[inter_number];
	   ext_signif1=*(extended_signif+inter_go);
	   length1=end1-beg1+1;
	   dense1=(4*signif1)/length1;
	   ext_dense1=(4*ext_signif1)/length1;
	   total_signif+=ext_signif1;
	   number_of_successful_steps=0;
	   index_of_step=inter_go;
	   for(int inter_step=1;inter_step<=num_step;inter_step++)
	  {
	   new_num=*(int_new_num+MaxNumInt*interval_intensity+inter_number+inter_step);
       test_inten2=*(inter_weight+new_num);
	   

	             if((test_inten2>0)||(test_inten2<0))
				 {
	signif2=StripCur->IntAllInformGray[interval_intensity].Signif[inter_number+inter_step];
	beg2=StripCur->IntAllInformGray[interval_intensity].BegInt[inter_number+inter_step];
	end2=StripCur->IntAllInformGray[interval_intensity].EndInt[inter_number+inter_step];
	length2=end2-beg2+1;
	   dense2=(4*signif2)/length2;
	   ext_signif2=*(extended_signif+new_num);
	   ext_dense2=(4*ext_signif2)/length2;
	   comp_density1=(16*dense2)/(dense1+dense2);
	   comp_density2=(16*ext_dense2)/(ext_dense1+ext_dense2);
	              if(((comp_density2>=6)&&(comp_density2<=10))||
					  (comp_density1>=6)&&(comp_density1<=10))
				    {
                 low_left1=*(left_lower+index_of_step);
				 up_left1=*(left_upper+index_of_step);
				 low_right1=*(right_lower+index_of_step);
				 up_right1=*(right_upper+index_of_step);
				 low_left2=*(left_lower+new_num);
				 up_left2=*(left_upper+new_num);
				 low_right2=*(right_lower+new_num);
				 up_right2=*(right_upper+new_num);
				       if((up_left1==low_left2)&&(up_left1>=0))
				        {
				        previous_intensity=interval_intensity-1;
new_num1=*(int_new_num+MaxNumInt*previous_intensity+up_left1);
						test_inten3=*(inter_weight+new_num1);
beg3=StripCur->IntAllInformGray[previous_intensity].BegInt[up_left1];
end3=StripCur->IntAllInformGray[previous_intensity].EndInt[up_left1];
signif3=StripCur->IntAllInformGray[previous_intensity].Signif[up_left1];
length3=end3-beg3+1;
dense3=(4*signif3)/length3;
				        }
					   else
					   {
						previous_intensity=-1;
						new_num1=-1;
						dense3=0;
					   }
				          if((up_right1==low_right2)&&(up_right1>=0))
				            {
				            next_intensity=interval_intensity+1;
new_num1=*(int_new_num+MaxNumInt*next_intensity+up_right1);
						test_inten4=*(inter_weight+new_num1);
beg3=StripCur->IntAllInformGray[next_intensity].BegInt[up_right1];
end3=StripCur->IntAllInformGray[next_intensity].EndInt[up_right1];
signif3=StripCur->IntAllInformGray[next_intensity].Signif[up_right1];
length3=end3-beg3+1;
dense4=(4*signif3)/length3;

				            }
						  else
						  {
						  next_intensity=-1;
						  dense4=0;
						  }
						  if((previous_intensity<0)&&(next_intensity<0))
						  {
							  if(number_of_successful_steps!=0)
							  {
							  //*(adjac_link+inter_go)=number_of_successful_steps;
								  *(extended_signif+inter_go)=total_signif;
	 ChainAssignment(adjac_link,inter_go+1,number_of_successful_steps);
							  }
						  break;
						  }
                          dense4+=dense3;
						  comp_density3=(16*dense4)/(dense4+dense1);
						  comp_density4=(16*dense4)/(dense4+dense2);
						  if((comp_density3>=5)&&(comp_density4>=5))
						  {
						  number_of_successful_steps++;
						  total_signif+=ext_signif2;
						  }
				   }
				  else
				  {
					  if(number_of_successful_steps!=0)
							  {
							  //*(adjac_link+inter_go)=number_of_successful_steps;
						  *(extended_signif+inter_go)=total_signif;
		ChainAssignment(adjac_link,inter_go+1,number_of_successful_steps);
							  }
					  break;
				  }
				 }
				 else
				 {
					 if(number_of_successful_steps!=0)
							  {
							  //*(adjac_link+inter_go)=number_of_successful_steps;
					  *(extended_signif+inter_go)=total_signif;
		ChainAssignment(adjac_link,inter_go+1,number_of_successful_steps);
							  }
				  break;
				 }
dense1=dense2;
index_of_step=new_num;
ext_dense1=ext_dense2;
	  }
   }
		}
	 }
}
//----------------------------------------------------------------------------
	void

	CBunchGray::IsolatedClustersLeft(int* cluster_number,int* int_properties,int* int_new_num,int* left_lower,int* left_upper,
int* right_lower,int* right_upper,int* inter_weight,int* inter_intens,int* inter_num)
{
int NumInt;
int PrevNewNumber;
int prop_index,prev_prop_index;
int clus_number;
int inten,num_interv,new_number,first_new_number;
int interval_weight,first_interval_weight;
int continuation_num;
int NumChainCluster;
int NumberOfMembers;
int* ClusterList;
int beg1,end1;
int signif1;
int length1;
int dense1;

NumChainCluster=0;
ClusterList=new int[TotalNumInt];

   for(int inu=0;inu<NUM_INTEN1-1;inu++)
   {
        NumInt=StripCur->num_of_intg[inu];
        if(NumInt)
		{
			for(int inu_int=0;inu_int<NumInt;inu_int++)
			{
            
			NumberOfMembers=0;
			inten=inu;
			num_interv=inu_int;
			first_new_number=*(int_new_num+inten*MaxNumInt+num_interv);
			clus_number=*(cluster_number+first_new_number);
			prop_index=*(int_properties+first_new_number);
			if((clus_number)||(!prop_index))
			 {
			goto L;
			 }
			if(num_interv==0)
				   {
				prev_prop_index=3;
				   }
				   else
				   {
                   PrevNewNumber=*(int_new_num+inten*MaxNumInt+num_interv-1);
                   prev_prop_index=*(int_properties+PrevNewNumber);
				   }
			if(!prev_prop_index)
			{
			goto L;
			}
			first_interval_weight=*(inter_weight+first_new_number);
			beg1=StripCur->IntAllInformGray[inten].BegInt[num_interv];
	        end1=StripCur->IntAllInformGray[inten].EndInt[num_interv];
			length1=end1-beg1+1;
			signif1=StripCur->IntAllInformGray[inten].Signif[num_interv];
			dense1=(4*signif1)/length1;
	while(TRUE)
   {
			
			new_number=*(int_new_num+inten*MaxNumInt+num_interv);
			interval_weight=*(inter_weight+new_number);
			continuation_num=-1;
	   				
ClusterizeRight(inten,num_interv,new_number,int_properties,int_new_num,cluster_number,
right_lower,right_upper,inter_weight,inter_intens,inter_num,&continuation_num);
                   if(continuation_num<0)
				   {
					   if(NumberOfMembers==0)
					   {
						   if(first_interval_weight>0)
						   {
							   NumChainCluster++;
							*(cluster_number+first_new_number)=NumChainCluster;
							
						   }
					   }
					   else
					   {
						ChainProcessing(inu,inu_int,NumberOfMembers,ClusterList);
						NumChainCluster++;
ClusterMembersAssignment(NumChainCluster,NumberOfMembers,inu,inu_int,
first_new_number,ClusterList,cluster_number,int_new_num);
					   }
					   goto L;
				   }
NumberOfMembers++;
  inten++;
  *(ClusterList+NumberOfMembers)=continuation_num;
  if(inten>=NUM_INTEN1-1)
  {		
ChainProcessing(inu,inu_int,NumberOfMembers,ClusterList);
NumChainCluster++;
ClusterMembersAssignment(NumChainCluster,NumberOfMembers,inu,inu_int,
first_new_number,ClusterList,cluster_number,int_new_num);
goto L;
  }
num_interv=continuation_num;
				   
//break;
   }
L:;   
			}

		}
   }
   delete [] ClusterList;
}
//----------------------------------------------------------------------------
	void

	CBunchGray::ClusterizeRight(int inten,int num_interv,int new_number,int* int_properties,int* int_new_num,int* cluster_number,
int* right_lower,int* right_upper,int* inter_weight,int* inter_intens,int* inter_num,int* continuation_num)
{
int lower_bound,upper_bound;
int beg1,end1,beg2,end2;
int prior;
int greater;
int num_clust;
int new_num;
int prop_index,prev_prop_index;
int PrevNewNumber;
int comparable1,comparable2;
int intersect_measure;

*continuation_num=-1;
lower_bound=*(right_lower+new_number);
upper_bound=*(right_upper+new_number);
   if(lower_bound>=0)
   {
	   if(lower_bound==upper_bound)
	   {
       beg1=StripCur->IntAllInformGray[inten].BegInt[num_interv];
	   end1=StripCur->IntAllInformGray[inten].EndInt[num_interv];
	   beg2=StripCur->IntAllInformGray[inten+1].BegInt[lower_bound];
	   end2=StripCur->IntAllInformGray[inten+1].EndInt[lower_bound];
	   prior=Intersection_measure(beg1,end1,beg2,end2,&greater,&comparable1,&comparable2,
	   &intersect_measure);
	   new_num=*(int_new_num+(inten+1)*MaxNumInt+lower_bound);
	   num_clust=*(cluster_number+new_num);
	   prop_index=*(int_properties+new_num);
	   if(lower_bound==0)
				   {
				prev_prop_index=3;
				   }
				   else
				   {
                   PrevNewNumber=*(int_new_num+(inten+1)*MaxNumInt+lower_bound-1);
                   prev_prop_index=*(int_properties+PrevNewNumber);
				   }
	      if((!num_clust)&&(prop_index>=1)&&(prev_prop_index>=1))
	      {
	      *continuation_num=lower_bound;
	      }
		  else
		  {
			  if((!num_clust))
			  {
				  
			  }
		  }
	   }

   }
}

//----------------------------------------------------------------------------
int

CBunchGray::Intersection_measure(int beg_first,int end_first,int beg_second,int end_second,
int* greater,int* inter_compar1,int* inter_compar2,int* intersection_length)
{
int inter_beg,inter_end,max_len,min_len;
int prior;
int length_first;
int length_second;
int inter_length;
int compar1,compar2;

length_first=end_first-beg_first+1;
length_second=end_second-beg_second+1;
inter_beg=max(beg_first,beg_second);
inter_end=min(end_first,end_second);
inter_length=inter_end-inter_beg+1;
min_len=min(length_first,length_second);
max_len=max(length_first,length_second);
*greater=0;
*inter_compar1=0;
*inter_compar2=0;
	if(length_first>=2*length_second)
	{
	 *greater=3;
	}
				else
			  {
					 if(length_first>=length_second)
					  {
					  *greater=2;
					  }
						  else
							{
							  if(2*length_first>=length_second)
								{
								*greater=1;
								}
							}
			 }
if(inter_beg>inter_end)
{
prior=3;
}
else
 {
	 compar1=(16*inter_length)/(inter_length+length_first);
	 compar2=(16*inter_length)/(inter_length+length_second);
	 *inter_compar1=compar1;
	 *inter_compar2=compar2;
  if(((inter_length)*2)>(max_len))
  {
  prior=0;
  }
  else
  {
  if(((inter_length)*2)>(min_len))
  {
  prior=1;
  }
	else
	{
	 prior=2;
	}
  }
 }
 if(prior<3)
 {
 *intersection_length=inter_length;
 }
 else
 {
 *intersection_length=0;
 }
		return(prior);
}

//----------------------------------------------------------------------------
	void

CBunchGray::ChainProcessing(int inten,int num_int,int num_steps,int* ListOfIntervals)
	{
return;
	}
	//----------------------------------------------------------------------------
	void

CBunchGray::ClusterMembersAssignment(int num_clust,int number_of_members,int start_inten,int start_interval_number,
int start_new_nuw,int* ListOfIntervals,int* cluster_numbers,int* new_num)
	{
		int new_number;
		int num_intensity;
		int num_interval;

		*(cluster_numbers+start_new_nuw)=num_clust;
	for(int coun=1;coun<=number_of_members;coun++)
   {
	   num_intensity=start_inten+coun;
	   num_interval=*(ListOfIntervals+coun);
new_number=*(new_num+(num_intensity)*MaxNumInt+num_interval);
*(cluster_numbers+new_number)=num_clust;
   }
	}
	//----------------------------------------------------------------------------
	void

CBunchGray::LocalBackgroundFinding(int* interval_weigtht,int* lower_left,int* upper_left,
int* lower_right,int* upper_right,int* int_intensity,int* int_old_number,
int* interval_properties,int* new_num,int* local_signif_sum,int key)
	{
    int weight_interv;
	int interv_intensity;
	int interv_number;
	int interval_signif0;
	int beg0,end0,length0,dense0;
	int previous_intensity;
	int next_intensity;
	int lower_left_interval,upper_left_interval;
	int lower_right_interval,upper_right_interval;
	int fit_best_left,fit_best_right;
	int greater_adjacent_left,greater_adjacent_right;
	int new_number;
	int added_signif;
	int extended_signif;

	
	
		for(int coun_int=0;coun_int<TotalNumInt;coun_int++)
   {
	   weight_interv=*(interval_weigtht+coun_int);
	   if(!key)
	   {
	     if(weight_interv<=0)
	     {
		 goto L;
		 }
	   }
	   else
	   {
		   if(weight_interv>=0)
	     {
		 goto L;
		 }
	   }
		 fit_best_left=-2;
	     fit_best_right=-2;	 
	     greater_adjacent_left=-2;
	     greater_adjacent_right=-2;
		 extended_signif=0;
		 added_signif=0;
		 lower_left_interval=*(lower_left+coun_int);
		 upper_left_interval=*(upper_left+coun_int);
		 lower_right_interval=*(lower_right+coun_int);
		 upper_right_interval=*(upper_right+coun_int);
	     interv_intensity=*(int_intensity+coun_int);
	     interv_number=*(int_old_number+coun_int);	   
     interval_signif0=StripCur->IntAllInformGray[interv_intensity].Signif[interv_number];
	 extended_signif+=interval_signif0;
         beg0=StripCur->IntAllInformGray[interv_intensity].BegInt[interv_number];
	     end0=StripCur->IntAllInformGray[interv_intensity].EndInt[interv_number];
	     length0=end0-beg0+1;
	     dense0=(4*interval_signif0)/length0;
		 
		    if(interv_intensity!=0)
			{
			previous_intensity=interv_intensity-1;
			  if(lower_left_interval>=0)
			   {
LocalGrowing(beg0,end0,dense0,previous_intensity,lower_left_interval,upper_left_interval,
&fit_best_left,&greater_adjacent_left,&added_signif);
extended_signif+=added_signif;
if(greater_adjacent_left>=0)
{
new_number=*(new_num+(previous_intensity)*MaxNumInt+greater_adjacent_left);
weight_interv=*(interval_weigtht+new_number);
  if(!weight_interv)
  {
*(interval_weigtht+new_number)=-1;
  }
}
			   }
			}
			else
			{
			previous_intensity=-1;
			}
			  if(interv_intensity!=NUM_INTEN1-1)
			  {
			  next_intensity=interv_intensity+1;
			  if(lower_right_interval>=0)
			  {
LocalGrowing(beg0,end0,dense0,next_intensity,lower_right_interval,upper_right_interval,
&fit_best_right,&greater_adjacent_right,&added_signif);
extended_signif+=added_signif;
   if(!key)
   {
if(greater_adjacent_right>=0)
{
new_number=*(new_num+(next_intensity)*MaxNumInt+greater_adjacent_right);
weight_interv=*(interval_weigtht+new_number);
  if(!weight_interv)
  {
*(interval_weigtht+new_number)=-1;
  }
}
   }
			  }
			  }
			  else
			  {
			  next_intensity=-1;
			  }
			  *(local_signif_sum+coun_int)=extended_signif;
	     
L:;
   }

}
	//----------------------------------------------------------------------------
	void

CBunchGray::LocalGrowing(int beg1,int end1,int dense1,int fibre,int lower_bound,int upper_bound,
int* best_fit,int* greater_adjacent,int* additional_signif)
{
	int beg2,end2;
	int interval_signif2,length2,dense2;
	int comp1,comp2,greater,prior,inter_length;
	int comp_density;
	int added_signif;
	int fit_num;
	int fitness_number;

	*best_fit=-1;
	*greater_adjacent=-1;
	
added_signif=0;
	  if(lower_bound==upper_bound)
	  {
	  beg2=StripCur->IntAllInformGray[fibre].BegInt[lower_bound];
      end2=StripCur->IntAllInformGray[fibre].EndInt[lower_bound];
      prior=Intersection_measure(beg1,end1,beg2,end2,&greater,&comp1,&comp2,&inter_length);
      length2=end2-beg2+1;
      interval_signif2=StripCur->IntAllInformGray[fibre].Signif[lower_bound];
      dense2=(4*interval_signif2)/length2;
	  comp_density=(16*dense2)/(dense1+dense2);
	  if((comp_density>=5)&&(comp_density<=11))
	  {
		  if((prior<=1)&&(comp1>=5)&&(comp2>=5))
		  {
           *best_fit=lower_bound;
		   if((comp_density>=6)&&(comp_density<=9))
		   {
		   added_signif=(interval_signif2*inter_length)/length2;
		   *additional_signif=added_signif;
		   }
		     if((comp1>6)&&(comp2>comp1)&&((comp_density>=6)&&(comp_density<=10)))
			 {
             *greater_adjacent=lower_bound;
			 }
		  }
	  }
	  return;
	  }
	  fit_num=-1;
	fitness_number=0;
for(int coun_shift=lower_bound;coun_shift<=upper_bound;coun_shift++)
   {
   beg2=StripCur->IntAllInformGray[fibre].BegInt[coun_shift];
   end2=StripCur->IntAllInformGray[fibre].EndInt[coun_shift];
   prior=Intersection_measure(beg1,end1,beg2,end2,&greater,&comp1,&comp2,&inter_length);
   length2=end2-beg2+1;
   interval_signif2=StripCur->IntAllInformGray[fibre].Signif[coun_shift];
   dense2=(4*interval_signif2)/length2;
   comp_density=(16*dense2)/(dense1+dense2);
   if((comp_density>=5)&&(comp_density<=10)&&(comp2>=6))
	  {
      added_signif+=(interval_signif2*inter_length)/length2;
	  
	      if(comp1>fitness_number)
		  {
		  fitness_number=comp1;
		  fit_num=coun_shift;
		  }
		  
	  }
   }
   *best_fit=fit_num;
   *additional_signif=added_signif;
}
	//----------------------------------------------------------------------------
	void

CBunchGray::ChainAssignment(int* record_list,int first_member,int chain_length)
{
	int label_ind;
	int start_int;
	int end_int;

	start_int=first_member;
	label_ind=-start_int;
	end_int=first_member+chain_length-1;
*(record_list+first_member-1)=end_int;
	for(int coun_chain=start_int;coun_chain<=end_int;coun_chain++)
   {
   *(record_list+coun_chain)=label_ind;
   }
}
	//----------------------------------------------------------------------------
	void

CBunchGray::FindingLocalBackgroundGrains(int* adjac_link,int* lower_left,int* upper_left,
int* lower_right,int* upper_right,int* int_intensity,int* int_old_number,
int* new_num,int* local_signif_sum,int* local_background,int* valuable_interv,int* value_of_place)
{
	int signif_sum;
	int adjacent_linked;
	int beg0,end0;
	int interv_intensity,interv_number;
	int interv_number1;
	int new_lower_left,new_upper_left,new_lower_right,new_upper_right;
	int adjacent_intensity;
	int found_greater,found_greater1;
	int density_of_interval;

	found_greater=-1;
	found_greater1=-1;

	for(int coun_int=0;coun_int<TotalNumInt;coun_int++)
   {
	   signif_sum=*(local_signif_sum+coun_int);
	   adjacent_linked=*(adjac_link+coun_int);
	   if((adjacent_linked>=0)&&(signif_sum>0))
	   {
		 interv_intensity=*(int_intensity+coun_int);
	     interv_number=*(int_old_number+coun_int);
		 beg0=StripCur->IntAllInformGray[interv_intensity].BegInt[interv_number];
		 new_lower_left=*(lower_left+coun_int);
		 new_lower_right=*(lower_right+coun_int);
		   if(adjacent_linked>0)
		   {
		   interv_number1=*(int_old_number+adjacent_linked);
		   end0=StripCur->IntAllInformGray[interv_intensity].EndInt[interv_number1];
		   new_upper_left=*(upper_left+adjacent_linked);
		   new_upper_right=*(upper_right+adjacent_linked);
		   }
		   else
		   {
		   new_upper_left=*(upper_left+coun_int);
		   new_upper_right=*(upper_right+coun_int);
		   end0=StripCur->IntAllInformGray[interv_intensity].EndInt[interv_number];
		   }
		   adjacent_intensity=interv_intensity-1;
		       if((new_lower_left>=0)&&(adjacent_intensity>=0))
			   {
		   LocalComparison(beg0,end0,signif_sum,adjacent_intensity,new_lower_left,
new_upper_left,&found_greater,new_num,local_signif_sum);
			   }
			   adjacent_intensity=interv_intensity+1;
			   if((new_lower_right>=0)&&(adjacent_intensity<NUM_INTEN1))
			   {
			LocalComparison(beg0,end0,signif_sum,adjacent_intensity,new_lower_right,
new_upper_right,&found_greater1,new_num,local_signif_sum);
			   }
			   if((found_greater>=0)||(found_greater1>=0))
			   {
			   *(local_background+coun_int)=1;
			   }
			   else
			   {
				   density_of_interval=(4*signif_sum)/(end0-beg0+1);
Strip_value_painting_secondary(beg0,end0,coun_int,density_of_interval,valuable_interv,
value_of_place);
*(BackgroundGrains+coun_int)=NumberOfBackgroundGrains;
*(BackgrGrainOldNumber+NumberOfBackgroundGrains)=coun_int;
NumberOfBackgroundGrains++;
			   }
	   }
   }
}
	
//----------------------------------------------------------------------------
	void

CBunchGray::LocalComparison(int beg1,int end1,int signif,int fibre,int lower_bound,int upper_bound,
int* is_greater,int* new_num,int* exten_signif)
{
	int beg2,end2;
	int interval_signif2;
	int comp1,comp2,greater,prior,inter_length;
	int extended_signif,max_signif;
	int new_number;
	int greater_found;
	

	
greater_found=-1;

	  if(lower_bound==upper_bound)
	  {
	  beg2=StripCur->IntAllInformGray[fibre].BegInt[lower_bound];
      end2=StripCur->IntAllInformGray[fibre].EndInt[lower_bound];
      prior=Intersection_measure(beg1,end1,beg2,end2,&greater,&comp1,&comp2,&inter_length);
      interval_signif2=StripCur->IntAllInformGray[fibre].Signif[lower_bound];
	  new_number=*(new_num+fibre*MaxNumInt+lower_bound);
	  extended_signif=*(exten_signif+new_number);
	  max_signif=max(extended_signif,interval_signif2);
       
		  if((prior<=1)&&(comp1>=5)&&(comp2>=5))
		  {
           if(max_signif>signif)
		   {
			   greater_found=lower_bound;
		   }
		   
		     
		  }
	  *is_greater=greater_found;
	  return;
	  }
	  
for(int coun_shift=lower_bound;coun_shift<=upper_bound;coun_shift++)
   {
   beg2=StripCur->IntAllInformGray[fibre].BegInt[coun_shift];
   end2=StripCur->IntAllInformGray[fibre].EndInt[coun_shift];
   prior=Intersection_measure(beg1,end1,beg2,end2,&greater,&comp1,&comp2,&inter_length);
   interval_signif2=StripCur->IntAllInformGray[fibre].Signif[coun_shift];
   new_number=*(new_num+fibre*MaxNumInt+coun_shift);
	  extended_signif=*(exten_signif+new_number);
	  max_signif=max(extended_signif,interval_signif2);
      if((prior<=1)&&(comp2>=6))
	  {
          if(max_signif>signif)
		   {
			greater_found=lower_bound;
			*is_greater=greater_found;
			return;
		   }
	      
	  }
   }
*is_greater=greater_found;   
}
//-----------------------------------------------------------------------------
void

CBunchGray::Strip_value_painting_secondary(int beg_int,int end_int,int num_int,int signif,
int* painted_strip_sc,int* intense_consistency_sc)
 {
int paint_coun;
int current_inhabitant;
int paint_start,paint_finish;
int val;

	paint_start=beg_int>>PRESSING;
	paint_finish=end_int>>PRESSING;
	for(paint_coun=paint_start;paint_coun<=paint_finish;paint_coun++)
	 {
		current_inhabitant=*(painted_strip_sc+paint_coun);

	  if(!current_inhabitant)
		{
		*(painted_strip_sc+paint_coun)=num_int+1;
		*(intense_consistency_sc+paint_coun)=signif;
		}
		 else
		 {
		  val=*(intense_consistency_sc+paint_coun);
			if(val<signif)
			{
		*(painted_strip_sc+paint_coun)=num_int+1;
		*(intense_consistency_sc+paint_coun)=signif;
			}
		 }

	 }

}
//-----------------------------------------------------------------------------


void

CBunchGray::ArrangeIntervals(int* valuable_interval,int* visibility,int* local_signif_sum,
int* local_background,int* interv_intensity,int* previous_number,int* lower_left,
int* upper_left,int* lower_right,int* upper_right,int* adjac_link,int* new_number)
{
	int signif_sum;
	int background_index;
	int interv_visibility;
	int MaxVisibility;
	int total_number,contin_number,contin_number1;
	int* interval_zone;
	int number_of_intervals[8];
	int inter_num;
	int zone_number;
	int corn_presense;
	int num_int;
	int bound_int;
	int grain_intensity;
	int grain_previous_number;
	int grain_lower_left,grain_upper_left,grain_lower_right,grain_upper_right;
	int adjacent_linked;
	int grain_beg,grain_end,grain_end0,dense0;
	int interv_number1;
	int contin_result,contin_result1;
	int clust_num;
	int interval_signif0;
	int extended_signif,additional_signif1;
	int additional_signif;
	int first_cont_interval,last_cont_interval,first_cont_interv1,last_cont_interv1;
	int joined_interv,total_joined_interv;
	int num_extent;
	int contin_intensity,contin_intensity1;
	int number_of_intersect_int;
	int lower_cand;
	int upper_cand;
	int lower_shift;
	int upper_shift;
	int failure_counter_left,failure_counter_right;
	long weighed_intensity;
	int added_weighed_intensity;

upper_shift=-1;
lower_shift=-1;		
contin_result=-1;
first_cont_interval=-1;
last_cont_interval=-1;
first_cont_interv1=-1;
last_cont_interv1=-1;
joined_interv=-1;
contin_number=-1;
contin_intensity=-1;
contin_intensity1=-1;
additional_signif1=-1;
additional_signif=-1;
num_extent=4;
NumberOflusters=0;

if(!NumberOfBackgroundGrains)
{
	return;
}
ClusterGrains= new int[NumberOfBackgroundGrains];
BegIntervOfClusters= new int[NumberOfBackgroundGrains];
EndIntervOfClusters= new int[NumberOfBackgroundGrains];
GrainIntensityIntervalOfClusters= new int[NumberOfBackgroundGrains];//not applied?
LowerIntensityOfClusters= new int[NumberOfBackgroundGrains];
UpperIntensityOfClusters= new int[NumberOfBackgroundGrains];
AverageIntensityOfClusters= new int[NumberOfBackgroundGrains];
SignificanceOfClusters= new int[NumberOfBackgroundGrains];
CardinalityOfClusters= new int[NumberOfBackgroundGrains];
	for(int space_go=0;space_go<PressedLength;space_go++)
  {
	corn_presense=*(valuable_interval+space_go);
	if(corn_presense)
	 {
	num_int=corn_presense-1;
	(*(visibility+num_int))++;
	 }
	  
  }
  MaxVisibility=0;
  memset(number_of_intervals,(int) '\0',sizeof(int)*(8));
  for(int interv_go=0;interv_go<TotalNumInt;interv_go++)
  {
signif_sum=*(local_signif_sum+interv_go);
background_index=*(local_background+interv_go);
        if((signif_sum>0)&&(!background_index))
		{
		interv_visibility=*(visibility+interv_go);
		
 if(interv_visibility>MaxVisibility)
 {
 MaxVisibility=interv_visibility;
 }
		}
  }

interval_zone=new int[8*NumberOfBackgroundGrains];

for(int count=0;count<NumberOfBackgroundGrains;count++)
	 {
	 total_number=*(BackgrGrainOldNumber+count);
	 interv_visibility=*(visibility+total_number);
	 zone_number=(interv_visibility*8)/(MaxVisibility+1);
	 inter_num=zone_number*NumberOfBackgroundGrains+
	 number_of_intervals[zone_number];
	 number_of_intervals[zone_number]++;
	 *(interval_zone+inter_num)=total_number;
	 }
           
	 for(int coun_zone=0;coun_zone<8;coun_zone++)
		{
		 inter_num=(7-coun_zone)*NumberOfBackgroundGrains;
		 bound_int=number_of_intervals[7-coun_zone];
 for(int cou_int=0;cou_int<bound_int;cou_int++)
 {
 total_number=*(interval_zone+inter_num+cou_int);
 extended_signif=0;
 clust_num=*(BackgroundClusters+total_number);
           if(!clust_num)
	        {
				
				additional_signif=0;
				additional_signif1=0;
 signif_sum=*(local_signif_sum+total_number);
 adjacent_linked=*(adjac_link+total_number);
 grain_intensity=*(interv_intensity+total_number);
 grain_previous_number=*(previous_number+total_number);
 interval_signif0=
StripCur->IntAllInformGray[grain_intensity].Signif[grain_previous_number];
	 //extended_signif+=interval_signif0;
	 extended_signif+=signif_sum;

 grain_beg=StripCur->IntAllInformGray[grain_intensity].BegInt[grain_previous_number];
 grain_end0=StripCur->IntAllInformGray[grain_intensity].EndInt[grain_previous_number];
 dense0=(4*interval_signif0)/(grain_end0-grain_beg+1);
 grain_lower_left=*(lower_left+total_number);
 grain_lower_right=*(lower_right+total_number);
        if(adjacent_linked>0)
		{
		interv_number1=*(previous_number+adjacent_linked);
		grain_end=StripCur->IntAllInformGray[grain_intensity].EndInt[interv_number1];
		grain_upper_left=*(upper_left+adjacent_linked);
		grain_upper_right=*(upper_right+adjacent_linked);
		for(int count_interv=total_number;count_interv<=adjacent_linked;count_interv++)
	           {
               *(BackgroundClusters+count_interv)=NumberOflusters+1;
		       }
		}
		else
		{
			*(BackgroundClusters+total_number)=NumberOflusters+1;
         grain_upper_left=*(upper_left+total_number);
         grain_upper_right=*(upper_right+total_number);
grain_end=StripCur->IntAllInformGray[grain_intensity].EndInt[grain_previous_number];
		}
		failure_counter_left=0;
		failure_counter_right=0;
		contin_intensity=-1;
		contin_intensity1=-1;
		ClusterGrains[NumberOflusters]=total_number;
		BegIntervOfClusters[NumberOflusters]=grain_beg;
		EndIntervOfClusters[NumberOflusters]=grain_end;
		total_joined_interv=1;
		weighed_intensity=((long)(grain_intensity))*((long)signif_sum);
		
              for(int count_cont=1;count_cont<=num_extent;count_cont++)
	           {
      if(grain_lower_left!=-1)
      {
contin_result=GrainsGrowing(total_number,grain_intensity,grain_previous_number,
grain_lower_left,grain_upper_left,grain_beg,grain_end,dense0,signif_sum,-count_cont,
adjacent_linked,new_number,local_signif_sum,&additional_signif,&first_cont_interval,
&last_cont_interval,&joined_interv,&added_weighed_intensity);
                 if(contin_result==1)
				 {
contin_intensity=grain_intensity-count_cont;
contin_number=*(new_number+contin_intensity*MaxNumInt+first_cont_interval);
number_of_intersect_int=last_cont_interval-first_cont_interval+1;
total_joined_interv+=joined_interv;
weighed_intensity+=(long)added_weighed_intensity;
lower_cand=*(lower_left+contin_number);
        if(lower_cand==-1)
		 {
lower_shift=FindingIntervalsWithAdjacent(contin_number+number_of_intersect_int,contin_number,1,
							 lower_left);
if(lower_shift!=-1)
{
grain_lower_left=*(lower_left+lower_shift);
}
else
{
grain_lower_left=-1;
}
		 }
		 else
		 {
			 grain_lower_left=lower_cand;
		 }
contin_number=*(new_number+contin_intensity*MaxNumInt+last_cont_interval);
upper_cand=*(upper_left+contin_number);
         if(upper_cand==-1)
		 {
upper_shift=FindingIntervalsWithAdjacent(contin_number-number_of_intersect_int,contin_number,-1,
							 upper_left);
if(upper_shift!=-1)
{
grain_upper_left=*(upper_left+upper_shift);
}
else
{
grain_upper_left=-1;
}
		 }
		 else
		 {
		 grain_upper_left=upper_cand;
		 }
extended_signif+=additional_signif;
         
				 }
				 else
				 {
					 grain_lower_left=-1;
					 grain_upper_left=-1;
					 failure_counter_left++;
//we can continue here the process if failure_counter_left is sufficiently small
				 }
	  }
	  else
	  {
		  contin_result=0;
		  additional_signif=0;
	  }
		  if(grain_lower_right!=-1)
		  {
contin_result1=GrainsGrowing(total_number,grain_intensity,grain_previous_number,
grain_lower_right,grain_upper_right,grain_beg,grain_end,dense0,signif_sum,count_cont,
adjacent_linked,new_number,local_signif_sum,&additional_signif1,&first_cont_interv1,
&last_cont_interv1,&joined_interv,&added_weighed_intensity);
                    if(contin_result1==1)
				 {
                 contin_intensity1=grain_intensity+count_cont;
            contin_number1=*(new_number+contin_intensity1*MaxNumInt+first_cont_interv1);
			number_of_intersect_int=last_cont_interv1-first_cont_interv1+1;
            total_joined_interv+=joined_interv;
			weighed_intensity+=(long)added_weighed_intensity;
                 lower_cand=*(lower_right+contin_number1);
				 if(lower_cand==-1)
		 {
lower_shift=FindingIntervalsWithAdjacent(contin_number1+number_of_intersect_int,contin_number1,1,
							 lower_right);
if(lower_shift!=-1)
{
grain_lower_right=*(lower_right+lower_shift);
}
else
{
grain_lower_right=-1;
}
		 }
		 else
		 {
			 grain_lower_right=lower_cand;
		 }
             contin_number1=*(new_number+contin_intensity1*MaxNumInt+last_cont_interv1);
                 upper_cand=*(upper_right+contin_number1);
				 if(upper_cand==-1)
		 {
upper_shift=FindingIntervalsWithAdjacent(contin_number1-number_of_intersect_int,
contin_number1,-1,upper_right);
if(upper_shift!=-1)
{
grain_upper_right=*(upper_right+upper_shift);
}
else
{
grain_upper_right=-1;
}
		 }
		 else
		 {
		 grain_upper_right=upper_cand;
		 }
				 extended_signif+=additional_signif1;
				 }
					else
					{
						grain_lower_right=-1;
						failure_counter_right++;
//we can continue here the process if failure_counter_right is sufficiently small
						/*if(failure_counter_right>=2)
						{
							break;
						}*/

						if((failure_counter_left>=1)&&(failure_counter_right>=1))
						{
							break;
						}
					}
		  }
		  else
		  {
		  contin_result1=0;
		  additional_signif=0;
		  }
	 
			}
			if(contin_intensity!=-1)
			{
			LowerIntensityOfClusters[NumberOflusters]=contin_intensity;
			}
			else
			{
			LowerIntensityOfClusters[NumberOflusters]=grain_intensity;
			}

			   if(contin_intensity1!=-1)
			    {
			    UpperIntensityOfClusters[NumberOflusters]=contin_intensity1;
			    }
			    else
			    {
			     UpperIntensityOfClusters[NumberOflusters]=grain_intensity;
			    }
			SignificanceOfClusters[NumberOflusters]=extended_signif;
			CardinalityOfClusters[NumberOflusters]=total_joined_interv;
AverageIntensityOfClusters[NumberOflusters]=
(int)(weighed_intensity/(long)extended_signif);
			NumberOflusters++;
 }
 } 
		}

    delete[] interval_zone;
}
//-----------------------------------------------------------------------------


int

CBunchGray::GrainsGrowing(int num_grain,int gr_intensity,int gr_prev_number,
int adjacent_lower_interv,int adjacent_upper_interv,int beg_grain,int end_grain,
int grain_dens0,int signif,int direct,int adj_link,int* new_num,int* local_signif_sum,
int* added_signif,int* starting_cont_interv,int* finishing_cont_interv,
int* joined_intervals,int* added_w_intens)
{
int beg2,end2;
int interval_signif2;
int comp1,comp2,greater,prior,inter_length;
int extended_signif,max_signif;
int new_intensity;
int extension_result;
int new_number;
int dens1;
int comp_density1;
int shift;
int number_of_intervals;
int total_signif,joined_signif,dense_signif;
int number_of_dense_int;
int number_of_joined_intervals;
int first_interval,last_interval;
int total_joined_length,joined_length;
int added_intens;
int grain_length;
int comp_total_length;
int dense_total;

first_interval=-1;
last_interval=-1;
extension_result=0;
number_of_joined_intervals=0;
number_of_dense_int=0;
        total_signif=0;
		dense_signif=0;
		joined_signif=0;
		max_signif=0;
		added_intens=0;
		comp_total_length=0;
		dense_total=0;
		grain_length=end_grain-beg_grain+1;
new_intensity=gr_intensity+direct;
shift=abs(direct);
new_number=*(new_num+new_intensity*MaxNumInt+adjacent_lower_interv);

	if(adjacent_lower_interv==adjacent_upper_interv)
	  {
	  beg2=StripCur->IntAllInformGray[new_intensity].BegInt[adjacent_lower_interv];
	  if(*(BackgroundClusters+new_number))
	  {
	  return(extension_result);
	  }
	  
      end2=StripCur->IntAllInformGray[new_intensity].EndInt[adjacent_lower_interv];
prior=
Intersection_measure(beg_grain,end_grain,beg2,end2,&greater,&comp1,&comp2,&inter_length);
interval_signif2=StripCur->IntAllInformGray[new_intensity].Signif[adjacent_lower_interv];
joined_length=end2-beg2+1;
	  dens1=(4*interval_signif2)/joined_length;
	  extended_signif=*(local_signif_sum+new_number);
	  max_signif=max(extended_signif,interval_signif2);
	  comp_density1=(16*dens1)/(dens1+grain_dens0);
	  if((prior<=1)&&(signif>max_signif))
	  {
		     if(comp2>=6)
			 {
		  if(((comp_density1>=6)&&(comp_density1<=10))||((shift<=2)&&(comp_density1>=3)&&
			  (comp_density1<=11)))
		  {
              
			  number_of_dense_int++;
			  number_of_joined_intervals++;
			  joined_signif+=interval_signif2;
			  added_intens=new_intensity*interval_signif2;
	          *(BackgroundClusters+new_number)=NumberOflusters+1;
BegIntervOfClusters[NumberOflusters]=min(BegIntervOfClusters[NumberOflusters],beg2);
EndIntervOfClusters[NumberOflusters]=max(EndIntervOfClusters[NumberOflusters],end2);
		  }
		  else
		  {
			  if(((shift<=2)&&(comp_density1>=2)&&(comp_density1<=10)&&(comp2>=7))||
				  ((comp2>=7)&&(shift==1)&&(comp_density1>=2)&&(comp_density1<=10))
				  ||
				  ((comp2>=7)&&(comp1>=7)&&(shift<=3)&&(comp_density1>=2)&&(comp_density1<=10)))

			  {
			  number_of_joined_intervals++;
			  *(BackgroundClusters+new_number)=NumberOflusters+1;
			  joined_signif+=interval_signif2;
			  
			  }
		  }
			 }
			 else
			{
				if((shift==1)&&(comp1<=2)&&(comp2>=5)&&(comp_density1>=6))
				{
			  *(BackgroundClusters+new_number)=NumberOflusters+1;
			  number_of_dense_int++;
			  number_of_joined_intervals++;
			  joined_signif+=interval_signif2;
			  added_intens=new_intensity*interval_signif2;
BegIntervOfClusters[NumberOflusters]=min(BegIntervOfClusters[NumberOflusters],beg2);
EndIntervOfClusters[NumberOflusters]=max(EndIntervOfClusters[NumberOflusters],end2);
				}
			}
	  }
	  *added_signif=joined_signif;
	  comp_total_length=(16*joined_length)/(joined_length+grain_length);
	    if(number_of_dense_int==1)
	     {
			 extension_result=1;
			 first_interval=adjacent_lower_interv;
			 last_interval=adjacent_lower_interv;
			 
		 }
		else
		{
			if(number_of_joined_intervals==1)
			{
				if(comp_total_length>=6)
		  {
		  extension_result=1;
		  first_interval=adjacent_lower_interv;
		  last_interval=adjacent_lower_interv;
		  }
		  else
		  {
				extension_result=2;
				first_interval=adjacent_lower_interv;
		        last_interval=adjacent_lower_interv;
		  }
				
			}
		}
	 *starting_cont_interv=first_interval;
	 *finishing_cont_interv=last_interval;
	 *joined_intervals=number_of_joined_intervals;
	 *added_w_intens=added_intens;
	  return(extension_result);
     }
	else
	{
		number_of_intervals=adjacent_upper_interv-adjacent_lower_interv+1;
		total_joined_length=0;
		
		
		for(int coun_int=adjacent_lower_interv;coun_int<=adjacent_upper_interv;coun_int++)
         {
			 new_number=*(new_num+new_intensity*MaxNumInt+coun_int);
			 if(!*(BackgroundClusters+new_number))
			 {
beg2=StripCur->IntAllInformGray[new_intensity].BegInt[coun_int];
end2=StripCur->IntAllInformGray[new_intensity].EndInt[coun_int];
         interval_signif2=
			 StripCur->IntAllInformGray[new_intensity].Signif[coun_int];
		 if(interval_signif2>max_signif)
		 {
		 max_signif=interval_signif2;
		 }
         prior=
Intersection_measure(beg_grain,end_grain,beg2,end2,&greater,&comp1,&comp2,&inter_length);
		 joined_length=end2-beg2+1;
dens1=(4*interval_signif2)/joined_length;
comp_density1=(16*dens1)/(dens1+grain_dens0);
if((prior<=1)&&(signif>interval_signif2))
	  {
	   
			if(comp2>=6)
			{
		  if(((comp_density1>=5)&&(comp_density1<=10))||((shift<=2)&&(comp_density1>=3)&&
			  (comp_density1<=11)))
		  {
		  number_of_dense_int++;
		  number_of_joined_intervals++;
	      *(BackgroundClusters+new_number)=NumberOflusters+1;
		  dense_signif+=interval_signif2;
          total_joined_length+=joined_length;
		  added_intens+=new_intensity*interval_signif2;
BegIntervOfClusters[NumberOflusters]=min(BegIntervOfClusters[NumberOflusters],beg2);
EndIntervOfClusters[NumberOflusters]=max(EndIntervOfClusters[NumberOflusters],end2);
		    if(first_interval==-1)
			{
            first_interval=coun_int;
			}
			last_interval=coun_int;
		  }
		  else
		  {
 if(((comp2>=7)&&(shift<=2)&&(comp_density1>=2)&&(comp_density1<=10))||
	 ((shift==1)&&(comp2>=7)&&(comp_density1>=2)&&(comp_density1<=10))
	 ||((comp2>=7)&&(comp1>=7)&&(shift<=3)&&(comp_density1>=2)&&(comp_density1<=10)))
			  {
			  *(BackgroundClusters+new_number)=NumberOflusters+1;
			  number_of_joined_intervals++;
			  joined_signif+=interval_signif2;
			  total_joined_length+=joined_length;
			  if(first_interval==-1)
			   {
               first_interval=coun_int;
			   }
			   last_interval=coun_int;
			  }
		  }
		  
			}
			else
			{
				if((shift==1)&&(comp1<=2)&&(comp2>=5)&&(comp_density1>=6)&&(comp_density1<=10))
				{
			  *(BackgroundClusters+new_number)=NumberOflusters+1;
			  number_of_dense_int++;
			  number_of_joined_intervals++;
			  dense_signif+=interval_signif2;
			  total_joined_length+=joined_length;
			  added_intens+=new_intensity*interval_signif2;
BegIntervOfClusters[NumberOflusters]=min(BegIntervOfClusters[NumberOflusters],beg2);
EndIntervOfClusters[NumberOflusters]=max(EndIntervOfClusters[NumberOflusters],end2);
			     if(first_interval==-1)
			     {
                 first_interval=coun_int;
			     }
				 last_interval=coun_int;
				}
			}
			
		
	  }
		 total_signif+=interval_signif2;
			 }
		 }
		 if(total_joined_length)
		 {
dense_total=(4*total_signif)/total_joined_length;
comp_total_length=(16*total_joined_length)/(total_joined_length+grain_length);
		 }
*added_signif=joined_signif+dense_signif;
      if(dense_signif)
	  {
		  extension_result=1;
	  }
	  else
	  {
		  if(comp_total_length>=6)
		  {
		  extension_result=1;
		  }
		  else
		  {
           extension_result=2;
		  }
	  }
	  *starting_cont_interv=first_interval;
	  *finishing_cont_interv=last_interval;
	  *joined_intervals=number_of_joined_intervals;
	  *added_w_intens=added_intens;
		return(extension_result);
	}
}
//-----------------------------------------------------------------------------


int

CBunchGray::FindingIntervalsWithAdjacent(int last_member,int first_member,int direc,
int* boundary_int)
{
	int param;
	int new_member;

new_member=-1;
param=first_member+direc;
while(param!=last_member)
{
	if(*(boundary_int+param)!=-1)
	{
new_member=param;
break;
	}
param+=direc;
}

return(new_member);
	
}
