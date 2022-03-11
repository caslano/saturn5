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