#pragma once

#include "I_PeselValidator.hpp"

class PeselValidator : public I_PeselValidator
{
  public:
    virtual ~PeselValidator() override = default;
};