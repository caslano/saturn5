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
// has_reverse.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_reverse
        : is_std_list<T>
    {
    };
}

#endif

/* has_reverse.hpp
vhzSlrFBaKffMzt9vVLE6ej8U45CXvn8uPRQ7EAAV4xkra8YSYkB2Ehw1UeKjX1S5dP1NqZS9fk5w9ebmW3g58/+ielwt8og1ulVeh5Hz2/Q89X0/Hd6voKeN9HzF6DH9ogWAy2o4w3BQnF+QT2F04CEj7fFihfYQuJ9asfz95KyX3xhx8PoD9/uK5nHtgeg0L3X79cqcErhlrB/qDC6F1rC3lFhdDd38XOS3a6670zWfGf4c1Lcj5v7nPG6XyU=
*/