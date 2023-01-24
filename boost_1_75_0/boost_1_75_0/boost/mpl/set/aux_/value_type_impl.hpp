
#ifndef BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct value_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
utPi1avk8pifqEj2Izyw9uo6q4F3dCb3VhBNW1cjeic8ZuozbfEa4jmj3x0f/6qm7H0WmCxSq9qEmv6lKqQO+06oM7zu72sP5sWuyQABjAWyHIV8F2KV2eNgt8G5b5riEamWvKDu2t1fvnr0/Cl/w9BtCtpFVTprVoWYMd11rBZt/phOMeDF7dj+XUy6SBiNJSWa55z70dTBhNPkLvCZhfUII3srLHy5dg5XsU9po66IZ4kkfOBHx8996c9L2HZ88+uLKGTkDblteVfi9DioNSZjQkxZzSnvsXRVQhqOYiHfZpIa0sLMjASxFalb9qKXpJXGyNFkjn+HsiW8t/YbYgB8oFBmjHJYObjxbGrysEO1X17YILe7AZ6+d/f0bkT2OweuNtmfH9kf3zc22tsYKzPeUuOGaScUKe9j9rQix72hJl393Bsln2nnwLLV09PTXWxsrK8PgFOiJ26wGxLCI16YDIj7wYMPwicqU1vEwuhqKL5wT4lykF2putssWrnC2/PJaD8UubzYSlCs0ONuQIQruu/r9U8hE4IzD6JsCspL+lHx6nhZV2G6rc1eucci23KlyPS3H5weF3IDMaXusnodvTmxxTNu09FCrjM4lCinHErUNzQ2FzFwRfTLf6OJSWmLWVn4OUybZtbjl4SByc1Sqa/vZUu9Bs7G5/LpTbJb/uVpa8UeL3bwDq0oEkRpvTOqqD2twIFPbjZd
*/