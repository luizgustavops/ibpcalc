/**
 * \file ibpcalc.h
 * \author Luiz Gustavo
 * \date 20-jul-2019
 * \brief Invasive blood pressure parameters calculation library.
 *        This library contains the algorithm to calculate the systolic and diastolic
 *        pressures (in mmHg) of the buffer informed as argument to the ibpCalc function.
 */
#ifndef IBPCALC_H
#define IBPCALC_H
/**
 * \def SUCCESS
 * \brief Code returned if the API function finds the sys and dia values.
 */
#define SUCCESS 0

/**
 * \def FAIL
 * \brief Code returned if the API function doesn't find the sys and dia values.
 */
#define FAIL -1

/**
 * \brief Structure that contains the numerics of the Ibp parameter.
 */
struct IbpNumerics {
   int sys;      ///< Systolic value 
   int sysIndex; ///< Systolic index
   int dia;      ///< Diastolic value
   int diaIndex; ///< Diastolic index
};

/**
 * \brief The function that calculates the nearest sys and dia values of an Ibp waveform.
 * \param buf The Ibp waveform buffer.
 * \param size Size of the Ibp waveform buffer.
 * \param index Reference index informed by the user.
 * \param numerics Structure to store and return the closest sys and dia values found.
 * \return SUCCESS if sys and dia values were found and FAIL otherwise.
 */
int ibpCalc(const char* buf, int size, int index, struct IbpNumerics* const numerics);

#endif // IBPCALC_H
