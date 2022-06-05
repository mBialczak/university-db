#include "PeselValidator.hpp"

#include <algorithm>
#include <cctype>
#include <numeric>

namespace pesel_validator {

bool PeselValidator::validatePesel(const std::string& pesel)
{
    if (!isValidString(pesel)) {
        return false;
    }
    reset(pesel);

    return checkControlDigit();
}

bool PeselValidator::isValidString(const std::string& pesel) const
{
    return pesel.length() == pesel_length && hasOnlyDigits(pesel);
}

bool PeselValidator::hasOnlyDigits(const std::string& pesel) const
{
    return std::all_of(pesel.begin(), pesel.end(), isdigit);
}

void PeselValidator::reset(const std::string& pesel)
{
    std::transform(
        pesel.begin(),
        pesel.end(),   // we don't want last(control) digit here
        digits_.begin(),
        [](const auto ch) {
            return atoi(&ch);
        });
}

int PeselValidator::checkControlDigit() const
{
    auto sum = std::inner_product(digits_.begin(),
                                  digits_.end(),
                                  weights.begin(),
                                  0);

    return (sum % 10) == 0;
}

}   // end of namespace pesel_validator
