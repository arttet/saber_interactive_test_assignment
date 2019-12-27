#pragma once

#include <cstdio>
#include <string>

struct list_node_t final
{
    list_node_t * prev;
    list_node_t * next;
    list_node_t * rand;
    std::string data;
};

struct list_t final
{
    explicit list_t() noexcept;
    ~list_t();

    void serialize(FILE * file);
    void deserialize(FILE * file);

    void push_back(list_node_t && val);

private:
    list_node_t * head_;
    list_node_t * tail_;
    int count_;
};