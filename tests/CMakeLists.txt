project(university-db-ut
        LANGUAGES CXX)

# prepare Google Test
include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest
   GIT_TAG main)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(TEST_SRC
    StudentTests.cpp)

add_executable(${PROJECT_NAME}
                ${TEST_SRC})

target_include_directories(${PROJECT_NAME}
                            PUBLIC
                            ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME}
                      Student-lib
                      gtest_main
                      gmock_main)

target_compile_options(${PROJECT_NAME}
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(${PROJECT_NAME}
                        PRIVATE
                        cxx_std_20)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
enable_testing()
