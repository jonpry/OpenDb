add_library(odb_swig_common
    swig_common.cpp
)

set_target_properties(odb_swig_common
  PROPERTIES
    # python requirement
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(odb_swig_common
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    .
)

target_link_libraries(odb_swig_common
  PUBLIC
    defin
    lefin
)
