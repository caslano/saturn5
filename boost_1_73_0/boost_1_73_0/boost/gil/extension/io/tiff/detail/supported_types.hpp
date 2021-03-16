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
umpNnqsSd0bBnWH5kHR7HOVgYmAqaEhmksLX+WIJudErO9BgwPGzch+DpNJj8tKS6LlKKscleR1X5QOc4YT7oRqjA7pANBoMdWBzoX59p8kLbuLxuq2OGgCGrFx8uTHQTDdrZAfQZuN3EwygLI7AvAKycM5iaHo3h0Y6XUA46N0khqHp0jCU/n2k+MSBInH0SX5CiA7JLieGIAdHIbCJk2C5UTFLXomMeaWNBtFKVpcFzyxV+i6G22tA9NXWGpA=
*/