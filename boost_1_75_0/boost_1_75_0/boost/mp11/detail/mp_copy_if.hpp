#ifndef BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED

//  Copyright 2015-2019 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_copy_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_copy_if_impl
{
};

template<template<class...> class L, class... T, template<class...> class P> struct mp_copy_if_impl<L<T...>, P>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )
    template<class U> struct _f { using type = mp_if<P<U>, mp_list<U>, mp_list<>>; };
    using type = mp_append<L<>, typename _f<T>::type...>;
#else
    template<class U> using _f = mp_if<P<U>, mp_list<U>, mp_list<>>;
    using type = mp_append<L<>, _f<T>...>;
#endif
};

} // namespace detail

template<class L, template<class...> class P> using mp_copy_if = typename detail::mp_copy_if_impl<L, P>::type;
template<class L, class Q> using mp_copy_if_q = mp_copy_if<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED

/* mp_copy_if.hpp
g7R4fUVIKNxEJGxSECWeimFVtcMWV1QPw//Dyt0lnmGVI4aNGMa13uV/78JqX0WVO9BLFx+yOn/xf1Tw/F+KAyXorl2C3FUF+bpJG1dUgM5yPurWTQNEGqJKS5uTXpCbNT4z7UIhpszMz8jt1NdpOVnps/KMhv6waVolurT51ItX1M6b6SvxLawVd3Jfgf/SXYswOmXXVLrQ1B/x+55V6/bmoWGJdeyWVb2wCuNsaa24UmTU5GH4neKukkPA74xetMRXEhScOFWbjfHLLTeGZ/qqxOMUFnXDeTUzfTinCvWTUaPOnlRd6yuppvFhi2kGBrPOk8SrJmOLONNbMj/TWwOd3w63RTWXuP0u/TtDmriwAuPuT6aZssgneGuqJs6alJkk/iAya/z+V1Na5K51hae0psTrEk/I1AW6/BgQRkbOzEmZWKh25h2JVP3CUr+bmgiImko3V0C4f2zIqamej9HzFRrL/C65Pm+6eBajQ7VrCkbhkvk0wq4jPzOlLmAI8VbMQ8t8iN0yaiprvDwqWDAXoA106v8/F1nVrtySCmpFD2IcrXSX1NJwN0qOnRniTJPKLJqZPCFMjEepVvMZOeZZ1WhH8p+lWq5vkhJFH3/6c2uQiii/HYMkjS7TysrQJyrfwpR16cISlaCDpkk0z6il4ZTsD2M+IntndbborU2qZVHMorRh/kjq6Rb/wJmyA+TRGLN0+n9CzTyo
*/