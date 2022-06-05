#pragma once

#include "PeselValidator/I_PeselValidator.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace university::mocks {

using university::pesel_validator::I_PeselValidator;
using namespace testing;

class PeselValidatorMock : public I_PeselValidator
{
  public:
    PeselValidatorMock();

    MOCK_METHOD(bool, validatePesel, (const std::string& pesel), (override));
    bool operator()(const std::string& pesel) override
    {
        return validatePesel(pesel);
    }

  protected:
    //  correct pesel constants
    static const std::string ok_pesel_1;
    static const std::string ok_pesel_2;
    static const std::string ok_pesel_3;
    static const std::string ok_pesel_4;
    static const std::string ok_pesel_5;
    static const std::string ok_pesel_6;
    static const std::string ok_pesel_7;
    static const std::string ok_pesel_8;
};

const std::string PeselValidatorMock::ok_pesel_1 { "90090515836" };
const std::string PeselValidatorMock::ok_pesel_2 { "92071314764" };
const std::string PeselValidatorMock::ok_pesel_3 { "81100216357" };
const std::string PeselValidatorMock::ok_pesel_4 { "80072909146" };
const std::string PeselValidatorMock::ok_pesel_5 { "90080517455" };
const std::string PeselValidatorMock::ok_pesel_6 { "90060804786" };
const std::string PeselValidatorMock::ok_pesel_7 { "65071209862" };
const std::string PeselValidatorMock::ok_pesel_8 { "67040500538" };

PeselValidatorMock::PeselValidatorMock()
{
    ON_CALL(*this, validatePesel("90090515836")).WillByDefault(Return(true));
}

}   // namespace university::mocks

// "90090515836", true },
//                                                      { "", true },
//                                                      { "", true },
//                                                      { "", true },
//                                                      { "", true },
//                                                      { "", true },
//                                                      { "", true },
//                                                      { "67040500538", true },