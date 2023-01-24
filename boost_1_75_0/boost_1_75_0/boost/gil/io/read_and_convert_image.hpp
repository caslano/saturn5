//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_READ_AND_CONVERT_IMAGE_HPP
#define BOOST_GIL_IO_READ_AND_CONVERT_IMAGE_HPP

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/path_spec.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// \ingroup IO

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param reader    An image reader.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename Reader, typename Image>
inline
void read_and_convert_image(Reader& reader, Image& img,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_reader<Reader>,
            is_format_tag<typename Reader::format_tag_t>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    reader.init_image(img, reader._settings);
    reader.apply(view(img));
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param device    Must satisfy is_input_device metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_image(
    Device& device,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    ColorConverter const& cc,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<ColorConverter>;
    using reader_t = typename get_reader<Device, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(device, settings, read_and_convert_t{cc});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_image(
    String const& file_name,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    ColorConverter const& cc,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<ColorConverter>;
    using reader_t = typename get_reader<String, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(file_name, settings, read_and_convert_t{cc});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param cc        Color converter function object.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_image(
    String const& file_name,
    Image& img,
    ColorConverter const& cc,
    FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<ColorConverter>;
    using reader_t = typename get_reader<String, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(file_name, tag, read_and_convert_t{cc});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param device Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param img    The image in which the data is read into.
/// \param cc     Color converter function object.
/// \param tag    Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_image(
    Device& device,
    Image& img,
    ColorConverter const& cc,
    FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<ColorConverter>;
    using reader_t = typename get_reader<Device, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(device, tag, read_and_convert_t{cc});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename FormatTag>
inline void read_and_convert_image(
    String const& file_name,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<default_color_converter>;
    using reader_t = typename get_reader<String, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(file_name, settings, read_and_convert_t{});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param device    It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename FormatTag>
inline void read_and_convert_image(
    Device& device,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<default_color_converter>;
    using reader_t = typename get_reader<Device, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(device, settings, read_and_convert_t{});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename FormatTag>
inline
void read_and_convert_image(
    String const& file_name,
    Image& img,
    FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<default_color_converter>;
    using reader_t = typename get_reader<String, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(file_name, tag, read_and_convert_t{});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename FormatTag>
inline void read_and_convert_image(
    Device& device,
    Image& img,
    FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<default_color_converter>;
    using reader_t = typename get_reader<Device, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(device, tag, read_and_convert_t{});
    read_and_convert_image(reader, img);
}

}} // namespace boost::gil

#endif

/* read_and_convert_image.hpp
XiyhDwHOKMWMOxDljoVH0vRvJCIUf95a86rElBd0f7Z2OF2MRR+0SxQYHNxbbCG1CoJZ9iO6fUhh4FKH5NgnNrrf+E3tHRmnnp7sKhV0uw5RrgpnRRzNZsg0VtWpanOJ9qczaOBOosgF7dI2A0xyJ4ddHo5AbvkMWR0ceF6IVdQO0GfhDzw1Fy+m4YxtOzWbhSdu5hTHycFVgWEyNyi5aWSyfhPwHrVAX4SslT2sFbEfVB9D8XQfgLeNWbctZos989JWesJDIYi8zD6xN9ItL5/Cv5pX+rjhNxSFd88VqV7NLRs7eJ3bfQ8ldwSQw+yIYPgc7RV5HgXes1spP1/exxS3ysQ8O1028oImK3pYnupdkgM2czNrb+5iWssZ/ENvCez8QzCpPvFcHDtoMiYuQ55A2zHJ1kkNqK5bvkGdp+Syu+YDYzmJE0vprvk9GM3b9D+GJesRbc0vNyBjDpOIE5JwiiZHrM7z5no6lfxTzwg3656em36TLAjfmeL04BzasZbFd9lWKH6ogfmbjZCTmU8bYzy+i8myleTzbQiMnb7o/LUVkMd5Jh/odB2paTvnoKn7dI1AtayigCkrIKZm1DHBNOL82Dmmr4vaxbzTa0bp8idd1V8nh6J5dp+cuVRUzU499X/1Bf0BOwx8hTbQ4dcYmx1fUWjGEruF9ml5rfmBai8YPEX9WrhDmUZ5Lbv1Owny3LzORJN+qn73
*/