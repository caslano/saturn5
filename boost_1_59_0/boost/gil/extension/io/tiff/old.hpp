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
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
*/