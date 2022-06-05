cmake_minimum_required(VERSION 3.14)

project(university-db
       LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# main-app target
add_executable(${PROJECT_NAME} src/main.cpp)
# target_link_libraries(${PROJECT_NAME} )
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wconversion -Werror)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# sub-directories with project components
add_subdirectory(src/StudentRecord)
add_subdirectory(src/PeselValidator)
add_subdirectory(src/UniversityDB)

# add directory with test target
add_subdirectory(tests)

enable_testing()
