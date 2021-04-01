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
FPal+RA1S653W1VkKqL3r7FK/hXMqt3T00ZTRqPixGccZsymgWV8/hDoS0s59zrAikVn2ghxzayeqVX5w0MLmY0kSS6jwhepoIfsYuGhTfjPXmxIIwOK1Ch9yzHy9MeMa7In4F5ThUIm1rtT+0Vv2vp1BZD07JHpaVt71uIEqvEMzyUj0Okpvf/mqb5YyxPDzTDEH8tATwmiwQOBqLAzE5Chih4KBDQTGxcvNOUcKcnXSnUUQCTDaJMp7Aiz7de2XcJgC5+US8XZOMGowfHbBlPL2xoDzZGrUQN+Ung/epYZ4U6ZNJ6Ci7374rwOjuAJzl/r04Pb9tu3FoparN975PycrGGcCBGgPrQ4lCg8u6UyK28kRby6mhNjI99XHX04GsYM0HyRlJOZ9iDZyTju8KeayWBJIM+1FEqS/ewizbWMFDx24TjKqqSm7T9aNkHupjxWo1wNUd1Dl7nN0aNrTwrDn95cnW0bEof/nQdXJdf9FH2ZTgCn7r6FUVq18Kw/t7CcDUXSwgDMgPm6AsE2TEjRpo3gaCc92h3EFCuH+Y7u24wYY+WbXsi/kw==
*/