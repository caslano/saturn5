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
53krWN8IS4Um2iaX9uCYwZyLpbIKWC5eRrM1LOdS8LAncu+4goURNC01KW0QvHv5neeD6GU0ephGD8k6zvNlGf22+OWIdRIl7B/ynxtltpIfDVVE9pX3ayNSeZ4nCNI+ZcZ7cBpmVx3/yeS//9bkJvmdgqTT+Ky89GG3WkOfLtX1W6Lsiw6XUnIrx/9j1U6WxX8DyAWB8NtXPHKW7Z2dzHe+PIFPLfHEQUmJg0na6xubaX9ivXd3NXlXZTuzU5hHbdfzz2qFsyDoGJnfpceITKVHQKbbw5n/OWWlPL0BUOT8TBCZ9tpwPy8eieZ8pR+nAWoxS3vZPr179cAyerIYw41/MCZCJxpzuVJvLI3xbh1Ncl1Mo+8S+RpyjB9EYnS5tCwW4jPMZLhaF0efv6nJmNPJfk51cRLrbTI3JiM0mijtrS3Ra/P851HBWEmWPCIqQPClONZDsxG6VH4T/O2KsiLh4jMzVkljQEpuV5hZDQbY2gtUhprQoK6ltibiOE3hkwVYhOs2+y61TTKa1Dut+21Gc9y7lukRuvjgnMbHopwiLLYUIK6+sI7wr9PMcC9wbR2SLLc4gkARnOgjLXD87dQaTR7Za9EUErDM1fPdcooDsnr6yrv4REGS+2qpT6gRsTCH6VFLMDrIfeYj6dEAWQLPsZoBMlkexwZwKKzqZX6GkuPBNkuXYaxAeEE46LDdca0l1cgp9mDd0pm81FWIuW4YR4Rc70JiH4M52XXCSq+eZqStrlBl8bUzy/K8JE9mKNif5nLZrzHEO0A2LDNnRDerNLTqiRrQRibIokmfHtV/dVWvE1zMYhNZvB6rZxavQ0nwgTt+gFm8LqWheC2paR5cj7yZ5Qrfn5OBZ7aUq9VSrgAbCxWCotmQvlbTsvGZ/yIkP11GHFGctpz/co77I5/o5xMfw8uxmrRCrHZGVkXaXt1EQhNi0q6IBStDC9ZvL0nBOoKLcRsSJVfZmnJFf3y5ht4VGQU1rFK0FOODUlzWGl+KzpsbMcqeGkQHJZrmRsZf8ES7UlCMygzJL+UxPah9XMNyZDW2i9Agb5Krds5lj0y/d7+A3EVCkIIQIxQXURoCk5zvLDZGyVsWQz3qG3eI+MaFNhJR4dUdrugjGjV9rsy790R7lxN6jrAtJ/iqe3oNnf7eX1qGBpYTTjHEWa2e0wYYXRmKw+vDmYlyIZKJgrLiwGWPEROq/ZkOGzIRm9feYYQM2D0lLXBmr/gTzjpy/ukIPWP8eWDeNUyZ4xEJ6Oq0QV4uZUpmCJh4ufJkYuGJeqeV8gd4E4/Q5n36WM/LXXm+kab9yjCkfRli4XyHUVwPy6xlZOhc9UXlePB59Vu2JZTLlbSzAd34IEyzGcZ3NA8WfyVB+ALn385eqiN+3LnAxPaWOKMqmF8stT4Af8sj9Cx+hXiojlcPm5639JCNENf2fOSrNrIsmW+vx8aF3ITukGbMfV1/8DLI5eYlI9m1HxcsG7txSU5moNg0XETdMmYHyfj/RU+Qw3QhvRWZ6Pm17JszHvym2JOU+1IA1ctmzpPHfcf1uS27gvPVsaDIWnjPQ+ZauDF1KiIyeaMaohbkUzrZelqGj3NRM9sbnpm4/cYYDlZd5TjPZmUEXsnXdOf+d6yfg0a/VKxp+M6E/NP4pTcUbvyO+O4nuDW0JZLgROQbUrqRUl8ohvEhKR1JqQCKuSOYtFtJu/qZ0gYZz5FWGzTpDR7lU4Q+JRtd+RRI/tXkR6oppBRy/6frgtGaDwfxYHwrwcvUH873MzQfbzHXkeT5nTyvKY+5d2rdtSbKia2bq9lmak5exdQEfoYaRjvqgOf1O+ZItaPuGcIGGnk84qZr36TfHfhrzPw=
*/