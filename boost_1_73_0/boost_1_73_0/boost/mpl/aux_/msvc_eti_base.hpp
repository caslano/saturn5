
#ifndef BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED

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

#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)

template< bool > struct msvc_eti_base_impl
{
    template< typename T > struct result_
        : T
    {
        typedef T type;
    };
};

template<> struct msvc_eti_base_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
        typedef result_ first;
        typedef result_ second;
        typedef result_ tag;
        enum { value = 0 };
    };
};

template< typename T > struct msvc_eti_base
    : msvc_eti_base_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else // !BOOST_MPL_CFG_MSVC_70_ETI_BUG

template< typename T > struct msvc_eti_base
    : T
{
#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304))
    msvc_eti_base();
#endif
    typedef T type;
};

#endif 

template<> struct msvc_eti_base<int>
{
    typedef msvc_eti_base type;
    typedef msvc_eti_base first;
    typedef msvc_eti_base second;
    typedef msvc_eti_base tag;
    enum { value = 0 };
};

}}}

#endif // BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED

/* msvc_eti_base.hpp
I/xUk+xpvV5Te9LrdWyYun5lKpCnWiBEAm+WXVNQGp1qUTiSFR8jgs3hrXqoITPGE6L20bQipCy8xSKk8sANRqLnauXxWShcySsSNHXhC5iqq7kINAMJN/LkbwacU+YSBL8CEZ3FKKBQtspxB9IPiwM/iib4Wh0ByrUMPSlbesojCYFbLLRKv9v8UK86jYue07Za1RN3yiIpTWmRtoGcKVdimmcfOt1q88I6gxrZvQZl47Qcwsgjo6mPRtMw8rT1qJNnneGZDpxI/fohNLjsSfnS2ENOJb4lLmS6dDKBxaPILen6M2mW3Sk9k8R1LrqObmSNIkSgJCsW0QQoXs0xE0YWznaD66UOtAJk6usBMG3hdcA5ICwcz5FcLAiPRXpWuqBM/hIYERKjfR5Qsa+ZN+nYVBkV1JXeBfZQalc2B2GxjBGIFlBaQl9B2NOszQWwTDpefXDrNQa37y/t117+/GY08WZXl+1bGO66JAFJL/WXctWv1Rn/S93dzFCWkV6m9lcpYHGd7NyCNCPVLesKUpK8rqyybw1XBpRnq9zVSB+Apb5F7pgZUEBiv9JrybFd7Vrv3hQuuNfujMqJ/4YeVQazZu+icCZqc9t93+i33g6uxdCeHhvcODo2LgaJZ5zffoq7kZvv5lxjML/K
*/