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
0XdSndhOUm9/PXOTy52cURATMQddOHAaSosRsGYEE53KEd8pISQsymEubRYtoiFXKu1oAxbznLHITqINYSMcV+mJWA0Kilg6vlmtLLuaZnpyTZHyyCij0ihyRHkgpVRTmiMoVYrGK/ud1y6qnPoE31qaRbwpaEXBwFr3GPaO12AorLQRvN07+b13egJvu0dH3cOTM+jtQvfwjMHe7B2+pNJLcmYAZ4VBS84NyEmRS0xrn0e7O49+fbgFvW7pMniwvgH8oI38JLhmsGvEBKfafAz6P+7qNBp3pUryMkVY42rHFl1ZrGdrvDCCOymOpMK0uXN6tB+/3Dvuvth/Fe8ddPs0hRe3LB8fnITlQQNuUen3+r+0rvh+xr5Du2XPr4REglQ4UcVTS88FZafjP3nlxg6oKvjo4fUFqqXKKfdL1AsjlRt5D522H45cWAeXWtwbtp6zIT4BStoNiAlOtJlfxyZZisNyXAF7/mBdDjpODAqHsfYvQ6RGMwRirRhjs3W1D+m3tKGTx6jQCD80NLEEkM4BVaJTWl70TYUCYX2kDUNZVKlUY0bhrieekDRoytXt1xfcXzQZ9kkl4aS/k+r9JTPe95mxhM79mNFEhonh8MwSTRaDIlSvlGnrliixeKFUaLNMicXNaYYKlHbQ
*/