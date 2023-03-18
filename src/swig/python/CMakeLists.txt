include("swig_lib")

swig_lib(NAME          odb_py
         NAMESPACE     odb
         LANGUAGE      python
         I_FILE        ../common/odb.i
         SWIG_INCLUDES ${PROJECT_SOURCE_DIR}/include
                       ${PROJECT_SOURCE_DIR}/src/swig/python
         SCRIPTS       ${CMAKE_CURRENT_BINARY_DIR}/odb_py.py
)

target_include_directories(odb_py
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/odb
)

target_link_libraries(odb_py
    PUBLIC
        odb
        ${TCL_LIBRARY}
        cdl
        odb_swig_common
)


install(
    TARGETS odb_py 
    DESTINATION "."
)


#install(
#    FILES ${CMAKE_CURRENT_BINARY_DIR}/odb_py.py
#    DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)

