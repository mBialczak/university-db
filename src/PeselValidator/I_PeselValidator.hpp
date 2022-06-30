#pragma once

#include <string>
namespace university::pesel_validator {

class I_PeselValidator
{
  public:
    virtual ~I_PeselValidator() = default;
    virtual bool validatePesel(const std::string& pesel) = 0;
    virtual bool operator()(const std::string& pesel)
    {
        return validatePesel(pesel);
    }
};

}   // end of namespace university::pesel_validator
