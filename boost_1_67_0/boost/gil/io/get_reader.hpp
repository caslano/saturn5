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