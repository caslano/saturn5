///////////////////////////////////////////////////////////////////////////////
/// \file dont_care.hpp
/// Definintion of dont_care, a dummy parameter
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007
#define BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007

#include <boost/config.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        struct dont_care
        {
            BOOST_FORCEINLINE dont_care(...);
        };
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* dont_care.hpp
Do73Dw+O+p/tGtQw7lyF3kJkpgSb0Ze2bkdSkV3xaay89wFeP14fX8vXLzqd/f2jTnv/8PjHg6OjH4/bR/1aPq/gwSeapj/aCmZXnApb38kSKWaRZ6J8aB5DcdszrCjyXRvKsQiW+/Bo5VKxpK7uj8rOqOyJam6o6IP7kRePeqUXvNgMC7GNrvoOIYMP4lFqc/KSr3gr8F236bwSAJViPx7Bl7OMG7Aov2HOeDolZc0cWUI5
*/