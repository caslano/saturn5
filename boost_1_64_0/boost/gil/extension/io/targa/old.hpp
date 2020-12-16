//
// Copyright 2010 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_OLD_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_OLD_HPP

#include <boost/gil/extension/io/targa.hpp>

namespace boost { namespace gil {

/// \ingroup BMP_IO
/// \brief Returns the width and height of the BMP file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid BMP file
template<typename String>
inline point_t targa_read_dimensions(String const& filename)
{
    using backend_t = typename get_reader_backend<String, targa_tag>::type;
    backend_t backend = read_image_info(filename, targa_tag());
    return { backend._info._width, backend._info._height };
}

/// \ingroup BMP_IO
/// \brief Loads the image specified by the given targa image file name into the given view.
/// Triggers a compile assert if the view color space and channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its color space or channel depth are not
/// compatible with the ones specified by View, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void targa_read_view( const String& filename
                    , const View&   view
                    )
{
    read_view( filename
             , view
             , targa_tag()
             );
}

/// \ingroup BMP_IO
/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, and loads the pixels into it.
/// Triggers a compile assert if the image color space or channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its color space or channel depth are not
/// compatible with the ones specified by Image
template< typename String
        , typename Image
        >
inline
void targa_read_image( const String& filename
                     , Image&        img
                     )
{
    read_image( filename
              , img
              , targa_tag()
              );
}

/// \ingroup BMP_IO
/// \brief Loads and color-converts the image specified by the given targa image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        , typename CC
        >
inline
void targa_read_and_convert_view( const String& filename
                                , const View&   view
                                , CC            cc
                                )
{
    read_and_convert_view( filename
                         , view
                         , cc
                         , targa_tag()
                         );
}

/// \ingroup BMP_IO
/// \brief Loads and color-converts the image specified by the given targa image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void targa_read_and_convert_view( const String& filename
                                , const View&   view
                                )
{
    read_and_convert_view( filename
                         , view
                         , targa_tag()
                         );
}

/// \ingroup BMP_IO
/// \brief Allocates a new image whose dimensions are determined by the given targa image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid BMP file
template< typename String
        , typename Image
        , typename CC
        >
inline
void targa_read_and_convert_image( const String& filename
                                 , Image&        img
                                 , CC            cc
                                 )
{
    read_and_convert_image( filename
                          , img
                          , cc
                          , targa_tag()
                          );
}

/// \ingroup BMP_IO
/// \brief Allocates a new image whose dimensions are determined by the given targa image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid BMP file
template< typename String
        , typename Image
        >
inline
void targa_read_and_convert_image( const String filename
                                 , Image&       img
                                 )
{
    read_and_convert_image( filename
                          , img
                          , targa_tag()
                          );
}


/// \ingroup BMP_IO
/// \brief Saves the view to a targa file specified by the given targa image file name.
/// Triggers a compile assert if the view color space and channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if it fails to create the file.
template< typename String
        , typename View
        >
inline
void targa_write_view( const String& filename
                     , const View&   view
                     )
{
    write_view( filename
              , view
              , targa_tag()
              );
}

} // namespace gil
} // namespace boost

#endif

/* old.hpp
FLusjiJXHtdHV/qzsUuG9QMVeW7YT6RASikNvHSyjOma7XHUrrT7eh3rEwWHrS1EseQ+FlRZJ2jJlS1wtSybqEzOK1SlL6rodjX8TpbUOsQPFW8ECnJAQWVLVyfLX5G46LLe7r9o/ZPl4ztoSLqTXWRkLxyWY3A02NJ/VKCu/zH2MHPCmVZGLkiQGFpf/hP0SUfXxK4S3q4G7ep+6zoo4wVI3przHgp52BahL954OWzXIW3NWcDOVoZ1XYVY0p4ktZPkOWcLu3u556y5rwOAjfVJWlpna495OuLfKZ4E/Dvdld92WCeaRy396GF17K+MR15XvFRGI9EWCc125JI0veeZP7EZXZmvczvRANhmTGji1c0QgLeosonveDy14I1MK6u06MNgz2W2JepucWazTpqnsbiDyQxUZrmw4ryi2abpDT0vG9p3L9v46tsNG38FKUINekvaI9Pq8Is2m+X4v5fG/+aQySf/2UUq218fd/X/iPUJbEt11n91kFlvXW8ZgUbSzsFptq6LfQRp9aKTlioa81Gz5kwzUWTD2yj9IZM1J6ivxTMKTT4aLLAYtG5yqT/YC7IBWFRphUH0HTdZnTs12xX0C0uhXP+M7uhCzq0QYOEpKzr20W2wN1jmWPsAqv9F6pEg09ei6Hgk2JY/wCQ+DUg7NFqzPXRRsmkUnmRrX3qCDdOaLiyXFbfphmk4yaVCXN/EDHoRpaKIkZzzNHGp26W+V8Y5c6/MaITGge9SiH1umk3kGgSpoZKHZBf+iq5b0HUPCWFTh1APKlNoSFRQD4RJJ/UbzbbqgiT18wtMhKUL+wY/sO0sMXyD+0CxGCjJPJ4GMm8KUHpLw/aLfmrC6uQ7Fa/Z5l2UGvWdWIKarOFuDX+2znqTdtnkK2msRJ+lGEr0T/JiThVxoZda+xD1uRWjSWrtV/PVoMEw0um0Xlh0wLBvcffUWy9kqkL93q1eED0ZY6mI5GcV8SIGnmAwn7VlQzI5nr7rmqeJQw3MvU4GcGZUPdd5u9hbhF5UQ1MyoQYJsI96yQ5RgpIeJd7OnY54v8LMmKXuQK49v79ZfImSQhm72AG18OCVKuTgiUHWhNIzkAYlLlUSUdc5vu0Axwqoi/aRI0fI9eXv+kPqfmZCxj1XSuwcX/R1AzYKOHmfLjG1lCuTqLaRSr5rsj6TFvqlWjjFD4+xwl7tzAo7rj0rrP3L5VzL4m8TqbBqiAw/S6kCcCKqKDSn9j1Pc2pe3xjrOnOO39Oa58NS2KcqXlumWtfdb4LfnOP3CpfaN8Y15qFIV0lkaWg6a+iVIVjk+U6N7tY3cmYnl/pQDNTFDRp8/pb2L4cT/JidrqIfzXnRwiq74Jmjt96zoyem582eyLRdlU0KTWylq9Aytcgt57Up1fpGYgZvS23EZqSnUTSKGvReKjYrSAbTobN4t+bcjYR1XRPNlsLdoHk9kG72nuXC5ijUK0Qj2bAH5Q7wK2HAEPsgKZ1z3+kTzzm7Wi0dP2tOSxNZsF3WnCZIsE2LoJw8HmRbSbhDKfozjgxYipv8GlHBAih1q9V29Zyo2EiEWRe+THPO3kzYlsBGvfyo2ANQO1SLZ6BtbrVKrEKOWkVTd29aArrV71zkJyGXU+RN5vulH9tBr5wpYZ4xanq3wd8YLUv2UMnjKKEBgca1LaI3mu8hrAsmgSX2r01S6Q58Y1aItm4odKN6kl3dQuYM/hM6xwM9NMrtI0Y9GmCd0N8MrVexjno4Rit1LcnuEm+S66UE3Z9etNfwp0XZ16ElShOWiXR1iaepIJd4mi4ugxC4ABirvECosuc//JRY9g1zjsx3vJXpDiCH2SLEbEZbAUvtbSTGf82B0n4udS8=
*/