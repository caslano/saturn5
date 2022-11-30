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
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
*/