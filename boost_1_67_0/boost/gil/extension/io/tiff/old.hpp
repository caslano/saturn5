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