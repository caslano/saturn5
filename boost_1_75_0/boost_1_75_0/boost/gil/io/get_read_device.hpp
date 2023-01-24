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
h1fWUWRQLMH2j3JLM6vPe4Mqte9RchNX5d8rTubJHb13TN0HG4PIvQw7pBcr11IEFLxt8nTmtvZq7ZPevDR4LabXK8YX7/An/Ypg7/Fl7OkfNSrl8BCRKNZCmsysD/Yci6FDMJeNZwDbfUOGOpbXGiov7nnRbyYZ6R6/vqBtaSwncqj7jOTYW69feWp/8nx+y4n/gbPQOSnEZMneLNmBQ9Jhwz7aVmyAejOkr6T6ZnyS+oVZ3wugVxW+/0XaWumSGfBrW1BcscBKXh2F2LxhCIwms38z/86lgFav8j73PM+UkCMvi4ztn4GW95lLzDIKOpiGeeWIhZTwqk1uIlnDoC8TeZdtVO5DrUEjFklk8/ZJHC2JA2J8HJmfU1w+RhAO8IA8YpOApklXFchBBxfjuoGb6oq6NXQQ7JkVmnpHoLNIlpfSbTAswUeMBKAf9Dr8/fFhINUZhVhjkIbnoJiPHf9iPlG52Aowa8mxzCdLWwDkukEV8zurd8vNsxtcx3mVT7ruw83gO8WzaGHyoolfbO+db83Q0047nd7IIR6zLJonbvRx1H8ix+cBlrLeI1uNi3qYmtDiiEUQgZvg/IvbIBbq0YXnOzWkCbz2KWK5dbu19Qyv/SwyI1ze3J7S7kOEol3MyrOauyUGKrOaS+ZChmDw8OqbH70vVWW86R4KSj8XWv2uR3+IQrewbCqTz/NwM3iW4QPiWW+LQBfa
*/