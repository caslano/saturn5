//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_READ_VIEW_HPP
#define BOOST_GIL_IO_READ_VIEW_HPP

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/path_spec.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \ingroup IO

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param reader    An image reader.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Reader, typename View>
inline
void read_view(Reader reader, View const& view,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_reader<Reader>,
            typename is_format_tag<typename Reader::format_tag_t>::type,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                typename Reader::format_tag_t
            >::type
        >::value
    >::type* /*dummy*/ = nullptr)
{
    reader.check_image_size(view.dimensions());
    reader.init_view(view, reader._settings);
    reader.apply(view);
}

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param file      It's a device. Must satisfy is_input_device metafunction.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename View, typename FormatTag>
inline
void read_view(
    Device& file,
    View const& view,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            typename is_format_tag<FormatTag>::type,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<Device, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file, settings, detail::read_and_no_convert());
    read_view(reader, view);
}

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param file It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param view The image view in which the data is read into.
/// \param tag  Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename View, typename FormatTag>
inline
void read_view(Device& file, View const& view, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename is_format_tag<FormatTag>::type,
            detail::is_read_device<FormatTag, Device>,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value>::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<Device, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file, tag, detail::read_and_no_convert());
    read_view(reader, view);
}

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename String, typename View, typename FormatTag>
inline
void read_view(
    String const& file_name,
    View const& view,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_supported_path_spec<String>::type,
            typename is_format_tag<FormatTag>::type,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<String, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file_name, settings, detail::read_and_no_convert());
    read_view(reader, view);
}

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param view      The image view in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename View, typename FormatTag>
inline
void read_view(String const& file_name, View const& view, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_supported_path_spec<String>::type,
            typename is_format_tag<FormatTag>::type,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<String, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file_name, tag, detail::read_and_no_convert());
    read_view(reader, view);
}

}}  // namespace boost::gil

#endif

/* read_view.hpp
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
*/