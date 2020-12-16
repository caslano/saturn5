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
7+Aq+P7hrreE7jxfsFQONUaRM4fofRSHcjWZYTR31atImE5TnhraOOt1aEbT8Zpe6OzYgG4d77Rx7L9j4O+SsMgpzskTp+/6zRWt5eXmhU0MqrV1NNTrifCXoo4DOfk280f6aBRpg1BzdvfU/N315SVOC2duDSOyB8HkyDuNV/Rl93TVqfKq2GdFjr/MtQfRmPEt8ERbgz4Hu42agwM3VW6DRcWFW9PfKPyr/tbaJFx2vCrzamWdVFlnrawLZZWUdbLKauObhWzQR+HhZDcPO7Tv5h+d9rvVQHN6mxN0nOf7Z/hCDvjtNfSk/h7WcGl4DY7ejdXeUy9EXg+VBwKlwTJfNR+2d/MIbPMHWp5hTpE3mFMhB9dj+/XTGnSOUh87cJDWQuHe1WZgv9iobYaF21AXCEUmjJ8YzKklfnwl0fCTrePHoekWitbD0XzYJd/n6OohjSPww+Cd4VPnCdTetkbPJaoPW0CXoCFm+Sq94QPSu919RdaTl5NXqNn8Tl9NVV8KMPzfHyq0iF2b8wiFV73WPRfbTYsMVuQP6XtYI5s7fFxiuew+bcKR+cY0dbVhlFCZtXpfHp6EuPWnbUerCbEuplSTjtUG21s7fBb5c6PgMzcqPl9qQomNJ1v05QQ1325Mczseb5uiyelJiRnh8IdTn+qutzWltvftrg+H8B1YZITrJw3se2r4LB3RChsPWh+ZWhtnI0LjwWyt3nldk8ET9Xo2G3T99WgT6oIBZGkoVAFZ8TInF/wc4EcC6HEuh16rHd916ic3d+i+tDQUoXulH9z0rpXPd8rpTqO3G6rK57rGdNa1QGvjfv9KVefe8nX0gpvuNXq4ooqOy9RCHHydf3AdhrbF7VVtzmyu6zxkd54vGDkT5qZv93avMz+9DUjX8X2ZmoNFamoOIf292arejohpMFnklJcfNHfnXd0/0fDvba6Ve+0rxktyFP5durzEN6O0zO/Iu5rrVYDLocV2auyoW8naOnKba+1c8HXbHc52sxZHK6vmJ4lT7gv362U0/xytr8JIeaG3rNQbQBaJHt+w69gTK/KGN7GCzLy0WPN5Z6r3axCLDgyL3e3soTSdEa3e2vVmspE+Sp02ZV7OwZWywsLi2Kr5XtdUnRYrDTo0YIn62srV6PvfS1x2jAsHru3v7gfVl7rVZcCXVwX/cgffeKyqD8uGuZByKyc012RJjLLNLqLs6PrkLZGqsiWqXYJJWa3sAWuDNFRiBUarr/PaqOuc3zwcN8hMzLRPU8dlpnJEo8yJFVxLfX6s36u1cWTFSlXnfl+X3zfQxh+bH/X9m7Q61/vO/G5pXv2EYLGvOC9QKU797a760nB8y6lf5aoPuerXuOvLgiX55QEbR49Sdwr4GGXZ8AofT6myb7SyN1RZqlb2riqbp5V9qMp+0so+VmViVJX9g70zAY+rquL4mRl2ELpB23ShFChQaUnSdJUCaZK2sW0SknQBAkO2tqHZyCRdcEERQRBERBAQcGHfBEUBkR1ENgHZEZR9E5WlrIrg7713586ZO3fSVP3c+b7LpP9z3l3POffcc++77yODPar4NtnBYPEMNtRgX1fP7mywPvXsIoPdr55dZbBLFV+XwZ5T2JcMtlUig10A1gE2UvFdZvjOVNhVButW2DUGG6Lyu8lg76j63W2wQvXsQwa7TWFPGOxD9eyLBntZ8X1ssC1VX209PGrHOMW3u8YGqm+BDc/Rt+sG+/Yh5g63sUF17oFT9Mrmzlc82MIMT2TtLN+nFV/K5VO2eaHhc8qz66YqRW9p64mmJHZqDmNdlmLaQClwYMTLz9zRmucBa0OWGH70ylYu3R9LDc3XzsnKZzA8rIvCZXbkENY=
*/