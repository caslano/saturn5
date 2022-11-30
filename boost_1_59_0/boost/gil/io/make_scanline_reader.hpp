//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_MAKE_SCANLINE_READER_HPP
#define BOOST_GIL_IO_MAKE_SCANLINE_READER_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_reader.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename String, typename FormatTag>
inline
auto make_scanline_reader(String const& file_name, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_scanline_reader<String, FormatTag>::type
{
    using device_t = typename get_read_device<String, FormatTag>::type;
    device_t device(
        detail::convert_to_native_string(file_name),
        typename detail::file_stream_device<FormatTag>::read_tag());

    return typename get_scanline_reader<String, FormatTag>::type(
        device, image_read_settings<FormatTag>());
}

template< typename FormatTag >
inline
typename get_scanline_reader< std::wstring
                            , FormatTag
                            >::type
make_scanline_reader( const std::wstring& file_name
                    , FormatTag const&
                    )
{
    const char* str = detail::convert_to_native_string( file_name );

    typename get_read_device< std::wstring
                            , FormatTag
                            >::type device( str
                                          , typename detail::file_stream_device< FormatTag >::read_tag()
                                          );

    delete[] str;

    return typename get_scanline_reader< std::wstring
                                       , FormatTag
                                       >::type( device
                                              , image_read_settings< FormatTag >()
                                              );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag >
inline
typename get_scanline_reader< std::wstring
                            , FormatTag
                            >::type
make_scanline_reader( const filesystem::path& path
                    , FormatTag const&
                    )
{
    return make_scanline_reader( path.wstring()
                               , image_read_settings< FormatTag >()
                               );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_scanline_reader(Device& io_dev, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_adaptable_input_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_scanline_reader<Device, FormatTag>::type
{
    return make_scanline_reader(io_dev, image_read_settings<FormatTag>());
}

}} // namespace boost::gil

#endif

/* make_scanline_reader.hpp
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
*/