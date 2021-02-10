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
M28nSUTNI3fOh4k9D9E3dqO7QzSIx6CFlDfxp1vSAOADj10PDTsccfQwmANqJsZTK4zoESf5SKRafrJILxuGM4KOhjh55NnKU8g2X7GdVzvKjGZSl7masGZELwe32LYhM/BNyh1ZVZpL4GjKoyFtrGjUlhfW0fXjFNTqDRc3OpuB2+YuWsOmMa+i1wVZmjZIH7Etw4KiSYtn9mewNnDXw3kafB4CU0vomx/9LeGgaFrFiXvTPrI6Z/0RSJjV7XfOjuD2ZNK/kisGG/gf6I2ZvtRm2ZeaggfVMJkt2YOs1MxG0XwJEgsevr+TgGeT0D2OdmRLCkOOn3Rgu4PB2UBz0VROBSqfvHbGp/btCCEex31cz0MUM7algQc7G2VemZyTsBZU45xcgoZemGL2pgm3jM85tsFt2zo7tk67p2eDS1P+3ipfEmkbnvflKsk0ZGZ9nLrexILWhjJZ5A0CewMfWDEL4OKJzlmLtLomFwbkqMyRf/hQ6mEG4SyiHqJPajJY13kQpp5al1LqTDghqdrMoqaS3ksch642BGKOlnIoUXHJnpKukrPLReHiD82GitXXr79C5clla5G6YWEUhGidQKD9NFTeXP1qM/MGK942Td1X+I97MVf4L+QBAYGOAEqbF3LDq7AJay7l3aGT
*/