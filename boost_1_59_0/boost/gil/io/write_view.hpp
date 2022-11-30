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
template <typename Writer, typename ...Views>
inline
void write_view(Writer& writer, any_image_view<Views...> const& view,
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
template <typename Device, typename ...Views, typename FormatTag>
inline
void write_view(
    Device& device, any_image_view<Views...> const& views, FormatTag const& tag,
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

template <typename String, typename ...Views, typename FormatTag>
inline
void write_view(
    String const& file_name, any_image_view<Views...> const& views, FormatTag const& tag,
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
template <typename Device, typename ...Views, typename FormatTag, typename Log>
inline
void write_view(
    Device& device, any_image_view<Views...> const& views, image_write_info<FormatTag, Log> const& info,
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

template <typename String, typename ...Views, typename FormatTag, typename Log>
inline
void write_view(
    String const& file_name, any_image_view<Views...> const& views, image_write_info<FormatTag, Log> const& info,
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