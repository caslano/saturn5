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
wBFHRpIz9rlC/Hlxn445LFNRLTrTUwNRHvUg0cW1oJW9AzBufJh6THm62CNGxBOGyIbRtNxaJ2fQLrmqbNSZJVPHZvctDaJkE2YiJDdhNZLDkH2FXKJW4gL/KrS3BxcPhEnp5Lo6kRtem1z2978V4fypXOsm67NCscEaPfdJ2Mvf2QnLa51y8iK403E1bTn1DU8izfjlcNlVFo4t2iaX8WQ1TqVJ+wlUrk2VpY6tw8V9OoiTrcSw5PFzxs4iYT8IiIh+04rs9GRFW5EjqkjkcnpZzCjfSpSJ5LfckdVBhLCs48arXGninqjNAkPqErQLj5fkL+vJai8vOI4ku6l0D+olQy9peknVS7JeEvny5kHSiN+XH0QAU3GRDRVouP4p/O6y4Re/nDrC3iHm3x+85lb+W+u7W+glTvIf6MNQZPo4UGR6canIlLlUZboDMvmPR/4p+VJt8pX036b4UcAWFn5FKtlZvRRSnnBTwPwx7Fv0oO2LWkG7dlSnbXfKkldWdUQJVtU69HKFCfwMZsGmBdhLvF9e31m8z51IFTdcAY7/tOdydwwQBNuoVm81tZoIBAcO/Jfwe+Fa/Q5PCbxGvwPozs4n/3/ad7pfcViI9zURL8hChqZXlGOaPsVFNu4gQ/9afura8sMpIick3ycH0l2DnKyqr4X0+lo0R32+CGAzMyBZGp0uyWwc+4QhWvGXAWhG83Gb0A5UOZBu2GU9cDSRrreawJ8BjzwsjaU4bnYy92ufvkV6vx6IY2T8DdlNx3vBD9ozoCW5PPAXWfz4WjbTdBFmJJ2/4knrfyp+Q/rjS0j0OuHBmpqcHGHMPMhhOUftdPLLBj96opx4anwg44a7DBkdRAdJob0bL/kliYc2GOeu8K1tKP34UKVtIo0vuCsstX9yTE/68WR4UChIhUoKWvAL1QxCkTFN04iSNF4laBJmTAAdhDDKyxlGvvQ67XY7J/RDByUbmDBV6NiCZ11gapXdBpM53QLQRsYvzrH54gMORatyJhsHGUWixIFQe6TbVtbYbLB06SVDKgIbwv+b0eBA5zPNLt+NitP1EG5bOu7h7QZn150otZgP6lLSMxPYh5B34UDnsFUDncVLBjr3rhno3LkA1xWgr8Nv0UBnwXqGSYQ8ipaTF6YRLOaVYNwGxu1wJ1B15DSwb5xX1eFN+7ltYaCs8z4E68OorZhdv0NR4JKgzZwQysJ1q+S12Ciec6n2yH1tWub/FuSgd66sGm1adogPVhfp9ZqpX+w7UJ6z57OjOohe2Pk6vsnpOeOY/5eKQs1tUoTq0pr51ZXZTm3ZehZ5/RGHcrg4HOs+6k15uPHGGpSY8cEdWNdfRhlCXeMaUM7l0JHrO3kWI9nvIuEhXIsWFn3T2x0eOZ3+WjI6uXajFiCJLUc9HimmzQ7zJtTIOiKEMHMYJCOu7VJjk3OfCyi4E/l5oKnk53Ii8jNrHurnN+dkv0JbpbuSuHCyyHgHQfIyPYDJ/Rq45Bk8HW4na3hRJfqBRC5ox6ikEyS1UFK1DkI6QFJdkNC0fdFBv26R/lprCBCl9NcTQc9T+l9Iv7pa6MOS9OuNRT8s9LFwEGWlc4cffUqQw0pnKOmrlZ4X7GA6PvqPMpR9Z4qyem4D6YqQukzE8yk+F6kIB3E/L0L5buNU9ifQk37Byxm6BKGYAWbrcacTjc810rdmJIbtC+HJh0p/10dPjzDmyBsT3u8YiEZhDsojDkIN4CfM8bV+ax0s3ZDV3uckfBMXLEJs2HyFx7/Gz5cx42B20ZOx2LRVl/ddY0ZzJYnnjDY2D1ldOdfB5+6Nbcv7vX4xl/d7yvL+R4UerMJ3j/Nf3q/VGY+6C88TFX9E5mI=
*/