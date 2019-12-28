#include <gtest/gtest.h>

#include <1st_assignment.h>

#include <bitset>
#include <cstdint>
#include <sstream>

struct test_int32_t : testing::TestWithParam<int32_t>
{
};

struct test_int8_t : testing::TestWithParam<int8_t>
{
};

template <typename T>
void test(T const value)
{
    std::ostringstream actual;
    details::out(actual, value);

    std::ostringstream expect;
    expect << std::bitset<CHAR_BIT * sizeof(T)>(value);

    EXPECT_EQ(actual.str(), expect.str());
}

TEST_P(test_int32_t, bitset)
{
    int32_t const value = GetParam();
    test(value);
}

TEST_P(test_int8_t, bitset)
{
    int8_t const value = GetParam();
    test(value);
}

// clang-format off

INSTANTIATE_TEST_CASE_P(test_range, test_int32_t, testing::Range(-100, 100, 1));
INSTANTIATE_TEST_CASE_P(test_limit_values, test_int32_t, testing::Values(
    std::numeric_limits<int32_t>::min(),
    std::numeric_limits<int32_t>::max()
));

INSTANTIATE_TEST_CASE_P(test_range, test_int8_t, testing::Range(
    std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max(), 1));

// clang-format on

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
