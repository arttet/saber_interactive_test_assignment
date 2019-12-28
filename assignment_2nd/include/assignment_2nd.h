#pragma once

#include <cstdio>
#include <string>

struct ListNode final
{
    ListNode * prev{ nullptr };
    ListNode * next{ nullptr };
    ListNode * rand{ nullptr };
    std::string data;
};

class List final
{
public:
    explicit List() noexcept;
    List(List && other) noexcept;
    ~List();

    void Serialize(FILE * file) const;
    void Deserialize(FILE * file);

    void swap(List & other) noexcept;
    void push_back(std::string && value);

    ListNode * get_head() noexcept;
    ListNode const * get_head() const noexcept;
    int get_count() const noexcept;

private:
    ListNode * head;
    ListNode * tail;
    int count;
};

bool operator==(List const & lhs, List const & rhs);
