# https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html

cmake_minimum_required(VERSION 3.25)
project(rrenvironment DESCRIPTION "raspberry pi 4b drivers" LANGUAGES CXX)

include(FetchContent)
include(FindPkgConfig)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CPACK_PACKAGE_NAME "rrenvironment")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
set(JSON_VERSION v3.11.3)
set(rrenvironment_SOURCES 
    src/rrenvironment/rrenvironment.cpp
    src/rrenvironment/Actions.hpp 
    src/rrenvironment/Wiring.hpp
)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "wiringpi, wiringpi (>= 3.2)")
set(PUBLIC_HEADER include/rr_logger_hook.hpp)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/${JSON_VERSION}/json.tar.xz)
FetchContent_MakeAvailable(json)
list(APPEND CMAKE_MODULE_PATH ${nlohmann_json})
include_directories(${json_SOURCE_DIR}/include include)

pkg_search_module(DLIB REQUIRED dlib-1)

#  /usr/local/lib/pkgconfig/dlib-1.pc

# Create library outline
add_library(rrenvironment SHARED  ${rrenvironment_SOURCES} )

# install locations
configure_file(rrenvironment.pc.in rrenvironment.pc @ONLY)
install(
    TARGETS rrenvironment
    LIBRARY DESTINATION ${RR_LIBRARY_OUTPUT}
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    PUBLIC_HEADER DESTINATION ${RR_PUBLIC_HEADER}
)

enable_testing()

# Test components
include_directories(src)
add_executable(test_l298 test/test_l298.cpp)
target_link_libraries(test_l298 /usr/lib/libwiringPi.so)
target_link_libraries(test_l298 rrenvironment)
target_link_libraries(test_l298 dlib)
add_test(NAME test_l298
         COMMAND test_l298)

