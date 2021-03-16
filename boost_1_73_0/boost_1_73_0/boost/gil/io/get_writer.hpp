//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_GET_WRITER_HPP
#define BOOST_GIL_IO_GET_WRITER_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_write_device.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \brief Helper metafunction to generate writer type.
template <typename T, typename FormatTag, class Enable = void>
struct get_writer {};


template <typename String, typename FormatTag>
struct get_writer
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
    using device_t = typename get_write_device<String, FormatTag>::type;
    using type = writer<device_t, FormatTag>;
};

template <typename Device, typename FormatTag>
struct get_writer
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
    using device_t = typename get_write_device<Device, FormatTag>::type;
    using type = writer<device_t, FormatTag>;
};

/// \brief Helper metafunction to generate dynamic image writer type.
template <typename T, typename FormatTag, class Enable = void>
struct get_dynamic_image_writer {};

template <typename String, typename FormatTag>
struct get_dynamic_image_writer
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
    using device_t = typename get_write_device<String, FormatTag>::type;
    using type = dynamic_image_writer<device_t, FormatTag>;
};

template <typename Device, typename FormatTag>
struct get_dynamic_image_writer
<
    Device,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_write_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using device_t = typename get_write_device<Device, FormatTag>::type;
    using type = dynamic_image_writer<device_t, FormatTag>;
};

}} // namespace boost::gil

#endif

/* get_writer.hpp
QV9QZytl6WwnZej5tK+3F9O+3iBIf5kHf9r0l4m7BkTLSbs4+if9Zf4JMOX6y5MtvirVc9AfCxJ96FJqEz3lvsWbgA7peIl8/UAH95mmlGs/h/tG3I/qUfJt/ZzWEdXk3BdwV8bO4/dif8rvdrHjjsND87OPcLHyCcC9ScaVoh4kfU2xL6Ocv613/vZE0nipATiGZJwy4hjpJCBblx+TfkGHGC1aSjKdJ1rursvX43uovWJJ7ZVyY42bZlyTcYs=
*/