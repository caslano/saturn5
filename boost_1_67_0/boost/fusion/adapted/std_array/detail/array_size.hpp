/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_ARRAY_SIZE_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_ARRAY_SIZE_01062013_1700

#include <cstddef>
#include <boost/type_traits/integral_constant.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template<class T>
        struct std_array_size;

        template<template<typename, std::size_t> class Array, typename T, std::size_t N>
        struct std_array_size<Array<T, N> > : boost::integral_constant<std::size_t, N> {};
    }
}}

#endif

/* array_size.hpp
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
*/