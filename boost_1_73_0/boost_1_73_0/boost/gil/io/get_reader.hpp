//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_GET_READER_HPP
#define BOOST_GIL_IO_GET_READER_HPP

#include <boost/gil/io/get_read_device.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \brief Helper metafunction to generate image reader type.
template
<
    typename T,
    typename FormatTag,
    typename ConversionPolicy,
    class Enable = void
>
struct get_reader {};

template <typename String, typename FormatTag, typename ConversionPolicy>
struct get_reader
<
    String,
    FormatTag,
    ConversionPolicy,
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
    using device_t = typename get_read_device<String, FormatTag>::type;
    using type = reader<device_t, FormatTag, ConversionPolicy>;
};

template <typename Device, typename FormatTag, typename ConversionPolicy>
struct get_reader
<
    Device,
    FormatTag,
    ConversionPolicy,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using device_t = typename get_read_device<Device, FormatTag>::type;
    using type = reader<device_t, FormatTag, ConversionPolicy>;
};

/// \brief Helper metafunction to generate dynamic image reader type.
template <typename T, typename FormatTag, class Enable = void>
struct get_dynamic_image_reader
{
};

template <typename String, typename FormatTag>
struct get_dynamic_image_reader
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
    using device_t = typename get_read_device<String, FormatTag>::type;
    using type = dynamic_image_reader<device_t, FormatTag>;
};

template <typename Device, typename FormatTag>
struct get_dynamic_image_reader
<
    Device,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using device_t = typename get_read_device<Device, FormatTag>::type;
    using type = dynamic_image_reader<device_t, FormatTag>;
};

/// \brief Helper metafunction to generate image backend type.
template <typename T, typename FormatTag, class Enable = void>
struct get_reader_backend
{
};

template <typename String, typename FormatTag>
struct get_reader_backend
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
    using device_t = typename get_read_device<String, FormatTag>::type;
    using type = reader_backend<device_t, FormatTag>;
};

template <typename Device, typename FormatTag>
struct get_reader_backend
<
    Device,
    FormatTag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type
>
{
    using device_t = typename get_read_device<Device, FormatTag>::type;
    using type = reader_backend<device_t, FormatTag>;
};

/// \brief Helper metafunction to generate image scanline_reader type.
template <typename T, typename FormatTag>
struct get_scanline_reader
{
    using device_t = typename get_read_device<T, FormatTag>::type;
    using type = scanline_reader<device_t, FormatTag>;
};

} // namespace gil
} // namespace boost

#endif

/* get_reader.hpp
6IMQmC3QTsIoiJlDwSnNQxjKu92hvDTEUl7imFoBIySdPsZMPMwAw23GtlXWWbFbiRvQGyS3dElAVGWApNmzpEMYFKWotcaAS1JUvj84TFuXqhL5gvt8lswy7wrMtaGgzMaEf1Cw5gUgevFnf8adKKA3YvZRHXXm7yWibsxwLwkxXjAhseqm7W+6cy6CiDNRPzo4eFl/+UPjx8NDgtH1kO7jhacHBKYyos6t9bbZ63XO01MBrfhTLjOzUJWauiXS6JZZg/DTzSpc5sF+CoU2XEi07IpEs2nG+kUgUdGRMb8PEzE3mpkB2snIJh8ti9DytwmKffe7745XV6WnHJZ6Yl7HJdipn50U6vFcZtsS3NSpi3EV1u+yRl3pD3KRr/GQcV3jMeO6xqZxXaNsXNdYGdc1Hj6uazxqXNd4tnFd41nHdU8bdf0xx3w7GU/7GkGepoOdjD0+83Sw4Mr1QS3pql1VX8FQ0jv50x32pVkZFR/TqT5mAHjvQP/+y94HjfEKpgTPM8gr9OOCUd7WA273C5vo1eY4i1jWDzvmHYTYtH4ixLZ2wh3ZA5Z3to/rHiUb2a5pivUtKmzLpN0wvKKyOmIqlqVB35RkqyWEs1o/LINbm9GouiSwaSSVgybIqnAhfxlmxmPGylIZy+5D
*/