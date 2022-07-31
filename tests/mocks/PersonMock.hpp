// #include "Person/PersonMock.hpp"

// #include "gmock/gmock.h"
// #include "gtest/gtest.h"

// namespace university::mocks {
// using namespace testing;

// class PersonMock : public person::Person
// {
//     PersonMock(const std::string& firstName,
//                const std::string& lastName,
//                const std::string& pesel,
//                const std::string& address,
//                Gender gender);

//     MOCK_METHOD(std::string, firstName, (), const)

//     //             std::string firstName() const;
//     // std::string lastName() const;
//     // std::string pesel() const;
//     // std::string address() const;
//     // Gender gender() const;
//     // virtual std::ostream& sendToStream(std::ostream& os) const = 0;
// };

// PersonMock::PersonMock(const std::string& firstName,
//                        const std::string& lastName,
//                        const std::string& pesel,
//                        const std::string& address,
//                        Gender gender)
//     : Person(firstName, lastName, pesel, address, gender)
// { }

// }   // namespace university::mocks
