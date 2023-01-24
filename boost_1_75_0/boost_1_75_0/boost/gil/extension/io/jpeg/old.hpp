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
ms2bMlwsOAV/pp7PO3rIT0A95g+tSLhU5LwxiJ56Nw+8m6dur0L0j3BSIUKhVxjyNlZNawjZ7nxBeq4jej/rSw3ihPGTMNb1eDXkhqbQhDw/Taz5NXlf1vtZMZ5hhokMSp9UC2EWqqWW3jP7nr7jkQuJ4xMJYYKvy0RlUeFGUXpUNa+EqjC4/QabuRuBJVMM0tJjo3JLa89LHlYQrdLm27O90McM4b8FFyUlemr8o3S99qw9tUYk9dtP6G+zskmJalGjo9Ubo6Ow2FYQ2c0Ui7wkNcunqvVu3VN6kbmAu9ysYUz/b+rhImaMTTq/YQxyHdcNQIPb0gPZYPnxF0Xq1Vjhv2QbTzDoF0Qo10iE7WiqRjhxBWtvviryjln/pbdKrhEl1cLzCP/CRepbQulu6qIgUInVeWaJsbvqcaDZmMqVHr7ys3MDbZ4sf28i3zjJKfYQiUgpwGx5Aa2m6PAvMM20trbxtvckUDe8ouL+TEyPYXRP8HhlMeZXJoEfV7C+fb4EFoO2X0Pt+Ve1Lxx1hwI1fB/Oc0WCzkeoYXegtneiH+f1h745O0GhJ13uGfTbbf3hLIxp8oMfLO+Nn6jGsp3FUebBPver1IPpT+5JKXRN14o4YBKXgqzCwUSA99oHiZy16YDvbIEz6Sdf9J+qw/FJEuU3FpUpxMU+icXXCAe1+TYprqsnhw0JrqtyPmeunMd8PmemnMdgBa1o
*/