// boost heap: integer log2
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_DETAIL_ILOG2_HPP
#define BOOST_HEAP_DETAIL_ILOG2_HPP

#include <string> // std::size_t

namespace boost {
namespace heap {
namespace detail {

template <typename IntType>
struct log2
{
    IntType operator()(IntType value)
    {
        IntType l = 0;
        while( (value >> l) > 1 )
            ++l;
        return l;
    }
};

#ifdef __GNUC__
template<>
struct log2<unsigned int>
{
    unsigned int operator()(unsigned int value)
    {
        return sizeof(unsigned int)*8 - __builtin_clz(value - 1);
    }
};

template<>
struct log2<unsigned long>
{
    unsigned long operator()(unsigned long value)
    {
        return sizeof(unsigned long)*8 - __builtin_clzl(value - 1);
    }
};

#endif

} /* namespace detail */


template <typename IntType>
IntType log2(IntType value)
{
    detail::log2<IntType> fn;
    return fn(value);
}

} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_DETAIL_ILOG2_HPP */

/* ilog2.hpp
Ms5kU8r3zfuEfK28qJOGRZ2ccABzNrBnQIW6CmP/ykoctlMvYES0VJGE1QAwiBbsaZkfN4UbOQAXxSn65PgkeFquQmnQFc8D60+8Xaxd/NSl/hxrQ94sWvbwb0lgGKd696+FiQZdKHCSd5hIWcgpYb3IKQuoUmXS161+8zNN7Zefia2kD38jq1g6R1PZK9SHxBBqM3EQbdLkg958RsvmE2r1GsagbENZvhVhd5RHQWPn8nhhcXx5OHn//95Yezqst5F4qqjdwYsHv1ayJ6/iNThegeP17f3wg6K+igUIkVkFbqNfLFckzwGCOlrsfx85kFXSm/jVruU/eIW0mRlUiZVZaSo6tFKdiRegJ0ukbddqpVlxcoyl2YH1mqVZHZjKxmmUd6X63iIuJfDswlUS+5eXkKZnbR8M5Q/gSez/hEdm4zZ+sYcrLn2C6cCoe6W3fnvAPBxUfZ+Slvi3m/O+qnuR/SnJzH+sZS7ueJWh52qhHc3Wzl7/XZutNc7g9n9dtPycoL6K5Ucy87jctEGW8zlCfTlh9kVTEe2HKlBjUN/eKNV5gDQGIwv4y6UprpBe68XqD+q0LewzvWd41ooacylqzEM80E3VBeVE6UfzdHMGnNOrBxt1cyjfCZEcMG8ROSjtuOr7Hq0t9W1W+ArIdzFWQ7tADTPuFGiMnL10uVT1MmnWNKVCHUPL6m7dtsmlZv6EJ/mIzaK2j/Ni1aO66lIbHpSGhlb95pDAZIxcbvvxYf2OvmZNhgvv5VJ8hzLUP7q94LNYbY69T3AG+xubi3VvPmyX8znLkSUr5agOeLKjELkePfhIZKdQCPGin+pCzPA8J4Q4H0J898ZYIZbS/v8vhYkeRODYpK+BSyGKe/1KRA7KXpf6yt0sF0BsRp30Px9WD27UN158JS7VOVcKbiyulSPDLN0qDXpyxY+l4NJJcFJmC6h/cqn7rmP6KJ9DF7Gkqniop0mqed23bU3Y8aOPR22rnufLhYipIQOZnMyEyQktUKxcLly1Z3i28bXR4K5YGfaQ//8buAC8JgkDuwQ2KvR5wkssavv9bLUEzuzAin6LnvY+mbb0hhiDQVgsWklHpcvNMbbF0cnulMn6RSVjO+Ak+u/mx4KZPHRKRZQnpCe9VSZ9bS0n5aFatwPpHn708Tz7nx9GfPNlNhczz+AnijYlNJNDueq5Yoi+sObZEEMkewUFncOOgU5dfr/X5fcoy28O5Pdrlp+4MGGgx2GMlp/nDpFZ6PrORFhFIjz71xER9vP80BgtwtYfdC6zgVFwd0Zlc8H1EbEpSTzVhdss5omVxJVhjOaETOW4vuec6NnnKHnNYXkxjzCg70Zeu2Pl9XNB5fLrek6lLq8zjVJeVHSio8buX+o01PQWda83xZfOJXOLMK+g28exHIePY6/BZ44zJLBUW2NqJfOc1v+CEany7gEN6BJccuK32N+eYFt1D+NF+wrptks0XKjWAsWA3Ya+nm9ksPcnrfCL2PcquSU50k0aUrJCHodzeHrrErwjipAf6YRQfV1iVTfQ2CQJnVsAnVXBXCJql7C/713dXGwVjHarAx7knKS9ruevMZyX2M3BnnP+2/nEbS+dUe2lkdvL+2Lby0tA74w1cdvLlnuj28tfR9pLmTZtTfftZSTZnTLZW0oX7aUz0l7eE2GwTPpr5dvn7lH1z8n1j3mGLadu6l8wVgsUoQVHVvecTl1+G3X5Pczyy4T87qWn5XaLL8M7PqpOrRHZ3La6M+G5SHgpv4wIr6+3MKqZHBhHVBLozqgMRq3uQlSZuqi8YyULIkm/CvScBT3hT0Q+mUI+FgPJx9GZfAbr8vFmRlEWFJRddGyUaetFuQp5sRg=
*/