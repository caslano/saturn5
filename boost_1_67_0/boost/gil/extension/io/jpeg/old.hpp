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