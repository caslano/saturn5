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
9kvgi5OYr7WRLxZFS24AqHg5J7eC+20FozWvUsTlqrqT+da2vi1zsvLC8qytghye8Bp5o4Qr9pf2qkJ5W2c38xWufN1JPiRxpqo48nWh4WeTJQ7yLl+DKfA9JBzltsD3l/AUl0Fi+PADffo6vHj/Ceys+8/R2vxi9kl+DseAuGta1SeW2frTFgkjKxTPH9ay8fctjT8z70vsmcL5rzRH5B9HYvZcMGXMC+UkSR9T5xU1/8xWx1+rWnQr84ps9Tg=
*/