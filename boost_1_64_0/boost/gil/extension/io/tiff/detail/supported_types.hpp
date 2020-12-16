//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/tiff/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost{ namespace gil {

namespace detail {

// Read support

// TIFF virtually supports everything
struct tiff_read_support : read_support_true
{};


// Write support

struct tiff_write_support : write_support_true
{};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, tiff_tag>
    : std::integral_constant<bool, detail::tiff_read_support::is_supported>
{};

template<typename Pixel>
struct is_write_supported<Pixel, tiff_tag>
    : std::integral_constant<bool, detail::tiff_write_support::is_supported>
{};

}} // namespace boost::gil

#endif

/* supported_types.hpp
mNvYtGNoFlzsL56cjVYOZ/NzmTUaevBJc4P8YC03eOGRd+fbyRXhpAEs6VXMx1YsV5PpRoANexTtEAwPydRp5bagTwBwJmFlLC/Jhx+gLeVNL2C8rLkkNwFGauPzsJO74wXfz7uDS6jLap600UBFuRFgvWpKg4y2SgPn1FynTIfZ3jnCjeM+fj8CBY3sjtMwtvFvnqTTz5rCvlFdPU5EGvKIdppbTsWnoDAwQf3uZ55Xbphl3I+klur1s6xpubNgvzuRDwBsSMIME/AzzzAHGaFkHNprDy8dHnFAHCbNZJHdUA6RncRUIlMBUnmIu/vgLVkQcsvl1PLPZxmnN6CM7w6CXpyX0/eAKObIh/nz0DN4nwHlHznj2GbL3+3Z+Hfarjw+qiIJz+SAcMRBDjnkBuUUohHllAQyMEgCQQkGATcKKp6LOCO4cgQCQhyGa0FQUVBXBfFAVIx4EAiQcAiRW0AIitDjCARwIQiS/b6q9yYB1939Z/nRmX7V1dV3d3V1dfU92NTyyKsXMKVSRF8jVEnqRs3Rp0CNMGWUHM37RskikRhIHWsKzgqX2AoZaYaMUP93BDJQSTOzkP7t8MvpYfBGrHWSiRT/VlRejohUPKLtsEFaSu7A+snARJux+LHO148sxnL6DygBFFAJoAcGFas774xUd7z1/pqeV3wCoJZPK/z5QVLhQ/UsYvYZqfBdIGVkIHNuTu6EFdA1pVQH4+vpKkpdA1Rl7sIqvpuHS4VnLdajmBuAEaytWvsfalDxPG2Lygy6hD51Vb1Jlc1HIOuV0nrWguhTmnd+Yy0ZrY311Gh+ChCm3l8tKv/6Gnr8IsTRkZ2FUPINyIy/AAvn+624g8vDiCq0JuZaSAe/uKUEpto48eWeenQiJ06n5va317QgQ08jt/1AGWwBTyYzqOVpveASJ/NBMfPYCAXZJwYR08Yy6BtE4+A26y5o1ocPK4LAZ1T8ptJaD+OMAKiBu3GOXUDOdgmQk8QOMd5YFsPtacVIm9OVdRXeXche5eGfBLn/Lgy+dBcZ1H73SNH1mOe09AKwRQjugjoJAmBgmSwLuotHaoedu4V5HPliR24g8eXJJvcK5WhJCfNBEjA4gqtzqD6IolLvV0pcIklgMeJ0MPOJ3+T5oTq0k2vLu/v7q/66+nE1NJEU6LHAfFUsY9fVFwGltdKocFiaH3qorz/qV5RUC49Sly/yCu4S1To+FFvw05H18CcFf8Wh43BqLubPkrBxSqdJQsJ9sH/rctY14yF0luDXF/T93/sx+gYgMPguADfB8iJd318cjtmwXP0y3D/gVsLlwn0DdwCuGM4JPBdx4YbDPQ7ng5sANw1uDtwSuA/gfoC7DjSvfv9lkJ5a/VTBPrWC6QVudnO4krn9p2mUafQpVtnY2oB7EyREngAfIuBng8m6gRH7n4tkcumdgSK9d1Imly7wCwU5SQglY+8t5oJQzWhSL2qHkpaWMuaaAC1JlVB269arzXmZPdqC9r1CG7sv0KXkT8gMvWpvG4eTSd91wO5qYd940k75G65HgIa6e/R6TcYVab8FRElTTHehfKIZKev5y+fCs2ctLeBDf0GhtpyQAt5L/xw7meBwmWq4Ca1bVlW3kfhC6c+oyM20sQOhDCRkCJS9JsKDLUSx6HKEr5fIjZpzfbLlRR+9osW5B2mW5olsCHZ7xh0pV/cvWii3AiV4QGYgfSBYntsFdymhOQhlpOnCbeaK9YYRVszffkFYGcEBFvhHgOMPdEJ6Ezr7Q3w4qiaaTmK+PVZRcoGCnEa1A6yCFe09wJDV0g2S0wKm0wdzYyfkrHwGZuJZDTvF4y9r1KcQNTTj39+39/+SIzfE46NsEYU=
*/