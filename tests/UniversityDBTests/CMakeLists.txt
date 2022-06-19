project(UniversityDB-ut
        LANGUAGES CXX)

add_executable(${PROJECT_NAME}
              UniversityDB-UT.cpp)

target_include_directories(${PROJECT_NAME}
                           PRIVATE
                           ${CMAKE_SOURCE_DIR}/src
                           ${CMAKE_SOURCE_DIR}/tests/mocks)

target_link_libraries(${PROJECT_NAME}
                      StudentRecord-lib
                      UniversityDB-lib
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

gtest_discover_tests(${PROJECT_NAME})
