
#ifndef BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)

template< bool > struct msvc_type_impl
{
    template< typename T > struct result_
    {
        typedef typename T::type type;
    };
};

template<> struct msvc_type_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
    };
};

template< typename T > struct msvc_type
    : msvc_type_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else // BOOST_MPL_CFG_MSVC_70_ETI_BUG

template< typename T > struct msvc_type 
{
    typedef typename T::type type;
};

template<> struct msvc_type<int>
{
    typedef int type;
};

#endif

}}}

#endif // BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

/* msvc_type.hpp
8B8YU9PZ3swV/F8X08tI3l3CtbGy2XLhJ2Dp3IKdqY5IvunjcAIATXssXaV4lDYolN+fDC22s+mx1V2G2Rm+fscabqNZp53VT1zWbGfQXsyA++WDmMHPEnaH/IYfKdgK+Q7PpgTYoUV+7Enx20Deenwog37lBYSdZsRvd7WVF7QjtjMyIlx/v4Bg838SV616eJNctKL1D6ilXVldmQo4vjwiML/TdMi6vvXgCDGpqnVH29XVwX/o7bY56mrysgx7+pntc/dAnxheQ9tWuXvEJAbuxiSbALhQC6TzWuLTbyMZSU9JEIXvLMhRgytSrxEVO0Hmy7gIPjd/0Zss5/wsvaqDZb7PLhTyAgzHsLUNIaE6qxhp2iR613Hk534S3zE/r9Xn8zZl30zPRn3l7pq9nN6Ome5saKmGfo3wzh5J7aT5FfntCnXVubV0EkD36+ud1TD8+S9xTkyOOBOWGUa8PffKST/wXcYH4Cn59vguZEO6hvAOloolyBbtv3DhemeU8yT6QInd5EVzLrGO3DFewbgj++ta9LDR3gH2RWgERqfgoTWjEP7HMw7zbU0rT+ygavhiG2kik4twEngpMazPMLeIofw81BZehCvZEZ2qtv6gp1BFVHD4bPg56zPW53OJdeiZQP7Axmf4XwF5JL+onbHW5CQzqe3oVwWfO2Lb/7X8FxjHHtvNJqu1q9LFsaf9/S+iX1HzzbSLWHtY
*/