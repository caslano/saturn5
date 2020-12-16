//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_GET_WRITE_DEVICE_HPP
#define BOOST_GIL_IO_GET_WRITE_DEVICE_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/path_spec.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename T, typename FormatTag, class Enable = void>
struct get_write_device {};

template <typename Device, typename FormatTag>
struct get_write_device
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
    using type =
        typename detail::is_adaptable_output_device<FormatTag, Device>::device_type;
};

template <typename String, typename FormatTag>
struct get_write_device
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
    using type = detail::file_stream_device<FormatTag>;
};

}} // namespace boost::gil

#endif

/* get_write_device.hpp
xkXiL9GE8YC9PIewZg3V5MW7cyT2BgDILZdkccR4PRilNyaBRYVTqC2yrnsRCUXkFJXPijEpyZclM8/R7n6w+qvNxBvjQS6geXaeEuv+EID2k8QH+VE02e+14eYcLM2B91XU9y01ad2k6xdDz+c1oclMffMlJFRWSq/+I+/Tl83xSREg1CCZcNI407/7Gjgx50igg79++O09jAKLazR+jfFrhV8ifnfj1wU/qz0wm4LEitoUbBdnriuM4AB+ZWySWRpihudcDsQ0jOveva96StRa69+19Tc1d3DMrLkZLK/7K3hPNsrHBCE0myuldCOEO86xvniIo9sus1wX8XcKl8haJ7sO5A5N5O0Q0HCg5yVcYBl1GpeJya5jDInD/Tr88vDjfSx+0fg5GDgcNxH4FeEXhl9VEvviZi5+hfhtw681fon44f/08V1mjn9HzhB7Zzr/dsnOT/kIasPdZMZNpdsN4w/0T7iRoXtYbscF7oFlpUnynAli8QJIWR9rXc8wnvyrNhe9ZBj/ksHzBqKuehJOhtKl1i/QUIK4ich9O5BNUU5RjPPVGPKyHYouMtuhpN8qsN6XDaJhbT3eOuS2M2/PBfJ2GG+PyW0Mb/fKbUvecvU/Z02Ae5VcI9yL5Rrt/lWuYe45cg10ww8dHKieDHNPJeHI7+4PlVDa/ZbehLrHC2uwe3QgXcBlBzD5LA77xz+a7R4cKJoMfieAzGWJlVvMKI68La4+ivLFF5FESiR9DemuZdhdselpcxeyuyEDftQIhe5qfPpSn1q7y/LpfX1KdF9lqXLpU6r7FJ7khCIO33px+D+E+qlkfHPBoTNwdVdObNUm9AsGuFLG4YA2nKl/htwVjZeFO2WcMPcHcydtgEaATv8C9LBjVH7bnPq6R1CGUD7S29WTfLo4STLFXfBGOMqBO4jU+M+91DzjKDjcJ/RouMxHRGg9JgKMfoKfPe8v+NZAS/AT51VwLuX1VbGXgWSJTT2aYi8E3XhskvRBTGu4O59VvQspuSkfidupgl5GCp7FsctXDL1Nn2Ldus1mK0ep07QYt2IpTZnsHs2eNqKIvkxCn39eCuscb2E1LrzF1FHJ55Ux7UgenaTRLwTgdanGlrfUc0xBgrHS5O1WsMH4XclVC24y5uhtdEGN/BT2WGg+cVq73JQ23tPACKP8R+p260v6vnpzCvzdFRk7PsOIynUOHUlSzpFE59jjHFO1eXScc+wKuRsQM0RtP5NyrtbL6oyguVlDSB6e9Tj9NU+i6bFZlsSvxjOyULJxoC6UtDyHwtuS4bnhzsIg2Fm8i6Gex7XXdSHZVeB+s5QkXCErkj4ZzBPrtjLNQu2WnGPO4AZbZPCX7kqghW0YZqEKPNvsqmQGK2hiZ4YXIu4PcGVj5J2lQs92cu1yFafhLU1KCUsHZSl6CywdKJcsz3NjOTuimsxU36yatDNTRicZK5/jaraEZd5vlTan8cpZX2nLfEp25VBzo0FmWSNTeeMRYZKnzE54CTiw/X0kWbcaDyFQ8M26nd/H8DLaHT2KcZ8DIYIn7d9BQHBBL10lOXzGnrUMWmbkSeWS8qqn+wpc7lXFcrpzK7SjRRh3AuF3FvKUjWi0HaDXFpvTumKPGKNvyX1LfQK8jLe4itnaOnKO/j4+l008j3hOKU46vyQiy8m9SInn87PxoX48buF8MudItJAHecm4FcX2QYmBob7x60WBIs9IPyM3y6TqDRcNBBGfVpzvcP/YRFjxsA8hnFcwz2ZgZ55jRDPeumcYcGcYDo4LI8ZrALaDHB04H4b4fh4UJvo8KCzuYC3EtBkAhIcIjLuAJEEMCRalzcXbL78ZIMmlSnHvCkojf3kGUx4=
*/