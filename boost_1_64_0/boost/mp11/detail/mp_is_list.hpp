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
sbUJP+gaFnPH4pDL0MO4FAXSYAs/8VB077a+K8d3uogzjXb0t1IxO9klkRXIhzwWzd62oACUtMhQsvVky0mJo0KsY0rckghcWLMbY/MaSAoe73akKzDA0ZV+oHiLb87YbiB61jdA5s7884V80GaiDs2bHy2we5V0QlWLCmRixhwbV+b/CnfzxRZogMyLGFTx1xA8Mv6YeG1mXatqDqVIUuBFOKdOwc5sXfpOkUEGtslh1aPDDzO98nwKNsfXGow1reOwkBMLvQB175pYnzad5tC/Xauhp92Gt/hsj6lgFGLEtujRFL1G2e6GIof6FgikJ/76mcWl7WSrk65IB1KrwYkMZTK5AnqenEckxkogS+nG+KQEASEfsy8aTi13OKbz+4cDeSgyVBOECwYz0k6MAumk0I8UtYY4HyiHqYrtlo3qFnMIqAzDW9Bjyt6wD/3tDJwY33I34BIq4ymI+xKlwGDOwB7bBghrC4ujCe2pGSpy7WKeR1jFHda4OmxtQqKbsGGGOPcGYKYfISb2UuvCMZ7oi61pO0XigyHrBiKXgN+ITz1r+L8+SM3prw==
*/