//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_MAKE_WRITER_HPP
#define BOOST_GIL_IO_MAKE_WRITER_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_writer.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename String, typename FormatTag>
inline
auto make_writer(String const& file_name, image_write_info<FormatTag> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value>::type* /*dummy*/ = nullptr)
    -> typename get_writer<String, FormatTag>::type
{
    typename get_write_device<String, FormatTag>::type device(
    detail::convert_to_native_string(file_name),
    typename detail::file_stream_device<FormatTag>::write_tag());

    return typename get_writer<String, FormatTag>::type(device, info);
}

template< typename FormatTag >
inline
typename get_writer< std::wstring
                   , FormatTag
                   >::type
make_writer( const std::wstring&                  file_name
           , const image_write_info< FormatTag >& info
           )
{
    const char* str = detail::convert_to_native_string( file_name );

    typename get_write_device< std::wstring
                    , FormatTag
                    >::type device( str
                                  , typename detail::file_stream_device< FormatTag >::write_tag()
                                  );

    delete[] str;

    return typename get_writer< std::wstring
                              , FormatTag
                              >::type( device
                                     , info
                                     );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag >
inline
typename get_writer< std::wstring
                   , FormatTag
                   >::type
make_writer( const filesystem::path&              path
           , const image_write_info< FormatTag >& info
           )
{
    return make_writer( path.wstring()
                      , info
                      );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_writer(Device& file, image_write_info<FormatTag> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_adaptable_output_device<FormatTag, Device>::type,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_writer<Device, FormatTag>::type
{
    typename get_write_device<Device, FormatTag>::type device(file);
    return typename get_writer<Device, FormatTag>::type(device, info);
}

// no image_write_info

template <typename String, typename FormatTag>
inline
auto make_writer(String const& file_name, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_writer<String, FormatTag>::type
{
    return make_writer(file_name, image_write_info<FormatTag>());
}

template< typename FormatTag >
inline
typename get_writer< std::wstring
                   , FormatTag
                   >::type
make_writer( const std::wstring& file_name
           , const FormatTag&
           )
{
    return make_writer( file_name
                      , image_write_info< FormatTag >()
                      );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag >
inline
typename get_writer< std::wstring
                   , FormatTag
                   >::type
make_writer( const filesystem::path& path
           , const FormatTag&        tag
           )
{
    return make_writer( path.wstring()
                      , tag
                      );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_writer(Device& file, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_adaptable_output_device<FormatTag, Device>::type,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_writer<Device, FormatTag>::type
{
    return make_writer(file, image_write_info<FormatTag>());
}

}} // namespace boost::gil

#endif

/* make_writer.hpp
ywN3ghu5KczTNBZH7baXJQFy3/YjT7Q9c/z9ebrIT/IBmVi4dxDFKaQRZIK1gGa2YBH5fEq/USD4MM4mARfzVsENbhX67SgBwYKAaOE6zoRim4GtxdOiaRAjxzylXyIKBW11M48WlYkoR6IyzZIQN0I54CQ/QjG3IAt9lsjJ8uRmCy1TKeC1qin49SEKkRnY7tjQt7dh4gouWnDVH78dXo7hqjMadQbjDzA8hc7gAxF71x/0UPUcN0uA3cYJE7h5AnwRB5z5Zs/Raffl4U8/g03PpVjIg1L0INzzzLb3Ohd9GLBZlHKXlAjvmTdHAxMLReD7fdpbWz/w0Asyn8E2qd8RLM3i/fk2DUzRNqc8ZH7j0racKzzc8Mp2bPui34SdncqgfTGwzobNErlfiJwyqfmb8jbXbpbO2/In7VMM4FTfTd3qQ8kUSp79+LI6gPoKA5RvzfRFFqR8cpey6phgoT9depQmLEmiRB64vSudJXBFCvkUshVh/G7CjgBltrwdW0TJXZUwPvPZJJtpwhJPaC6d2uHCEXGI+nVEFsdRgmpvNMv2iP9nQlk0u3aDzEXnQW0oIUPDmAZr0sychjGvCzdxFwwtXxzBIAqZsTrUbIK+NB5dWkQtp1IhApM7uOKhH90IIE0T0fbWJIqC
*/