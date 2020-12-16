//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_OLD_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_OLD_HPP

#include <boost/gil/extension/io/tiff.hpp>

namespace boost { namespace gil {

/// \ingroup TIFF_IO
/// \brief Returns the width and height of the TIFF file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid TIFF file
template<typename String>
inline point_t tiff_read_dimensions(String const& filename)
{
    using backend_t = typename get_reader_backend<String, tiff_tag>::type;
    backend_t backend = read_image_info(filename, tiff_tag());
    return { backend._info._width, backend._info._height };
}

/// \ingroup TIFF_IO
/// \brief Loads the image specified by the given tiff image file name into the given view.
/// Triggers a compile assert if the view color space and channel depth are not supported by the TIFF library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid TIFF file, or if its color space or channel depth are not
/// compatible with the ones specified by View, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void tiff_read_view( const String& filename
                   , const View&   view
                   )
{
    read_view( filename
             , view
             , tiff_tag()
             );
}

/// \ingroup TIFF_IO
/// \brief Allocates a new image whose dimensions are determined by the given tiff image file, and loads the pixels into it.
/// Triggers a compile assert if the image color space or channel depth are not supported by the TIFF library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid TIFF file, or if its color space or channel depth are not
/// compatible with the ones specified by Image
template< typename String
        , typename Image
        >
inline
void tiff_read_image( const String& filename
                    , Image&        img
                    )
{
    read_image( filename
              , img
              , tiff_tag()
              );
}

/// \ingroup TIFF_IO
/// \brief Loads and color-converts the image specified by the given tiff image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid TIFF file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        , typename CC
        >
inline
void tiff_read_and_convert_view( const String& filename
                               , const View&   view
                               , CC            cc
                               )
{
    read_and_convert_view( filename
                         , view
                         , cc
                         , tiff_tag()
                         );
}

/// \ingroup TIFF_IO
/// \brief Loads and color-converts the image specified by the given tiff image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid TIFF file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void tiff_read_and_convert_view( const String& filename
                               , const View&   view
                               )
{
    read_and_convert_view( filename
                         , view
                         , tiff_tag()
                         );
}

/// \ingroup TIFF_IO
/// \brief Allocates a new image whose dimensions are determined by the given tiff image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid TIFF file
template< typename String
        , typename Image
        , typename CC
        >
inline
void tiff_read_and_convert_image( const String& filename
                                , Image& img
                                , CC     cc
                                )
{
    read_and_convert_image( filename
                          , img
                          , cc
                          , tiff_tag()
                          );
}

/// \ingroup TIFF_IO
/// \brief Allocates a new image whose dimensions are determined by the given tiff image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid TIFF file
template< typename String
        , typename Image
        >
inline
void tiff_read_and_convert_image( const String filename
                                , Image&       img
                                )
{
    read_and_convert_image( filename
                          , img
                          , tiff_tag()
                          );
}


/// \ingroup TIFF_IO
/// \brief Saves the view to a tiff file specified by the given tiff image file name.
/// Triggers a compile assert if the view color space and channel depth are not supported by the TIFF library or by the I/O extension.
/// Throws std::ios_base::failure if it fails to create the file.
template< typename String
        , typename View
        >
inline
void tiff_write_view( const String& filename
                    , const View&   view
                    )
{
    write_view( filename
              , view
              , tiff_tag()
              );
}

}  // namespace gil
}  // namespace boost

#endif

/* old.hpp
nENxhGcQ1iJsRfgY4TDClwgnETwI7YB/FcI/+r8wbHgmVvKR3svzDMud79M03ck8vnEDNcWJdFyiOpJf51EdmKdnTB+tPXdjlrkdMJ2u4pkedvlMZHIL54nna7ld7jso9kzjJiLLRcg9HC+W8QWY9b0seELvZQX2HmBTFx3GRCI/lMwzqVG7IKcdXk+qgE295xpjLXGBR0cXrVJKBH0Wobsn0BJQX2rcQn11km8gniVo8wltJ9D0mYzE9vXqTi54OFBgCEmL2ByguVu5YhEtOUg0VekEWf8CR02g7+kty7hXieD9SNSwZRFlVxq5ZkMUdbUXo+5ipmhuabCfQZq5rcGeht7wkLdyeZMBE7sYKsS7s4Hugd8BF+w8fl0lO5w3veoIpCwI4GgOZcpBnDc59JJtvGQhniVImYhmSjQD0QyJOgnbaWCn0EuK8ZJIL4nGSzy9xBsvfemlr/ESp3qGoZZNaZq0Nq+C7hDV2d7x4teWBFGrgWdbKHNnp7BXWznGvez+tVzt4MGdrgeaInxijunuBiLLtzRPmMNROpz2NZIMf/Gsx2OO4SeoGmDUGQvLYpFPBkdWh7IlzwauYGRiNUvLCRoq/zxORviUO3zSFCPp1xxA+gNI1x/xSdOK2+UcexdLUwc+GY0jxHRCnABElwAfJmAiAW0iS3cQoA8AXj+i94GWeW7dDUiQLMgLu3PkRmYhI3mLQrSGd9D8r3iZCNsyCBS/VchbmbytlrdSfjOEbZkhTUASo15TzrwStP435CzbT86y/OUs00/OMnxy5vTJWYqfnCX6y1m8v5z19ZezOH85i/HK2SasxWkVxA3L8jUiU9ps07jL5KwvvCfD5+fD4kGZL1imsek4CEG+0nDTQqwc5Vfv8+5hAcPtYyaRgHuo35MPrUYbiVY1uj1xSRmWLgPsGuFxW05pYCk4vSMUrfWxum0Mvx7Hq+o8Fk2+I4jRBuAOKXQURsVr1YMTvL86NgRZjPF0zQ6xDwXNdIynwUjRHwIBlTlRatBg1ICMuBdSGeu4vA85QR8dxMMEcxnEqQdYjBZl66U5oGI0+HH6ykZVdZtxJBtoWHM7eTNmybAEq9eR5qT7VJnhGLXlPPXqvPOD50c4rVt2O60v1d2HU5RRAbjgXLDb9a07AhHcc3daHbh0uoD1F/PGyIbiGSqNNAG5WGT42d8E4VR2cFogTk5gfhPqOkl6ERsWNLeAO2lGdyjjPsxCKybebVCv5Grr8jQP1nF0HtRTDAXnbBf9A61jPsoQC5XwCd75aj5QUgXlSUJ5LYMnKy9xrBfROZgxdm0X+0+WFR7/6jUvN0vlcwpqgM7XrkCycZvYiR0CyXEgCdDfAFJdUEv9OVmUUk3uG8/nX3F8C288430gWftTba5AVrYcpPNPgQ+sAzwgw2hf34r7XeTmuREyr6Elqe6oeAY9zaFcWyGjOODxLUcM3/TU0GJ6qm8xPdW2nJ4qL5ueKlpOT1X8+qFXAeeb8MBGDF6+oaPcf+go8xs6Sn1DR5ExdJgjH1Y0Tu+YkeM/ZmT7jxlZ/mNGpnfMeIzbs8ndnc5/q5ix/Q5K93rlVn/eoo/w0+gzGroRc1T6LN/+RH8GR3kYUFvGiISpsWxntQMPm1YDM6XwANNM6fLf3/RaVdM9j0pihQqfZVpVP7bFsKp2gDdsVGnL3+fBay1eqWaIViIaJ0sBg3nrwTjWT5wRjCpg9DVbg1M2K0kpQwqJCB9nyHbKWZze4NAuODVsnhgnDzjCOVcFaDoZ/U1uBIf2QxpNBXatMIoxxq/WVoZLtvI07NhhWFXk/f3FFPqTBUVBDEIcQl+EeIREhBQyjbpBpb/J87W55lyL71ffpKM=
*/