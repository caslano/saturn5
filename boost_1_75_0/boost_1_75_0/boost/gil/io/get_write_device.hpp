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
u7iugZZNf++C4QFurgb7Y8tsV13Xrn9fkaGJX6+GrXUJ+W5Me7KsY0/4vVHKgKXrdvkNDL/Al4A2NrsVF/4gL+NuaX6NnzqDpjXv5CL6do465LXqO72WmGQkOO6DSA3ym4SiLUUAq3GW+Y0B/yDdrILiAJIwfCFoCO5+eNAFgtsmuLu7BnfXTZAQXBYLtgRPCB50cfdFgrtDcGdh2T2rq7p7uKer6n6Zh5mqv6amevr/+uqrd4JkOF7knfmAyAeszmHu9zF+Bu0yx1UHiQeXpFXNYeUMQx1eT9GvN7qaCRGhQANOc4kDs5bPOOVjROF6mdMuWdw7z0IZAgUljVcbZbREwb8Cqxs3D57qDEjTe7NBeG8nLWVPOIwHP3bYyww6mNpRoYqe343tXgfa3SkLJhl9nq8ZgTnvPtXNG4/1C3Gn2qlJBeAVa6Qzq6VO25a/zBem2OmYq08oJ9HYmpw+vpwcuhJPPDe0CZ9nvBWYGBMEakpzjVGGl5ix7tAtU0hCQvEDBt0Hytf2DuiTclq7B2DdweNjhmOHkBCytQBRwlrlzMsFJ7FDekm5i+tno/Fz/LHq4VMiTbdRf6qwvD8+m9SdG7pxFsasD0zFwwOwe3X96GwxZasOhQmjjxVHONsFP1N1tzESsrlf3kvsH7h0z8zCeZ/BR4/ALblLlOy9Lb9adInEOyv9Qq1PY+gYr3ZJzCKiVKe2mCb4KLAd
*/