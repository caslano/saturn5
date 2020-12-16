//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_OLD_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_OLD_HPP

#include <boost/gil/extension/io/jpeg.hpp>

namespace boost { namespace gil {

/// \ingroup JPEG_IO
/// \brief Returns the width and height of the JPEG file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid JPEG file
template<typename String>
inline point_t jpeg_read_dimensions(String const& filename)
{
    using backend_t = typename get_reader_backend<String, jpeg_tag>::type;
    backend_t backend = read_image_info(filename, jpeg_tag());
    return { backend._info._width, backend._info._height };
}

/// \ingroup JPEG_IO
/// \brief Loads the image specified by the given jpeg image file name into the given view.
/// Triggers a compile assert if the view color space and channel depth are not supported by the JPEG library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid JPEG file, or if its color space or channel depth are not
/// compatible with the ones specified by View, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void jpeg_read_view( const String& filename
                   , const View&   view
                   )
{
    read_view( filename
             , view
             , jpeg_tag()
             );
}

/// \ingroup JPEG_IO
/// \brief Allocates a new image whose dimensions are determined by the given jpeg image file, and loads the pixels into it.
/// Triggers a compile assert if the image color space or channel depth are not supported by the JPEG library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid JPEG file, or if its color space or channel depth are not
/// compatible with the ones specified by Image
template< typename String
        , typename Image
        >
inline
void jpeg_read_image( const String& filename
                    , Image&        img
                    )
{
    read_image( filename
              , img
              , jpeg_tag()
              );
}

/// \ingroup JPEG_IO
/// \brief Loads and color-converts the image specified by the given jpeg image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid JPEG file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        , typename CC
        >
inline
void jpeg_read_and_convert_view( const String& filename
                               , const View&   view
                               , CC            cc
                               )
{
    read_and_convert_view( filename
                         , view
                         , cc
                         , jpeg_tag()
                         );
}

/// \ingroup JPEG_IO
/// \brief Loads and color-converts the image specified by the given jpeg image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid JPEG file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void jpeg_read_and_convert_view( const String& filename
                               , const View&   view
                               )
{
    read_and_convert_view( filename
                         , view
                         , jpeg_tag()
                         );
}

/// \ingroup JPEG_IO
/// \brief Allocates a new image whose dimensions are determined by the given jpeg image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid JPEG file
template< typename String
        , typename Image
        , typename CC
        >
inline
void jpeg_read_and_convert_image( const String& filename
                                , Image& img
                                , CC     cc
                                )
{
    read_and_convert_image( filename
                          , img
                          , cc
                          , jpeg_tag()
                          );
}

/// \ingroup JPEG_IO
/// \brief Allocates a new image whose dimensions are determined by the given jpeg image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid JPEG file
template< typename String
        , typename Image
        >
inline
void jpeg_read_and_convert_image( const String filename
                                , Image&       img
                                )
{
    read_and_convert_image( filename
                          , img
                          , jpeg_tag()
                          );
}


/// \ingroup JPEG_IO
/// \brief Saves the view to a jpeg file specified by the given jpeg image file name.
/// Triggers a compile assert if the view color space and channel depth are not supported by the JPEG library or by the I/O extension.
/// Throws std::ios_base::failure if it fails to create the file.
template< typename String
        , typename View
        >
inline
void jpeg_write_view( const String& filename
                    , const View&   view
                    , int   quality = jpeg_quality::default_value
                    )
{
    write_view( filename
              , view
              , image_write_info< jpeg_tag >( quality )
              );
}

} // namespace gil
} // namespace boost

#endif

/* old.hpp
hvPx7gBtsnZ9lrDrGsD877Ksgj4cL12vP2zk/FjPczg/1tmUedchTVxu7jdkmz9MylxvHj8fjCvW3o6wcnIf8dJwqXxrVLjJ1i/Kwm1Alu9wZd8bmuz7Dg9/CPDSdlu893a8D9H4eFSTzmBUfOu3JynHyZNUD/uLjgZtq/CXAI+UNnazcC6Cv/nK9wA1N8kxc6C7Y/EZSwL3IQqQPEN5opBXvqMt8p78sYZ3jL9Nixz4Trh5wG2ddi3SznGbxwhdmHxZF/a9W+jiOND2qTzrbbenh+8U0cPxQg97tB7OWLTY04MDsR6uVfI70KMLZd3UqNFFwTnN6OJgHOnoafI9rEZPl++NXl03e3U9z6vri6iMi+m7fC2iPBt0efzCiJJkAuXoUFwGfR6d5e9UBdmX8e+wJ2ejJ2ezJ+d6ltP6GueznLoMa5adEZAT70JO7jf4EX0b2vNJ4LUANIcqBe7kQ8Dj5qFkozw2pGXbRk9wMtLItrpHKb4HocPQRJPYfTRlbzVyD6vzyJ6fhvc909qzifsaHnKbpTQpNCts6Ezed+nP6Z5BfdUp3Kcy7ZQxYwHRntrk7ck0Wbo09f2Lmkr52cvXg+Z9WlM5v2V5e9Ppz2gqEztaYT9k1unl+FTYjjWfZxV0FW4TY9izLZzn02fj/dnSnrx5znOAF3OEovO4cz2aqXNR2Jtni43Uz7p8m+n9Knrf8bRS3zuLD0fMaXynAPFeymeNNPLIDb+B/qyS31JPg0ZeHuHBxDf3tkPma7x14UqaP7xG6H6VZ7+rm4Jz6TViDgAc6xC8Dc9egdffePqw107OJ34Dwo/g6DXswYYg/WBTEN/rlWGdV6/b6WGZUK/rqZzL8b8r53NlmxY2IXlf1ERrGC8G31/DvIDa/gSt1dg3VVfctx0l+ks9ep3H+fRI+hjRd3t1kyM60Ju6GfHkdWsGX94E8Qt7vs7zPX7JpuB7E8dws1+P84NuuG1+Q/pXkF+a8ruE5cc+hIh7ayA5ZJnzYZvmKMKdU/o+MGzO9K3uGOQrwXwg79lPUP3rNjxJc8UNVThHVpr3v6m7EvC4qir8kiZp0ALTtEmnaYq1QK3gkqYLtWLbNJk0KWkSJmkpqEynyaQZmGaGWbqxlUX2pYIKiCIuICIibqwuICgoLqCoiBuIC6KigCgKiv+977wz5528SSaIn5/5vvdl7rnnnnvuuefu557bBTpMlwHyXWKhUyfWF/cVTqr37xfCPpfxTlH1eCrJ+Rqyq9pD8jpNyOvkev+dmvnyTXW2S8OAJ+zPapX/62q7nwMn56kh9zUqgp9h5gx2/w5+5Mk27UwxR5g3CTnfXiHnNUH3rqTNtfQXy7bcDAu5PnCTQwIv7NCVbfRyEpffNQS6304KiNZBkQubYdeH1oCXw8sdv714b8jaRCXADdPpFPRdP1w7XbnynWvyY2SeaUrlHS/dJofePRpJ5/JG6IKPzY584yuVHE4YPvDI6mgx/YjEEXLIOHiHC7zgxADnt/40O31xxTLscaQ/puI913NIj0zdg6/Ks0Td73Wk/Zapclv3Guizu7pG2fKdQ/p8rtDnnfR7N+mzOz8Cu5mE0OcCh88Hfq0DFc2kMItgnYeO5M1GM9fFg1ZHhuGTm3GgG9Ywk9sA7ntYASwjP2IXiPI2l9XuqQ1T/3WRGksurnc/OZbsJRm8W8hglXrT9tJ6e06HsHyneIrzHsAD+79J1Q3u8oi8L6v35325yhvxNu8rxPhr+LlHnZ1cKeJNGh3/QTEmee/v3hdwV+xDJB/E+fYFPlwPfDGWyXHlI97YL/AyNf79ho8RXcB9dXQt4UteP07zhLwJQWZi7wx6o94tAe3rifYnSZY=
*/