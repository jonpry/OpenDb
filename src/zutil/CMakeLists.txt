add_library(zutil
    misc_functions.cpp
    files.cpp
    name.cpp
    mem.cpp
    parse.cpp
    poly_decomp.cpp
    util.cpp
)

target_link_libraries(zutil
  PUBLIC
        db
)

target_include_directories(zutil
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include/odb
    ${TCL_INCLUDE_PATH}
)

set_target_properties(zutil
  PROPERTIES
    # python requirement
    POSITION_INDEPENDENT_CODE ON
)
