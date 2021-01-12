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
DufB72E1TCDvLIDJ8GyYBc+BR8BFsDVcAjvCZbAn/BU8Hq6AY+BKOAleCyvgdXA+vAv+Ct4Lb4Mb4DNwI9xCGj0GX4VPwD1wK/wGPg27O99Kg8PhdjgGvginwJfgQvgqPA/uhEvgLngzfBOugx/CR+CncCvcC9+BP8LRZAw/8T0ZhuBzsD7cA5vAK8h7efBG2Ar+DnaAW2BH+DTsBp+Hw+DrcDh0vvk1Ck6Go+Hp8ARYAE+C
*/