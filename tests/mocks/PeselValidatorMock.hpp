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

    static const std::vector<std::string> ok_pesels;
    static const std::vector<std::string> wrong_pesels;
};

const std::vector<std::string> PeselValidatorMock::ok_pesels { "90090515836",
                                                               "92071314764",
                                                               "81100216357",
                                                               "80072909146",
                                                               "90080517455",
                                                               "90060804786",
                                                               "65071209862",
                                                               "67040500538" };

const std::vector<std::string> PeselValidatorMock::wrong_pesels { "0",
                                                                  "425",
                                                                  "5325",
                                                                  "2535325",
                                                                  "35292569",
                                                                  "notNumbers",
                                                                  "99012723456",
                                                                  "02271409862",
                                                                  "74110101745",
                                                                  "801105124678" };

PeselValidatorMock::PeselValidatorMock()
{
    // default action for all example correct pesels
    for (const auto& pesel : ok_pesels) {
        ON_CALL(*this, validatePesel(pesel)).WillByDefault(Return(true));
    }

    // default action for all example wrong pesels
    for (const auto& pesel : wrong_pesels) {
        ON_CALL(*this, validatePesel(pesel)).WillByDefault(Return(false));
    }
}

}   // namespace university::mocks
