project(Person
        LANGUAGES CXX)

add_library(${PROJECT_NAME}-lib
            STATIC
            Person.cpp)

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