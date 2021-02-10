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
rW885OyNcke2WePimwisBYVNC414tFhMQC7fB61eTdOFjhYsRhZ4ZoSqQVzGdz1e15EbIexRsOl2LYwGS525Kk6+q4eraudvHU7JaaBrmhpgEjGCzZR70v3X402OII+AD7m19FNNt71Fndv1Z9jUVTdJF1UceTFmUnrzjlD1qnLl9aAeo1C5ptjQi44LDdYNLN+hmhb9160lHtddqBdcrvZ7ltpaK1fqqwtXuV0ZrOsurOU6b2VIXouMgXYo2jzLd+Nyp/u6IeWMmZrKFFc0CKsuW2k7d8pK56Ge8fGasUrHrXjPTDDZO4drN+H07q+oLUMPCp7L7cvS4zAiO6V3c7kgVcuXwYphuol7yBQ2k6ZcOyhf4cQQRmUCE6koZqFm1P2EbEctvZdKF+rF66h0vP8BUEsDBAoAAAAIAC1nSlJ/q6WFyQYAADsRAAAdAAkAY3VybC1tYXN0ZXIvbGliL3ZhdXRoL3ZhdXRoLmNVVAUAAbZIJGC1V2tz00YU/e5fcQlDa1MTB0pngFAaTx6QaXAysd2UaTqatbSOtshaze7KxkP47z13V3IUkwedocpD1urec98P9x5/v6tFj+neK/J/ES7cPceJ0f/I2N1MHUWXFH7AdY77fUJ6dMVyGXXofpZLanuWqJLymj9H
*/