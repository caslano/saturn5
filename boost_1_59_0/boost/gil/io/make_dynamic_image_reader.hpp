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
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
*/