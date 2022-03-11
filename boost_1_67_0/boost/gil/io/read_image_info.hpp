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