//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_OLD_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_OLD_HPP

#include <boost/gil/extension/io/png.hpp>

namespace boost { namespace gil {

/// \ingroup PNG_IO
/// \brief Returns the width and height of the PNG file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid PNG file
template<typename String>
inline point_t png_read_dimensions(String const& filename)
{
    using backend_t = typename get_reader_backend<String, png_tag>::type;
    backend_t backend = read_image_info(filename, png_tag());
    return { static_cast<std::ptrdiff_t>(backend._info._width), static_cast<std::ptrdiff_t>(backend._info._height) };
}

/// \ingroup PNG_IO
/// \brief Loads the image specified by the given png image file name into the given view.
/// Triggers a compile assert if the view color space and channel depth are not supported by the PNG library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid PNG file, or if its color space or channel depth are not
/// compatible with the ones specified by View, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void png_read_view( const String& filename
                   , const View&   view
                   )
{
    read_view( filename
             , view
             , png_tag()
             );
}

/// \ingroup PNG_IO
/// \brief Allocates a new image whose dimensions are determined by the given png image file, and loads the pixels into it.
/// Triggers a compile assert if the image color space or channel depth are not supported by the PNG library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid PNG file, or if its color space or channel depth are not
/// compatible with the ones specified by Image
template< typename String
        , typename Image
        >
inline
void png_read_image( const String& filename
                   , Image&        img
                   )
{
    read_image( filename
              , img
              , png_tag()
              );
}

/// \ingroup PNG_IO
/// \brief Loads the image specified by the given png image file name and color-converts it into the given view.
/// Throws std::ios_base::failure if the file is not a valid PNG file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        , typename CC
        >
inline
void png_read_and_convert_view( const String& filename
                               , const View&   view
                               , CC            cc
                               )
{
    read_and_convert_view( filename
                         , view
                         , cc
                         , png_tag()
                         );
}

/// \ingroup PNG_IO
/// \brief Loads the image specified by the given png image file name and color-converts it into the given view.
/// Throws std::ios_base::failure if the file is not a valid PNG file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void png_read_and_convert_view( const String& filename
                               , const View&   view
                               )
{
    read_and_convert_view( filename
                         , view
                         , png_tag()
                         );
}

/// \ingroup PNG_IO
/// \brief Allocates a new image whose dimensions are determined by the given png image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid PNG file
template< typename String
        , typename Image
        , typename CC
        >
inline
void png_read_and_convert_image( const String& filename
                                , Image& img
                                , CC     cc
                                )
{
    read_and_convert_image( filename
                          , img
                          , cc
                          , png_tag()
                          );
}

/// \ingroup PNG_IO
/// \brief Allocates a new image whose dimensions are determined by the given png image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid PNG file
template< typename String
        , typename Image
        >
inline
void png_read_and_convert_image( const String filename
                                , Image&       img
                                )
{
    read_and_convert_image( filename
                          , img
                          , png_tag()
                          );
}

/// \ingroup PNG_IO
/// \brief Saves the view to a png file specified by the given png image file name.
/// Triggers a compile assert if the view color space and channel depth are not supported by the PNG library or by the I/O extension.
/// Throws std::ios_base::failure if it fails to create the file.
template< typename String
        , typename View
        >
inline
void png_write_view( const String& filename
                    , const View&   view
                    )
{
    write_view( filename
              , view
              , png_tag()
              );
}

}  // namespace gil
}  // namespace boost

#endif

/* old.hpp
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
*/