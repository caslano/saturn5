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
jDTN4Mbu8Q+sH62mK2PNUj08jniEagVehWbLfP1PoFq8SRQ++fCs9BSLrmLddI/1v2o1LG5nw6+v9hXcx4TeZZSqD0VU/7XSs6eF/wNlaAKDhuffZ/LYrzYexWPwyOVR58AK4hqmSKvu03a2ALYn1AC9NVF2RVvNeV2PX2RBHqUpdLTCwUdZViWH+pesE0NK4+JwOmWokU5G58TWqgaM9LpBbVQwKWxGyil12RFkt07va7f9cd/ga4dRuSuLkl7wcYvm4b9T5Ip7diEFY+aoggejg6HT6rLxPer7E/epVSe6+lMalYB8DjEdhLlHQab0sQk155lraq0aZTf5BgNFczKti+xmd5FWOXyDo4NC6SuCc9kOhW7WZSSdZ14blpi8lYd7QuYmj/+SeUo2PsOSd2dlAXwaEL+7z/eR88sBrk/LTzL+e7i0wY6TWhGpVpZMcIO+hNJXsAah8RJuYg2fmnj/lWpARtsJ3aRL+AHGSwUCbvpqcJjGSJTeVXxXXzje39Y9NN8IuXOKuDIJlHmI8vi+VpUtlS73ayssx/+ifSbvtJBwDdPSJxdjtw==
*/