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
n204OVA7NoUbqbj6Q3zmu/EA+yWKBvcOKo82zKO1zDePgnveeks7HxtC5+kHyW3bsZWdxuNX2LcHZdMT8ZZ4Ohc+QkbRPjmdHahlYwdYb2jLpUqLNh6aLMq9XC1q3uc3NwV4a0fyIL8+5G60YeIApaXPr035RsI7g9EBk1kl92i7QnOnMgGx/xRozAq8StTJOEm39pjbNDUnotet/RneWzjqKRzqtb7y6ZsOoWavzJcOUKvM
*/