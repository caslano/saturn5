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
bVSwemO/YVqKv0+QPzpIcSFT6E83T1XT9zrXTt0Jam9plu9NSpZLHKtWHTDJ9CUczuYpp1+WpdFpqWvXN7bmWSwoPuknXi7Jaeedq6FTLtOo/5QtbKpDuHZR/+qHhZymDiaVLHeh3j9QezQh5Ss/b1JbWf6qSUf4C1BLAwQKAAAACAAtZ0pSoA6UTeMNAAAeLwAAIwAJAGN1cmwtbWFzdGVyL2xpYi92YXV0aC9zcG5lZ29fc3NwaS5jVVQFAAG2SCRgtVp7U9tIEv+fT9Fh64jNGQy51O4GNtkztiCuEJu1zHKpTUolS2N7NrKk00g8dpPvft3z0MOWMZCcdwNGM9PT049fd0+rvfv9PluwCxs/jvzn4Ad/yxUXSfQn89L62Y7zBdR/uOoj/t60SRuKJV+cJmxe8gUacomjd/mFvjvOpo0+Em/0o00rPzr0FZ/gMlrZjeK7hM/mKTS6TTh89epn2IMXBy8OWtBzQ84CsFMWTlgya8Evvnzy77l7e7sv2JsWsBTcYF+TGs+5ABFN0xs3YYDfA+6xUDAfXAE+E17CJ/gHDyGdM5jygEF3ePGhPzhrwc2ce3MichdlIOZRFvgwd68ZJMxj/FrRiN0khWiKy5G4z0WKBLOUR+E+7s0gZclCEA3a3g1EBO61
*/