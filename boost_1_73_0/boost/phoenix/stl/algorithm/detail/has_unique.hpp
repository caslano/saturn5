// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_unique.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_unique
        : is_std_list<T>
    {
    };
}

#endif

/* has_unique.hpp
a8R2f3ub9ZZiLinxhePYI/iTc9qPvGLsdBXGuIqud99HTBLM+yPk3PzCHfPWW+TtEH+odzXT/Iosk5cVy1pzEj+t5Y73aQR33HHI3kziqGLY9YfIMbL/kLYGNvSLbJw3TiKvhFh1GbkfnMiR44wuHiJ2TIcvxY5EY28W3eO0k1z6STMYozt5lh1RfWLt4cSgAR9jK/DZqbhrX4V8ZcNXbSbX7x1ihPE9sJf+yO9J/iYH3xe8
*/