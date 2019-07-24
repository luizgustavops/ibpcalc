# ibpcalc

Exercise on calculating the systolic and diastolic pressures in an Ibp
waveform buffer.

* API call example:

     #include "ibpcalc.h"
     
     IbpNumerics numerics;
     
     int result = ibpCalc(buffer, size, index, &numerics);

* Limitation:

     A 10 bpm is the lowest heart rate this algorithm can work. This was defined to
     limit the search of the systolic and diastolic values despite the size of
     the input buffer, resulting in a cost of O(1), suitable for this type of
     application.

* Installation:

     Copy the ".so" library to the '/usr/lib' folder.

* Build environment:

     Ubuntu 16.04.2 LTS (xenial) x86_64

* Build requirements - Tool (package)

     cmake 3.5.1 (cmake cmake-data)
     
     make 4.1  (make)
     
     gcc 4.7.4 (gcc-4.7 gcc-4.7-base:amd64)
     
     CUnit 2.1-3 (libcunit1-dev libcunit1-doc libcunit1)
     
     cppcheck (cppcheck libtinyxml2-2v5 python-chardet python-pkg-resources python-pygments)
     
     valgrind (valgrind)

* How to build

     cmake .
     
     make (will generate the libibpcalc.so library and ibpcalc_test unit tests binary)
     
     make test (check the result log in the Testing dir)

* Static and dynamic analysis

     The static analysis is done with cppcheck command:
     
     ./static_analysis.sh

     The dynamic analysis is done with valgrind. After building the 'ibpcalc_test' application,
     run the following command:
     
     ./dynamic_analysis.sh

* Additional documentation

     Please read the doc/ directory files for algorithm explanation and the coding
     style used in this project.     
