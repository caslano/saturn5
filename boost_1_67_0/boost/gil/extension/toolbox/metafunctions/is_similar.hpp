//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP

#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_similar metafunctions
/// \brief Determines if two pixel types are similar.

template<typename A, typename B>
struct is_similar : std::false_type {};

template<typename A>
struct is_similar<A, A> : std::true_type {};

template<typename B,int I, int S, bool M, int I2>
struct is_similar
    <
        packed_channel_reference<B,  I, S, M>,
        packed_channel_reference<B, I2, S, M>
    > : std::true_type {};

}} // namespace boost::gil

#endif

/* is_similar.hpp
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
*/