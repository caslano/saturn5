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
J0hvmTVBbPPjCP1q0NQrkGaRw2RgiKA+PDyUDEvnNJfMIPCDdVSuEMyfYh3fRXbthb+PMSX03YsYU5awF3WCYteO3eBCGolBgFC2WUhjkVyc415RPkgknaBckngcpPexz7zrC+ejmAcnhUvwSGLZbfoax3hH+OhzhK/URQuGY9ln4AqBh8mMzeqr3/2WK55vw0fcYLp/7/2iTMe6aKehBn9fub8wfQC5wFEjd11kyA0TJKgeNdevS9Jl0OEyhgoZ7ZoTV5XpiYt7TRDgKcr5fmr44iOanAjzshDs943ZzYcfa99qnAMeUpwDhgFwpM/ziTthhP1lNVnN9uBeUZ+dBGmrI1YVWJWz2ZapI8o8VeBHiUPLtW7Ba65zJflgIyfmItUlmKYGxa8LHx/VrCOTMvCrGonZPlEQdOLU/IjYbU/VomacYZDi+537r6JSMP6neHIJaK3K8t7DXe5Rymi3xCBbjeHnpsZvaw/6Ne4zqwzew4UY+qxKZ5telVomuJ6ZTw5PS14B/v62pU+ni3WJnthufWMYbm826r4e8r30/8XQLaii4heBaV2G47MzCityWIHuENoXP3TUp5Le/GV6DD3dTimRheF7KrPcFTZXhq/c8WvptKQZX8JfGY6Vk0Q2c9EZJmRt/9Fo9GgCJtQumUxBJlolXgsGyQcHBbXhL9CyAWq6sc8V1tevmE3RAnCzoF9exTcXMs+0Kfri
*/