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
// has_remove_if.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_REMOVE_IF_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_IF_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove_if
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove_if.hpp
HI6N9chFS67TP8jmH3GbbzvtmvpIyJ82abSHH6PQ1T2N7hz7BZsbt1SIe6fV74siVyGIkTFh3Ty5MfydWsSH562nfDIP4qM2Cpj/qVPO25+P1+Z3P1yGLbc25cHJqjjF91mhD13HX1SocSDDib8QNGXEXZB3hfEfX1WAf+/jU/TMtov++hF14cfqKd+U1e/VPlyxkBWuWMIKV6xhpx/AK/LA/UAGZa1p4lQrOPZ2gsCGou6OsehXt93oSnW8HW4=
*/