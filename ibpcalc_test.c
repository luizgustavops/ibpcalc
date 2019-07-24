#include <stdio.h>
#include <CUnit/Basic.h>
#include "ibpcalc.h"

char testBuffer1[] = { 80,80,80,80,80,80,80,81,81,85,92,100,106,116,119,119,119,117,115,110,107,107,107,108,107,105,
100,99,97,93,92,90,87,86,84,83,83,82,82,82,82,81,81,81,81,80,80,80,80,80,80,80,80,80,80,80,81,81,85,92,106,112,116,119,119,
119,117,112,110,107,107,108,108,105,102,100,97,95,93,90,89,87,84,84,83,83,82,82,82,81,81,81,81,80,80,80,80,80,80,80,80,80,
80,80,80,81,81,85,100,106,112,119,119,119,117,115,112,107,107,107,108,107,105,100,99,97,95,92,90,89,86,84,84,83,82,82,82,
82,81,81,81,81,80,80,80,80,80,80,80,80,80,80,80,81,81,85,92,100,112,116,119,119,120,117,112,110,107,107,108,108,107,102,100,
99,95,93,92,89,87,86,84,83,83,82,82,82,82,81,81,81,80,80,80,80,80,80,80,80,80,80,80,80,81,81,85,100,106,112,116,119,119,119,
115,112,110,107,107,108,107,105,102,99,97,95,92,90,89,86,84,84,83,82,82,82,82,81,81,81,81,80,80,80,80,80,80,80,80,80,80,80,
81,81,81,92,100,106,116,119,119,119,117,115,110,107,107,108,108,107,102,100,99,97,93,92,90,87,86,84,83,83,82,82,82,82,81,81,
81,80,80,80,80,80,80,80,80,80,80,80,80,81,81,85,92,106,112,116,119,119,119,115,112,110,107,107,108,108,105,102,100,97,95,93,
90,89,87,84,84,83,82,82,82,82,81,81,81,81,80,80,80,80};

char testBuffer2[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                     };


void ibpcalc_test_example()
{
   struct IbpNumerics ibpNum;
   // Example test
   int result = ibpCalc(testBuffer1, sizeof(testBuffer1)/sizeof(testBuffer1[0]), 160, &ibpNum);
   if (result != SUCCESS || ibpNum.sys != 120 || ibpNum.sysIndex != 162 || ibpNum.dia != 80 || ibpNum.diaIndex != 152)
      CU_ASSERT(0);
}

void ibpcalc_test_boundary()
{
   struct IbpNumerics ibpNum;
   // Boundary conditions
   int result = ibpCalc(testBuffer1, sizeof(testBuffer1)/sizeof(testBuffer1[0]), 185, &ibpNum);
   if (result != SUCCESS || ibpNum.sys != 120 || ibpNum.sysIndex != 162 || ibpNum.dia != 80 || ibpNum.diaIndex != 190)
      CU_ASSERT(0);

   result = ibpCalc(testBuffer1, sizeof(testBuffer1)/sizeof(testBuffer1[0]), 186, &ibpNum);
   if (result != SUCCESS || ibpNum.sys != 119 || ibpNum.sysIndex != 209 || ibpNum.dia != 80 || ibpNum.diaIndex != 190)
      CU_ASSERT(0);
}

void ibpcalc_test_start()
{
   struct IbpNumerics ibpNum;
   // Near the start of the buffer - the start is not considered a valley!
   int result = ibpCalc(testBuffer1, sizeof(testBuffer1)/sizeof(testBuffer1[0]), 6, &ibpNum);
   if (result != SUCCESS || ibpNum.sys != 119 || ibpNum.sysIndex != 14 || ibpNum.dia != 80 || ibpNum.diaIndex != 45)
      CU_ASSERT(0);
}

void ibpcalc_test_end()
{
   struct IbpNumerics ibpNum;
   // Near the end of the buffer - the end is not considered a valley!
   int result = ibpCalc(testBuffer1, sizeof(testBuffer1)/sizeof(testBuffer1[0]), 336, &ibpNum);
   if (result != SUCCESS || ibpNum.sys != 119 || ibpNum.sysIndex != 308 || ibpNum.dia != 80 || ibpNum.diaIndex != 298)
      CU_ASSERT(0);
}

void ibpcalc_test_empty()
{
   struct IbpNumerics ibpNum;
   // Test with no peaks and valleys
   int result = ibpCalc(testBuffer2, sizeof(testBuffer2)/sizeof(testBuffer2[0]), 160, &ibpNum);
   if (result != FAIL)
      CU_ASSERT(0);
}

int main()
{
   CU_pSuite pSuite = NULL;

   // Initialize the CUnit test registry
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   // Sets the basic run mode, CU_BRM_VERBOSE will show maximum output of run details
   // Other choices are: CU_BRM_SILENT and CU_BRM_NORMAL
   CU_basic_set_mode(CU_BRM_VERBOSE);

   // Add a suite to the registry
   pSuite = CU_add_suite("ibpcalc_test_suite", 0, 0);
   // Check if add was successful
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   // Add the tests to the suite
   if (NULL == CU_add_test(pSuite, "ibpcalc_test_example", ibpcalc_test_example)) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if (NULL == CU_add_test(pSuite, "ibpcalc_test_boundary", ibpcalc_test_boundary)) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if (NULL == CU_add_test(pSuite, "ibpcalc_test_start", ibpcalc_test_start)) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if (NULL == CU_add_test(pSuite, "ibpcalc_test_end", ibpcalc_test_end)) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if (NULL == CU_add_test(pSuite, "ibpcalc_test_empty", ibpcalc_test_empty)) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run the tests and show the run summary
   CU_basic_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}
