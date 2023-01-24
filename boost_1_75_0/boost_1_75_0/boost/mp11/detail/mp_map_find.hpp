#ifndef BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>

namespace boost
{
namespace mp11
{

// mp_map_find
namespace detail
{

template<class M, class K> struct mp_map_find_impl;

template<template<class...> class M, class... T, class K> struct mp_map_find_impl<M<T...>, K>
{
    using U = mp_inherit<mp_identity<T>...>;

    template<template<class...> class L, class... U> static mp_identity<L<K, U...>> f( mp_identity<L<K, U...>>* );
    static mp_identity<void> f( ... );

    using V = decltype( f((U*)0) );

    using type = typename V::type;
};

} // namespace detail

template<class M, class K> using mp_map_find = typename detail::mp_map_find_impl<M, K>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED

/* mp_map_find.hpp
yoSvrWYD/dVmlGzV7inxSSiP9aTqGQl1M/0aOy3Q/8fqELkwcBpGeeUQ89KjK3sdvyq2ba3g9omMSNf0xZdAAOI4pq9JLV0PL+8NG3UL8YkkWTqOLRw4zRy9UnH6N9+j2gf5U/Zn5FSecicocwy2n0dF/KW2Uu+5yplS2PtMuTEsIpK0b8biCbnGdsUiFlc9xi//H0wETyZgCVRxPhCRRF6yQE5f6etIfvYFDzkSb3Ay/BST/sIxxCUy4vwN4dW3Nup2DMx6+vQ3BV6xWny+R0WgwBvZ2nT58CECM+DX+EdhEswS5jA4err9Mpx0zLIV+K2SmhARd/x5X/kX8fAg9q5jSFAkCf+YdX6FDXUluEO5ZEkz+HQ6WbEpzC7yorIc6LnKzWbIs8O5hNc/2l1yPP+0D6TqP4sh7+2bbYTSMQuX6FLZ28uzRd3NvtMMClKRiXKjmmLf5Vsx4Lcu38vDcA2y/T0F6aKad34le9coQmUHsJQHmNFabbIbPk3Sf/406QvO6eJ3JJZkuDlw2k25c/Zx3T1EN5IEkHbubFapuNi45BaJ2v/56/Kwon+wWc2nE5LvXYWYL+RDGa7ajriFrPlFBLOkrjR2S/aRNMSkvinStv9K85FfsqFa7uU4Pnd2W+VNucJU2ZK16SuwD1waOgWQk0SuSxMnsV0k7eD+0/mbV4Gs6YWNasp9JNZyUc9pZixJbYd+yU6OuKOs
*/