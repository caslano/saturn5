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
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
*/