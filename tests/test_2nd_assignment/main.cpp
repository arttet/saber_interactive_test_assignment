#include <gtest/gtest.h>

#include <2nd_assignment.h>

#include <algorithm>
#include <cstdio>
#include <unordered_map>

namespace
{
    char constexpr charset[] = "0123456789"                  //
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"  //
                               "abcdefghijklmnopqrstuvwxyz"; //

    size_t constexpr max_index = sizeof charset - 1;

    std::string random_string(size_t const length)
    {
        auto const rand_char = []() -> char { return charset[rand() % max_index]; };
        std::string str(length, '\0');
        std::generate_n(str.begin(), length, rand_char);
        return str;
    }

    List create_list(size_t const n_nodes)
    {
        List list;

        for (size_t i = n_nodes; i--;) {
            uint8_t const length = rand() % 16;
            list.push_back(random_string(length));
        }

        std::unordered_map<int, ListNode *> id_2ptr(n_nodes);
        ListNode * node;

        int id = 0;
        for (node = list.get_head(); node; node = node->next) {
            id_2ptr.insert({ id++, node });
        }

        for (node = list.get_head(); node; node = node->next) {
            id = rand() % n_nodes - 1;
            if (id != -1) {
                node->rand = id_2ptr[id];
            }
        }

        return list;
    }
}

struct test_list_t : testing::TestWithParam<uint8_t>
{
};

TEST_P(test_list_t, list)
{
    uint8_t const n_nodes = GetParam();

    std::FILE * file = fopen("file.bin", "wb");
    EXPECT_TRUE(file);

    List const expect = create_list(n_nodes);
    List actual;

    expect.Serialize(file);
    fclose(file);

    file = fopen("file.bin", "rb");
    EXPECT_TRUE(file);
    actual.Deserialize(file);
    fclose(file);

    EXPECT_EQ(actual, expect);
}

// clang-format off

INSTANTIATE_TEST_SUITE_P(test_list, test_list_t, testing::Range(
    std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max(), 1));

// clang-format on

int main(int argc, char ** argv)
{
    srand(597889);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
