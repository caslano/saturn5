//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_GET_WRITER_HPP
#define BOOST_GIL_IO_GET_WRITER_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_write_device.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \brief Helper metafunction to generate writer type.
template <typename T, typename FormatTag, class Enable = void>
struct get_writer {};


template <typename String, typename FormatTag>
struct get_writer
<
    String,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using device_t = typename get_write_device<String, FormatTag>::type;
    using type = writer<device_t, FormatTag>;
};

template <typename Device, typename FormatTag>
struct get_writer
<
    Device,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_output_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using device_t = typename get_write_device<Device, FormatTag>::type;
    using type = writer<device_t, FormatTag>;
};

/// \brief Helper metafunction to generate dynamic image writer type.
template <typename T, typename FormatTag, class Enable = void>
struct get_dynamic_image_writer {};

template <typename String, typename FormatTag>
struct get_dynamic_image_writer
<
    String,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using device_t = typename get_write_device<String, FormatTag>::type;
    using type = dynamic_image_writer<device_t, FormatTag>;
};

template <typename Device, typename FormatTag>
struct get_dynamic_image_writer
<
    Device,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_write_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using device_t = typename get_write_device<Device, FormatTag>::type;
    using type = dynamic_image_writer<device_t, FormatTag>;
};

}} // namespace boost::gil

#endif

/* get_writer.hpp
UQy12c/QlJw5M9FnvN0fzwZrRhHctXiMrkk5IcqGCSyTVbpij8MggS4f8iKCHlRYPSpcYiyB/QVXW/E7Gd1nbOK1mkWa2+GwN+BdYL8u5SjYED41zwqloEPemOSG+MthP/BFHorcrksPb/jIX87ynjVM5suNP81Tz2p1WfJ7AqxF6Cs3rHvVAic7Zx1MKbV9Vbp9k8A74Uk3f83cor1Ua2mTVWM/tkkZgd6geXgnH+FYFlKIpsaUZqB9bnhJ36GVOrnX/GNausD7lIX55lehcM7+ICqh289cXy6m9cCR174Gl7AascLgjfSzs+sbIPwz/ohG7hI2oDncd8g3pl0Kd8eQaIiCbf2LTT8csM7LF7KYfiMheT8kl5Ge8LAwoFxyzDrLNu8G/Y3frpA9/r8Sb6VmJDNfZsJiC881DOoytbW+5yG/Ra4voQzdjapP4fBp4XEk2lrEfRWMp8s7WhKHOjWGPjTgq3Plot0DUvvDeJNwhSkvmOJcIRAsiy1C1GiI7X06e5qKOWBrELeUrUWIHcikEW21jxK4jzZpltcNXxggzJJSJ4CVbHCDuw==
*/