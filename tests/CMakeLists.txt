project(university-project-tests
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

# subdirectories with tests
add_subdirectory(PersonTests)
add_subdirectory(PeselValidatorTests)
add_subdirectory(StudentTests)
add_subdirectory(EmployeeTests)
add_subdirectory(UniversityDBTests)
add_subdirectory(DBfileManagerTests)
add_subdirectory(DBdataGeneratorTests)
