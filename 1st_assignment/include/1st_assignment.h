#pragma once

#include <iostream>
#include <ostream>
#include <type_traits>

namespace details
{
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, std::ostream &>::type out(std::ostream & out, T const value)
    {
        int8_t n_bits = sizeof(T) * CHAR_BIT - 1;
        for (; n_bits >= 0; --n_bits)
            out << ((value >> n_bits) & 1);

        return out;
    }
}

template <typename T>
void print_bin_number(T value)
{
    details::out(std::cout, value);
}