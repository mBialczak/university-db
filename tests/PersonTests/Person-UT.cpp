#include "Person/Person.hpp"

#include "gtest/gtest.h"
namespace university::person::ut {

class PersonTests : public ::testing::Test
{
  public:
    PersonTests();

  protected:
    Person john;
    Person sally;
};

PersonTests::PersonTests()
    : john("John",
           "Dickens",
           "90090515836",
           "England, London, Puddle of Mudd st. 37",
           Gender::male)
    , sally("Sally",
            "Smith",
            "81100216357",
            "Australia, Sydney, Long Shore st. 22",
            Gender::female)
{
}

TEST_F(PersonTests, firstNameShouldReturnPersonsFirstName)
{
    EXPECT_EQ(john.firstName(), "John");
    EXPECT_EQ(sally.firstName(), "Sally");
}

TEST_F(PersonTests, lastNameShouldReturnPersonsLastName)
{
    EXPECT_EQ(john.lastName(), "Dickens");
    EXPECT_EQ(sally.lastName(), "Smith");
}

TEST_F(PersonTests, addressShouldReturnPersonsAddress)
{
    EXPECT_EQ(john.address(), "England, London, Puddle of Mudd st. 37");
    EXPECT_EQ(sally.address(), "Australia, Sydney, Long Shore st. 22");
}

TEST_F(PersonTests, genderShouldReturnPersonsGender)
{
    EXPECT_EQ(john.gender(), Gender::male);
    EXPECT_EQ(sally.gender(), Gender::female);
}

TEST_F(PersonTests, peselShouldReturnPersonsPesel)
{
    EXPECT_EQ(john.pesel(), "90090515836");
    EXPECT_EQ(sally.pesel(), "81100216357");
}
}   // namespace university::person::ut
