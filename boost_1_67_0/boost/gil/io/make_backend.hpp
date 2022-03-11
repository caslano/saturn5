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
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
*/