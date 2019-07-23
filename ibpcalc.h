/*
   Invasive blood pressure parameters calculation library.
   This library contains the algorithm to calculate the systolic and diastolic
   pressures (in mmHg) of the buffer passed as argument to the ibpCalc function.

   Author: Luiz Gustavo
   Date: 20-jul-2019
*/

/*
   Structure that contains the numerics of the Ibp parameter.
*/
struct IbpNumerics {
   int sys;
   int sysIndex;
   int dia;
   int diaIndex;
};

/*
   Function to calculate the Ibp parameters, stored in the IbpParam structure.
   Returns 0 if success and -1 if fail.
*/
int ibpCalc(const char* buf, int size, int index, struct IbpNumerics* const numerics);

