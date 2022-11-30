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
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
*/