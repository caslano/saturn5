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
LrNWzCpmrRRvNusfUEsDBAoAAAAIAC1nSlL9RGrzBwYAAFUbAAAdAAkAY3VybC1tYXN0ZXIvbTQveGMtdmFsLWZsZ3MubTRVVAUAAbZIJGDtWdtu2zgQffdXDNI8JIVjpN3dl2SzWEWmbaGK5Epys0UQGLRE20RlSaBkJwb68TukLk58VZOi2wXah0omec4MOTOHFPPm7Pv9a7xpvIFH/2xBw7NxOElbs99Vkx4nS8En0wxO/FN4f/7uNzjDx/vzJrRpxFkIbsaiERMT+DNQDX9P6eNjK2V/KXyfiRlPUx5HkMUwT1kTfKRswiwO+BifNAog4Gkm+GieMcimPIU0HmcPVDAYxwIHLJEnmYskThk88GwK2Cqf8TyDMWOAiCkTbLSEiaBRxoImJCJe8IAFyEcz/I8BHcULhkR+NaEozrjPlAPKarJytexKEkYF8AhoGEokZ2lLTcvrEXDtjnerOQQMF/qO/clokzYcaS7+PgLNaqtB2sDr2Q60DVc3NePGBc00AVGOZnkGcZHq1vB64JCu5iDCRhDSragt3Ry0DaurcMZN3zTQyAoPdgcpboij97BBuzZMw/usjHcMzyKu20IKsGwgn4jlgduTNE/8uiZgGtq1SaBjO8ikWZ/B7RPd0EwMsOEQ3WsiQ/mG
*/