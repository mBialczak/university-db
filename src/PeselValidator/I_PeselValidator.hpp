#pragma once

#include <string>
namespace pesel_validator {

class I_PeselValidator
{
  public:
    virtual ~I_PeselValidator() = default;
    virtual bool validatePesel(const std::string& pesel) = 0;
};

}   // end of namespace pesel_validator