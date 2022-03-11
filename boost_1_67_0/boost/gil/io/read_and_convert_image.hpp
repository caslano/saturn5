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