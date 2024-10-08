cmake_minimum_required(VERSION 3.12)
set(CRONO_TARGET_NAME "ndigo6g12_ugex")
project(${CRONO_TARGET_NAME})

# _____________________________________________________________________________________________________________________
# Build Windows/Linux(x86_64) `ndigo6g12_ugex.exe/Linux` executable, 
# for (Debug/Release) configurations.
# _____________________________________________________________________________________________________________________

# General Validations and Configurations ______________________________________________________________________________
# cd indirection from /tools to the project source code, "." if no shift
set(PROJ_SRC_INDIR ../..)

# Get the platform and architecure ____________________________________________________________________________________
# Check supported architecture, and set `CRONO_GEN_ARCH` to `x86_64` for all
# variations of `x64` platforms, and to `x86` for all variations of `x86` 
# platforms.
# Set `CRONO_GEN_PLATFORM` to either `windows` or `linux`
SET(CRONO_GEN_PLATFORM "windows")
IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CRONO_GEN_PLATFORM "linux")
ENDIF()

list(APPEND x64_archs Win64 AMD64 x86_64)
IF(CMAKE_SYSTEM_PROCESSOR IN_LIST x64_archs)
        set(CRONO_GEN_ARCH "x86_64")
ENDIF()

# Include directories paths ___________________________________________________________________________________________
set(CRONO_DEP_PKG_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/include)
include_directories(${CRONO_TARGET_NAME} PRIVATE ${CRONO_DEP_PKG_INC_DIR})

# Link to ndigo6g12_driver library ____________________________________________________________________________________
set(CRONO_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/lib)
set(CRONO_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/bin)
link_directories(${CRONO_LIB_DIR})
      
# Add the EXE ytarget  ________________________________________________________________________________________________
set(SRC_DIR ../src)
add_executable(${CRONO_TARGET_NAME} 
        ${SRC_DIR}/ndigo6g12_adc_averager.cpp
        ${SRC_DIR}/ndigo6g12_adc_dual.cpp
        ${SRC_DIR}/ndigo6g12_adc_quad.cpp
        ${SRC_DIR}/ndigo6g12_adc_single.cpp
        ${SRC_DIR}/ndigo6g12_example.cpp
        ${SRC_DIR}/ndigo6g12_tdc.cpp
)

set_target_properties(${CRONO_TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CRONO_BIN_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CRONO_BIN_DIR}
)

# Windows-specific Configurations _____________________________________________________________________________________
IF ( CRONO_GEN_PLATFORM  STREQUAL "windows")
        target_link_libraries(${CRONO_TARGET_NAME} ndigo6g12_driver_64)

        # Linux-specific Configurations _______________________________________________________________________________________
ELSEIF (CRONO_GEN_PLATFORM STREQUAL "linux") 
        add_compile_options(-fPIC -Wall $<$<CONFIG:Debug>:-g>)
        add_compile_definitions($<$<CONFIG:Debug>:CRONO_DEBUG_ENABLED>)
        target_link_libraries(${CRONO_TARGET_NAME} libndigo6g12_driver.a)
ENDIF()

