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