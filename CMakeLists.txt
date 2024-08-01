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
    src/rrenvironment/actions.hpp 
    src/rrenvironment/wiring.hpp
    src/rrenvironment/wiring/wiringgpio.cpp
    src/rrenvironment/actions/l298.hpp
    src/rrenvironment/actions/l298.cpp
    src/rrenvironment/observers.hpp
    src/rrenvironment/observers/hcsr04.hpp
    src/rrenvironment/observers/hcsr04.cpp
    src/rrenvironment/componentfact.hpp
    src/rrenvironment/componentfact.cpp
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
target_link_libraries(rrenvironment /usr/lib/libwiringPi.so)

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
# Test H Driver
include_directories(src)
add_executable(test_l298 test/test_l298.cpp)
target_link_libraries(test_l298 rrenvironment)
target_link_libraries(test_l298 dlib)
add_test(NAME test_l298
         COMMAND test_l298)

# Test ultra sonic
include_directories(src)
add_executable(test_hcsr04 test/test_hcsr04.cpp)
target_link_libraries(test_hcsr04 rrenvironment)
target_link_libraries(test_hcsr04 dlib)
add_test(NAME test_hcsr04
         COMMAND test_hcsr04)


include_directories(src)
add_executable(test_component_fact test/test_component_fact.cpp)
target_link_libraries(test_component_fact rrenvironment)
target_link_libraries(test_component_fact dlib)
add_test(NAME test_component_fact
        COMMAND test_component_fact)

