// // NOTE:  Person is an abstract class, which provides common functionalities
//           for deriving classes. this functionality is tested using a dummy inheriting class
//           with the only extension of sendToStream dummy implementation override.
//           Each deriving class tests its real implementation of sendToStream anyway

#include "Person/Person.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <ostream>
namespace university::person::ut {

class PersonDummy : public Person
{
  public:
    PersonDummy(const std::string& firstName,
                const std::string& lastName,
                const std::string& pesel,
                const std::string& address,
                Gender gender)
        : Person(firstName,
                 lastName,
                 pesel,
                 address,
                 gender)
    { }

    std::ostream& sendToStream(std::ostream& os) const override
    {
        os << "PersonDummy's sendToStream implementation\n"
           << "-------------\n"
           << "First name: " << first_name_ << "\n"
           << "Last name: " << last_name_ << "\n"
           << "PESEL: " << pesel_ << "\n"
           << "Address: " << address_ << "\n"
           << "Gender: "
           << (gender_ == Gender::male ? "male"
                                       : "female")
           << std::endl;

        return os;
    }
};

class PersonTests : public ::testing::Test
{
  public:
    PersonTests();

  protected:
    PersonDummy john;
    PersonDummy sally;
    PersonDummy mike;
    PersonDummy anna;
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
    , mike("Mike",
           "Dickens",
           "90080517455",
           "Australia, Sydney, Long Shore st. 22",
           Gender::male)
    , anna("Anna",
           "Smith",
           "67040500538",
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

std::string prepPatternString(const Person& person)
{
    std::string pattern;
    pattern += std::string("PersonDummy's sendToStream implementation") + "\n";
    pattern += std::string("-------------") + "\n";
    pattern += "First name: " + person.firstName() + "\n";
    pattern += "Last name: " + person.lastName() + "\n";
    pattern += "PESEL: " + person.pesel() + "\n";
    pattern += "Address: " + person.address() + "\n";
    pattern += "Gender: ";
    pattern += person.gender() == Gender::male ? "male"
                                               : "female";
    pattern += "\n";

    return pattern;
}

TEST_F(PersonTests, sendToStreamShouldCorrectlyInsertPersonToOuptutStream)
{
    std::string pattern1 = prepPatternString(john);
    std::string pattern2 = prepPatternString(sally);
    std::ostringstream osstream;

    john.sendToStream(osstream);
    std::string insertion_result1 = osstream.str();
    osstream.str("");
    sally.sendToStream(osstream);
    std::string insertion_result2 = osstream.str();

    EXPECT_EQ(pattern1, insertion_result1);
    EXPECT_EQ(pattern2, insertion_result2);
}

TEST_F(PersonTests, outputOperatorShouldCorrectlyInsertPersonToOuptutStream)
{
    std::string pattern1 = prepPatternString(john);
    std::string pattern2 = prepPatternString(sally);
    std::ostringstream osstream;

    john.sendToStream(osstream);
    std::string insertion_result1 = osstream.str();
    osstream.str("");
    sally.sendToStream(osstream);
    std::string insertion_result2 = osstream.str();

    EXPECT_EQ(pattern1, insertion_result1);
    EXPECT_EQ(pattern2, insertion_result2);
}

TEST_F(PersonTests, operatorLessThanShouldSortByLastNameAndFirstNameWhenLastNameSame)
{
    // start unsorted
    std::vector<PersonDummy> people { sally, mike, john, anna };

    std::sort(people.begin(), people.end());

    EXPECT_THAT(people, testing::ElementsAre(john, mike, anna, sally));
}

TEST_F(PersonTests, operatorEqualShouldCompareLastNameFirstNameAndPesel)
{
    auto anna2 = anna;
    auto mike2 = mike;

    EXPECT_EQ(anna, anna2);
    EXPECT_EQ(mike2, mike2);
    EXPECT_NE(anna, mike);
}

}   // namespace university::person::ut
