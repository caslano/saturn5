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
RJl4W56h2+N0cJUPg5QpdDgPI1V32hqONxGAdE+/A2IMRYIy1fHkbjgpuzme3PIW44bSvqsvT6vDMDsvKhN0w5CkD35kSEJyrXjlXJjTSPZSdDHFgeIAzgoxYeIsKy63PCo7lpizgAm/9EU85BpjFjJHRmC8iihoJ+ROOSrbDb/4F8V/+le/9NsCOcmF/zxer7raP/SuyGYkxNlnHANJ3tgJOYZM6DGNdNiwGjjtjxlzxAxwHXvjrsLEUt2ry+cZ/m1zpNPpA6mCfeEuiuQsmM4F57C/bvzwapdMof/mlwm+pZgBcCChikSe0UR6VkrkTiZyl1M3C+tAvmWlFMnIwh4XZWMJaUkI5zppEU9Yz5Y6FOTvqmp4v7qDuYp5MLe4ppWyOZiDM5UyA4FXgPGworIiL9M5FBqvud6n50Ixbk1F4/8YMcjFe26V6UuWnh8wvics9Va+AXk9kLnbmQ9ktqkYkdNtAMFfG3bJbKGGvLMYE3yAJZ+bWBdxX0Jc04eIfH8ORE/RHMPF5t5bYAtVlvMcpPGFDtpKfwEodIWS8fbnpaSjdlXULxpxWZ9nQAy6YuLqWvxCCHrPW3UrwC/poHfBydIqK74JFasZ//n8l99aJyoYMJtyNirVKMcvHaf/xt+UVOMP/LIxnOHvANoiIPmAHj7BDzsqQBLNt5KtviyyNAQlzvlE0kvUAt+jpNfslgG82WIPjq5uJMoEGWl2nXI3btM5rRMJOuuZelrnES3wHl6Te7que1qKmDWsMWZMG/0x2+w2TCMGfnNej3wFxY/pHdZnpoyoA69ICYM19X0j38+yyq2ABqZxOdYLkh/8zsnD755CthrtZG+aqqM7OpgIFjus+HaS5s8ldgopSGFF9RSOTtEU5jOFfMb5oCJOBuL8q3qcPfka5yHECfVhVxzqZY4tiZhy57x7Tg/QCW17EOlGOOkNXYv2aC7++bzEvVF9yIUaw2fD5y7QsZR0TF0XiHkNn+ai3Rbh85/FmM28Zi8SH15mPrZf5lKy10bvdinuvFrSbjdx8bcPJIoHZUg83vv6pijvIzt0RfXozajhUqf6vdGgH15xSNAOBr2qluU3zEX26Tukz7pH0S5HCuYS4Bh/mJ50tdWEkCxLsS0NbtJ1ZfYJ1+ly7iUatexbZl7kQ5/3KBIIY10W4clmzmr6v39Dx6HAMe9m8nvNEq8kn4h2/JVXF7iXy2/cBkX+XhM0WzC1deYCr1gslhh7ZZolNEi1hvmp1uAMtyBTtZZVXokuhFUbE3+2o9p1xTFmR3bNYwExZyJ1kDcxK5ags/RtsBfWNRNvpj1ORtJ2Hz0iIMhH66ZUqH7LCufYaT1w0pG25nflfhUO3eE1jsIJSzcsIdjzAabByExEUkg3Gp2slMp7SIUuf9L20atK8omcryVNKvfSDjqAGH+zddCOq+p4N3vepIAUAH4l4FYLkEE+E9DGAoyC93vI755Cdm1u7y5jXeSc4wWnHNkvpixxyTMYzwuYxHyMqcMaPCV4fsRj4mkG+FA8M/Esw1O1P0y4oD/s5RU9BnUTDXUDQ9mkMP5z8zvpSBp/D5rv7bDUg/naTm0tTzmsE6gOP49p1B43XNYpEj6xBgU6GNgb8n3uFMb/Gepuvf0S6mi9nQ3dIG9siq2/kAg/hS5fLS/7Qg0AYdivqcYJ/D+fapw3W0nu2U9jGhKN8d3jZr8enE53fdQRH5+dbo7oHnGZUM4pacxYnqEmPzPp5/Mlkdr410Cj7BsdjkL1LKNtrPY8QH+Fwggmyo5+d5kW8tw6pBvhj7NFfIKzg5iOXaquI055IpnNZmbzGHgEgS4G/mAHZjHwSQSmITQHgNuY1N8BMD+3kWo=
*/