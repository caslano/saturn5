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