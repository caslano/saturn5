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
rWk86HGrYVbgfdsdK8FV4Q36BsXrKHjjgTLZUryJYeq3Y+27iaaiohTvUrvqTgZ8b7Op9/QBEVKONzQsCHDa+KrbU2BdijfQe92B1R9dNIz3tCE8QxvDWRODjlaGp19bkzG1GKrxtBeX5CBKwbvCTXNjRbRyPIzR+mSohFmONwD/G3bN/kvNMnVrYmiV0UGKd22YSgVbgVenbpTjGcZEG/c0xSKR4t1or0Zdw/j+UgmuBG/8
*/