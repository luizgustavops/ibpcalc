/*
   The Ibp numerics calculation library implementation.
*/
#include <stdio.h>
#include <limits.h>
#include "ibpcalc.h"

#define MAXSEARCH 2

int isPeak(const char* buf, int size, int i)
{
   if (i > 0 && i < size-1) {
      if (buf[i-1] < buf[i] && buf[i] > buf[i+1]) {
         return 1;  
      }
      // Forward search
      else if (buf[i-1] < buf[i] && buf[i] == buf[i+1]) {
          // Maybe found a valley, lets look at the next elements
          int j = i;
          while(j < size && buf[j] == buf[j+1])
              j++;

          if (buf[j+1] < buf[j])
              return 1;
      }
      // Backward search
      else if (buf[i+1] < buf[i] && buf[i] == buf[i-1]) {
          // Look at the previous elements
          int j = i;
          while (j > 0 && buf[j] == buf[j-1])
              j--;

          if (buf[j-1] < buf[j])
              return 1;
      }
   }

   return 0;
}

int isValley(const char* buf, int size, int i)
{
   if (i > 0 && i < size-1) {
      if (buf[i-1] > buf[i] && buf[i] < buf[i+1]) {
         return 1;
      }
      // Forward search
      else if (buf[i-1] > buf[i] && buf[i] == buf[i+1]) {
          // Maybe found a valley, lets look at the next elements
          int j = i;
          while(j < size && buf[j] == buf[j+1])
              j++;

          if (buf[j+1] > buf[j])
              return 1;
      }
      // Backward search
      else if (buf[i+1] > buf[i] && buf[i] == buf[i-1]) {
          // Look at the previous elements
          int j = i;
          while (j > 0 && buf[j] == buf[j-1])
              j--;

          if (buf[j-1] > buf[j])
              return 1;
      }

   }

   return 0;
}

int ibpCalc(const char* buf, int size, int index, struct IbpParam* const params)
{    
   struct Sample {
      int value;
      int index;
   };

   struct Sample forwardMax[MAXSEARCH], forwardMin[MAXSEARCH],
                 backwardMax[MAXSEARCH], backwardMin[MAXSEARCH];
   int i = 0, iMax, iMin;

   printf("Size=%d, index=%d\n", size, index);

   // Initialize variables
   for(i = 0; i < MAXSEARCH; i++) {
      forwardMax[i].value = INT_MIN;
      forwardMax[i].index = -1;

      backwardMax[i].value = INT_MIN;
      backwardMax[i].index = -1;

      forwardMin[i].value = INT_MAX;
      forwardMin[i].index = -1;

      backwardMin[i].value = INT_MAX;
      backwardMin[i].index = -1;      
   }

   iMax = 0;
   iMin = 0;
   // Search FORWARD for, at maximum, MAXSEARCH peaks or MAXSEARCH valleys
   for(i = index; (i < size && (iMax < MAXSEARCH || iMin < MAXSEARCH)); i++) {

      printf("FORWARD search index = %d, value = %d, iMax = %d, iMin = %d\n", i, buf[i], iMax, iMin);

      if (isPeak(buf, size, i)) {
         forwardMax[iMax].value = buf[i];
         forwardMax[iMax].index = i;
         iMax++;
         printf(" + Found Max\n");
      }
      else if (isValley(buf, size, i)) {
         forwardMin[iMin].value = buf[i];
         forwardMin[iMin].index = i;
         iMin++;
         printf(" - Found Min\n");
      }
   }

   printf("\n");

   iMax = 0;
   iMin = 0;
   // Search BACKWARD for, at maximum, MAXSEARCH peaks or MAXSEARCH valleys
   for(i = index; (i > 0 && (iMax < MAXSEARCH || iMin < MAXSEARCH)); i--) {

      printf("BACKWARD search index = %d, value = %d, iMax = %d, iMin = %d\n", i, buf[i], iMax, iMin);

      if (isPeak(buf, size, i)) {
         backwardMax[iMax].value = buf[i];
         backwardMax[iMax].index = i;
         iMax++;
         printf(" + Found Max\n");
      }
      else if (isValley(buf, size, i)) {
         backwardMin[iMin].value = buf[i];
         backwardMin[iMin].index = i;
         iMin++;
         printf(" - Found Min\n");
      }
   }

   for(i = 0; i < MAXSEARCH; i++) {
      printf("\nForwardMax = %d [%d], ForwardMin = %d [%d].\n", forwardMax[i].value, forwardMax[i].index,
                                                                forwardMin[i].value, forwardMin[i].index);
   }
   for(i = 0; i < MAXSEARCH; i++) {
      printf("\nBackwardMax = %d [%d], BackwardMin = %d [%d].\n", backwardMax[i].value, backwardMax[i].index,
                                                                  backwardMin[i].value, backwardMin[i].index);
   }
   
   return 0;
}




