# CMAKE VERSION
cmake_minimum_required(VERSION 3.5)

# PROJECT
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(PROJECT_NAME "allocator" CACHE STRING "Project name")
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})

# SOURCES
set (
    SOURCES
        main.cpp
        customallocator.cpp
)

# HEADERS
set (
    HEADERS
        utils.h
        customallocator.h
        customcontainer.h
)

# EXECUTABLE
add_executable(allocator ${SOURCES} ${HEADERS})
add_executable(gtest_sample gtest_sample.cpp)

# PROPERTIES
set_target_properties (
    allocator
    gtest_sample
        PROPERTIES
            CMAKE_CXX_STANDARD 14
            CMAKE_CXX_STANDARD_REQUIRED ON
)

# INCLUDEPATH

# Linking

# Compiler options
if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(gtest_sample PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gtest_sample PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


### Package
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

### UNIT-tests

# GoogleTest package
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Tests linking
gtest_discover_tests(gtest_sample)
target_link_libraries(
    gtest_sample
    gtest_main
)

# Testing
enable_testing()
add_test(gtest_sample gtest_sample)
