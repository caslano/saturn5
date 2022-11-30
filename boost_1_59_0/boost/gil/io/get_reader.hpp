//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_GET_READER_HPP
#define BOOST_GIL_IO_GET_READER_HPP

#include <boost/gil/io/get_read_device.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \brief Helper metafunction to generate image reader type.
template
<
    typename T,
    typename FormatTag,
    typename ConversionPolicy,
    class Enable = void
>
struct get_reader {};

template <typename String, typename FormatTag, typename ConversionPolicy>
struct get_reader
<
    String,
    FormatTag,
    ConversionPolicy,
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
    using device_t = typename get_read_device<String, FormatTag>::type;
    using type = reader<device_t, FormatTag, ConversionPolicy>;
};

template <typename Device, typename FormatTag, typename ConversionPolicy>
struct get_reader
<
    Device,
    FormatTag,
    ConversionPolicy,
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
    using device_t = typename get_read_device<Device, FormatTag>::type;
    using type = reader<device_t, FormatTag, ConversionPolicy>;
};

/// \brief Helper metafunction to generate dynamic image reader type.
template <typename T, typename FormatTag, class Enable = void>
struct get_dynamic_image_reader
{
};

template <typename String, typename FormatTag>
struct get_dynamic_image_reader
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
    using device_t = typename get_read_device<String, FormatTag>::type;
    using type = dynamic_image_reader<device_t, FormatTag>;
};

template <typename Device, typename FormatTag>
struct get_dynamic_image_reader
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
    using device_t = typename get_read_device<Device, FormatTag>::type;
    using type = dynamic_image_reader<device_t, FormatTag>;
};

/// \brief Helper metafunction to generate image backend type.
template <typename T, typename FormatTag, class Enable = void>
struct get_reader_backend
{
};

template <typename String, typename FormatTag>
struct get_reader_backend
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
    using device_t = typename get_read_device<String, FormatTag>::type;
    using type = reader_backend<device_t, FormatTag>;
};

template <typename Device, typename FormatTag>
struct get_reader_backend
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
    using device_t = typename get_read_device<Device, FormatTag>::type;
    using type = reader_backend<device_t, FormatTag>;
};

/// \brief Helper metafunction to generate image scanline_reader type.
template <typename T, typename FormatTag>
struct get_scanline_reader
{
    using device_t = typename get_read_device<T, FormatTag>::type;
    using type = scanline_reader<device_t, FormatTag>;
};

} // namespace gil
} // namespace boost

#endif

/* get_reader.hpp
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
*/