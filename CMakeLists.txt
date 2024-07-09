# https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html

cmake_minimum_required(VERSION 3.25)
project(rrenvironment DESCRIPTION "raspberry pi 4b drivers" LANGUAGES CXX)

set(CPACK_PACKAGE_NAME "rrenvironment")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/rrobot")
set(VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

set(DLIB_VERSION v19.24)
set(JSON_VERSION v3.11.3)
set(source_file_prefix src/rrenvironment)
set(source_files ${source_file_prefix}/rrenvironment.cpp  
    ${source_file_prefix}/rrenvironment.hpp
    ${source_file_prefix}/components/component.hpp
    ${source_file_prefix}/components/l298.hpp
)

include(FetchContent)
FetchContent_Declare(dlib
    GIT_REPOSITORY https://github.com/davisking/dlib.git
    GIT_TAG        ${DLIB_VERSION}
)
FetchContent_MakeAvailable(dlib)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/${JSON_VERSION}/json.tar.xz)
FetchContent_MakeAvailable(json)
list(APPEND CMAKE_MODULE_PATH ${nlohmann_json})

# Add include paths
include_directories(${json_SOURCE_DIR}/include)
include_directories(${dlib_SOURCE_DIR})
include_directories(src)

# Create library outline
add_library(rrenvironment SHARED ${source_files})
target_link_libraries(rrenvironment dlib::dlib)
target_include_directories(rrenvironment PUBLIC ${source_files})

# Create library install locatons
string(APPEND RR_LIBRARY_OUTPUT  "/opt/rrobots/lib/" ${PROJECT_NAME})
string(APPEND RR_PUBLIC_HEADER "/opt/rrobots/include/" ${PROJECT_NAME})

# Create install setup
set_target_properties(rrenvironment PROPERTIES SOVERSION ${PROJECT_VERSION} VERSION ${PROJECT_VERSION} LINKER_LANGUAGE CXX)
set_target_properties(rrenvironment PROPERTIES PUBLIC_HEADER ${source_file_prefix}/rrenvironment.hpp)


# # Test builds
include(CTest)
add_executable(Testl298 test/components/test-l298.cpp)
target_link_libraries(Testl298 rrenvironment)
# enable_testing()

# add_test(NAME mytest COMMAND testDriver --config $<CONFIG> --exe $<TARGET_FILE:myexe>)

# install locations
configure_file(rrenvironment.pc.in rrenvironment.pc @ONLY)
install(
    TARGETS rrenvironment
    LIBRARY DESTINATION ${RR_LIBRARY_OUTPUT}
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    PUBLIC_HEADER DESTINATION ${RR_PUBLIC_HEADER}
)


