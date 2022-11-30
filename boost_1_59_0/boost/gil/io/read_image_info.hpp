//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_READ_IMAGE_INFO_HPP
#define BOOST_GIL_IO_READ_IMAGE_INFO_HPP

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/path_spec.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// \ingroup IO

/// \brief Returns the image format backend. Backend is format specific.
/// \param file      It's a device. Must satisfy is_adaptable_input_device metafunction.
/// \param settings  Specifies read settings depending on the image format.
/// \return image_read_info object dependent on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename FormatTag>
inline
auto read_image_info(Device& file, image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader_backend<Device, FormatTag>::type
{
    return make_reader_backend(file, settings);
}

/// \brief Returns the image format backend. Backend is format specific.
/// \param file It's a device. Must satisfy is_adaptable_input_device metafunction.
/// \param tag  Defines the image format. Must satisfy is_format_tag metafunction.
/// \return image_read_info object dependent on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename FormatTag>
inline
auto read_image_info(Device& file, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader_backend<Device, FormatTag>::type
{
    return read_image_info(file, image_read_settings<FormatTag>());
}

/// \brief Returns the image format backend. Backend is format specific.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param settings  Specifies read settings depending on the image format.
/// \return image_read_info object dependent on the image format.
/// \throw std::ios_base::failure
template <typename String, typename FormatTag>
inline
auto read_image_info(
    String const& file_name, image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader_backend<String, FormatTag>::type
{
    return make_reader_backend(file_name, settings);
}

/// \brief Returns the image format backend. Backend is format specific.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \return image_read_info object dependent on the image format.
/// \throw std::ios_base::failure
template <typename String, typename FormatTag>
inline
auto read_image_info(String const& file_name, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader_backend<String, FormatTag>::type
{
    return read_image_info(file_name, image_read_settings<FormatTag>());
}

}} // namespace boost::gil

#endif

/* read_image_info.hpp
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
*/