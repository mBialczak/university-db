#pragma once

#include "PeselValidator/I_PeselValidator.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace university::mocks {

using university::pesel_validator::I_PeselValidator;

class PeselValidatorMock : public I_PeselValidator
{
  public:
    MOCK_METHOD(bool, validatePesel, (const std::string& pesel), (override));
    bool operator()(const std::string& pesel) override
    {
        return validatePesel(pesel);
    }
};

}   // namespace university::mocks
