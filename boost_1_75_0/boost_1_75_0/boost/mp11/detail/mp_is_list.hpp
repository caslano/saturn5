#ifndef BOOST_MP11_DETAIL_MP_IS_LIST_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_IS_LIST_HPP_INCLUDED

// Copyright 2015-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>

namespace boost
{
namespace mp11
{

// mp_is_list<L>
namespace detail
{

template<class L> struct mp_is_list_impl
{
    using type = mp_false;
};

template<template<class...> class L, class... T> struct mp_is_list_impl<L<T...>>
{
    using type = mp_true;
};

} // namespace detail

template<class L> using mp_is_list = typename detail::mp_is_list_impl<L>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_IS_LIST_HPP_INCLUDED

/* mp_is_list.hpp
mF4xNOVeW5DgVEXwKA7ujHuK4Lj/tzzhwkSd/0DSAf1TayHxD7ObjZBLgfFa/YnPanC9X4mPmfL9nNlIFObEVP4gZCbsDvFZXeirtec+x5Jc+x/O/OVNTzHyZq4Xo/LTdpv02LPYtc8JX2/tTdOWc5c1VWomEyIUtCous166+QJdEamc1h29WioNDOekJ19dSr9xa3+KnBGWf3Bnw0zFysztzeEjxR0DriJ/A6lnuCDH4J215KlrRlzT1OVqdvkhfkFIkhpykyFrOGMFythIM2va+YLpdwDhlHaO17aBvqbDL/VNOVVYqQxiitOly8eAy+XFcGmNeyqPHPvjoxfgTY2O3LiDjzYvLiW/OJuYmT9/mkCy18XcEj9YfsLGWlVAQcj7cNIDr9AUv8bxNcGO4+gl857S+fIr0mhW+vRzI/r6kYbUQ/OsGoOoynLml+yXjc/xTvQOT+9dfDe/ndUexFi6u/jto4LZ05/94U6xiWuhqTxMWHaXm3FOZa5rRFzkJdjl0ub+V5TmYap6AyffC//F9vaZtMWPQSNs9feecn3+YpAvL/mGv+Ktjrq3Xixcwav0gcml4fQTI6ncRI7jwdLR1veG1zaGbvN73Ehne8Q9Y/ySX7HXzylzK/DXwy0uV9M9LsekIhs7EzXMHHVqXqY6ezUd44SGjsF+b9ap+KBq/be6Brl1bo6jXsluqnw7J37LR4DRw6KCwsxC
*/