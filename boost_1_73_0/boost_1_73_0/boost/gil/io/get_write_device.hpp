//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_GET_WRITE_DEVICE_HPP
#define BOOST_GIL_IO_GET_WRITE_DEVICE_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/path_spec.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename T, typename FormatTag, class Enable = void>
struct get_write_device {};

template <typename Device, typename FormatTag>
struct get_write_device
<
    Device,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_output_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using type =
        typename detail::is_adaptable_output_device<FormatTag, Device>::device_type;
};

template <typename String, typename FormatTag>
struct get_write_device
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

}} // namespace boost::gil

#endif

/* get_write_device.hpp
jFti3A7jdhrn6/dF4nGm1vV7GWkruJC0+6p/Ur+8z2M2Fw7NSMTPZ9IQ91VQfLyrTT8+V78TqS+u4wdreY2hA0u0TmeVaf1yvVZRu3+oVx8Hu/7VDIuDm2Ln8fskv1jtTzqGNcCVN+pMvmA9nHTM6ghXb8cAOQ9i4Gg68WgeRXOJZ6tQdKE7zvn5WlpfLGl9KTfWuGnGNRm3yLglxr1r3AfG+friPk9SH4eRzoLidvdg6/qas6B5frzC5iQqZ1g=
*/