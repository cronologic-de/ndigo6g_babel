cmake_minimum_required(VERSION 3.12)
set(CRONO_TARGET_NAME "ndigo6g12_ugex")
project(${CRONO_TARGET_NAME})
# _____________________________________________________________________________
# Build Windows/Linux(x86_64) `ndigo_ugex.exe/Linux` executable, 
# for (Debug/Release) configurations.
# _____________________________________________________________________________

# General Validations and Configurations ______________________________________
# cd indirection from /tools to the project source code, "." if no shift
set(PROJ_SRC_INDIR ../..)
set(SRC_DIR ../src)

# Get the platform and architecure ____________________________________________
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

# Include directories paths ___________________________________________________
set(CRONO_DEP_PKG_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/include)
include_directories(${CRONO_TARGET_NAME} PRIVATE ${CRONO_DEP_PKG_INC_DIR})

# Link to xtdc4_driver library ________________________________________________
set(CRONO_DEP_PKG_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/lib)
link_directories(${CRONO_DEP_PKG_LIB_DIR})

# Validate that directories exist _____________________________________________
IF(     NOT EXISTS "${CRONO_DEP_PKG_LIB_DIR}" 
     OR NOT EXISTS "${CRONO_DEP_PKG_INC_DIR}"
) 
        message(FATAL_ERROR 
                "Crono: Please copy driver installation folder driver to the project root. "
"Lib: <${CRONO_DEP_PKG_LIB_DIR}>, Include: <${CRONO_DEP_PKG_INC_DIR}>.")
ENDIF()
        
# Add the EXE ytarget  ________________________________________________________
add_executable(${CRONO_TARGET_NAME} 
        ${SRC_DIR}/ndigo6g12_adc_averager.cpp
        ${SRC_DIR}/ndigo6g12_adc_dual.cpp
        ${SRC_DIR}/ndigo6g12_adc_quad.cpp
        ${SRC_DIR}/ndigo6g12_adc_single.cpp
        ${SRC_DIR}/ndigo6g12_example.cpp
        ${SRC_DIR}/ndigo6g12_tdc.cpp
)

# Windows-specific Configurations _____________________________________________
IF ( CRONO_GEN_PLATFORM  STREQUAL "windows")
        add_library(ndigo_driver_64 SHARED IMPORTED GLOBAL)
        set_target_properties(ndigo_driver_64 PROPERTIES IMPORTED_IMPLIB 
                ndigo_driver_64.lib)  
        target_link_libraries(${CRONO_TARGET_NAME} ndigo6g12_driver_64)
        SET(OUTPUT_EXT ".exe")

# Linux-specific Configurations _______________________________________________
ELSEIF (CRONO_GEN_PLATFORM STREQUAL "linux") 
        # Compilation options
        add_compile_options(-fPIC -Wall $<$<CONFIG:Debug>:-g>)
        add_compile_definitions($<$<CONFIG:Debug>:CRONO_DEBUG_ENABLED>)

        # Link to ndigo_driver library 
        target_link_libraries(${CRONO_TARGET_NAME} libndigo6g12_driver.a)
ENDIF()

# Copy the generated executable to `/lib` folder ______________________________
add_custom_command(TARGET ${CRONO_TARGET_NAME} POST_BUILD 
        COMMAND "echo" Copying executable file `${CRONO_TARGET_NAME}${OUTPUT_EXT}` 
                to `/lib` folder ...
        COMMAND ${CMAKE_COMMAND} -E copy 
                \"${CMAKE_BINARY_DIR}/$<CONFIG>/${CRONO_TARGET_NAME}${OUTPUT_EXT}\" 
                \"${CRONO_DEP_PKG_LIB_DIR}\" 
)
