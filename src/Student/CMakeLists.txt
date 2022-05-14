add_library(Student-lib
            STATIC
            Student.cpp)

target_compile_options(Student-lib
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic
                       -Wconversion
                       -Werror)

target_compile_features(Student-lib
                       PRIVATE
                       cxx_std_20)
