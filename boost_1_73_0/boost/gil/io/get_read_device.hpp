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
Zb9dulXvSw/UiyJbL4x9vY7aI9JjZSwq3iyFyi5SO8+/Ujp0E+mO2QK9Js/VLt+3+jB3+zD3+TAPZGHqVrW1ZqW/G88bKIWd/aNjiNK99ycL8QeXx0fB3AePRwoP85xOs/fOHuYFjTnXYF7RmMsN5i2NeWg7D/O+xvTbxcN8qDHnGczHGnOBwfxVY+6R5ay6Te5IxxPYfO83OBLd3ZYPNCfvWEbi7wG1LIaZjUTbm+ZnPAqu
*/