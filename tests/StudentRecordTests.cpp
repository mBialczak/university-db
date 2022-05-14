#include "StudentRecord/StudentRecord.hpp"
#include "gtest/gtest.h"

TEST(StudentRecordTests, ShouldBeAbleToCreateStudentRecordObjects)
{
    StudentRecord named_student{"John", "Dick"};
}