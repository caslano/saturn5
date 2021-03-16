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
azB7L09sFnV06u0myWd7+rK4uGkuaw0Ajq/pZyhpmAED0VXog9Y1bxZFa8fzznnmKlfWdMta5cpsN48yZIeKeXuOXIBeYTUS2rDc6TxOecknyJZzOmHGvMuLsgFmPBmYMZlMcahrCUzai5lBfEIgm1taZroLA0EIVsR8uqN85NY8OiyLB+9nwl3j0Y7nRChYWIC+sNhVhidEKEFZa6k6oTjXk88OeBmAbyqt+FkhBJeLZ2EGVxHj97gXN7zPDiw=
*/