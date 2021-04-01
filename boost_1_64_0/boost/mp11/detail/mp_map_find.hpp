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
JGHJ+55TtZt/KT1fTpaOY7DqyfciSbWTcJItabnNY9duE+tov0yyEPyM8R4M56qkR63/JaQ/Z1MR0MULKx69WifmVbhTmdKA180VKDlqv/aIv1b9NXlSiBAQNNHE0LxjSQnuLzZsbLlIua87fnLw2zsHLyOdMaCxKhf0Dd8E3pncozrX7W/GCmR0EdtCdS69hVxkBTnRwwwoijwRbSSGxDiDPsRdegx/Dp+yl2ocHPNuI6trHLW5vKzgCT7Pij7R5vOFw4zq0WtyS6hz2pRqKIEObvV3Vt37JqexbPg/JsTqaAH8lfxE8f/TiPQZy/LgCDndx9DwjICze2kgvM19/NpnEjFoL2+UStHdAck9YQYushdxDsKcpAhS2eU21GD9wiq1dUeZmi/QsRCzv0wyYoxz7w+FH76uED+2UzzZdTpgeMthUip8ee+QYVD9NUtVxgZQKFIQ4SIUu+4yWFj6uaJLp075i4YWEwgr/SgsFzrUo2tvWsR8bCYikFn+7ffO6hSXSvqCx7yiIxN/DRUShduj4OW6DvutRo/jmqtXlOBMn6tPLw6xMMjR6A==
*/