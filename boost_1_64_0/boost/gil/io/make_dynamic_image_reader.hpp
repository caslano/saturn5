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
I3S79H7vgmSsxr30fv9sfmYV+uenX0aJ/rxkfpK6/Vl+tDvfW+AdIVb6p/OzvZPk57Oe3JOxTfKzFCTj6rYS+SlZfgtPecvv06lW+W3tV3zeuM9eftd2sZXfIV1LlN8OkB77g++7TvltzfJ76tR1y29VszXpa8mz5y57a2LK47lX5fHO6DrY5dn3UAl5fjxGeZbf6y/PIL/Woc8pn51Ohk2eITL+P+mV516fPH395HlG5elL12kcmUGkmQ/aREovKVKsiNTKTySNqlL1pVTL+Vouo2vrM0QE22/Tn8oXZ8n3bcfryrc2/Rr5ytnl+6ZLCfliRL530/9EvkY3lo/zc60bb58Q2Yyqey3Dw1Isstgcp3PZ8Bdizbks23POOmRqLdMJbKGJNG43zKY+PKwxPJeyBadlYEOL/KyPXGhEWOQdIMNuTtK4dNRLPetl5iemg0d5NdLxiaUjTTySUnHXPhV3t6VyvyMt0l1eO7DeSBnEWvEemO7pvnPXKeyCSFN6SCpyfysZ4/foB5Wpm/UDyoe4yn5gXvHskutqIwdXbhZCbmWOZM6+B7NfRuYVpVUl8Ew+rngu230jPC81+nM8Tx7xYjGIWDgCFM+tFvn+JkJWPPMsctumPjxnWNQHmwqz4jnpyL+AZ/mj18fzypESeB7cpXh23qR43rNJ8byTV37v2KR4xm/6N/A8e0zxHL7rRnjefSDoT/H85LCFZwNUIkEoyRhnUWcLtVDcuA61qGeNIAvNnhZ1KXhTTd6Oh/8FMBccvj6Y3x0uAea7OxXMUhsVzOINCuZ5XvF8coOCeWTDvwDmteN7n13wPqL8utvbQpW7w9rHpZY129Fl/bVPoAP7fFAcjbdLw2ox/DzLsNJHL3AEi7G1MQJBLKm9Dgkw2imgzRoOedNgHz/O65xeN0Eav22FmW8VEL2B4IPnmdJGLBIgFm13idl60BZpEY9x5KoDtz3ccbFOh+w9pDpxlCPbU9J6B8J092S8B76m0VlSyk4gJcEYJInO6OgXYR2FSHMtoP+fO+jhBUnhvs0dNtdJ7dc7+MgiFcv9Z2GwBAhpgzTnljX9Mo5PuBWP8ctZ1DxRFYvl+IvLnKhyBP2EuEJxggMmFBNpxL7uKilX7wIl85Qr6uENQYhsvAXY8kOWgRogLlwW4o7xj9r8mY32sC9w5sohw/17iWPKVLHjHlIlCJsQqpngDhonxymu1olmLgi8ywCuoXqAJ3qeMKp80QEZwTScV93capwqSdIULoPxyYxYpYwPwFiQOg/5lYK5fwdyXxkPZB8Ea5sIcKP4juuJ9y4wwhDnAmR4zuh3wNxFsVX0Wi7IqH6A+TuAPtCTz0+KsciSDFBdUenrgxy/MP9GThgKWMhvYMI2Gp7nwnWQewHzBk/Uz1dEUZPZK0e9doVovgdG2kpu6hnIoKxEtS/mExR92lkhU84JbJ5GNy/5xu9rHLIfJ4VxWjQM1o2oUG8kYmBPwtpOOUuCsS9h+e8EHTd52JCw5rTz4WVIqixti6SspXEfFRzledokVIEAufdha9Y2cQXza7FM2+kX8GH6kNhU7MHMeMVNwcweGT4EQ4qrFBh+AYOcVAOeTjlLg9PanRu5w+TKspLZCvdTxsmNxR4zpAdC0ig0wt7QFHDWKJFbDiZpAeBJ+nAn64WNEeG0M6Iy+HPAL5sr+NoPwE6PLKntzozcZPIWX/W+ti9f+zxY3LchiPvQ5OxgZ6MxMbOEdaPF+mk3ZDTNJ+EvVshfeyDkVoQAgvwGlkSTwaAQ/K2bQlB+47UQDLWS2dQIshRssF7QDSHcT0cIuObAFFYhGLlMGIBn5h/V7nSyMyIkjc8EBYGtGB9avuXCsMg=
*/