# https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html

cmake_minimum_required(VERSION 3.25)
project(rrenvironment 
    VERSION 1.0.1 
    DESCRIPTION "raspberry pi 4b drivers"
    LANGUAGES CXX)



add_library(rrenvironment SHARED include/rrenvironment/AbstractAction.hpp)

# https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

set(RR_LIBRARY_OUTPUT ${LIBDIR})
set(RR_PUBLIC_HEADER   ${INCLUDEDIR})

set_target_properties(rrenvironment PROPERTIES SOVERSION ${PROJECT_VERSION} VERSION ${PROJECT_VERSION} LINKER_LANGUAGE CXX)
set_target_properties(rrenvironment PROPERTIES PUBLIC_HEADER include/rrenvironment/AbstractAction.hpp)
configure_file(rrenvironment.pc.in rrenvironment.pc @ONLY)
install(
    TARGETS rrenvironment
    LIBRARY DESTINATION ${RR_LIBRARY_OUTPUT}
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    PUBLIC_HEADER DESTINATION ${RR_PUBLIC_HEADER}
)


