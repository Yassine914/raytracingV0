cmake_minimum_required(VERSION "3.20.x")

# Set to C++11
set(CMAKE_CXX_STANDARD              11 )
set(CMAKE_CXX_STANDARD_REQUIRED     ON )
set(CMAKE_CXX_EXTENSIONS            OFF )

set(PROJ_NAME raytracing)
set(SRC_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(PROJ_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# ___________ RAYTRACER V0 _________
project("${PROJ_NAME}" LANGUAGES CXX)

# ____ SRC ___
file(GLOB SRC CMAKE_CONFIGURE_DEPENDS "${SRC_DIR}/*/**.cpp")
add_executable("${PROJ_NAME}" "${SRC}" "src/main.cpp")
include_directories("${SRC_DIR}/")

# ____ DIRS ___
# for debug builds
target_compile_definitions("${PROJ_NAME}" PUBLIC RES_PATH="${PROJ_DIR}/res/")

# for release builds (make filepaths relative to the exe)
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RES_PATH="./res/")

# ____ LIBS ___

# NOTE: for stb_image.h
# set ( EXTERNAL
# src/external/stb_image.h
#  )

# GLFW
add_subdirectory("${LIB_DIR}/GLFW")
include_directories("${LIB_DIR}/GLFW/include")

# EIGEN 3
include_directories("${LIB_DIR}/Eigen/")

target_link_libraries("${PROJ_NAME}" PRIVATE glfw)

# ___ DEFINES ___
if(WIN32)
    target_compile_definitions("${PROJ_NAME}" PUBLIC _WIN32)
endif()

# ___ CL ARGS ___

# compiler flags

# linker flags
target_link_options("${PROJ_NAME}" PRIVATE -Wl,--no-undefined -luser32)


# _________ COMPILER OPTIONS ________
message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message (STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message (STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})

target_compile_options("${PROJ_NAME}" PRIVATE -Wall -Wextra) #-O2)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # /wd #### - Disable warning
    # /we #### - treat warning as error
    add_compile_options("/W4")      # Enable level-4 warnings
    add_compile_options("/we 4265") # Class has virtual functions, but its non-trivial destructor is not virtual
    add_compile_options("/we 5204") # Class has virtual functions, but its trivial destructor is not virtual
    add_compile_options("/wd 4100") # unreferenced formal parameter
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wmaybe-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wsometimes-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
endif()

