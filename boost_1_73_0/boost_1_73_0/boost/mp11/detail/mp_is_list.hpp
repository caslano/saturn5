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
WK9XC4+qQ2Ms/OkFZILUzHnsjmoQEHFoTy7qh8fjF7LQhUBGZV3jJkechuHl6+V6s1illxZttXy/CdHQCQR7sOMfg1Vqb+wRPaN5MhhPUIKCj0x422WNbnxgihcHsGad9bulgJJonCg4RXxdSuN72ad2LwI0ShpJZTX38NcGnMKHimJtpTYpPNLS835G9cHVDqlToHtVhZcfbt6vF8vbnndFKWtw+Vn4zFbwm2C/mmNdf1qrrMkz/8E4bNK/bNrnsFd85rfc7X7dSKFxy3Qy6ieT7ZhF0Xg8Hg6mgwGdjkbFcJRPt3Q89v9RerY038m5vwv9vdyz/F84GNNRMo3IaLwlNOlPEjLdRv1kEPWLZJsMB9E3OfjLy8X6enl7e3O9+RUb+tSQWXjs0vD0h+kzUEsDBAoAAAAIAC1nSlK98UzwvQEAAK0DAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQxOVVUBQABtkgkYK2TUW/aMBDH3y3lO1w7IXWVMofRl0VWJMTYQOsIKllfpj0E50KiEhs5Ryu+fS+YAirSnvqSOL7z7/73P0cRtqTzFhOhalNafj3h7sW6ok3EJMvm+wf8HGd+Mcvuf0O+pUpoawxqqq0Bh+G2RaHk6aiSnvYJFuie
*/