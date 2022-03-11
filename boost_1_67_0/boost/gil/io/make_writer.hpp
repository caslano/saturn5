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