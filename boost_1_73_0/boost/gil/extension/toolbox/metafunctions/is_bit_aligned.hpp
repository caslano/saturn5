//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_BIT_ALIGNED_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_BIT_ALIGNED_TYPE_HPP

#include <boost/gil/bit_aligned_pixel_reference.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_bit_aligned metafunctions
/// \brief Determines whether the given type is bit_aligned.

template< typename PixelRef >
struct is_bit_aligned : std::false_type {};

template <typename B, typename C, typename L, bool M>
struct is_bit_aligned<bit_aligned_pixel_reference<B, C, L, M>> : std::true_type {};

template <typename B, typename C, typename L, bool M>
struct is_bit_aligned<bit_aligned_pixel_reference<B, C, L, M> const> : std::true_type {};

template <typename B, typename C, typename L>
struct is_bit_aligned<packed_pixel<B, C, L>> : std::true_type {};

template <typename B, typename C, typename L>
struct is_bit_aligned<packed_pixel<B, C, L> const> : std::true_type {};

}} // namespace boost::gil

#endif

/* is_bit_aligned.hpp
aLfuYl8M+dUg9dV6HDp34upf+Xc5mt/F7POgfkF3gXwDR4QVdQ1EO8F3/6ZSOtYxNvJb8iiStit++2fy2nGQHeP40/hjHDt2sdOvNHbJZs7yvdl0y/f6T+PDSizoOL5lf7fuY6dVu0brF7YafobbdCumtO9HtunI2D1M4fH7o52/U1znpXnELkNfP5BSjyiSJqBN9rUBlq3fwq5Ly22IifksmhXvDTHxnk03sZ71/odND47z
*/