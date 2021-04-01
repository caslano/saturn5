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
xSJOuRRFbH5KSSD8bUUUtT5pye1f4iGItX6xwl+OrUTc6C2zwrFb7/g7zcHvqAISVKTTm/TulHURqww3VoCx2j5ygrkcQlv9lkxQCWz8fPHtTTw5ItJE+tEuHvm+LD1pH9NXWNdB4ZVt1zs7jgG+bc+G+dfm0olipmvaxpheyFvWO4ZNTmxg27uQAF8TfpfUPOFsDj5j/8nPirnh+UMITdsoyEFFVk7kPVFJwXnMClvZiPGE6nNr4SCzvIG2VH8kwgmka6qcowqjGJ0D60cJM0lv43LsIK3cIw7Rv9kxf1scyTigJaNNTIx6L6Ui1j6LAw00GcFbxjXlYFsNiGRUungW1L9oRsT2a06Dzxbl7kbbOKgY5uFM+QLZNxWXVrdzX/kCQ8hTvVfVu3RCGQKdmzmUqhFC7D5CBDEUyUFnfGbkSKKWKVHiburVzVVXEL/0G+znQdcF45WtlUljvqXni+mygHMJcAl6gh/GrHPjfdgFOjHT3n0HcyHDhkwZ/NjAb1ZIJ1Kd9a48Tg/LPo91SSmitqNKJVWrBkZijGkdyOL9ivgETbk4jolCbw==
*/