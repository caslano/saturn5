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