//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_GET_READ_DEVICE_HPP
#define BOOST_GIL_IO_GET_READ_DEVICE_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/path_spec.hpp>

#include <type_traits>

namespace boost { namespace gil {

template< typename T
        , typename FormatTag
        , class Enable = void
        >
struct get_read_device
{};

template <typename Device, typename FormatTag>
struct get_read_device
<
    Device,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using type = typename detail::is_adaptable_input_device
        <
            FormatTag,
            Device
        >::device_type;
};

template <typename String, typename FormatTag>
struct get_read_device
<
    String,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using type = detail::file_stream_device<FormatTag>;
};

} // namespace gil
} // namespace boost

#endif

/* get_read_device.hpp
o6iH205vCRkmHL9PZ2l+tce1BeWDaIX9MrWgnc46RICHcqTk+B0scFYYexWNLWlHjLJAG+t7jl5BUPgLEj9FZqNgr6k88vn7vOxj/RpG7c6LzjQLZQrW6bhT96vn9d4VBz6jXL+6iXf4M+gTPOSb+FtIG0DB5VYRZaon2XYJ2p0hrqHwKgB6WHEcT9olSWwB7bEJF5crFAKW0ijuxrH3mG+oN4GbCXQNy0DI9btWF23sQ54WwOB6pJZ/1Y8xD6dOfIq6WueXMRPRe2Q/93MshnWMHgbayy+WCC6iUmzEUHI99amz9YCHY8QC7GvV7IH1WH/g9GmzQD3AwyJl8NIXSScckduOEAF+fFHTULeqE324Kknt0qSyHmGndF4MnrYQORXYp3aLRJ+MEQDlyFB3VpzOLNq0MrfHo+8juNqgwyH8Rp5RRExgA/vPeOjHc4VXa23ZFcumaasolwWzi1XhM2sgX3lOtU87WF/9RZISuUO7WZKGOu1pk/4PKlMLjjlWRi7PwmUu7kVty6d80uDWHWfZuvEwM4Cn01Nmy8A0CuYYUcqG/GJ+UlZyNw==
*/