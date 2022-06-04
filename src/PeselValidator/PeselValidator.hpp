#pragma once

#include "I_PeselValidator.hpp"

namespace pesel_validator {

class PeselValidator : public I_PeselValidator
{
  public:
    virtual ~PeselValidator() override = default;

    bool validatePesel(const std::string& pesel) override;
};

}   // end of namespace pesel_validator
