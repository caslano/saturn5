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
2DplVq7tfbMChCizoCDmxvevazWTDDVnedB/xtM8JOZKEeN8mIat2XXtY36E+LEEli8+9gXBxb3H1kYvGcLU73R5OVfgEHyATyPtmv0XIpkYv5PFOh+Xy5PA0UJNjdFRNZXhcZVhtUKCZ+b0xbkxrlEFsXbm25El4xFj0wbiNIE9O+TCmk3spftUoctCNR7tyNKIsbGy8tevyl+VX4FkZALAA9unZHMdpRSXDrMxdp7eBhFMpRIhFMGNVz88KRuy7BzYR6jeiMWyemLGj8yYWGpvKe1njR1oJZXYiRnbjah9EfA7XZUpAWxljegScctWK2VOMU5Hzibu59H6TBJzypOmsRz/NZ1y8Eh1/CYLrF7qyWi89HXEjORbqZLm1v3KQbbxx58KBsRZPcaiUkwxG+qQ/+Z5dMZbObzxOe1xsmSNd+/SZ+G3d6rfU1gRk0+0zhrGmE78411FTDNqaBXYPrwLEX96iOsb0uqV1Hs8JifUrV9wtKpGlZWwHb9XUCZHjBfkco1ZCXF4chjfbPkWG5fsjQ5zNyv8D5pnQeLmcbKIvS3sHzAPDr3NN0S+VGXADnaDjgCOn55m9UVCRWibFt4J6nazKXOc8UvR9x7ZtADxH7fZxKiV7kg6Z7sK6j+Iy38hPW1+o+fG5YLYJX4yB5NIHteTOofrpG/YHWJiYvyM04TAdv0EnkEJLcgYCdDcsG35aJRh9t153m+x
*/