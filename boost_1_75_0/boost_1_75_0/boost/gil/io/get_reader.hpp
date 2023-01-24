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
WZzsHRAhPFeSZtme6+gbjk7VR8R3adcbv9Y/yuZPZgQsrY9V8yYDf/SjZQPUB+ZffUrMH7J4F+9O/OMBj7Um+15iNbeR2Gu6Hl4L5XfvxtjZqUMC6Wj3b3MQajvzTcdYV9TJtbM7VpDEBCj99hXMOJjiePqV+8EMPQI0Y9AuDTlrz2Rp3jwnb15PIZejH/u1bIW6bM6+fwM/1MC/OS2/03LmS0jfgtL3o/fEruynXBpB8S7jInrap+lQ3RbtvL6135oD9NnXjo4LGqT/hkBDBDpMwrg3weyRwiF/u2SDvz5s8Gp3f7knrvdqUm5zvGZ27j3K153b8/rIGOOVsIlcXmhFXVeGHqtBY67T6NfABWhr+8E+FhXBN9BdDkeVtm++yvQ5Bt6sHzckM7pH3mSACCaWJvELHw9LKjvfmyiTeSdivZHtQjJxxhn/i1JVlqtrlPCx2orQIEzMOZVN2FY44DOUXGCWfqNYNNTbYtpS5p3vSzX+9mXoVteiOzHpu7irKFapCXn9fqknvn+lBeCUoI8z5mJ7z5Pc05Wl/kqU7Lqkf/OQeLLw7XDtGWh3rpho2fmOg5jBuG0wbQD8AbJ7/81LEx9G8g8GL/X070CmgC9VG/Ere9JCWFkH3hs8k+CtJ6zvkamvSx926MipCdWKKw4vTWGjE6eWF2d523yo4C1bTYRdsug5ZfwkU11HEXfrqze3JdfDE/txnict
*/