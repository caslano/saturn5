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
rAeZTX4+JwEdg30QAJa9AJfA5qw65WE6Xt9LNnSkQ9rU0Xor0PhH9VagF/+utwWdfIS/W8zybzkG88mawv2QFE/hapK7MdDocn4JPoz1vBOssjNnc14j8eR9hc8AoRBz1rcyTmixB2V4+m8Y/E9Q1568zIHkT9qEIrtePxe2PJ+W/SADivR9yKof8dOJTz/P1zjpsbWh+9OYEhwjbFeSHef+tLcTn2vlU+sFfo1Aq2SxkzblbwcdeIP3et5Iw3HTVytipiBh1xdcLimV0Z7JgfqSiSxlGe9hSoIgpRvFno4dshp5ppaJBzF4sS3CYCilY2L2YWzSeNwrSpuLOUZ6rNl/Ism1k5QcgFfzZ5k1FVmguwHibwf59UEAC50owcfjwFvzMKrtlWJkN/cUTnOo//JTTvEX/MEova8uJXhXORvPOoS50Pg4p+uKME+hoRE2WBFyAORVnMHmwE/HXSDXyx7HLqllDcBw20HrTAxTmcJAcJH5Xs35324h+adIB6Hm/gd1/wNQ822kGdyM5py7Ocxo0Q8LnRizNc99aMxXENN8R6N1ZLRHGe15RKtSZfPcayyQkj0bodiZkpaQXYc3XNF+I0ep9QZEM3clmwVpWZrVEgMwwicDTr83u1y8dqgN5xHM+oYHxc4x0ZFVB2SnLNcYR1oE45EJkFoDKThY5G5v0AkYbFtmTHDJ0wjPwvEuxxI8n+KZjeefeM7i+QrPd3hW49mH5zCeqvchZNn3cc6aZN1+ddwLX6j527Pr5W6U+xk6Rm6698i1P4m8r88b65lSlp79mPncSAdr0jey/9cz1viWwebkkfyMndIpPbuNz0hpyov1221wf1q/O5wqOyH8NeHmFlw4kr/dnfecQ+OG10ncroibvCvnIykAcqxUCrOFZnjwwvzcdn5ZLf5HfllXVcrrmwckr08ukpe8QmwJVkj+9vFP9FZy3TdRL2E1dnMaO0ypAxZKok89oPYPO0W69p5Eg2Y6ZT7D29T0IFDvFwHUTXtLhHP+D+xUAzVEOAoHV/m5Z2vk/IiLzTR73GSG/CfpHRgHciR75j3K5gwLkCAFcGoBRu8U59gTkQHtOfhjFWLlCBZC8++l+d9m5f/aiGr5J0Ro0LbqBarI3v1sAOVh9nrnqCVN3bV8UjRjN/sqBCZCtli64SOkVfiMWA/51cGH+YLMv4rlTjjzBWn//RI8S9L52Q8Cb5QA6RNFIuxxqpSKi17xlnKRC15Tevet1NdGo1zvPmmVK6btDlfkjrfMaFIrr/WuaCXKm61LaGhsnPbzAjcfb5M7rgQ2gtIxpRbc7qRZFojLy0LxJ8PMgIcUkmOF7PuVeaeGaXLm5gl8x/R7u2R0wt1FAGRdyfa/QwQj7iQV1jbR7T7sXV09HCnqUXR03X5IMEPoMZiXkZnbx9m3/zVGIjM1kVIuHR65H/1vLa+BaOmBNGB9r4VKHk49JBk7J7VKl+umfkcEuTtLZDLOi2R0GWgREvESNgMU0TsQQk/QMO9Lkq7iMpbB68wwyHjR+1RGt95dWCr++RBTCb16u0XotOboLGnPtxrzpG1hX8C/z2Mcw8/3gYnz04zTqSR1mvEzf1PTjGBqwD8tzTgWmJjrMXYD7Xc8xXiW41mIZzWebXjmmn3QOyD9meadseUQFapnOtYuSHHSvm0ShzbucQe882AmNyW+ANMr18bwz2EsbmBcM6/8vIxT1pnP4g1iGfrMzMMb0psb+jB3Ym44+45A39zQG+YjCl0YmmcO19fVoQJzgMTaH8o1e8mbGRzL4YwHHzqc6bnrHHH3BYeKAh8yk/6V/5ImtwWkARfMG+5Dd9NbPRObcD9tvhGFi7QwHkhN2hPqbsY=
*/