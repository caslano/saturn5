//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_OLD_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_OLD_HPP

#include <boost/gil/extension/io/pnm.hpp>

namespace boost { namespace gil {

/// \ingroup PNM_IO
/// \brief Returns the width and height of the PNM file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid PNM file
template<typename String>
inline point_t pnm_read_dimensions(String const& filename)
{
    using backend_t = typename get_reader_backend<String, pnm_tag>::type;
    backend_t backend = read_image_info(filename, pnm_tag());
    return { backend._info._width, backend._info._height };
}

/// \ingroup PNM_IO
/// \brief Loads the image specified by the given pnm image file name into the given view.
/// Triggers a compile assert if the view color space and channel depth are not supported by the PNM library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid PNM file, or if its color space or channel depth are not
/// compatible with the ones specified by View, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void pnm_read_view( const String& filename
                  , const View&   view
                  )
{
    read_view( filename
             , view
             , pnm_tag()
             );
}

/// \ingroup PNM_IO
/// \brief Allocates a new image whose dimensions are determined by the given pnm image file, and loads the pixels into it.
/// Triggers a compile assert if the image color space or channel depth are not supported by the PNM library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid PNM file, or if its color space or channel depth are not
/// compatible with the ones specified by Image
template< typename String
        , typename Image
        >
inline
void pnm_read_image( const String& filename
                   , Image&        img
                   )
{
    read_image( filename
              , img
              , pnm_tag()
              );
}

/// \ingroup PNM_IO
/// \brief Loads and color-converts the image specified by the given pnm image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid PNM file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        , typename CC
        >
inline
void pnm_read_and_convert_view( const String& filename
                              , const View&   view
                              , CC            cc
                              )
{
    read_and_convert_view( filename
                         , view
                         , cc
                         , pnm_tag()
                         );
}

/// \ingroup PNM_IO
/// \brief Loads and color-converts the image specified by the given pnm image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid PNM file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void pnm_read_and_convert_view( const String& filename
                              , const View&   view
                              )
{
    read_and_convert_view( filename
                         , view
                         , pnm_tag()
                         );
}

/// \ingroup PNM_IO
/// \brief Allocates a new image whose dimensions are determined by the given pnm image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid PNM file
template< typename String
        , typename Image
        , typename CC
        >
inline
void pnm_read_and_convert_image( const String& filename
                               , Image& img
                               , CC     cc
                               )
{
    read_and_convert_image( filename
                          , img
                          , cc
                          , pnm_tag()
                          );
}

/// \ingroup PNM_IO
/// \brief Allocates a new image whose dimensions are determined by the given pnm image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid PNM file
template< typename String
        , typename Image
        >
inline
void pnm_read_and_convert_image( const String filename
                               , Image&       img
                               )
{
    read_and_convert_image( filename
                          , img
                          , pnm_tag()
                          );
}


/// \ingroup PNM_IO
/// \brief Saves the view to a pnm file specified by the given pnm image file name.
/// Triggers a compile assert if the view color space and channel depth are not supported by the PNM library or by the I/O extension.
/// Throws std::ios_base::failure if it fails to create the file.
template< typename String
        , typename View
        >
inline
void pnm_write_view( const String& filename
                   , const View&   view
                   )
{
    write_view( filename
              , view
              , pnm_tag()
              );
}

} // namespace gil
} // namespace boost

#endif

/* old.hpp
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
*/