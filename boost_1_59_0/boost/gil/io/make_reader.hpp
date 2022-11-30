//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_MAKE_READER_HPP
#define BOOST_GIL_IO_MAKE_READER_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_reader.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename String, typename FormatTag, typename ConversionPolicy>
inline
auto make_reader(
    String const&file_name,
    image_read_settings<FormatTag> const& settings,
    ConversionPolicy const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader<String, FormatTag, ConversionPolicy>::type
{
    typename get_read_device<String, FormatTag>::type device(
    detail::convert_to_native_string(file_name),
    typename detail::file_stream_device<FormatTag>::read_tag());

    return
    typename get_reader<String, FormatTag, ConversionPolicy>::type(device, settings);
}

template< typename FormatTag
        , typename ConversionPolicy
        >
inline
typename get_reader< std::wstring
                   , FormatTag
                   , ConversionPolicy
                   >::type
make_reader( const std::wstring& file_name
           , const image_read_settings< FormatTag >& settings
           , const ConversionPolicy&
           )
{
    const char* str = detail::convert_to_native_string( file_name );

    typename get_read_device< std::wstring
                            , FormatTag
                            >::type device( str
                                          , typename detail::file_stream_device< FormatTag >::read_tag()
                                          );

    delete[] str; // TODO: RAII

    return typename get_reader< std::wstring
                              , FormatTag
                              , ConversionPolicy
                              >::type( device
                                     , settings
                                     );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag
        , typename ConversionPolicy
        >
inline
typename get_reader< std::wstring
                   , FormatTag
                   , ConversionPolicy
                   >::type
make_reader( const filesystem::path&                 path
           , const image_read_settings< FormatTag >& settings
           , const ConversionPolicy&                 cc
           )
{
    return make_reader( path.wstring()
                      , settings
                      , cc
                      );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag, typename ConversionPolicy>
inline
auto make_reader(
    Device& file,
    image_read_settings<FormatTag> const& settings,
    ConversionPolicy const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader<Device, FormatTag, ConversionPolicy>::type
{
    typename get_read_device<Device, FormatTag>::type device(file);

    return
        typename get_reader<Device, FormatTag, ConversionPolicy>::type(device, settings);
}

// no image_read_settings

template <typename String, typename FormatTag, typename ConversionPolicy>
inline
auto make_reader(
    String const&file_name,
    FormatTag const&,
    ConversionPolicy const& cc,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    ->  typename get_reader<String, FormatTag, ConversionPolicy>::type
{
    return make_reader(file_name, image_read_settings<FormatTag>(), cc);
}

template< typename FormatTag
        , typename ConversionPolicy
        >
inline
typename get_reader< std::wstring
                   , FormatTag
                   , ConversionPolicy
                   >::type
make_reader( const std::wstring&     file_name
           , const FormatTag&
           , const ConversionPolicy& cc
           )
{
    return make_reader( file_name
                      , image_read_settings< FormatTag >()
                      , cc
                      );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag
        , typename ConversionPolicy
        >
inline
typename get_reader< std::wstring
                   , FormatTag
                   , ConversionPolicy
                   >::type
make_reader( const filesystem::path& path
           , const FormatTag&
           , const ConversionPolicy& cc
           )
{
    return make_reader( path.wstring()
                      , image_read_settings< FormatTag >()
                      , cc
                      );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag, typename ConversionPolicy>
inline
auto make_reader(
    Device& file,
    FormatTag const&,
    ConversionPolicy const& cc,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_reader<Device, FormatTag, ConversionPolicy>::type
{
    return make_reader(file, image_read_settings<FormatTag>(), cc);
}

}} // namespace boost::gil

#endif

/* make_reader.hpp
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
*/