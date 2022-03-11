//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_WRITE_VIEW_HPP
#define BOOST_GIL_IO_WRITE_VIEW_HPP

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/get_writer.hpp>
#include <boost/gil/io/path_spec.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// \ingroup IO
template<typename Writer, typename View>
inline
void write_view(Writer& writer, View const& view,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_writer<Writer>::type,
            typename is_format_tag<typename Writer::format_tag_t>::type,
            typename is_write_supported
            <
                typename get_pixel_type<View>::type,
                typename Writer::format_tag_t
            >::type
        >::value
    >::type* /* ptr */ = nullptr)
{
    writer.apply(view);
}

/// \ingroup IO
template<typename Device, typename View, typename FormatTag>
inline
void write_view(Device& device, View const& view, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_write_device<FormatTag, Device>::type,
            typename is_format_tag<FormatTag>::type,
            typename is_write_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /* ptr */ = nullptr)
{
    using writer_t = typename get_writer<Device, FormatTag>::type;
    writer_t writer = make_writer(device, tag);
    write_view(writer, view);
}

/// \ingroup IO
template<typename String, typename View, typename FormatTag>
inline
void write_view(String const& file_name, View const& view, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_supported_path_spec<String>::type,
            typename is_format_tag<FormatTag>::type,
            typename is_write_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /* ptr */ = nullptr)
{
    using writer_t = typename get_writer<String, FormatTag>::type;
    writer_t writer = make_writer(file_name, tag);
    write_view(writer, view);
}

/// \ingroup IO
template<typename Device, typename View, typename FormatTag, typename Log>
inline
void write_view(
    Device& device, View const& view, image_write_info<FormatTag, Log> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_write_device<FormatTag, Device>::type,
            typename is_format_tag<FormatTag>::type,
            typename is_write_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /* ptr */ = nullptr)
{
    using writer_t = typename get_writer<Device, FormatTag>::type;
    writer_t writer = make_writer(device, info);
    write_view(writer, view);
}

/// \ingroup IO
template<typename String, typename View, typename FormatTag, typename Log>
inline
void write_view(
    String const& file_name, View const& view, image_write_info<FormatTag, Log> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_supported_path_spec<String>::type,
            typename is_format_tag<FormatTag>::type,
            typename is_write_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /* ptr */ = nullptr)
{
    using writer_t = typename get_writer<String, FormatTag>::type;
    writer_t writer = make_writer(file_name, info);
    write_view(writer, view);
}

////////////////////////////////////// dynamic_image

// without image_write_info
template <typename Writer, typename Views>
inline
void write_view(Writer& writer, any_image_view<Views> const& view,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_dynamic_image_writer<Writer>::type,
            typename is_format_tag<typename Writer::format_tag_t>::type
        >::value
    >::type * /* ptr */ = nullptr)
{
    writer.apply(view);
}

// without image_write_info
template <typename Device, typename Views, typename FormatTag>
inline
void write_view(
    Device& device, any_image_view<Views> const& views, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_write_device<FormatTag, Device>::type,
            typename is_format_tag<FormatTag>::type
        >::value
    >::type * /* ptr */ = 0)
{
    using writer_t = typename get_dynamic_image_writer<Device, FormatTag>::type;
    writer_t writer = make_dynamic_image_writer(device, tag);
    write_view(writer, views);
}

template <typename String, typename Views, typename FormatTag>
inline
void write_view(
    String const& file_name, any_image_view<Views> const& views, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_supported_path_spec<String>::type,
            typename is_format_tag<FormatTag>::type
        >::value
    >::type * /* ptr */ = nullptr)
{
    using writer_t = typename get_dynamic_image_writer<String, FormatTag>::type;
    writer_t writer = make_dynamic_image_writer(file_name, tag);
    write_view(writer, views);
}

// with image_write_info
/// \ingroup IO
template <typename Device, typename Views, typename FormatTag, typename Log>
inline
void write_view(
    Device& device, any_image_view<Views> const& views, image_write_info<FormatTag, Log> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_write_device<FormatTag, Device>::type,
            typename is_format_tag<FormatTag>::type
        >::value
    >::type * /* ptr */ = 0)
{
    using writer_t = typename get_dynamic_image_writer<Device, FormatTag>::type;
    writer_t writer = make_dynamic_image_writer(device, info);
    write_view(writer, views);
}

template <typename String, typename Views, typename FormatTag, typename Log>
inline
void write_view(
    String const& file_name, any_image_view<Views> const& views, image_write_info<FormatTag, Log> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_supported_path_spec<String>::type,
            typename is_format_tag<FormatTag>::type
        >::value
    >::type * /* ptr */ = nullptr)
{
    using writer_t = typename get_dynamic_image_writer<String, FormatTag>::type;
    writer_t writer = make_dynamic_image_writer(file_name, info);
    write_view(writer, views);
}

}} // namespace boost::gil

#endif

/* write_view.hpp
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
*/