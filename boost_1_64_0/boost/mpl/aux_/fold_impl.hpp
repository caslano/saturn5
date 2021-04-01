
#ifndef BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX fold
#   include <boost/mpl/aux_/fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

/* fold_impl.hpp
IazH6rVYd8/xPmHCzfOEZvOnOUwwEkqEYxA2GTpdur1gZfTaPmKcSzvfYwlk00WaCxIdP3BLJ8sWpcDIy8+u0b5+vmCnNeR49OeJ8mGUYhEFgDNCpA375R7qO5eoB9OrgNVfkCuyJ5WuSmEYhxNajWzrE6rjVYxy0zooem9Z0CiFOEfk8WY8Q6M2Gg6Vn6W3kxFzD3bX6PTvPhj34A96WPBdKfQCNyiyqXrGMTr1EbWE0oun1/qK6WLb74CI7XgVxxVChVoM/013TVVq10hdXfuleqXXRjwH7/7smYsDct6jP0kvQYe5o/jzMTAvgxI5lmpIzOgY05eY/g0q//GlfD7AdzGxMjT5cEvTLA54ZkdIDXGZZ8ZoOG7rpUYMgOBYPYjQYD9oAli4LysB8DanzVYP9wmnkUdiybL2dXzFNiLodBwVOXo2x+v9qn/8GR0VijGxGfpi0SNVEGSs0kjHmG71fhDVmtTYWaZ0O1pthTjvwweCdHR4M0MiS2umUBSCf1TRose1A2quDvKD58QNROwl6sznEemlkxo4EnbO5tstl5+dJf2SNQGCJA==
*/