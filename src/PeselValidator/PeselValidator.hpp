#pragma once

#include "I_PeselValidator.hpp"

#include <array>

namespace pesel_validator {

constexpr size_t pesel_length = { 11 };

class PeselValidator : public I_PeselValidator
{
  public:
    ~PeselValidator() override = default;

    bool validatePesel(const std::string& pesel) override;
    virtual bool operator()(const std::string& pesel);

  private:
    bool isValidString(const std::string& pesel) const;
    bool hasOnlyDigits(const std::string& pesel) const;
    void reset(const std::string& pesel);
    int checkControlDigit() const;

    // pesel length is constant
    static constexpr size_t pesel_length = { 11 };
    // control digits weights used for checking control sum
    static constexpr std::array<int, pesel_length> weights = { 1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1 };
    // variable first ten digits of PESEL number
    std::array<int, pesel_length> digits_ = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    // control digit
    int control_dig_ = 0;
};

}   // end of namespace pesel_validator
