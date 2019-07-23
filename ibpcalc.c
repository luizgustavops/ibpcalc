/*
   The Ibp numerics calculation library implementation.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ibpcalc.h"

// Local definitions
#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define FAIL -1

// Because of the given IBP waveform characteristic
// shape, we need to search only for 2 peaks and to
// valleys forward and backward to find the nearest
// systolic and diastolic pressure values.
#define MAXSEARCH 2

// Debug on/off
#define print printf
//#define print //

// Local functions

int isPeak(const char* buf, int size, int i)
{
   if (i > 0 && i < size-1) {
      if (buf[i-1] < buf[i] && buf[i] > buf[i+1]) {
         return TRUE;
      }
      // Forward search
      else if (buf[i-1] < buf[i] && buf[i] == buf[i+1]) {
          // Maybe found a valley, lets look at the next elements
          int j = i;
          while(j < size && buf[j] == buf[j+1])
              j++;

          if (buf[j+1] < buf[j])
              return TRUE;
      }
      // Backward search
      else if (buf[i+1] < buf[i] && buf[i] == buf[i-1]) {
          // Look at the previous elements
          int j = i;
          while (j > 0 && buf[j] == buf[j-1])
              j--;

          if (buf[j-1] < buf[j])
              return TRUE;
      }
   }

   return FALSE;
}

int isValley(const char* buf, int size, int i)
{
   if (i > 0 && i < size-1) {
      if (buf[i-1] > buf[i] && buf[i] < buf[i+1]) {
         return TRUE;
      }
      // Forward search
      else if (buf[i-1] > buf[i] && buf[i] == buf[i+1]) {
          // Maybe found a valley, lets look at the next elements
          int j = i;
          while(j < size && buf[j] == buf[j+1])
              j++;

          if (buf[j+1] > buf[j])
              return TRUE;
      }
      // Backward search
      else if (buf[i+1] > buf[i] && buf[i] == buf[i-1]) {
          // Look at the previous elements
          int j = i;
          while (j > 0 && buf[j] == buf[j-1])
              j--;

          if (buf[j-1] > buf[j])
              return TRUE;
      }

   }

   return FALSE;
}


// The ibpCalc function

int ibpCalc(const char* buf, int size, int index, struct IbpNumerics* const numerics)
{    
   struct Sample {
      int value;
      int index;
   };

   // Local variables to store the search result of the forward and backward peaks and valleys
   struct Sample fwMax, fwMin, bwMax, bwMin;

   // Local variables to store the overall values of max and min found
   const struct Sample* max = NULL;
   const struct Sample* min = NULL;

   // Local aux variables
   int i = 0, maxSamples, iMax, iMin;

   print("Size=%d, index=%d\n", size, index);

   // Initialize variables
   fwMax.value = INT_MIN;
   fwMax.index = -1;
   bwMax.value = INT_MIN;
   bwMax.index = -1;

   fwMin.value = INT_MAX;
   fwMin.index = -1;
   bwMin.value = INT_MAX;
   bwMin.index = -1;

   iMax = 0;
   iMin = 0;

   // Limit the search to 6 seconds of waveform to find a heartbeat.
   //
   // A 10 bpm is the lowest heart rate this algorithm can work. This will limit
   // the search despite of the size of the buffer informed to the algorithm,
   // resulting in a cost of O(1).
   // As we have 8ms between samples, the max samples to be searched will be
   // 6000ms / 8ms = 750 samples, 375 samples for each side (forward and backward).
   maxSamples = 375;

   // Search FORWARD for, at maximum, MAXSEARCH peaks or MAXSEARCH valleys.
   for(i = index; (i < (index + maxSamples) && i < size && (iMax < MAXSEARCH && iMin < MAXSEARCH)); i++) {

      print("FORWARD search index = %3d, value = %3d, iMax = %3d, iMin = %3d\n", i, buf[i], iMax, iMin);

      if (isPeak(buf, index + maxSamples, i)) {

         if (buf[i] > fwMax.value || (buf[i] == fwMax.value && abs(index - i) < abs(index - fwMax.index))) {
             fwMax.value = buf[i];
             fwMax.index = i;
             print(" + Found Max [%d][%d]\n", buf[i], i);
             iMax++;
         }

      }
      else if (isValley(buf, index + maxSamples, i)) {

         if (buf[i] < fwMin.value || (buf[i] == fwMin.value && abs(index - i) < abs(index - fwMin.index))) {
            fwMin.value = buf[i];
            fwMin.index = i;
            print(" - Found Min [%d][%d]\n", buf[i], i);
            iMin++;
         }

      }
   }

   print("\n");

   iMax = 0;
   iMin = 0;

   // Search BACKWARD for, at maximum, MAXSEARCH peaks or MAXSEARCH valleys
   for(i = index; (i > (index - maxSamples) && i >= 0 && (iMax < MAXSEARCH && iMin < MAXSEARCH)); i--) {

      print("BACKWARD search index = %3d, value = %3d, iMax = %3d, iMin = %3d\n", i, buf[i], iMax, iMin);

      if (isPeak(buf, index + maxSamples, i)) {

         // Check for peak with nearest index
         if (buf[i] > bwMax.value || (buf[i] == bwMax.value && abs(index - i) < abs(index - bwMax.index))) {
            bwMax.value = buf[i];
            bwMax.index = i;
            print(" + Found Max [%d][%d]\n", buf[i], i);
            iMax++;
         }

      }
      else if (isValley(buf, index + maxSamples, i)) {

         // Check for valley with nearest index
         if (buf[i] < bwMin.value || (buf[i] == bwMin.value && abs(index - i) < abs(index - bwMin.index))) {
            bwMin.value = buf[i];
            bwMin.index = i;
            print(" - Found Min [%d][%d]\n", buf[i], i);
            iMin++;
         }

      }
   }

   // Debug
   print("\nForwardMax = %d [%d], ForwardMin = %d [%d].\n", fwMax.value, fwMax.index,
                                                            fwMin.value, fwMin.index);

   print("\nBackwardMax = %d [%d], BackwardMin = %d [%d].\n", bwMax.value, bwMax.index,
                                                              bwMin.value, bwMin.index);

   // Calculate the closest peak
   if (fwMax.index != -1 && bwMax.index != -1) {

      if (abs(index - fwMax.index) < abs(index - bwMax.index))
         max = &fwMax;
      else
         max = &bwMax;

   }
   else if (fwMax.index != -1)
       max = &fwMax;
   else if (bwMax.index != -1)
       max = &bwMax;

   // Calculate the closest valley
   if (fwMin.index != -1 && bwMin.index != -1) {

      if (abs(index - fwMin.index) < abs(index - bwMin.index))
         min = &fwMin;
      else
         min = &bwMin;

   }
   else if (fwMin.index != -1)
       min = &fwMin;
   else if (bwMin.index != -1)
       min = &bwMin;

   // Check if valid values were found
   if (max != NULL && min != NULL) {

       print("\nMax = %d [%d], Min = %d [%d].\n", max->value, max->index, min->value, min->index);

       numerics->sys      = max->value;
       numerics->sysIndex = max->index;

       numerics->dia      = min->value;
       numerics->diaIndex = min->index;

       return SUCCESS;
   }
   
   return FAIL;
}




