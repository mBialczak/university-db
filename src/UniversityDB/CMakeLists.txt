project(UniversityDB
        LANGUAGES CXX)

add_library(${PROJECT_NAME}-lib
            STATIC
            UniversityDB.cpp)

target_link_libraries(${PROJECT_NAME}-lib
                      StudentRecord-lib
                      PeselValidator-lib
                      DBfileManager-lib)

target_include_directories(${PROJECT_NAME}-lib
                          PRIVATE
                          ${CMAKE_SOURCE_DIR}/src)

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
