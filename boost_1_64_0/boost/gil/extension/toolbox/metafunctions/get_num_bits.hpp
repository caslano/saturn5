//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_NUM_BITS_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_NUM_BITS_HPP

#include <boost/gil/channel.hpp>
#include <boost/gil/detail/is_channel_integral.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// get_num_bits metafunctions
/// \brief Determines the numbers of bits for the given channel type.

template <typename T, class = void>
struct get_num_bits;

template<typename B, int I, int S, bool M>
struct get_num_bits<packed_channel_reference<B, I, S, M>>
    : std::integral_constant<int, S>
{};

template<typename B, int I, int S, bool M>
struct get_num_bits<packed_channel_reference<B, I, S, M> const>
    : std::integral_constant<int, S>
{};

template<typename B, int I, bool M>
struct get_num_bits<packed_dynamic_channel_reference<B, I, M>>
    : std::integral_constant<int, I>
{};

template<typename B, int I, bool M>
struct get_num_bits<packed_dynamic_channel_reference<B, I, M> const>
    : std::integral_constant<int, I>
{};

template<int N>
struct get_num_bits<packed_channel_value<N>> : std::integral_constant<int, N>
{};

template<int N>
struct get_num_bits<packed_channel_value<N> const> : std::integral_constant<int, N>
{};

template <typename T>
struct get_num_bits
    <
        T,
        typename std::enable_if
        <
            mp11::mp_and
            <
                detail::is_channel_integral<T>,
                mp11::mp_not<std::is_class<T>>
           >::value
       >::type
    >
    : std::integral_constant<std::size_t, sizeof(T) * 8>
{};

}} // namespace boost::gil

#endif

/* get_num_bits.hpp
LPt2IP95+K+l9PIbahq4MJOEu+Vsa6BMxZb0Ig/ot1006EEGdb5o0B0ManTRoA4IIjfg0+QWezdZ6nrDPtT1z5XSPX6AzFK73sFHhYKM04B8qhJyLkCifaBVqkhchYU/Nq+Vo0An3v+J5lmgCbYChgwYdzF+LuUNTXsC4632Lw1Wk2Fwmj34E0LU/OQbXfQkeHSlXh9qISR1YW2LTrNX5YhmriSwjgJfA5AM/lMAtLWzTdjL42FdHg9HAMyHeR4RC1Q/2wRHVb2ASZC/oGsId0td7AFw18P1hxsK9wzcc3BT4F6BexPufbhv4JbArYHbCncQ7jjcObgY4KqFX95Nqsjrq1DDYN6P1dAhtdKvwEPWtBXykHUlx5NKCkwCxLKd9zlaUQUEHlshL1jbpGfCUgKJ5dImF9UPcG6X5OdfCqPLPAqF/Gfdi3fWHIHFqOncIxF4GsJnHD6+wgeWj2/54+5RSlNzvlrmh0KZZV8y5jj34v21RtyBQp0EVC+X++Aj/2OSvAG9iWgQQZLHPBqxA77xgrb+VPzQoLfJhaK0qioFEDXC15HkSHOr5pfN/Go93cxcr99j8U36ZzeXrTI3+SJ47PpXtNJ2bqfV3o3R3gxNRMtjPUumXQi8VOR7E020U3WjknkAd9G+5jk+nxf18Do42iNlE+4Rr/Z2LhUc+c8n/BmiOjb3C6k6IHP2ng/J5ruqibX52iJC5bbevDnPxjh8eHGkFvSjDUV6sIUJPCZnmohuysd/VG3R9ivW+iUG75Uf5GyufZh7Wo+YwGqUC8gSHOihzx5TfdlIByaYmholIfCZRmnu8HnNCxpllj4JzeiqhOlzRdJ1U/BpljA3WstsQDVg3qJo1rxq8c3cgYK8eTCrqIccSYI3m7cIky5RRZE1UABU65oLEj9lRczvEa8xdwHABX0D9udKY9pO4gff0AG4d+Di0KqPwg2HmwHHMB3vYVG6cjJd9A7pc9gYTPcbCgsfMd1Lw7Sh6pbcX/A+dmV/rBD8mhh6Dv9lj04k+cE9MZRDQHsA7gIAUSEssRo/rfEAg5mpB+4FGJ+knqkdxunYlm3Fc35YgmNlhttCaBif/17eKWu7DlUpMbj9zefLZO5jiRhaKEtE8jTL/mGhSNHICcCYO/GFDlXhJ57Qn10msa9HeM6yCNMe4bR/iFDTW4Kyh6LjX75OBtxnfK57WafxOIDM/EKVziP9D9/YTkhVuhSGpmkLgrGXLJfYWYz9gsa+jG+hDPtIwzozbLCGuaRjq1o/pPzIxeWveL4ulyzqts1qlc1pvLeugFikmbyUBD3KtucW8KG2fao/xN/WKe7XiuihTJYaZ1HlFkuWCMH6G/woazxVzDLIzX3jgCqun4qi54YElG2BngYInyOtz8fxiayg2e3FOCc1DCBQbQP4N+kJRe0u6AGMvMQeKQ3Pgilh9ZSdtTBXLglnd2uW4o9drtsW3woSsJ7+8prAEaMeSmDSf0LC3uDqkMBF4cBTvAe1ZeB1yeRtkOAtATu4lMFxDE7ANUMLCPDPGsEcW4ZMUVI85zQye4rtK/EPt2nwhmXhhNM1Ye9WGrIYIaGipDL31JNKtx3RXAN6IC/2edi6gy0YVG4ntNxeC65ROmtv3yodnZNc1NXFI54R2vrm7KT8rBIcVlcAamavESIh3+V+6eyS8x9pLO2XcaDJRKOMfJFrIiKzAJxk/U3aBnvyC61zuqZMZcqTSxmESBWSs9XEpP8HP3KYFXDVAv00P+sa8wQyYmeO5naxxpwmGUNf1RqlLpwVoe+LaFfyD5IuEIn4jPgrItrKjM+Q1pCzJML991KVb5p89nxIslnDIz6evh/JSzDvIIXxrEB2VrI=
*/