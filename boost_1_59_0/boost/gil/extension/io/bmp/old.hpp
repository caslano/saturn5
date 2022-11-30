//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_OLD_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_OLD_HPP

#include <boost/gil/extension/io/bmp.hpp>

namespace boost { namespace gil {

/// \ingroup BMP_IO
/// \brief Returns the width and height of the BMP file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid BMP file
template<typename String>
inline point_t bmp_read_dimensions(String const& filename)
{
    using backend_t = typename get_reader_backend<String, bmp_tag>::type;
    backend_t backend = read_image_info(filename, bmp_tag());
    return { backend._info._width, backend._info._height };
}

/// \ingroup BMP_IO
/// \brief Loads the image specified by the given bmp image file name into the given view.
/// Triggers a compile assert if the view color space and channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its color space or channel depth are not
/// compatible with the ones specified by View, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void bmp_read_view( const String& filename
                  , const View&   view
                  )
{
    read_view( filename
             , view
             , bmp_tag()
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
void bmp_read_image( const String& filename
                   , Image&        img
                   )
{
    read_image( filename
              , img
              , bmp_tag()
              );
}

/// \ingroup BMP_IO
/// \brief Loads and color-converts the image specified by the given bmp image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        , typename CC
        >
inline
void bmp_read_and_convert_view( const String& filename
                              , const View&   view
                              , CC            cc
                              )
{
    read_and_convert_view( filename
                         , view
                         , cc
                         , bmp_tag()
                         );
}

/// \ingroup BMP_IO
/// \brief Loads and color-converts the image specified by the given bmp image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void bmp_read_and_convert_view( const String& filename
                              , const View&   view
                              )
{
    read_and_convert_view( filename
                         , view
                         , bmp_tag()
                         );
}

/// \ingroup BMP_IO
/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid BMP file
template< typename String
        , typename Image
        , typename CC
        >
inline
void bmp_read_and_convert_image( const String& filename
                               , Image&        img
                               , CC            cc
                               )
{
    read_and_convert_image( filename
                          , img
                          , cc
                          , bmp_tag()
                          );
}

/// \ingroup BMP_IO
/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid BMP file
template< typename String
        , typename Image
        >
inline
void bmp_read_and_convert_image( const String filename
                               , Image&       img
                               )
{
    read_and_convert_image( filename
                          , img
                          , bmp_tag()
                          );
}


/// \ingroup BMP_IO
/// \brief Saves the view to a bmp file specified by the given bmp image file name.
/// Triggers a compile assert if the view color space and channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if it fails to create the file.
template< typename String
        , typename View
        >
inline
void bmp_write_view( const String& filename
                   , const View&   view
                   )
{
    write_view( filename
              , view
              , bmp_tag()
              );
}

} // namespace gil
} // namespace boost

#endif

/* old.hpp
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
*/