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
zQprg+CgtFtUEgHrvvS1X5Tau6YmTB2I6N5IaDoo6OoJ4gjoyHmxucMz4jzUjeq5tfXV8DmL4vMx5+ooesO5CcCzC7nKHtHaeTYGlKy0+fZ9fAmFOgFkwcwa1J69X1648ihEuKccAUKx5ElWfshpwhfFsdTgRsy/SniQlgLK4AL+9yzNAaUO16ctMHLDoXDW2MP5L7fAwWpotDiLL/JwTZjw6m9qkjyiQykn1KuT5McsPSuL71vdA+a6AKbFM8ba9obtgkYcBXBYItgD8zQraGDysyWep2I/YOsj9eUjSPA0k7A9xNS4YZl+CfdroM+PZkNgzYmfiyrA4zLmB3Jfsd+lgEfbCd9TrDgV0LQU5jdCL5fVB1+0Q3Zasutq9F3PCR8DIGlRUPBL6iV2lqucExlypPFUXJpJ6NLWGhwLpgn0FPE6rqTH5XOk6CnmXToqXDC58kq1xZNMLwkSKY9SgrTHjPBjawPqA0pRRWwBJt0KVapZVh6U0/d9sFNu+8LxZhOfsiHWovBMAB2Y0hZ6yg/AvIAuS+RP5MJ/MVHbUPfehqaNz0uzWVcBHg==
*/