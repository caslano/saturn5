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