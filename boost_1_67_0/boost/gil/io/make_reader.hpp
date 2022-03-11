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