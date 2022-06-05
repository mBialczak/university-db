project(university-db-ut
        LANGUAGES CXX)

# prepare Google Test
include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest
   GIT_TAG main)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
# gtest_discover_tests(PeselValidator-ut
#                     PeselValidator-ut)

# subdirectories with tests
add_subdirectory(PeselValidatorTests)
add_subdirectory(StudentRecordTests)
