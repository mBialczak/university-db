#pragma once

class std::string;

class I_PeselValidator
{
  public:
    virtual ~I_PeselValidator() = default;
    bool validatePesel(const std::string& pesel) const = 0;
};