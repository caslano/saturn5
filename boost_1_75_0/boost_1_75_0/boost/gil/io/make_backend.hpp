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
a/fP/Ik22O74S4FcAHubH9dXYX4gUZXJGhmjoya4fGD2bZrHIlM9QiErMeddzecNKMhM3I00jT2pP73Wgz9cCZBA9ZtOu8fSSg6igX0MJ/rs+/QXYOglvgEgL/P9R/vLnTo7Z0Hyfio+dnFSLoehopNtDqOAavmtJEvt7MZX0SsGhZ7HAmaTarI9mZZ8ohV0wuWTfbdxr7jHzBNwFe+t19fBwyutRC4kIAWOy+uGx4dOjk7Yweh6VUu9A8lP6Pwrqr6uR8KvqiTRpbJNUZvBxhwFGsD4ymiK2h7R+Iug9AKJpOxsyhfKysrY2NjdxcnScWOmWX0Xfn9p4rE8XPaxrHlDcf9oxlVno+qMVm3OQQo7trUY+i5bS9eQQi+2/TUy2piLfzt3MlvIf/feNIun/3N64E8LPjInvXN5MHNqo01qy0bMudiP74heukqipXPc6dOAn+YKbn4mh39Ew4xWs/rvVz3DHgqY98nupfOBjOUMG6putfj8Gxg4yLwEfU+1w7jj2a7BW+X3tclHCR25C8O3Xum/jZAZazR8vHLIKrGAMfF0zdNPxz6dGEoKA/3V2wW8zkR6Zjwk7Qja/sr5ULMJYEw9Lru2tyd7mfxrQkTmT/Xuk87uCC0r5DsrA4/dvTPSPR/j12Slwl4bi41cGNtL8U3FUP633imbG83MJEq06FOB/WnYVluEeVLtWaO8GafeHWgLNeasVP5p
*/