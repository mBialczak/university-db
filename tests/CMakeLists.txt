project(university-db-ut
        LANGUAGES CXX)

set(TEST_SRC)

add_executable(${PROJECT_NAME}-ut ${TEST_SRC})
target_link_libraries(${PROJECT_NAME}-ut gtest_main gmock_main)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)