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
Z7fFNRLjfawQZ4WxBc8F9+oOvjdzCOyJ1EAkcEJ2TMAb4B+v30L8hRLgqiN+fVr+f8CFfs8TzXMmFN1PF3FqwYEXR8QFQl78+KyFwgIPx+vSlVSz8831ucaJKGsEED0RIxEjF6fMB0jGXyIXbdure41CF2RUSB0//b7rr1b+TNcR3QU3mnylvf7MwG1KD5bKPNn6FtahkxbN95uDaL8X08FRyDuK7ALbqtFZenoyjLXVlGGdDMsMzzXic8p5180L6J8XuRS1vysNqovQK7S7TpS32A/mMX/cwnMhjKMeurmEWvOeXfMJGPFT6xsLU+byuwX/SG24+fqZsfjAw/1PW+oagVgTMNjbNMa5RCvA/g09AF+XozAPfuhONNnkM27CLm94tD5zbBZVgzibDpPhE4mk9K0NvPLAU21juIFlmEfpJabaMDQW6OwPT9yrrf451I8iOm+iEvg7LC/HmYfvN34nQqBzmfWmlKEdeU+Glz7QkiGQivxzD89DsLOUQ2KQMMgYWbT4PYR8GVkseNzzA0ADv4wH9EWVCgEtx/UFyTPkeqRzSQZK8CPwG5kETronoOW3ZpM4IfLoZ2xqe1yGlVMbhcQHjrS+pMTFndMGdF7W2xlTorLJlcNASCapzzGUJo8dZUeauhhYgQTFTpgP8qSweDbO48tdqM8RU+yPypiMeiWB0uSX0UOTp0UVKk9p/Ekux0BpSWOlgUil
*/