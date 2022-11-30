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
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
*/