cmake_minimum_required(VERSION 3.14)

project(university-db-project
        LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# main-app target
add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME}
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic
                       -Wconversion
                       -Werror)
target_include_directories(${PROJECT_NAME}
                           PRIVATE
                           ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}
                      DBdataGenerator-lib
                      UniversityDB-lib)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

enable_testing()

# sub-directories with project components
add_subdirectory(src/Person)
add_subdirectory(src/Student)
add_subdirectory(src/Employee)
add_subdirectory(src/PeselValidator)
add_subdirectory(src/UniversityDB)
add_subdirectory(src/DBfileManager)
add_subdirectory(src/DBdataGenerator)

# add directory with test target
add_subdirectory(tests)
