#include <assignment_2nd.h>

#include <unordered_map>

List::List() noexcept
    : head(nullptr)
    , tail(nullptr)
    , count(0)
{
}

List::List(List && other) noexcept
    : List()
{
    swap(other);
}

List::~List()
{
    while (head)
    {
        ListNode * node = head;
        head = node->next;
        delete node;
    }
}

void List::Serialize(FILE * const file) const
{
    std::unordered_map<ListNode *, int> ptr_2id;

    int id = 0;
    for (ListNode * node = head; node; node = node->next)
        ptr_2id.insert({ node, id++ });

    fwrite(&count, sizeof(int), 1, file);
    for (ListNode * node = head; node; node = node->next)
    {
        int const size = node->data.size();

        fwrite(&size, sizeof(int), 1, file);
        fwrite(node->data.data(), sizeof(char), size, file);

        id = node->rand ? ptr_2id[node->rand] : -1;
        fwrite(&id, sizeof(int), 1, file);
    }
}

void List::Deserialize(FILE * const file)
{
    std::unordered_map<ListNode *, int> ptr_2id;

    int n = 0;
    fread(&n, sizeof(int), 1, file);

    int id = 0;
    for (int i = 0; i < n; ++i)
    {
        int size = 0;
        std::string data;

        fread(&size, sizeof(int), 1, file);
        data.resize(size);

        fread(const_cast<char *>(data.data()), sizeof(char), size, file);
        push_back(std::move(data));

        fwrite(&id, sizeof(int), 1, file);
    }
}

void List::swap(List & other) noexcept
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(count, other.count);
}

void List::push_back(std::string && value)
{
    ListNode * node = new ListNode;
    node->data = value;

    if (!head) {
        head = node;
        tail = node;
    } else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }

    ++count;
}

ListNode const * List::get_head() const noexcept
{
    return head;
}

int List::get_count() const noexcept
{
    return count;
}

bool operator==(List const& lhs, List const& rhs)
{
    if (lhs.get_count() != rhs.get_count())
        return false;

    ListNode const * lhs_node = lhs.get_head();
    ListNode const * rhs_node = rhs.get_head();

    for (; lhs_node && rhs_node; ) {
        if (lhs_node->data != rhs_node->data)
            return false;

        lhs_node = lhs_node->next;
        rhs_node = rhs_node->next;
    }

    return lhs_node == rhs_node;
}
