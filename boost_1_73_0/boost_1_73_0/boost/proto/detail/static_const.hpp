///////////////////////////////////////////////////////////////////////////////
/// \file static_const.hpp
/// Contains definition of static_const for declaring static constants that 
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012
#define BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        struct static_const
        {
            static T const value;
        };

        template<typename T>
        T const static_const<T>::value = {};
    }
}}

#endif

/* static_const.hpp
UwxU+pR+bpGJEw+aaP8mUPMveqi/LLTdb2D2LwYadAR+4xg/3GBh/RHgjeUGrHQTvwQsVBtg4rMbiXliT54bLXy2ysTm19hvTwPfduUavjFwqB7Q8n4TjYab6Jhk4vA7JswzQP8GJm56yMD2PUDXby28dNhCfhUDHd80kXa5hXGzDWxeCXz+toW0S0yUK2vg5ngTGz8GVpI/TyRaqDgD6PQ+fdMSC7n9DCQ8amHSfQZeG2Ch3VcWzn+Sa5DRHHM=
*/