//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/raw/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read support

template< typename Channel
        , typename ColorSpace
        >
struct raw_read_support : read_support_false {};

template<>
struct raw_read_support<uint8_t
                       , gray_t
                       > : read_support_true {};

template<>
struct raw_read_support<uint16_t
                       , gray_t
                       > : read_support_true {};

template<>
struct raw_read_support<uint8_t
                       , rgb_t
                       > : read_support_true {};

template<>
struct raw_read_support<uint16_t
                       , rgb_t
                       > : read_support_true {};

// Write support

struct raw_write_support : write_support_false {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel,raw_tag>
    : std::integral_constant
        <
            bool,
            detail::raw_read_support
            <
                typename channel_type<Pixel>::type,
                typename color_space_type<Pixel>::type
            >::is_supported
        >
{};

template<typename Pixel>
struct is_write_supported<Pixel, raw_tag>
    : std::integral_constant<bool, detail::raw_write_support::is_supported>
{};

}} // namespace boost::gil

#endif

/* supported_types.hpp
4FnMsv+TCR18Cz8FKmyBgPW9ePAGQ0KcWnZbqcAD3iTbEIFawCsKF6cDs6ywpkVN4FJDNXw2dmuetsQR0HgLHgw1agvkbsSmvAPXfu1M5YxLAerq2W3ZMoGlGt6NewN1oRrB1V87gwfxZMFELu4NJPC6uB74RAYUgkdEdWwORB0gsRO9okvEznBbTmhcj/fyO7w3w5Xfg3swhPjpX68LRmT/XJiGgtin85G7kdcGo1BpgkjNTVAPiO7osgF1IwXDyzDBIIRzY3eCKp4jpEV9BlkPdjuZGaGXww7Te5HXzHjA8FwQLHqdQzAzolcaKGVUL660+qtP4H9mlCrC2oAwDtrfJScKMgB4o4CZj8wegnpJkbxCSdigvQVLy6/w3hxH8m59Rusi9vVGne8T20xZL7Yzyly+TUzT1C/pBe7a1QBalfWgTZPzKAjsGezDjmVmzZAw1RPlQ+DseYws4kdIqPrIs8GJIcYbYWNcYntQQsgWNrAJoJokAec/aKfOxGHhdcUN7AB4Y0nC5QN8qky5Zt57fHBXSQ7w3rBPVYDCdYbLkfVe9lNoQpN9DK6LxBMe0b18wXDCauWPf8eM8P3GjGyCJgX8c6a4/tH1WOJZhk883T7sdZeVsCBE98PI5BP2uNqFZ8TME8AUPgVp+JIJJQndhDK+nvcGP1kGr5MJZHDTuV3W0Qa/Pw8O7PFdTtcqoSx5+vshs7VNvd6m
*/