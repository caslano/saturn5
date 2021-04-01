
#ifndef BOOST_MPL_EMPTY_BASE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

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

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_empty.hpp>

namespace boost { namespace mpl {

// empty base class, guaranteed to have no members; inheritance from
// 'empty_base' through the 'inherit' metafunction is a no-op - see 
// "mpl/inherit.hpp> header for the details
struct empty_base {};

template< typename T >
struct is_empty_base
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_empty_base<empty_base>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

}}

namespace boost {

template<> struct is_empty< mpl::empty_base >
    : public ::boost::integral_constant<bool,true>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,is_empty,(mpl::empty_base))
};

}

#endif // BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

/* empty_base.hpp
X/nW+srkkgxVWIlwmXetYAopVxzkvVbJRgR5ezFk4Zs9aa9esFJEA609jczGqZc1FOi2CZ9jleFpQGqSiV+gh9tfwQ/CGbwY5Gd3XcxzOXwTbhODF+J8BQhudqpdklPy9MLbbZREKCDxbYPHXOvQW6hU00c7TvQcUFpsLOeTfpZKsc80f2Qz3FoWLE/EashVO+4YZSAXAiEK1/HB0uFw2WQP9Y6hNh79isFTNO6eQCuD0oYm9HUO6HBfbnHKUiWxkEVifZkmE7GL714oyRAiJvyOXOeWDPYRGCkJINXSHb/S5j5NdQF4i1mEYmU+t7xCq1evPWX6Jv8P0d2DVvGsAFi9NGllOwPmVgwOaGadHgQNnPqWGMRumUB7F9ZqQ7r54r3zQbJz3gf0CQfCHglWjkVuUpSv3A1tHjEEfTSeIv4Fq0NwGCeELIjN8oz16FNGszAoKRcMdELicSkKnjVtJyOWKWe6K4+U2Pj53zKatKoxRxFLXa85ak/4Qo0SwFaXrD5R1xznFDcUgfQFm+ecjxUX5B8SuqohRdj7StzCRxJExXuft+yLyO68NQ==
*/