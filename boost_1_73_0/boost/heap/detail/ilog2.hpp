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
eouaUvDB9BuIWxBuNuGbEN5hwtci3GjCVyG8wYSjCK8w4akIXzNnvpgzuvqaD42/esHtNuibO3sW3YPGbmbwxgXX++bGZ5sztep3Ttuvgie3VrI5rYL/W1HoTp4xXHWMy/JqXw1SifQuVJ4qhG2S2tdCGhGh0KYkr7Y5EOsrEXgJQza4koaRL6c9oUuh2JmWkF4w1+jM0Tda/HTp2U5Mknu5oQyhW1awW0RKsQiwAJT8yWPJ
*/