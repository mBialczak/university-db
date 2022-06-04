#include "PeselValidator.hpp"

#include <algorithm>
#include <cctype>

namespace pesel_validator {

bool PeselValidator::validatePesel(const std::string& pesel)
{
    if (!isValidString(pesel)) {
        return false;
    }
    reset(pesel);
}

bool PeselValidator::isValidString(const std::string& pesel) const
{
    return pesel.length() == pesel_length_constant && hasOnlyDigits(pesel);
}

bool PeselValidator::hasOnlyDigits(const std::string& pesel) const
{
    return std::all_of(pesel.begin(), pesel.end(), isdigit);
}

void PeselValidator::reset(const std::string& pesel)
{
    std::transform(
        pesel.begin(),
        pesel.end() - 2,   // we don't want last(control) digit here
        digits_.begin(),
        [](const auto ch) {
            return atoi(&ch);
        });
}

int PeselValidator::calcDesiredControlDigit() const
{
}

}   // end of namespace pesel_validator
