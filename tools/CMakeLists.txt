cmake_minimum_required(VERSION 3.13) 
cmake_minimum_required(VERSION 3.13) 
set(CRONO_TARGET_NAME "ndigo6g12_driver")
project(${CRONO_TARGET_NAME})

# 
# _____________________________________________________________________________
# Build Windows(x86/x86_64) `ndigo6g12_driver.dll` library, 
# for (Debug/Release) configurations.
# Publish conan package to local cache as per `CRONO_PUBLISH_LOCAL_PKG` 
# argument.
# `conan install` is used to fetch, build, and deploy the dependency.
#
# Dependencies: 
# - 'crono_project_tools'
# - `crono_dma_driver`
# - `crono_components`
# - `crono_lib`
# - `clr_crono_base`
# clr_ndigo6g12_driver dependencies:
# - `clr_crono_base`
# - `crono_dma_driver`
# - `crono_components`
# - `crono_lib`
# Prequisites: 
# - conan remote server(s) that have the traversal dependencies are added 
#   and authenticated.
# - Conan recipe is on the same folder.
# 
# Arguments:
# `CRONO_PUBLISH_LOCAL_PKG`: Publish project packages to conan local cache
# - Passed as `-DCRONO_PUBLISH_LOCAL_PKG=N`
# - Values:
#        `N` : Do not publish.
#    Default : Publish
# _____________________________________________________________________________

# Install project tools(if not already installed, or old), then include 
# `crono_common.cmake` and initialize it 
IF(("${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt"
    IS_NEWER_THAN "${CMAKE_CURRENT_SOURCE_DIR}/deploy_manifest.txt") 
    OR (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/crono_common.cmake")) 
        message(STATUS "Crono: Installing Cronologic Project Tools ...")
        execute_process(COMMAND "conan" install crono_project_tools/[~1.3.0]@ 
                --update                        # Get latest version from remote
                -if ${CMAKE_CURRENT_SOURCE_DIR} # `tools` folder
        )
ENDIF()
   
include(${CMAKE_CURRENT_SOURCE_DIR}/crono_common.cmake)
crono_cmake_common_init()
crono_set_version_vars_from_recipe()

set(CMAKE_CXX_STANDARD 17)
# _____________________________________________________________________________
# Build the driver
#
# Source files settings
set(SOURCE 
        ${PROJ_SRC_INDIR}/src/ndigo6g12.cpp
        ${PROJ_SRC_INDIR}/src/ndigo6g12_interface.cpp
)
set(HEADERS
        ${PROJ_SRC_INDIR}/src/LMX2594_cfg.h
        ${PROJ_SRC_INDIR}/src/ndigo6g12.h
        ${PROJ_SRC_INDIR}/include/ndigo6g12_interface.h
        ${PROJ_SRC_INDIR}/include/ndigo6g12_internal_interface.h
)
crono_add_windows_resource_files(SOURCE
        ${PROJ_SRC_INDIR}/src/ndigo6g12_driver.rc)

# Common definitions passed to target_compile_definitions
set(CRONO_COMMON_COMPILE_DEFS
        PRIVATE NDIGO6G12_DRIVER_EXPORTS
        PRIVATE CRONO_DMA_DRIVER_STATIC
        PRIVATE CRONO_KERNEL_DRIVER_STATIC
        PRIVATE USE_CRONO_KERNEL_DRIVER
)

IF(${CRONO_GEN_PLATFORM} STREQUAL "windows")
        # Create the driver library
        add_library(${CRONO_TARGET_NAME} SHARED "${SOURCE}" "${HEADERS}")
        target_compile_definitions(${CRONO_TARGET_NAME}
                ${CRONO_COMMON_COMPILE_DEFS}
                PRIVATE _CRT_SECURE_NO_DEPRECATE
        )
        crono_add_dep("crono_dma_driver;crono_components;crono_lib")
        target_link_libraries("${CRONO_TARGET_NAME}" 
                crono_components crono_dma_driver crono_lib setupapi)
        crono_set_def_VER_ORIGINAL_FILENAME_STR()
ELSE()
# Linux
        crono_add_objs_static_lib(
                "${CRONO_TARGET_NAME}"
                "${SOURCE}" 
                "${HEADERS}"
                "crono_dma_driver;crono_components;crono_lib"
                "crono_dma_driver;crono_components;crono_lib"
                "${CRONO_COMMON_COMPILE_DEFS}"
        )
ENDIF()
crono_append_target_postfix()

# Include for all
include_directories(
        PUBLIC ${crono_dma_driver_INC_DIR}
        PUBLIC ${PROJ_SRC_INDIR}/src
)

# _____________________________________________________________________________
# Build ndigo_c_test
#
set(C_TEST_TARGET_NAME "ndigo6g12_c_test")
set(C_TEST_SOURCE 
        ${PROJ_SRC_INDIR}/c_test/ndigo6g12_c_test.cpp)
crono_add_windows_resource_files(C_TEST_SOURCE
        ${PROJ_SRC_INDIR}/c_test/ndigo6g12_c_test.rc)
crono_add_sub_exec_target_to_lib(
        "${C_TEST_TARGET_NAME}"         # sub_target_name
        "${C_TEST_SOURCE}"              # sub_target_sources
        "${CRONO_TARGET_NAME_GEN_EXP}"  # target_lib_name
        "${PROJ_SRC_INDIR}/src"         # Include directory
)                
crono_append_target_postfix_to_target(${C_TEST_TARGET_NAME})

# Build example
#
set(UG_EXAMPLE_TARGET_NAME "ndigo6g12_ug_example")
set(UG_EXAMPLE_SOURCE 
        ${PROJ_SRC_INDIR}/ug_example/ndigo6g12_app.h
        ${PROJ_SRC_INDIR}/ug_example/delay.h
        ${PROJ_SRC_INDIR}/ug_example/ndigo6g12_adc_single.cpp
        ${PROJ_SRC_INDIR}/ug_example/ndigo6g12_adc_dual.cpp
        ${PROJ_SRC_INDIR}/ug_example/ndigo6g12_adc_quad.cpp
        ${PROJ_SRC_INDIR}/ug_example/ndigo6g12_adc_averager.cpp
        ${PROJ_SRC_INDIR}/ug_example/ndigo6g12_example.cpp
        ${PROJ_SRC_INDIR}/ug_example/ndigo6g12_tdc.cpp
)
crono_add_sub_exec_target_to_lib(
        "${UG_EXAMPLE_TARGET_NAME}"         # sub_target_name
        "${UG_EXAMPLE_SOURCE}"              # sub_target_sources
        "${CRONO_TARGET_NAME_GEN_EXP}"  # target_lib_name
        "${PROJ_SRC_INDIR}/src"         # Include directory
)                
crono_append_target_postfix_to_target(${UG_EXAMPLE_TARGET_NAME})


set(AVG_EXAMPLE_TARGET_NAME "ndigo6g12_averager_example")
set(AVG_EXAMPLE_SOURCE 
        ${PROJ_SRC_INDIR}/ug_example/ndigo6g12_averager_example.cpp
)
crono_add_sub_exec_target_to_lib(
        "${AVG_EXAMPLE_TARGET_NAME}"         # sub_target_name
        "${AVG_EXAMPLE_SOURCE}"              # sub_target_sources
        "${CRONO_TARGET_NAME_GEN_EXP}"  # target_lib_name
        "${PROJ_SRC_INDIR}/src"         # Include directory
)                
crono_append_target_postfix_to_target(${AVG_EXAMPLE_TARGET_NAME})


# _____________________________________________________________________________
# Build ndigo6g12_write_partial_bitstream
#
set(WRITE_PBITSTREAM_TARGET_NAME "ndigo6g12_write_partial_bitstream")
set(WRITE_PBITSTREAM_SOURCE 
        ${PROJ_SRC_INDIR}/write_partial_bitstream/ndigo6g12_write_partial_bitstream.cpp)
crono_add_windows_resource_files(WRITE_PBITSTREAM_SOURCE
        ${PROJ_SRC_INDIR}/write_partial_bitstream/ndigo6g12_write_partial_bitstream.rc)
crono_add_sub_exec_target_to_lib(
        "${WRITE_PBITSTREAM_TARGET_NAME}"       # sub_target_name
        "${WRITE_PBITSTREAM_SOURCE}"            # sub_target_sources
        "${CRONO_TARGET_NAME_GEN_EXP}"          # target_lib_name
        "${PROJ_SRC_INDIR}/src"                 # Include directory
)                
crono_append_target_postfix_to_target(${WRITE_PBITSTREAM_TARGET_NAME})

# _____________________________________________________________________________
# Build CLR 
#
IF(${CRONO_GEN_PLATFORM} STREQUAL "windows")
        # 
        # Build clr_ndigo6g12_driver __________________________________________
        #
        set(CLR_DRIVER_TARGET_NAME "clr_ndigo6g12_driver")
        set(CLR_DRIVER_SOURCE 
                ${PROJ_SRC_INDIR}/clr_driver/clr_ndigo6g12_driver.cpp
                ${PROJ_SRC_INDIR}/src/ndigo6g12.cpp
                ${PROJ_SRC_INDIR}/src/ndigo6g12.h
                ${PROJ_SRC_INDIR}/clr_driver/clr_ndigo6g12_driver.h
        )
        crono_add_windows_resource_files(CLR_DRIVER_SOURCE
                ${PROJ_SRC_INDIR}/clr_driver/clr_ndigo6g12_driver.rc)
        add_library(${CLR_DRIVER_TARGET_NAME} SHARED "${CLR_DRIVER_SOURCE}")
        target_link_options(${CLR_DRIVER_TARGET_NAME} PUBLIC /ASSEMBLYDEBUG)
        crono_append_target_postfix_to_target(${CLR_DRIVER_TARGET_NAME})
        crono_set_def_VER_ORIGINAL_FILENAME_STR_to_lib(${CLR_DRIVER_TARGET_NAME})
        set_target_properties(${CLR_DRIVER_TARGET_NAME} PROPERTIES 
                COMMON_LANGUAGE_RUNTIME ""
                VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.6.1"
        )
        target_compile_definitions(${CLR_DRIVER_TARGET_NAME}
                ${CRONO_COMMON_COMPILE_DEFS}
                PRIVATE _CRT_SECURE_NO_DEPRECATE
        )
        crono_add_dep_to_lib("${CLR_DRIVER_TARGET_NAME}" 
                "crono_dma_driver;crono_components;crono_lib;clr_crono_base")
        target_link_libraries(${CLR_DRIVER_TARGET_NAME} 
                crono_dma_driver crono_components crono_lib setupapi
        )
        crono_set_target_dotnet_ref_property_dep(
                "${CLR_DRIVER_TARGET_NAME}"     # target_name
                "${CRONO_BUILD_TYPE}"           # build_type
                "clr_crono_base"                # dep_target_name
                "true"          # dep_has_postfix
                "true"          # dep_support_x64_32
                "true"          # dep_support_any_CPU 
        )

        #
        # Build ndigo6g12_csv_writer __________________________________________
        #
        set(CSV_WRITER_TARGET_NAME "ndigo6g12_csv_writer")
        set(CSV_WRITER_SOURCE 
                ${PROJ_SRC_INDIR}/csv_writer/ndigo6g12_csv_writer.cpp)
        crono_add_windows_resource_files(CSV_WRITER_SOURCE
                ${PROJ_SRC_INDIR}/csv_writer/ndigo6g12_csv_writer.rc)
        crono_add_sub_exec_target_to_lib(
                "${CSV_WRITER_TARGET_NAME}"     # sub_target_name
                "${CSV_WRITER_SOURCE}"          # sub_target_sources
                "${CRONO_TARGET_NAME_GEN_EXP}"  # target_lib_name
                "${PROJ_SRC_INDIR}/src"         # Include directory
        )
        crono_support_vs_std(${CSV_WRITER_TARGET_NAME})
        crono_append_target_postfix_to_target(${CSV_WRITER_TARGET_NAME})
ENDIF()

# _____________________________________________________________________________
# Build ndigo6g12_driver_test 
#
set(UNIT_TEST_TARGET_NAME "ndigo6g12_driver_test")
set(UNIT_TEST_SOURCE 
        ${PROJ_SRC_INDIR}/driver_test/ndigo6g12_basic_tests.cpp
        ${PROJ_SRC_INDIR}/driver_test/ndigo6g12_test_helpers.cpp
        ${PROJ_SRC_INDIR}/driver_test/ndigo6g12_test_helpers.h
)
# The following is needed for Visual Studio to handle tests from Test menu 
# (e.g. Test Explorer, etc...), before creating the exe. Don't call it from
# crono_common.cmake, Test Explorer won't probably work then
enable_testing()
crono_add_sub_gtest_target_to_lib(
        "${UNIT_TEST_TARGET_NAME}"       # sub_target_name
        "${UNIT_TEST_SOURCE}"            # sub_target_sources
        "${CRONO_TARGET_NAME_GEN_EXP}"   # target_lib_name
        "${PROJ_SRC_INDIR}/src"          # Include directory
)
# Add test for Visual Studio to detect.
add_test(NAME basic_tests COMMAND ${UNIT_TEST_TARGET_NAME})


# Publish packages on conan local cache _______________________________________ 
IF (NOT CRONO_PUBLISH_LOCAL_PKG STREQUAL "N")
        # Set `CRONO_TARGET_NAME` for next calls. e.g. `crono_target_post_build_export_pkg`
        IF(${CRONO_GEN_PLATFORM} STREQUAL "windows")
                # WRITE_PBITSTREAM_TARGET_NAME is the last target built selected by 
                # Windows, so set the packaging as ITS post build event.
                set(CRONO_TARGET_NAME ${WRITE_PBITSTREAM_TARGET_NAME})
        ELSE()
                # C_TEST_TARGET_NAME is the last target built selected by Linux, so
                # set the packaging as ITS post build event.
                set(CRONO_TARGET_NAME ${C_TEST_TARGET_NAME})
        ENDIF()
        # Build packages of `ndigo_driver` (main project)
        crono_target_post_build_export_pkg_main() 
ENDIF()

# _____________________________________________________________________________
message(STATUS "Crono: architecture is <${CRONO_GEN_ARCH}> for <${CRONO_GEN_PLATFORM}>" )
