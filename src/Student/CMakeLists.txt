project(Student
        LANGUAGES CXX)

add_library(${PROJECT_NAME}-lib
            STATIC
            Student.cpp)

target_include_directories(${PROJECT_NAME}-lib
                           PRIVATE
                           ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME}-lib
                      Person-lib)

target_compile_options(${PROJECT_NAME}-lib
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic
                       -Wconversion
                       -Werror)

target_compile_features(${PROJECT_NAME}-lib
                       PRIVATE
                       cxx_std_20)
