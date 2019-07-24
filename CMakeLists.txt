cmake_minimum_required(VERSION 2.9)

project (ibpcalc)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

add_library(ibpcalc SHARED ibpcalc.c)

enable_testing()

add_executable (ibpcalc_test ibpcalc_test.c ibpcalc.c)

target_link_libraries(ibpcalc_test -lcunit)

add_test (ibpcalc_test ${EXECUTABLE_OUTPUT_PATH}/ibpcalc_test)
