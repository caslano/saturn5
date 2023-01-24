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
9ifFDLwK3tFnKPFRI0cxyk0Lybgk4PmSgti6XbgfuppeqG+riz4EYueai0d837Nby+Bvg7WWvRludFHsM+OFqr03FHNh48VyZB5L2LDbv3GbfQ87z2/3kF2H05soZW+PihRswszpjdrqSB4WC+zQSzzPPEtXdHixl0Vqni0m+VU+goG3Z1fBP28RbOaT1TAfAquwClUT3Ewwmee5P7iUYlJ+E2LyydR3hVsHTaKoENd431FM0pxejDE3JonNOussr23crXJxKaUghjpDpMRYA6PoH1y52QJ2ToU+dhD9Cu6v/NRGPccTmR9uTy093x02JyI2K8Homo+/yrLRGN03QPtH+beMum0DuErtiLWNCOGBWdDBdG7bPYdrB35Fq7+jEvsd7dIp9sN7RjAuKYk7RWzd5eMwj+6Wy5/id4Ya3gKTckWQ0pv8bbsX2OOBzFRETaRdlmGig/C66rYEo7obwaiRWdaBzo5gD4/Tg8wPq1m12bOPGY+2Rbie3dIi+fbSE1pokqhTvyyVcb3FypCbUn81c/5LQ4LiI/PvNBszd6ZpmshAVt8FbCS1yROHLVE5zzuR/Fg7CY40iA96aztrQ28vmK5qDqKphVPYTq7QlXSR8S84Pns1pAMbN7em8SWPBCblLDCXBqisnTTeJgkZ6bzuVGD8ld0a5eJT8PyR65cxY+awj343mpZua01VZKLoIenAyex2NLboD7wT
*/