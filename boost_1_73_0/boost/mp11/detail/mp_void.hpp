#ifndef BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost
{
namespace mp11
{

// mp_void<T...>
namespace detail
{

template<class... T> struct mp_void_impl
{
    using type = void;
};

} // namespace detail

template<class... T> using mp_void = typename detail::mp_void_impl<T...>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED

/* mp_void.hpp
1IsIqRcLvzCsjz9RJxzWv8xvGdFErrfeoxwnfaHt/6mEcpxjnZ+nC/OzvgPckq61qXJtoovhWkVXxz4pon0d+zZtTdxHfkxf2vfd5hT1rdKut6WFfF/9hq7fwx3MzZKbybC1XklfOQ5lUy55qV2JssGrxB2MvNKalxRzUoKJIwm1E0ZXykbrt1B/vq4d8zXSHd8p/YkkSecN+ms9nPc7lNcCJWOyrdQi0ojZLO/GE9bySrAk
*/