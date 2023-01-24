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
3fw21Htz4w79u2dLfDTBzeNGlnp4RkbpeCUS1HwjLP+Hq/1kMf9D8+KD01GZEs00qXXzSv9YWocrWYGeqMRDbABzyHKeqTT2ctHUdsoUPgnQsKPXr8KxuZzj6MRpqNqPpyPfV+++4oz0oATK1RkA0GsxyP679+cJha7n7mGWUmutPFs/tsceIievczzBOCYX1yFf4MZrmepdve3+VHce5gRj+5b8IWZyVQ9LASczcUei7YFM3Lg7KQ2eTAIh7Vpkzu0xaTDo4nnlzbj2Evt5IO9JOf7m8CTPYn3w1zeQIGMFdQQN+UT/XG98S7bGHuDrFzNO0FB7nV6MHyUV7e729PZGm28ngt787j2XKHvoSzqH5O3hajU7bksdXakoM4eV/Z8q5A55+mNA66XoKXe6bmm9s/ahuwMb3TYc6+fdpx6eY7VttQQY+hg8Qa+dQpTBAf+cxH74HFuaPRAuNXDS12yrH1eJeEmTNYqbHfcK/rNxnLfAbVL6s2XHU4RqgVkzWOZz0JoAGTDSPuxV3sbajhnSr0TxK1MkBAAq7mzkkJeW3X2r5vXByNmn4zzbnnZ8OVAW6aZ6YMgrD18FwyTo/LPoEWb3NJfnRtpHIRzH2hZBd8oC1Tohq18YaA5euJShORV/KunpPvHQ4t/CNUt6xI7B7Ioc73SrEzxkdUP6ve0WqHYYfz+wfPTGUghjIXNoy9n59Sh5otzlLv3i
*/