cmake_minimum_required(VERSION 3.10)
project(mspcrt VERSION 1.0.0 LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(third_party/dirent)
add_subdirectory(third_party/dlfcn-win32)
add_subdirectory(third_party/winpthreads)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/third_party/getopt
    ${PROJECT_SOURCE_DIR}/third_party/winpthreads/include
)

file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/lib/*.c"
    "${PROJECT_SOURCE_DIR}/third_party/getopt/*.c"
)

add_library(libpcrt STATIC ${SRC_FILES})
set_target_properties(libpcrt PROPERTIES OUTPUT_NAME "libpcrt")
target_compile_definitions(libpcrt PRIVATE _PCRT_STATIC STATIC_GETOPT)

add_library(pcrt SHARED ${SRC_FILES})
set_target_properties(pcrt PROPERTIES OUTPUT_NAME "pcrt")
target_compile_definitions(pcrt PRIVATE _PCRT_BUILD EXPORTS_GETOPT)

install(TARGETS pcrt libpcrt
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

install(FILES third_party/getopt/getopt.h DESTINATION include)
