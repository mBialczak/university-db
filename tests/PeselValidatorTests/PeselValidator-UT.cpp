#include "PeselValidator/PeselValidator.hpp"

#include "gtest/gtest.h"

namespace university::pesel_validator::ut {

using PeselWithVerification = std::pair<std::string, bool>;

class PeselValidatorTest : public testing::TestWithParam<PeselWithVerification>
{
  protected:
    PeselValidator validator;
};

std::vector<PeselWithVerification> pesels_verified { { "90090515836", true },
                                                     { "92071314764", true },
                                                     { "81100216357", true },
                                                     { "80072909146", true },
                                                     { "90080517455", true },
                                                     { "90060804786", true },
                                                     { "65071209862", true },
                                                     { "67040500538", true },
                                                     { "0", false },
                                                     { "425", false },
                                                     { "5325", false },
                                                     { "2535325", false },
                                                     { "35292569", false },
                                                     { "notNumbers", false },
                                                     { "99012723456", false },
                                                     { "02271409862", false },
                                                     { "74110101745", false },
                                                     { "801105124678", false } };

INSTANTIATE_TEST_SUITE_P(PeselSet,
                         PeselValidatorTest,
                         testing::ValuesIn(pesels_verified));

TEST_P(PeselValidatorTest, validatePeselShouldCorrectlyVerifyPesels)
{
    auto [pesel, expected_result] = GetParam();
    bool result = validator.validatePesel(pesel);

    EXPECT_EQ(result, expected_result);
}

TEST_P(PeselValidatorTest, operatorShouldCorrectlyVerifyPesels)
{
    auto [pesel, expected_result] = GetParam();
    bool result = validator(pesel);

    EXPECT_EQ(result, expected_result);
}
}   // namespace university::pesel_validator::ut
