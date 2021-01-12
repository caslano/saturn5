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
4+/QoepWkXOFxOSBuQfM/SM9zBAwP4EpFh5mGJjiYezGNJgtNabFYCbocjqqPMyuYA4nzVqOh5km04AZ7uaq1LIonVQbbWI3SC077tvn1Y6tTcmWI5M0m2MQRXuav7sGv6NNyai2hf9T86GwytpO2DamkPZN7b48VZpXamls/uixtXXx1tqFYwprF04oqi2pGFU2t4xydl8Vvty+aq6Nj6Ekgqr6ZnXWprHrssplACCvMmRu
*/