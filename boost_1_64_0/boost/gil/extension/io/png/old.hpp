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
dN8KfXorfvvETrp0uNdvcoSrR6sD+s7Dy+w7W0vo2xrStzVS316GjiAdnxWjjLxPNUXUfYeq+7WingxehOq+k3jRcXqM1umml4jT47e18yVdWUf/j6D/3fhPZWD96JkraDml+ZM6RuXl+wzVIRfvSIXXUWq/Oi9Ebd/Np32YsRF2nUa6x7xI3fssdG+fmZilAm7G9PX479e5KU7v2D7K6SNeTykiW3gU8FrAd4zEaW1b4fRbWMze1jZ62VemXg6U0MsVNJZvkHpZ5hx1gvE8ngJbNi2H/Lp8FOsvfqv+7mihsyZuE+neMaK/A5x1/h1K599ZIv2xlD4obnpQXIl56dupP4rRGLyZ9Dqu8w3QV8BZ54fmSjwuX2DcsapPTBAPw9wnEr7Sy4sC5ptb8JurhfrDQeoPCWj7wq0BfeFgmTo3Mo7OvQo6l5Q6V6be9Eygc9lsfFdsNLEjlrL+qJmMjpDrpeOFHh6v9HCbqE8TlyJdGRV6eLzQw4zSwxNKpM9SehUXOO6mqZ5zpGN5TTNAx44XOrZjrsRj3gPjskrHdlLeu1jHCF/p2LWkY0eJcbeA34GV8qyrb9tZ3xQCrWF2B+je9jJ178QSutdD4/BJUvf+Q/1pEvrTpPTnVFFXJu4Uqv89Qn+ahP6crvTnjBLpz6T0Oo7Hbh1Xoh87jer3XdSPnUU6djbla9I2lV5TM22tf01C/86fK/G47IFxZyr9u4D4u5D1j/DLWFOfg99iYWnXIOeWsQYxunmeyUMkNvp4UYA+nlemPl48wfi7V+pjmWviUr6i15N5EX7YOYvxoeDtgTtBe+C8Z46bw8ZwJZ4kx16uP55LjH5jFpIQe+5hp2gZj3LwPnpTwD66OXuuhvZdOjdo39zkI5Pwrvl4CKX9P78CdE2bfK9ok++jObe1BZzL50d8Jnq5LZftIXqHA6jmQMezr7pCyKBqLK+thojgUkdZ/iQfYcHHv9k7D/Aoqi0An5lFmqihd6SLgAihiIhASAIJhCSk0ESWlA1ZSFl2E0JQFFFRVBQrxV5AFBVsiGBBwfLsBZ8+O/LsjaKIYnn/zN6d3AwbiK9973sffMZk7r1zy+nn3DvnXl+LecxU87hBm0c76Rp9tGhbgbVrqnLC6+dNivP9nDiuusMwoD9De3Ps5+4q9n6TNr9GUWi6riUhJd3Gzy0KP32i2gbOhqrNRc6T2k+7TfOhbtNwfodLDq/S5LDV7nYlh1ereaq+HJm3pr3WTvR29K35K11Uf3e7ZKhV11er0/pQfk6091xz/BM+kAMXtw/kVLh9IDWGSw5/pnygWylvbJ1f47fThfKB7nLLUcrWUmbfN2kdMlFl9+jtTpeDyjppZbk+Eu/5ws/38lySY+d6dp6DORVepwzf6r6Iz1U1Odu/Wqf7V8jt9TXIbYvWGiG371f1Fg22OgStjamdrKoV/1u0+qBGqw8p+i847D6pLrNdct8Zp6ruYbvfQPUZMOY0da51g8ajzf6Ne8+WfKsT4+TYdc77QfN27r2SSHqe/FTnW7iNCm9OjcL1qMhZKX2/55+g+e7V5zDRcsmdfEGMWzrKSiVQNd5mfbx/Is4QkTu7Xef/H6ffFs6ZK46LcAGU/ZU879zGeSuDvS1rTk+2t2mWc1VUY9lwgMsf4sNUruSxNsyG5hXmBDvaZlDHnuHf+plDHwRxktb5sPBBrZrrRwzveojRRoxPHJkQ9t+6q294tzC/mrsLf4trcIb1KQ2Oxp9dkQ3iWs1s99N/Anb2obiwzecL33fMceP/DhihmGiDj+CfOLDdehjYXqVgu63WsI066J8D86FmDl2s/hPwr7BQ7S37r5Kvd2J1+n32MDAOKhg/V2s=
*/