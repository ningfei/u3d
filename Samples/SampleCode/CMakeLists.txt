PROJECT (vtkU3DExporter)
cmake_minimum_required(VERSION 3.5)

SET(EXPORTER_SRC "vtkU3DExporter.cxx" "vtkU3DExporter.h")



FIND_PACKAGE(VTK REQUIRED)
INCLUDE (${VTK_USE_FILE})


find_library(U3D_LIB IDTF)
if(NOT U3D_LIB)
	message(STATUS "Couldn't find U3D libraries.")
endif(NOT U3D_LIB)
find_path(U3D_INCLUDE_DIR u3d/SceneConverterLib.h)
if(NOT U3D_INCLUDE_DIR)
	message(STATUS "Couldn't find U3D headers.")
endif(NOT U3D_INCLUDE_DIR)
message(STATUS "Found U3D libraries at: ${U3D_LIB}")
message(STATUS "Found U3D headers: ${U3D_INCLUDE_DIR}")
#add_definitions(-DHAVE_U3D)
include_directories(${U3D_INCLUDE_DIR}/u3d)


find_package(PythonLibs REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS} )
message("Libs of Python: " ${PYTHON_LIBRARIES} )
include_directories("${PYTHON_INCLUDE_DIRS}")
include_directories("${PYTHON_INCLUDE_PATH}")

include(vtkWrapPython)

vtk_wrap_python3(${PROJECT_NAME} ${EXPORTER_SRC})


ADD_LIBRARY(${PROJECT_NAME} MODULE ${EXPORTER_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
if( WIN32 )
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
else()
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES SUFFIX ".so")
endif()

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    ${U3D_LIB}
    ${VTK_LIBRARIES}
    ${PYTHON_LIBRARIES}
    vtkWrappingPythonCore
    ${VTK_PYTHON_LIBRARIES}
)

set(VTK_PYTHOND_LIBS)
    foreach(TMP_LIB ${VTK_MODULES_USED})
        set(VTK_PYTHOND_LIBS ${VTK_PYTHOND_LIBS} ${TMP_LIB}PythonD)
    endforeach()
