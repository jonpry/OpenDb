############################################################################
########################### Project Setup ##################################
############################################################################

# Setting CMake version properly to ensure correct policies behavior
cmake_minimum_required(VERSION 3.14...3.16)
# Setting up OpenDB project
project(odb VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

find_package(Python3 COMPONENTS Development REQUIRED)

find_package(SWIG 3.0 REQUIRED)
if (SWIG_VERSION VERSION_GREATER_EQUAL "4.1.0")
  message(STATUS "Using SWIG >= ${SWIG_VERSION} -flatstaticmethod flag for python")
endif()
include(UseSWIG)

# Configure build version
configure_file (
    "${PROJECT_SOURCE_DIR}/include/odb/version.hh.in"
    "${PROJECT_BINARY_DIR}/include/odb/version.hh"
)

############################################################################
################################# Targets ##################################
############################################################################

add_subdirectory(src/db)
add_subdirectory(src/defin)
add_subdirectory(src/defout)
add_subdirectory(src/lef)
add_subdirectory(src/lefin)
add_subdirectory(src/lefout)
add_subdirectory(src/def)
add_subdirectory(src/zutil)
add_subdirectory(src/tm)
add_subdirectory(src/cdl)
#add_subdirectory(test/cpp)

add_library(odb INTERFACE)
target_link_libraries(odb
  INTERFACE
    db
    cdl
    defin
    defout
    lefin
    lefout
    tm
    zutil
    ${TCL_LIBRARY}
)

############################################################################
################################# SWIG #####################################
############################################################################

#include(${SWIG_USE_FILE})
option(BUILD_PYTHON "Build Python SWIG module" ON)

add_subdirectory(src/swig/common)
if (BUILD_PYTHON)
  add_subdirectory(src/swig/python)
endif()

############################################################################
############################### DOXYGEN ####################################
############################################################################
find_package(Doxygen)

if (DOXYGEN_FOUND)
  set(DOXYGEN_EXTRACT_STATIC YES)
  set(DOXYGEN_REFERENCED_BY_RELATION YES)
  set(DOXYGEN_REFERENCES_RELATION YES)

  doxygen_add_docs(docs include)
endif()

############################################################
# Unit testing
############################################################
enable_testing()

