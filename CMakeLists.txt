cmake_minimum_required(VERSION 2.9)

project (ibpcalc)
set(CMAKE_BUILD_TYPE Release)

option(BUILD_DOC "Build documentation" ON)

# If Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doc/doxygen_ibpcalc)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Add doxygen target ALL to build documentation and application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating doxygen documentation"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen not found!")
endif (DOXYGEN_FOUND)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

add_library(ibpcalc SHARED ibpcalc.c)

enable_testing()

add_executable (ibpcalc_test ibpcalc_test.c ibpcalc.c)

target_link_libraries(ibpcalc_test -lcunit)

add_test (ibpcalc_test ${EXECUTABLE_OUTPUT_PATH}/ibpcalc_test)
