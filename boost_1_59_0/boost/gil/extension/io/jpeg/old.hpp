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
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
*/