
#ifndef BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED
#define BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED

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

#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)

template< typename T >
struct is_msvc_eti_arg
{ 
    BOOST_STATIC_CONSTANT(bool, value = false);
};

#else // BOOST_MPL_CFG_MSVC_60_ETI_BUG

struct eti_int_convertible
{
    eti_int_convertible(int);
};

template< typename T >
struct is_msvc_eti_arg
{ 
    static no_tag test(...);
    static yes_tag test(eti_int_convertible);
    static T& get();

    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(test(get())) == sizeof(yes_tag)
        );
};

#endif

template<>
struct is_msvc_eti_arg<int>
{ 
    BOOST_STATIC_CONSTANT(bool, value = true);
};

#endif // BOOST_MPL_CFG_MSVC_ETI_BUG

}}}

#endif // BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED

/* is_msvc_eti_arg.hpp
iuQ8Cok+JGcYibXVRmc7Sg+Qn+fpfZiKY4160g7rKC5IA6Qu0Qq/htYBzJ+XJBPV/OvTlFFUixHeel0CuF/3w2PmygxNbtK+wq0bojd89nSq5kLVQi5ePkVhENXkggJmNh3c27yCMbkVv2FqnGjmkex+UE5Y286wl5Iib5NFqvt8Fd2Vc/xJ1xVbXoCXdEik3Ns7QUZhEquLocEGy9MTv+r7skDElZcqjkfZc4gqvfQKOUSuESfioRWk+We175SY4BORIcIzYgI+AjBKS9O45PRTPP7V3E3KsUg9o4bK0BWAZoXmfncng24aU3fr5l+KHgx/ZWqaBNtgvwWNmpsDSbDBv09cBv6PAtk5tHQYI9i+QGoX1gIGr5mi/kbYtQYzAKEIcg2C3b8rs6UQkJ/uS+L1ruYSzplaGDg58Jedt7L9xEs7D4zlqnDgt//Y+0XjAsIAPR/ypXMjYKTuLlLzqR6LhXzeXnatKXj/k0w413qfuXXWIo1ohVo7ng3/GNOj3Ze9b/aYZfEbu9YTI4s3fa9XKH4nOLVa9jAIgqItb703HWsIDF9HO1UN7w==
*/