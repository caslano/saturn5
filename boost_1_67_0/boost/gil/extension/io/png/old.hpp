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