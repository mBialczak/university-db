project(PeselValidator
        LANGUAGES CXX)

add_library(${PROJECT_NAME}-lib
            STATIC
            PeselValidator.cpp)

add_compile_options(${PROJECT_NAME}-lib
                    PRIVATE
                    -Wall
                    -Wextra
                    -pedantic
                    -Wconversion
                    -Werror)

target_compile_features(StudentRecord-lib
                        PRIVATE
                        cxx_std_20)