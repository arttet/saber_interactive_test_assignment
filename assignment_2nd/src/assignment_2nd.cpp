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
    while (head) {
        ListNode * node = head;
        head = node->next;
        delete node;
    }
}

void List::Serialize(FILE * const file) const
{
    fwrite(&count, sizeof(int), 1, file);

    std::unordered_map<ListNode const *, int> ptr_2id(count);
    int id = 0;

    for (ListNode const * node = head; node; node = node->next) {
        size_t const size = node->data.size();

        fwrite(&size, sizeof(size_t), 1, file);
        fwrite(node->data.data(), sizeof(char), size, file);

        ptr_2id.insert({ node, id++ });
    }

    for (ListNode const * node = head; node; node = node->next) {
        id = node->rand ? ptr_2id[node->rand] : -1;
        fwrite(&id, sizeof(int), 1, file);
    }
}

void List::Deserialize(FILE * const file)
{
    int n = 0;
    fread(&n, sizeof(int), 1, file);

    std::unordered_map<int, ListNode *> id_2ptr(n);
    int id = 0;

    for (int i = 0; i < n; ++i) {
        size_t size = 0;
        std::string data;

        fread(&size, sizeof(size_t), 1, file);
        data.resize(size);

        fread(const_cast<char *>(data.data()), sizeof(char), size, file);
        push_back(std::move(data));

        id_2ptr.insert({ id++, tail });
    }

    for (ListNode * node = head; node; node = node->next) {
        fread(&id, sizeof(int), 1, file);
        node->rand = id != -1 ? id_2ptr[id] : nullptr;
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

ListNode * List::get_head() noexcept
{
    return head;
}

ListNode const * List::get_head() const noexcept
{
    return head;
}

int List::get_count() const noexcept
{
    return count;
}

bool operator==(List const & lhs, List const & rhs)
{
    int const lhs_count = lhs.get_count();
    int const rhs_count = rhs.get_count();
    if (lhs_count != rhs_count)
        return false;

    std::unordered_map<ListNode const *, int> lhs_map(lhs_count);
    std::unordered_map<ListNode const *, int> rhs_map(rhs_count);

    ListNode const * lhs_node;
    ListNode const * rhs_node;

    int id = 0;
    for (lhs_node = lhs.get_head(), rhs_node = rhs.get_head(); lhs_node && rhs_node;
         lhs_node = lhs_node->next, rhs_node = rhs_node->next) {
        if (lhs_node->data != rhs_node->data) {
            return false;
        }

        lhs_map.insert({ lhs_node, id });
        rhs_map.insert({ rhs_node, id });
    }

    for (lhs_node = lhs.get_head(), rhs_node = rhs.get_head(); lhs_node && rhs_node;
         lhs_node = lhs_node->next, rhs_node = rhs_node->next) {
        int const lhs_id = lhs_node->rand ? lhs_map[lhs_node->rand] : -1;
        int const rhs_id = rhs_node->rand ? rhs_map[rhs_node->rand] : -1;

        if (lhs_id != rhs_id) {
            return false;
        }
    }

    return lhs_node == rhs_node;
}
