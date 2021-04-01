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
PVEEuCjBYGXpXREbNWJA+ZI8qaAmssEwnRsAg+ewiUSGpuuZWBBeNgHgxcXofbRKKf3slCe1laY22JJ+U7cyjHPXKPsDOQk7bzu4y48YwpsM71qUoo7Eaff/ZQr2lMeLbX9NOGazGGh/QJRnbUGbd8iB73gAdhjDkeUcV16gCovJiGHSW9/zBC7VbYOd5IIG5Fq5HXbZQUMAZn60nIz56YecMh6LQZc9eUUS0yfmF1n57A5Ga+TbkIyFrzut8SoXcVloh5YLbXNnoN6KbLpi+fwDrvdLAylLspI6iPNgS2yoXPg/16ky1v/emnvGKBe9myxHUFz1mIh53FP98g1iy0Y6+2WU6ybw4oad/B5TmfHWXTsAu2S2E/1HBNULfxLWLyhG1GDnGa9ijb8cJNLBpDhvB41SRY3IiPyC62b+PudQ9bOPtO2Q975k7gNKISe0HtndrGxWjk0Udypb63qkn2KFvEpqYvVYnNrZenV1vfM9AqRfKOuTqcDyHfjPwixtuUl3iLsUMsugQwaZkqh5IJnwaZxha7/G2YMbXmL2sDTWuZoFhVciD/E8qA==
*/