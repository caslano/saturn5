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
yAtmWiPy6qYnCLKbymLTrTF93wt5Jku1LEEC+Nunyr0nZtpIuBOyilmdunOoW0/MtH/APbZ7HIdBzI3aqqaxkENmQJDR/SqThDfxpGO7uF5qRfG5iPkNBUNPzPSCr9TYrjVk3GdIvmMa/qkZztzmPkBCYlJdqeBguYunspZImi4Z+kAn4pwzjPiXleUwiYapIWHsS+nnOhIPk8zlfli2BGjMl2m+vqGPQof5uIFkqhL8ID1A0kcNdB0oWz4XZWeWPK3+b+auAzyKagtvGgklbICEXgIECU2DAaRFEk0waKJRRJAuIKKiIiYIihheQMElimLB+lBQEVERURH0GWrovffOLKFEamjZ9//nzM7uBPD173t8bGbm3HPvnPuf2+fcc98cgxQeQgrudrpbfSIJKSQ0BuFvQaZX23XIBc7QQSIUoR43eTCvueHTLqE/jwq8S/KjrWlItLAFZjVMzk0srWylXwkE286OyjZN2C5OELbMMNgzj/0VnQU+FOsX7FdfDSSUnqgZGmHsJwjtlPtSCIaL2OjXGqebPxLCDxwZgZiP0ddOQFJ2UbRzTFtQXetzjgU4x4TjVm4uBuPmEhysh4ASvxyMtzjfWeBZ7j7HgITPIAUdqIeKJva/AsiqMvtGKEMfRGgAQqWmlVHp0sea0pUzpdsJOrJaXrN6+1hmtTBFqzPKCMaA1HmrSC14gyrpuYTaa0SP1RnVBjN0SCTjvdxcd4nFKe9Bl+7zN3m/iBRqS8o6OAqytg/1Du7j5Nt7sncKKIYXuekBqbiPxi0E26omp6/PlSK2WiIZU5qoYuB50V6S1+NVePMOlArOtdiFkLxUyWdA5uPP+hg8Vh+n6+PyIQF6pjoesT8mt2XyPm617o7MOF+fye8x573j05CHmUNX+zgMycfkZT7T/qbM+9u3z0xG9Pa3Z7ZQX0my6x5pFaTQL602htVYXN9VlBqMBR49weA2D3Ebg8CCSvRPzZtQ7oMzBS4FLudPd8FGNR82qm8yfevAg0OVZKt3ztKwds2+xVucE3pq1bhouoJfDgZ/d+BpRpsIcwd95FDZl3HfcGsHfdEgfePpioJJgCnAwYqq7v5O0wvTPuNkRcIki9WjHlJvdPtBMk9kiSAjG7xCgwaxuji2MyeQ7tyY4FsVKXXi+SUBWZFJ7U5mRrINMwWuCoFBGzmDbaBJCyZNB4V4F/e3VWCqXhVrN/G+Q3HMUaFvxjugoPgT8eehpCHQ6NA9ARjvUktts6CVqGOXg5BqddaHJkuND0Sm+PNzH+rSpQuYLpxgu+FauMCoE7QuN/iBdgZt7ehW3JmyxRgM7oIIn6p7MvZSn5beB/Owp1X6jgLfVt4+M1A+WJlP3/fXZjvFq5Fo9JaI2IgXONYmz2PIKXnql7fQnR1uodvQ6UU35DEL3RZmlBUINE0xa+GWY9NHFZuKJse3Po4leVJsupschRHKsSXcuzGfDfHt4BhAY5/1ESBrJjZUtm4bVtFh2CRkmGn9RdPqiLe5eRQ850mgGS1BwH1bM/wmhm8KNNu7m53JawrK6G2SM3kFTG1CpRl8e0Enz4Kk7DZo/+ZiDJ2bFPDVZZT1rFB1uhMYn8fArJug2SFhwZLyKil8+fS3N1rfVRUU91McoS2Vzorcd5jcn1jc+0zuY8BHDm7P7nCLJFzFZH3OYt1ssv5O1kiwEoBtd/Lr8yjGOByqMZKsGIvMGLmMcUA32JV9ypyNUCHqRepmRJ5uRg62In9iRs4AI6/VmZ+PA9j6v4IW1iGHNi7PlubmNfAilhHj5GjhNgRjsW67Q92l5beuklmZ/dHoS7796gtlv7pz3uk6OZdChsXn3nEZDt3xQSaNKQXlxy8=
*/