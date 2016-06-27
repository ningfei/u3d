PROJECT (vtku3dexporter)
cmake_minimum_required(VERSION 3.5)

option(WRAP_PYTHON "Build Python wrappers" ON)

# U3D
FIND_LIBRARY(U3D_LIB NAMES IDTF)
MESSAGE(STATUS "Found U3D library at: ${U3D_LIB}")

FIND_PATH(U3D_INCLUDE_DIR u3d/SceneConverterLib.h)
MESSAGE(STATUS "Found U3D include dir: ${U3D_INCLUDE_DIR}")
INCLUDE_DIRECTORIES(${U3D_INCLUDE_DIR}/u3d)

# VTK
FIND_PACKAGE(VTK REQUIRED
    vtkIOExport
    vtkRenderingCore
    vtkWrappingPythonCore)
MESSAGE(STATUS "Found VTK libraries: ${VTK_LIBRARIES}")
MESSAGE(STATUS "Found UseVTK.cmake: ${VTK_USE_FILE}")
INCLUDE(${VTK_USE_FILE})
SET(VTK_MODULES_USED vtkIOExport) 

# Combine projects
SET(LIBS ${VTK_LIBRARIES} ${U3D_LIB})
SET(EXPORTER_SRC vtkU3DExporter.cxx vtkU3DExporter.h)
ADD_LIBRARY(${PROJECT_NAME} ${EXPORTER_SRC})
MESSAGE(STATUS "Added library: " "${PROJECT_NAME}")

if(WRAP_PYTHON)
    # Python
    FIND_PACKAGE(PythonLibs REQUIRED)
    MESSAGE(STATUS "Found Python include dir: " ${PYTHON_INCLUDE_DIRS} )
    MESSAGE(STATUS "Found Python library: " ${PYTHON_LIBRARIES} )
    INCLUDE_DIRECTORIES("${PYTHON_INCLUDE_DIRS}")
    
    # VTK Python wrappers
    INCLUDE(vtkWrapPython)
    vtk_wrap_python3(${PROJECT_NAME}Python PYTHON_SRCS "${EXPORTER_SRC}")
    MESSAGE(STATUS "Generated Python wrappers: " "${PYTHON_SRCS}")
    
    # PythonD library
    ADD_LIBRARY("${PROJECT_NAME}PythonD" ${PYTHON_SRCS} "${EXPORTER_SRC}")
    IF(WIN32)
        LINK_LIBRARIES( winmm )
    ENDIF(WIN32)
    TARGET_LINK_LIBRARIES("${PROJECT_NAME}PythonD" 
        ${LIBS}
        vtkWrappingPythonCore 
        ${VTK_PYTHON_LIBRARIES})
    
    # Python library
    ADD_LIBRARY("${PROJECT_NAME}Python" MODULE "${PROJECT_NAME}PythonInit.cxx")
    set(VTK_PYTHOND_LIBS)
    foreach(TMP_LIB ${VTK_MODULES_USED})
        set(VTK_PYTHOND_LIBS ${VTK_PYTHOND_LIBS} ${TMP_LIB}PythonD)
    endforeach()
    TARGET_LINK_LIBRARIES("${PROJECT_NAME}Python" 
        "${PROJECT_NAME}PythonD" 
        ${VTK_PYTHOND_LIBS})
    SET_TARGET_PROPERTIES("${PROJECT_NAME}Python" PROPERTIES PREFIX "")
    if(WIN32 AND NOT CYGWIN)
        SET_TARGET_PROPERTIES("${PROJECT_NAME}Python" PROPERTIES SUFFIX ".pyd")
    endif(WIN32 AND NOT CYGWIN)
    
endif(WRAP_PYTHON)
