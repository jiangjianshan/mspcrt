cmake_minimum_required(VERSION 3.10)

project(winpthread C)

include_directories(include)
include_directories(../../third_party/dlfcn-win32/include)

set(WINPTHREAD_SOURCES
    src/barrier.c
    src/barrier.h
    src/clock.c
    src/cond.c
    src/cond.h
    src/misc.c
    src/misc.h
    src/mutex.c
    src/nanosleep.c
    src/rwlock.c
    src/rwlock.h
    src/sem.c
    src/sem.h
    src/spinlock.c
    src/sched.c
    src/thread.c
    src/thread.h
    src/wpth_ver.h
    src/version.rc
)

set(WINPTHREAD_HEADERS
    include/pthread.h
    include/pthread_compat.h
    include/pthread_signal.h
    include/pthread_time.h
    include/pthread_unistd.h
    include/sched.h
    include/semaphore.h
)

# Build shared library
add_library(pthread_shared SHARED ${WINPTHREAD_SOURCES})
target_compile_definitions(pthread_shared PUBLIC IN_WINPTHREAD DLL_EXPORT)

target_include_directories(pthread_shared
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(pthread_shared PROPERTIES
    OUTPUT_NAME pthread
    ARCHIVE_OUTPUT_NAME pthread
    DEFINE_SYMBOL ""
)

add_library(pthread_static STATIC ${WINPTHREAD_SOURCES})

target_include_directories(pthread_static
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(pthread_static PROPERTIES
    OUTPUT_NAME libpthread
)

install(FILES ${WINPTHREAD_HEADERS} DESTINATION include)

install(TARGETS pthread_shared pthread_static
    EXPORT pthread-targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

export(EXPORT pthread-targets
    FILE "${CMAKE_BINARY_DIR}/pthread-targets.cmake"
    NAMESPACE pthread::
)

set(CMAKE_CONF_INSTALL_DIR lib/cmake/pthread)
set(INCLUDE_INSTALL_DIR include)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/winpthread-config.cmake.in
    ${CMAKE_BINARY_DIR}/pthread-config.cmake
    INSTALL_DESTINATION ${CMAKE_CONF_INSTALL_DIR}
    PATH_VARS INCLUDE_INSTALL_DIR
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(EXPORT pthread-targets
    FILE pthread-targets.cmake
    NAMESPACE pthread::
    DESTINATION ${CMAKE_CONF_INSTALL_DIR}
)

install(FILES ${CMAKE_BINARY_DIR}/pthread-config.cmake
    DESTINATION ${CMAKE_CONF_INSTALL_DIR}
)
