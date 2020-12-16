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
NVubc7F5sRQqDhyoJgNlfb/wMEm1SOL6/oh5sr4/+48rHqyD83xbHNxMHzh9T8CTZVR3BONwIHyWmwgOV/iKW7jkXcRj2iDtnNt0yXsx0sTj53j0RL2HB1fUp7eRcS88NiK6EX8ciYXkMjxvfMhYXHOKSjkncItvzm9YGCaqKSaqjyFU6ifl7IX3SbnaJHgW/CJ41ky5EZ7VG5l4vviziFSmkQ3P8Lk2PNNOEc8yt9jwDLrFh+fBQ4LnqlYmnm82pFD7bvbDc8ohklaTRDwb/SJ49iv04hm2VfGMIARRZRCseCaCwxXyws2Kp35CGNBK8cxEmnjs0op43nWIeN6Pe8VT9jUb+48R0XagEtF4XAXRFYLor4ronSaiUQhF+0Y5w29WPG/dKHhOnSt4rrrzRniuaGji2eQnEWleQxuev/1kw/PKCeI5r5kNzx+a+fCcdFDwHNnSxHPQTRRqYjM/PDMOkvQSScRz+8+CZ8VTXjyX7VA88whA1DwEK56FJ4ln42b+eEa2VDxj1HQ7pCXxvHCAeAbgXvGUHBtvuolnQQvF82ALG555iudRaZtC9rTAh8bL4u/Z4/P3nG/6e74Al0hn0PeMuqcTJqe0VzM8y5jrIMnxxw3of2sR5SmL3LyFtLiEYLrpl88/u8huLd11wteG3+I9+FxQ+Q46lRof0hHCaX/VJuH2ptJ8918v6tz1k6jzapKpzo0l1Xm5ganOnnMEkYIGNnWenGP7mtjsONVZ0MT2NfFQE9/XxMX7RZ3fxJvq3B1DmRaCIyuS+FCf2ftJ+xa0zEKU/59EnXee8Krzolk9/jCozoIfveqse4Lq7NHEX50p8arOLkiSfpDiqc7Y/VTnrfGWOuUQ24VHqc6a8arOyHhTnSuhTuqmUafcX0U36KS5KNEf4zz/3rgAcH+Jvjceyl+syud8hugvww5iX3v/G9pr6T/XigL6Q376hk+8kQJeiDEVsHO25OGJGJsCnvrBpoCZx6iAJxrbFNC/sU8Bd+4TBTS91VRATn0KldjYrz459pHUjCTWp/FzRAELC7wKaG3WpyFELOoJBKsCphRQATsa+StgcXNVwKa9ug+2ORXw5V4q4HvcmwoIoQKSjlABH4JKBUxqbqtPWHrQ9kkhzUKo2T491UjxfGuNtk9zBM+mHW6EZ+P6Jp6u70Wk6vVteNaabcOzp5t4Vm9kw7NSIx+eZ/YInrviTDy716NQhbF+eM7aQ9Jukohnmx8Ez6HHvHgON/vPaAIQVR3BimfGMeL5Wqw/nplxiueYPboPII54dt1DPB+Js/AkWMYfh4jnPXGK551xNjwj7Hg2iLPwrIX3yfhrteDZ4wfBc1fCjfDcUdfEs90sh7T/de3nX82y4VnOIJ7oI/zxXNTQh+fU3YLnhFtMPJvXpVBTwGHh2Xc3SbkkEU/394JnPbcXz7nbFM91BCBqBYIVT4ebeLZt6I9nzC2KZwukiceoW4hn6G7iWQH3Jp6chBifHiSel29WPM/cbMMz0o7n5pstPFffpHieXil4Vpqta4Ltb4Tna9EmngXfOqT+R9vwfOk7G56/HiGeL9xkw/O5m3x4dt4leLaHQOqeIJpCZYDDwjNiF0kJJBHP92cJnhuOWuMRE89sAhD1AoIVz1lHieexBv54bmqmeB7aKcIvwSPsG3YSzwXNLDxp1WHcf4B4ft1M8ZzazIbnsso2PMc2s/B8qYHi+dkKwbPJLMGzfbsb4dm2jonnh9+ISI3r2PBs9q0Nz8GHiWfjBjY86zfw4Rm0U/A83tTEc29tCuVo4Idn3g6STsSYeHb6TvD8yxEvntPXKJ5xBCCqMYIVz75HiOcHMf54jmmqeL6NNGkH0pQ=
*/