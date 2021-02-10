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
pzd4vNHyFiFzV2yCRRDTbj+i8nq6dIVjPTpJ6Pl9pSfS1M8jgTMLkifqBG8ICqf5nNKc60Tw3IcK33J8ZDoP6fW5tWXuYCrznOIA67Qh87KgpCWahh49B1dB5aje+XiuBE+yMdWyIiiOvHR1VS/pgmbUEAnySL2Ke2+YlmyZJNzgDe5PXuDO+MqWI34r6bD2yijsHNpc/6jxxbPy8yshYnaQZMJAm+v/XQDcG/8QINdUDG6b7wog5OjbIbxxO7RcBFZ+wthBO1S71fiT8C6rUzXL9mUhnzZqAF8nWjk83d9/2iAxcdPrmgG4M+pBp2oDyFGT9wvb27DBxFu/0KD4+Gs0EciuuaYisX3PRoNNTjM9DTZZY/tFmBx+H2yuRX6KI7i9FCFHLQ4bc4tf64vD276Xp1/yutSfjySU9qpv2v4d7zbs1vjxqJN6ehL3duODVwe9o7M6ky/8EVHRZzW3BQ28T+aiKovTJA6qTT8XYYtUW2eops3gOYK65FWpva+RQawU/HsVWnDxtPHXrUfD7IedDX/87IfD/yz+zSy+vDt+Rhr/b1h0FV8G+NlnVMXbXcWGN3hn9m8Sz+w688xWUs/sS9xzlyd/xGHRVxz+6pdG9D+W36bliBp/A1BLAwQKAAAACAAtZ0pSCnm5
*/