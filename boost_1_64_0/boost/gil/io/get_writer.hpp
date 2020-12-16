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
Gu/pWiybTWZdDcJXiC+KMccQtjfJUGMWpFLTtlnD1G/kMwGSYFkkmCRHwJB5AJjh2T+rBRKqM5LLAm/KV0rDa8A6VGNXQpixLhiyoHQwYhNG5GlXRrmAALWOkUZhDdc3tpqTll6IoAfl61fWkUZpMEOufuzHw+c9GObIRojRGXzmx5m5DmFISudZu5tIyb7fw6zc4qLTafpQQqGmlU5fmugMEguDj++66jE9QS7MQtm6GOzL41E3V5uTYZLT3tno15iJwNnZ1ZN0fjEWXioiBIm0RubvfhEZfPTuYk/88vidnqiDLbwp8AuxAVvcoMFQdouEq2DwRC1uQa2c4SnBYr1J98scV2t/TkI+BofowyfJwr/6sC2QpTSWB2RnRJp4+P56eKD5ATl3gnRtRpNg0//V23wWm495AbogMiPAexKof+i7Ejoq1u/913IFbTOeFr6XD80LMiMuCQyQ626HHN3yVqQ8JnmWGl+plkJ/H8oxQSyZBoOUwP2iWaG/Z5JaMYEl8Xea8c6Nl0PfipJo4FJays863q7B2rjQzuFGtieuwg1Tu4IvG8RxZLzp/RVI5tKzMIB2NsLgEdIjprG4Hb53xRbGLz/t7HbBE5UO9oFJzqf3QGHbMf494zyykz0ZRjrO2C2nnb33DOzkHLWOf7Ybk1OLRVdV483pcvh5RIFvpCZLkoPQnL6fdKEYEZOR9afA6ozV1xaUMvV+HmUkMLMN4pWCpbDRCTyiZ0u3Pxd5dZvVm34Wn5OaEkDmLwLUaC/OGatFjpkORaZlzeQqMscqAY1Ha2+xqpr2Fo660lvMivbtZ2Ov4d2QmXl/mpw3kjWsZKk5F3BNqRnjcUipyUSLdm2p6SuhLx+xSsPPDlXN2mJxRjoG03lUhROeqG3NmXSm1JJkIJgcVGi0v6uYqgKDx4huq3ViFvgkzxiUOyf0CPD/fpjuWgzMmPxfuH+DteEAtG0dRqLZOn9NZagdwAYE2Rqj477Wev0z31ZmHuVdxYoAP4Bfi0BvCR0VzXpzbX0pMm5HuK2+vOPR6zdXBaF+FQQwzxLjBeHMDJ3vqy4JIJnVZb5fdZnvV122SdXYcYtUF545+1fcCm0paawuH+OG0HbBcEfKAKHN/U7rCViNadhPiKqRP9D59G5WBtdmjoWhqPkoIc7YdagS2/yqxNgUrRIhcd4qcRB8rvyUJku1Sly4Cst65K1ninQnbjR3Hm9Dus99G54GTiy9J9DBn3s3bAZ3BTpux3ULrgZ+l/Arj+d6+MXhNw7PI/DLwP0kXHvhuh2/0fj9qf3dPZXVGdvpZNfC2UPhxnsFcmoa4D2ILiWnODirqi6Czbgqa94NgbjRMZRzH5lNycrKZWpsm7cv++IZqaF7OaQMBjtIk0AyVsj9WtGjGtW5pMrFqXGdVz6/8Zoa2X0RZfq659o1d5ChDH92QQdWsa5C/I1xbcvXIotgmvniifMsmbEZyfy/D/3k7k/VN87mqTqW+NlhDr1aVOfQq8zzh2XYNdHwDruafmD56IhWVx8fgMKoY1nYfjLKehn07fP+Ip78hSfz0YJ3jYL3+cbCggnGftyJwAXZnnwe/DYM7QXvTrkHyx1KVIz7EdwZP5EVbkIe9MjA4+fzGHjcgQ8fsK0T5x8GbcI+/ZIvkXNGWz0teL83UDd/v3kFPIsDpMuNpnOrUsW+znFmgH7aexBMoucTmY+z693cOh37X03fqqXFt2rr6lmnXAt06FQUPawqvzM/JW96KYv+n/kauNmT9lAbnRCQTB/tnynnk+R0kDMenGjWY/DCEB4O2jnZpZjNfp7jm1gjoxVLnu/cATLdbB7AP++inu5ZW9ZKMTlD0nFM+i4kXRA=
*/