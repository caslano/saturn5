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