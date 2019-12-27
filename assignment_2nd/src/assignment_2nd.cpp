#include <assignment_2nd.h>

#include <string>

list_t::list_t() noexcept
    : head_(nullptr)
    , tail_(nullptr)
    , count_(0)
{
}

list_t::~list_t() = default;

void list_t::serialize(FILE * /*file*/)
{
}

void list_t::deserialize(FILE * /*file*/)
{
}

void list_t::push_back(list_node_t && /*val*/)
{
}
