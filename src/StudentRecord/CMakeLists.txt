add_library(StudentRecord-lib
            STATIC
            StudentRecord.cpp)

target_compile_options(StudentRecord-lib
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic
                       -Wconversion
                       -Werror)

target_compile_features(StudentRecord-lib
                       PRIVATE
                       cxx_std_20)
