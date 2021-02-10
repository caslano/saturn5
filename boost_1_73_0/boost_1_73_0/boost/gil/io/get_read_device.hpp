//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_GET_READ_DEVICE_HPP
#define BOOST_GIL_IO_GET_READ_DEVICE_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/path_spec.hpp>

#include <type_traits>

namespace boost { namespace gil {

template< typename T
        , typename FormatTag
        , class Enable = void
        >
struct get_read_device
{};

template <typename Device, typename FormatTag>
struct get_read_device
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
    using type = typename detail::is_adaptable_input_device
        <
            FormatTag,
            Device
        >::device_type;
};

template <typename String, typename FormatTag>
struct get_read_device
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

} // namespace gil
} // namespace boost

#endif

/* get_read_device.hpp
l1Jm7luL3wpcux9dR1yXdm2x6Fq4VOr0/nn5qom8hicOy7v4/O1mdTkDKr3Clizk9TrV4XKioFtx6UDZl1uEPWGZLWUKd8moCGblXYblyxqCXgzxFzC3I07vsYvsLCv76sfB0vlylOlSUbqZKkjkhX7uRWmaPZr3o4nBPwFQSwMECgAAAAgALWdKUhWYgtDxBAAASRAAAB4ACQBjdXJsLW1hc3Rlci9saWIvdmF1dGgvb2F1dGgyLmNVVAUAAbZIJGDtV21v00gQ/p5fMRQhJZFpWg5xFCi6UChX0TZRX8RVBFkbexIvOLvW7rpJuN5/v5ldu2lLSuBAd3w4t43t2ZlnZufl2abT/nFXA9qw8or9X0wX3b1F3+gPmLjl2nF8AeGHrAZ0X+WkAwuTi7gFq00uoOlN4srLM36O41WOBhwbf3TYchDzI0nIjC13dDE3cpw5aO60YHNr6zHchwcbDzYieCmUxByOHaohmnEEz1Iv+S0Ts9m6xecRoAORr1dQJ5m0YPXITYVBoOdcJqgspiAspGgTI4f0IhW4DGEkc4SdXv9s7/B1BNNMJhmDzHUJNtNlnkImzhEMJijPA0YhjAM9InMCT6V1BFg6qdU6+UZwaCaWMdi9yK0GcS5kLobkSDjInCvsk04nKU1O
*/