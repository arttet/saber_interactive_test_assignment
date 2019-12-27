#include <vld.h>

#include <gtest/gtest.h>

#include <assignment_2nd.h>

#include <cstdio>

namespace
{
    char constexpr charset[] = "0123456789"                  //
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"  //
                               "abcdefghijklmnopqrstuvwxyz"; //

    size_t constexpr max_index = sizeof charset - 1;

    std::string random_string(size_t const length)
    {
        auto const rand_char = []() -> char { return charset[rand() % max_index]; };
        std::string str(length, 0);
        std::generate_n(str.begin(), length, rand_char);
        return str;
    }

    List create_list(size_t n_nodes)
    {
        List list;

        while (n_nodes--) {
            uint8_t const length = rand() % 16;
            list.push_back(random_string(length));
        }

        return list;
    }
}

struct test_list_t : testing::TestWithParam<uint8_t>
{
};

TEST_P(test_list_t, list)
{
    std::FILE * file = nullptr;

    uint8_t const n_nodes = GetParam();
    List const expect = create_list(n_nodes);
    List actual;

    {
        file = fopen("file.bin", "wb");
        expect.Serialize(file);
        fclose(file);
    }

    {
        file = fopen("file.bin", "rb");
        actual.Deserialize(file);
        fclose(file);
    }

    EXPECT_EQ(actual, expect);
}

// clang-format off

INSTANTIATE_TEST_CASE_P(test_list, test_list_t, testing::Values(
    1
));


// clang-format on

int main(int argc, char ** argv)
{
    srand(597889);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
