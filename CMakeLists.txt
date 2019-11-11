cmake_minimum_required(VERSION 3.14)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(PROPAGATE_CONST_IS_NOT_SUBPROJECT ON)
endif()

project(propagate_const VERSION 1.0.0 LANGUAGES CXX)

if(EXISTS ${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
endif()

option(ENABLE_SANITIZERS "Enable Address Sanitizer and Undefined Behaviour Sanitizer if available" OFF)

add_library(propagate_const INTERFACE)
target_include_directories(propagate_const
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_sources(propagate_const
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/propagate_const.h>
        $<INSTALL_INTERFACE:include/propagate_const.h>
)

target_compile_features(propagate_const
    INTERFACE
        cxx_std_14
)

add_library(propagate_const::propagate_const ALIAS propagate_const)

if (${PROPAGATE_CONST_IS_NOT_SUBPROJECT})
    include(CTest)
    if (BUILD_TESTING)
        find_package(Catch2 REQUIRED)

        add_executable(test_propagate_const test_propagate_const.cpp)
        target_link_libraries(test_propagate_const
            PRIVATE
                propagate_const::propagate_const
                Catch2::Catch2
        )

        target_compile_options(test_propagate_const
            PRIVATE
                $<$<CXX_COMPILER_ID:MSVC>:/EHsc>
                $<$<CXX_COMPILER_ID:MSVC>:/W4>
                $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>>:-Werror;-Wall;-Wno-self-assign-overloaded;-Wno-unknown-warning-option>
        )

        set_target_properties(test_propagate_const PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS OFF
        )

        if (ENABLE_SANITIZERS)
            set(SANITIZER_FLAGS_ASAN "-fsanitize=address -fno-omit-frame-pointer")
            set(SANITIZER_FLAGS_UBSAN "-fsanitize=undefined")

            include(CheckCXXCompilerFlag)
            check_cxx_compiler_flag("${SANITIZER_FLAGS_ASAN}" COMPILER_SUPPORTS_ASAN)
            check_cxx_compiler_flag("${SANITIZER_FLAGS_UBSAN}" COMPILER_SUPPORTS_UBSAN)

            if (COMPILER_SUPPORTS_ASAN)
                add_library(asan INTERFACE IMPORTED)
                set_target_properties(asan PROPERTIES
                    INTERFACE_COMPILE_OPTIONS "${SANITIZER_FLAGS_ASAN}"
                    INTERFACE_LINK_OPTIONS "${SANITIZER_FLAGS_ASAN}"
                )
                target_link_libraries(test_propagate_const
                    PRIVATE
                        asan
                )
            endif(COMPILER_SUPPORTS_ASAN)

            if (COMPILER_SUPPORTS_UBSAN)
                add_library(ubsan INTERFACE IMPORTED)
                set_target_properties(ubsan PROPERTIES
                    INTERFACE_COMPILE_OPTIONS "${SANITIZER_FLAGS_UBSAN}"
                    INTERFACE_LINK_OPTIONS "${SANITIZER_FLAGS_UBSAN}"
                )
                target_link_libraries(test_propagate_const
                    PRIVATE
                        ubsan
                )
            endif(COMPILER_SUPPORTS_UBSAN)
        endif(ENABLE_SANITIZERS)

        add_test(
            NAME test_propagate_const
            COMMAND test_propagate_const
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        catch_discover_tests(test_propagate_const)
    endif(BUILD_TESTING)

    include(GNUInstallDirs)

    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/propagate_const.h"
        DESTINATION
            ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt"
        DESTINATION
            "${CMAKE_INSTALL_DATAROOTDIR}/licenses/propagate_const"
    )

    install(
        TARGETS propagate_const
        EXPORT propagate_const-target
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    install(
        EXPORT propagate_const-target
        NAMESPACE propagate_const::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/propagate_const"
    )

    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/propagate_const-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/propagate_const-config.cmake
        INSTALL_DESTINATION
            "${CMAKE_INSTALL_LIBDIR}/cmake/propagate_const"
    )

    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/propagate_const-version.cmake
        VERSION ${PROPAGATE_CONST_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT
    )

    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/propagate_const-config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/propagate_const-version.cmake
        DESTINATION
            "${CMAKE_INSTALL_LIBDIR}/cmake/propagate_const"
    )
endif()
