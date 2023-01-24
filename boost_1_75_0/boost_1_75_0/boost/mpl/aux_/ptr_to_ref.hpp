
#ifndef BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED
#define BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    ||  ( BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        && !(defined(__STD_STRICT_ANSI) \
            || defined(__STD_STRICT_ANSI_ERRORS)) )

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    *BOOST_MPL_AUX_STATIC_CAST(X*, 0) \
/**/

#else

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    aux::ptr_to_ref(BOOST_MPL_AUX_STATIC_CAST(X*, 0)) \
/**/

#endif


namespace boost { namespace mpl { namespace aux {

template< typename T > static T const& ptr_to_ref(T*);

}}}

#endif // BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

/* ptr_to_ref.hpp
4IdPTlNyU4SfEIZQqZEeQ7SCtUIXgp7F7MRPxIxDFkI73zq8cWhYXCcxkmghuPlkTLknNfGbT7T4nPilM5G9fn8b9fQICLx/vhqc4FP50LyqsuVKtwz/I8uTEJrJ1jCCAQxJ6vhgW/velrqm5F3ey8bdnVEsoDt5IPYwYi7N4Ca8ZOqKH+PtWk6a6PqtS/Pkuv5BZdr9aUhEc9blkmKS8kBGr/Yh89Llj8G1oypwhgUIizy3eAnmxrE/mQe54DJ8JanGbOnYYc3ymt1Xbn3ZgzW7/vnMqzW5Cwp8lUmDQTMgoeF5L4Vsw/uZ1o99FBMgA9VXO5ab7FbQNd16QI+MqHNSIHg1yg0A5n9MsDkPvY7g/ZiT/dfSk3OLnUKSb5vr3YX8zzlr2OeW1x3Z8ETfF2zxTV443X0RyaPoMhzlRmlPhDWACk4HG4TBaQ7SBSdenPbImggPqX4F9Zo/1qQ6hzFjV8XShe97TScObruluAqtL0s0VbCdjOlhxQ7eknp9SJ00POk29X/eoWMW/RXU72iOUVwrEnD0ccF9YZBT1LTWR+KgUIR1NHx2YN/HuaT24FexxOvbc+66DG7WNinSzovVDfnldhd8Z7fAgdBeQGOtD1Xqd6oQnGzCjP1tpsvb633fGkr/vkTMCComWdaCmGsQfUsLNH/zwbOW1UUoT4k0BbUk1ld2CN/Zh9rHQPZUxPdHAbK4kja5BOCw
*/