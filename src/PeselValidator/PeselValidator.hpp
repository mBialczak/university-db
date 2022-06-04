#pragma once

#include "I_PeselValidator.hpp"

#include <array>
namespace pesel_validator {

class PeselValidator : public I_PeselValidator
{
  public:
    virtual ~PeselValidator() override = default;

    bool validatePesel(const std::string& pesel) override;

  private:
    bool isValidString(const std::string& pesel) const;
    bool hasOnlyDigits(const std::string& pesel) const;
    void reset(const std::string& pesel);
    int calcDesiredControlDigit() const;

    // pesel length is constant
    static constexpr size_t pesel_length_constant = { 11 };
    // control digits weights
    static constexpr std::array<int, 10> weights = { 1, 3, 7, 9, 1, 3, 7, 9, 1, 3 };
    // variable first ten digits of PESEL number
    std::array<int, 10> digits_ = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    // control digit
    int control_dig_ = 0;
};

}   // end of namespace pesel_validator
