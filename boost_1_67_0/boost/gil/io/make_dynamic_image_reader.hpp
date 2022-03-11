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