# https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html

cmake_minimum_required(VERSION 3.25)
project(rrenvironment 
    VERSION 1.0.1 
    DESCRIPTION "raspberry pi 4b drivers"
    LANGUAGES CXX)

set(DLIB_VERSION v19.24)
set(JSON_VERSION v3.11.3)


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

# Create library outline
add_library(rrenvironment SHARED src/rrenvironment/rrenvironment.hpp)
target_link_libraries(rrenvironment dlib::dlib)

# Create library install locatons
string(APPEND RR_LIBRARY_OUTPUT  "/opt/rrobots/lib/" ${PROJECT_NAME})
string(APPEND RR_PUBLIC_HEADER "/opt/rrobots/include/" ${PROJECT_NAME})

# Create install setup
set_target_properties(rrenvironment PROPERTIES SOVERSION ${PROJECT_VERSION} VERSION ${PROJECT_VERSION} LINKER_LANGUAGE CXX)
set_target_properties(rrenvironment PROPERTIES PUBLIC_HEADER src/rrenvironment/rrenvironment.hpp)
configure_file(rrenvironment.pc.in rrenvironment.pc @ONLY)
install(
    TARGETS rrenvironment
    LIBRARY DESTINATION ${RR_LIBRARY_OUTPUT}
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    PUBLIC_HEADER DESTINATION ${RR_PUBLIC_HEADER}
)


