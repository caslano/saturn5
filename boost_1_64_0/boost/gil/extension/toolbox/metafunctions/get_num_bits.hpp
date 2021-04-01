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
7vI4ntl+hoMZ+LuG254S91hDSapyf51+4BPBq4LQP+KSTIwjUypVIBAoE5JcuUgFBCjW1Ml52+Drp6h7Tz90ud8B3YBC5/nlp4lEdbGGZ73g/6AACaMBSIwEB+CGEccwLHx2jl3XZ2Xvv+glO/n9adXg+afL5bpjZtUOeXLqAdjecJaQ5YaIvuSdCwOjHhAuwsfaJdaaCSIDG7VsYD053XgAXNTiWFgBXyzAvBYAI23VB4GC0ZhNC4CH2IqD4jf8wPgZIlV6NVMm4RO1fjWZtVgmUDqY0tIxs4v7U+yuPypnzdpEkK32/dIGxOc48K7NeSM+N32izpMg+KpMLnKXFwnG3KuiRe/3AststHw7dig2oLLDoJq3tcq8B0u7hUczVPXBYzvb/3njavHcOswnvNpPwbFiPchB+5+YuN/qPqGHZyQP992/r9mMytFWpJafcIuTX9kJDY7qGUSv8XsNK3eEzkC31qpTzwGzpukEaT6v3QeQCXXDTjKVqHIylImkwwjxSGXwpnTNKx4gawNFZ3mV825In8W+B+DpFEQ0zb/+8AbTOrmrCJhuQA==
*/