//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_MAKE_DYNAMIC_IMAGE_READER_HPP
#define BOOST_GIL_IO_MAKE_DYNAMIC_IMAGE_READER_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_reader.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename String, typename FormatTag>
inline
auto make_dynamic_image_reader(
    String const& file_name, image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_dynamic_image_reader<String, FormatTag>::type
{
    using device_t = typename get_read_device<String, FormatTag>::type;
    device_t device(
        detail::convert_to_native_string(file_name),
        typename detail::file_stream_device<FormatTag>::read_tag());

    return typename get_dynamic_image_reader<String, FormatTag>::type(device, settings);
}

template <typename FormatTag>
inline
auto make_dynamic_image_reader(
    std::wstring const& file_name, image_read_settings<FormatTag> const& settings)
    -> typename get_dynamic_image_reader<std::wstring, FormatTag>::type
{
    char const* str = detail::convert_to_native_string(file_name);

    using device_t = typename get_read_device<std::wstring, FormatTag>::type;
    device_t device(str, typename detail::file_stream_device<FormatTag>::read_tag());

    delete[] str; // TODO: RAII

    return
        typename get_dynamic_image_reader<std::wstring, FormatTag>::type(device, settings);
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template <typename FormatTag>
inline
auto make_dynamic_image_reader(
    filesystem::path const& path, image_read_settings<FormatTag> const& settings)
    -> typename get_dynamic_image_reader<std::wstring, FormatTag>::type
{
    return make_dynamic_image_reader(path.wstring(), settings);
}
#endif  // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_dynamic_image_reader(
    Device& file, image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_dynamic_image_reader<Device, FormatTag>::type
{
    typename get_read_device<Device, FormatTag>::type device(file);
    return typename get_dynamic_image_reader<Device, FormatTag>::type(device, settings);
}

// without image_read_settings

template <typename String, typename FormatTag>
inline
auto make_dynamic_image_reader(String const& file_name, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_dynamic_image_reader<String, FormatTag>::type
{
    return make_dynamic_image_reader(file_name, image_read_settings<FormatTag>());
}

template <typename FormatTag>
inline
auto make_dynamic_image_reader(std::wstring const& file_name, FormatTag const&)
    -> typename get_dynamic_image_reader<std::wstring, FormatTag>::type
{
    return make_dynamic_image_reader(file_name, image_read_settings<FormatTag>());
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template <typename FormatTag>
inline
auto make_dynamic_image_reader(filesystem::path const& path, FormatTag const&)
    -> typename get_dynamic_image_reader<std::wstring, FormatTag>::type
{
    return make_dynamic_image_reader(path.wstring(), image_read_settings<FormatTag>());
}
#endif  // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_dynamic_image_reader(Device& file, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    ->  typename get_dynamic_image_reader<Device, FormatTag>::type
{
    return make_dynamic_image_reader(file, image_read_settings<FormatTag>());
}

}} // namespace boost::gil

#endif

/* make_dynamic_image_reader.hpp
XvKSydMKboRAk3VZ+tV8PG58LAP1FwYJWDoKNgCed5T+r9NSpmV7AQzKSqH6veMGzlZI5pCAWb6kF8Ksf6HByRyaZu3/Sz+Wbog/yWmQ++6QqOgvupmy5Pdzdd6IqXCrJSOrPkmrMMlab7Q5W5ZGjDkn6saDqHdmVM8cGjGgLzdLdXMPmvRSanAQGrn21xHZj0EbOBLpSSg0DO0XokTzL0Jk1/uaNhfqBMJlhJCS28CgXT6NFHpFng+0qxkYY3eJfB4WiaeVs7X2cKY/kFgjsCSWanmy7mVWvIM/uv83e8YJauSvA7zXLLU0LABARCam06+Rv8oTZnPLPdHcrFlNKZZQORYIHXaYGHRZVn53Rj0YziVdSs/RX4Z//yPpt+P31pJC9EKcME3y3Cv9WkdHV25Pipf2jxCgbfwTH6AwzG78XJBr5sg30S+t+ouNX5skA9UTKdk0KP9LVmQ3AWfoK3dMDIkjmT34tSEnRPE8+CwNiUn22/CTQlrgkKjhd/c1s2b3alORhapcjyZ3/Jt7j6WiUtAY7yMvEtkeIRwU103A7MHhKEZYzlEvI+n/MTKf6aQ95zbi+ABTIp7syPv9l7+eKKxIfVP8a6Fny17ASJRS1vc1NosDBfEjQYAmavTKaU09zvBNsvzBBRrPH/0jC5uln5Iz3USUlEbFoEMGCdijc5yRZBBL+AMin3priJ7BtvciPPutsJpVmVgn
*/