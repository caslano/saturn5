//
//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_MAKE_BACKEND_HPP
#define BOOST_GIL_IO_MAKE_BACKEND_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_reader.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename String, typename FormatTag>
inline
auto make_reader_backend(
    String const& file_name, image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader_backend<String, FormatTag>::type
{
    using device_t = typename get_read_device<String, FormatTag>::type;

    device_t device(
        detail::convert_to_native_string(file_name),
        typename detail::file_stream_device<FormatTag>::read_tag());

    return reader_backend<device_t, FormatTag>(device, settings);
}

template <typename FormatTag>
inline
auto make_reader_backend(
    std::wstring const& file_name, image_read_settings<FormatTag> const& settings)
    -> typename get_reader_backend<std::wstring, FormatTag>::type
{
    char const* str = detail::convert_to_native_string(file_name);

    using device_t = typename get_read_device<std::wstring, FormatTag>::type;
    device_t device(str, typename detail::file_stream_device<FormatTag>::read_tag());

    delete[] str;  // TODO: RAII

    return reader_backend<device_t, FormatTag>(device, settings);
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template <typename FormatTag>
inline
auto make_reader_backend(
    filesystem::path const& path,
    image_read_settings<FormatTag> const& settings)
    -> typename get_reader_backend<std::wstring, FormatTag>::type
{
    return make_reader_backend(path.wstring(), settings);
}
#endif  // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_reader_backend(Device& io_dev, image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader_backend<Device, FormatTag>::type
{
    using device_t = typename get_read_device<Device, FormatTag>::type;
    device_t device(io_dev);

    return reader_backend<device_t, FormatTag>(device, settings);
}

template <typename String, typename FormatTag>
inline
auto make_reader_backend(String const& file_name, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader_backend<String, FormatTag>::type
{
    return make_reader_backend(file_name, image_read_settings<FormatTag>());
}

template <typename Device, typename FormatTag>
inline
auto make_reader_backend(Device& io_dev, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader_backend<Device, FormatTag>::type
{
    return make_reader_backend(io_dev, image_read_settings<FormatTag>());
}

}} // namespace boost::gil

#endif

/* make_backend.hpp
5LEOY+5lyt23jyn3AlPuNJ/cuOum8sqtLQd/Kv89Hsd15D/X2y5/Sz/5Rwy2yb9ioMif82fyF12i/FN6/w/kdxVfT/6WJeTPGuCT/5cnbfKXUfkX/Zn8rUX+fb3+O/LbjpZcebWk/LMyAvm2ob0kCxlylBeyMLu/X3mvD8HvxxRPDwtXIVuKkO28Qm6mDNoz2k6SlFuEkawU+3mMXeemUq74EnK5Qvb3pEC6WZpC9YVQhwdphRyEClmhv2JMY+jNj5vHzaTlJnTCvSl2IsT+YIDg/QNi0tbErKaaSwU9NtkV/ApjRxsfFjFPj/U08zRXRpIUnq90QQYaHzFjqX16sNrqzQ3al75XSmapfE97+1J5kK99uaNfifZlf39tXx67bvtCmY0jFyju3B7/Wfvid/5oKlFIekjln3LZlL9N/E5XyAM9qP7nI9Jynwdwz1RFPu605G0DeZtTXtfqpLmR3iKdlj+EU2mY/OmwfiuGovRV6AoJ8Yr8u8qWCMkpciaL9kgt2km9ERS+8kEZHsx8jP5/Dsrgby5Ixincw59DwYJ/Pj/rLvnn5y/dNT/MS7Lr+bhr8vNIvxvnJ1nyEy75GYX8tOz+z+bncmf1g8PhzsMHJD8GSEadEvm59jxR3+e5UG9GmjMjvzzMjHwbLVsPf4qTy99a48IvYgQgw8xUAjI14RG+vj0+irwxmcukYefI/kYE7mWCtQX1QA1ZL51l2er5sJmx+cxHhuaum1QF78eQ3ihfBcY/gX/GRX/8Ax++pjx1tPBvz/LftyT+E/L5JcZWpLqf9Rap2d1MSX/9RyoY/oCoYDz6GGPLPlHBoyAZH+03VfBPlqfsIv/83NrtmvJ0F/NjQV/hz/OjRWriGYds80KG9nf1Qv+PMvTl/ZKhdQPoXUwz9DZIxkrca4auLU9mp6b20D9dMHMS0iJD7fO4AsSG67xrjzZdnbtK05WOVmtyr0BvA3u78RWMUE33prHIZNM+etxnnKyhqReK1P4Poru4G4xIIM4VEubN2DxkjGsZNBSZekEG9trMDmEuh9POts8iZmD7P5D//Hmv/Jn33UD+SQ9Z8m/r6Sf/qT9s8g/ufSP5XwOjyp/60HXkP3j+P5C/lSX/nHst+VNt8m/sYslf1V/+lnb5Z/a6kfwrCr3yj+tilz+V8tf/N+XPlu/v57zyn0235B9ik7+Syp8G+bv1oPxWvbjY0xRZ8uAnMpI7gaZeVy3LqvgtXCHLQbPqBddGKP4ASMAzPCEOz/CsijM8sfzwHFwxH9QsbL7BeG7+WV8n3abWCKQt4zZzaJQoQ6OuoGame0/dwnDj3e6B6t/Bm49n2f9pPjg1XavjpCT00SL8wFNMJsIr+IqCJGQlAQmlIyEziZuRxMkeN0yigiSxurM3CfjZxb2XGxIrf2YVw8OFm0Ulh4nGFpCvHSt67XW1HH57xqvHpmn2enTCtRsjXUAyN1UgSe6sgzOuVco3OmQm+2ErM3dRjRymWBYr4yE/clgOOdThbjonSCNABYvYOZPrGcnl0QfMXH7PnA33q2Uvyeq9qpnFk+tQrkV+R5TPjWU+jpyWfHTKaRP5XKhsvIhd1Ck/gA0v790DgYX/eE3N9mchlub+5nus3Mf5Dd/ue0DKcFeWn24Ysr3RzcpwDPIW1121Fy0FOPIVI+ckc1PNm5tNJvxi1M7cfHfa/IRKG/Y+zMghyGOZCkUjuMT8/34R4D4KEAcByvsEaAQBvmOXmhs+FxcUIJqkU4p4kWLS/aYUaykAo/sG5H6j839lfJj9h63/u/+a/jzF6v/asf97mEf981s5Det1PNVaOj+4orlXu/Ovjnu784MZpry//aPe76u71X8HeiU=
*/