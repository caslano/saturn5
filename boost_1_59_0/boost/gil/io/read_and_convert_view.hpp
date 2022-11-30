//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_READ_AND_CONVERT_VIEW_HPP
#define BOOST_GIL_IO_READ_AND_CONVERT_VIEW_HPP

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/path_spec.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// \ingroup IO

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param reader    An image reader.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename Reader, typename View>
inline
void read_and_convert_view(Reader& reader, View const& view,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_reader<Reader>,
            is_format_tag<typename Reader::format_tag_t>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    reader.check_image_size(view.dimensions());
    reader.init_view(view, reader._settings);
    reader.apply(view);
}

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param file      It's a device. Must satisfy is_input_device metafunction.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename Device, typename View, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_view(
    Device& device,
    View const& view,
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
    read_and_convert_view(reader, view);
}

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename String, typename View, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_view(
    String const& file_name,
    View const& view,
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
    read_and_convert_view(reader, view);
}

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param view      The image view in which the data is read into.
/// \param cc        Color converter function object.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename View, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_view(
    String const& file_name,
    View const& view,
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
    read_and_convert_view(reader, view);
}

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param file It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param view The image view in which the data is read into.
/// \param cc   Color converter function object.
/// \param tag  Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename View, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_view(
    Device& device,
    View const& view,
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
    read_and_convert_view(reader, view);
}

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename String, typename View, typename FormatTag>
inline
void read_and_convert_view(
    String const& file_name,
    View const& view,
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
    read_and_convert_view(reader, view);
}

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param file      It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename View, typename FormatTag>
inline
void read_and_convert_view(
    Device& device,
    View const& view,
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
    read_and_convert_view(reader, view);
}

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param view      The image view in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename View, typename FormatTag>
inline
void read_and_convert_view(
    String const& file_name,
    View const& view,
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
    read_and_convert_view(reader, view);
}

/// \brief Reads and color-converts an image view. No memory is allocated.
/// \param file It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param view The image view in which the data is read into.
/// \param tag  Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename View, typename FormatTag>
inline
void read_and_convert_view(
    Device& device,
    View const& view,
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
    read_and_convert_view(reader, view);
}

}} // namespace boost::gill

#endif

/* read_and_convert_view.hpp
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
*/