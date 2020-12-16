//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_OLD_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_OLD_HPP

#include <boost/gil/extension/io/bmp.hpp>

namespace boost { namespace gil {

/// \ingroup BMP_IO
/// \brief Returns the width and height of the BMP file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid BMP file
template<typename String>
inline point_t bmp_read_dimensions(String const& filename)
{
    using backend_t = typename get_reader_backend<String, bmp_tag>::type;
    backend_t backend = read_image_info(filename, bmp_tag());
    return { backend._info._width, backend._info._height };
}

/// \ingroup BMP_IO
/// \brief Loads the image specified by the given bmp image file name into the given view.
/// Triggers a compile assert if the view color space and channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its color space or channel depth are not
/// compatible with the ones specified by View, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void bmp_read_view( const String& filename
                  , const View&   view
                  )
{
    read_view( filename
             , view
             , bmp_tag()
             );
}

/// \ingroup BMP_IO
/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, and loads the pixels into it.
/// Triggers a compile assert if the image color space or channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its color space or channel depth are not
/// compatible with the ones specified by Image
template< typename String
        , typename Image
        >
inline
void bmp_read_image( const String& filename
                   , Image&        img
                   )
{
    read_image( filename
              , img
              , bmp_tag()
              );
}

/// \ingroup BMP_IO
/// \brief Loads and color-converts the image specified by the given bmp image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        , typename CC
        >
inline
void bmp_read_and_convert_view( const String& filename
                              , const View&   view
                              , CC            cc
                              )
{
    read_and_convert_view( filename
                         , view
                         , cc
                         , bmp_tag()
                         );
}

/// \ingroup BMP_IO
/// \brief Loads and color-converts the image specified by the given bmp image file name into the given view.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its dimensions don't match the ones of the view.
template< typename String
        , typename View
        >
inline
void bmp_read_and_convert_view( const String& filename
                              , const View&   view
                              )
{
    read_and_convert_view( filename
                         , view
                         , bmp_tag()
                         );
}

/// \ingroup BMP_IO
/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid BMP file
template< typename String
        , typename Image
        , typename CC
        >
inline
void bmp_read_and_convert_image( const String& filename
                               , Image&        img
                               , CC            cc
                               )
{
    read_and_convert_image( filename
                          , img
                          , cc
                          , bmp_tag()
                          );
}

/// \ingroup BMP_IO
/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, loads and color-converts the pixels into it.
/// Throws std::ios_base::failure if the file is not a valid BMP file
template< typename String
        , typename Image
        >
inline
void bmp_read_and_convert_image( const String filename
                               , Image&       img
                               )
{
    read_and_convert_image( filename
                          , img
                          , bmp_tag()
                          );
}


/// \ingroup BMP_IO
/// \brief Saves the view to a bmp file specified by the given bmp image file name.
/// Triggers a compile assert if the view color space and channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if it fails to create the file.
template< typename String
        , typename View
        >
inline
void bmp_write_view( const String& filename
                   , const View&   view
                   )
{
    write_view( filename
              , view
              , bmp_tag()
              );
}

} // namespace gil
} // namespace boost

#endif

/* old.hpp
8Na4W0HrLGgnmS2GJ5N/eA5sH2l7PLawc+7oHDl6lK0jE1G5wkWMl1sMt1/PN+qombGxqK2B70TJ0/DEyInRxHByiz8VFrE1Ap0w41S02fBR46nJkT+85LXuRo6bic5E7Rw5GU3FpiO21nJkMzn7pmzVH9nM7sSJ2L48HSX3mfIsh45tNxSJDEXT7cvKSHw82b0XMm6DkpFjjdUxFD1+KiW3TccPxmwGqDuu3w2YmRofG49G5DbKONj6ZYKKOX40NT09kRwSk9eJmSnjWmdEqMvgcPsGTxMhJ+FEaiYuXwKNDk2OJ0eHRiYjW285NBqfGY6MJ+O2Wy+7jC8jbTe++5aF7YDOF6m2OqvdR7YOtX7paDuf1pcO9qowvjawdWT7PSHbKchsG5XrYiqWiI5EknKUrUrkKyhZATamQyJlTCK52Y+OyuUhHreZleyaSUbtD+zRM+MReWPGxoxWnw1PRU+w1VbT6E4nTrTR5qOTnQUgH6XdRycHR5KTnag9OhXtEtw7OXTYbxtybLIVOiiv7Uak5xsxOTKqQv6wMeb1HDs2mTrWaMx8oo6eGUlEWueBkdRozFa06sCj5bQzFZmQifDHiUrQ0Um5ksanEynbhydn4jaPN1okPRAdPXZ07Gi7x7faPo9KZlLjE+OpE4ciJ04Ny9XTuAecT9iM0HAkmpK1Nj49ZSNQlszIzERKujtx9PHDk9ORqLFG7Yd1XhhfFo1MdN5WmY4blSeNgmwsrsmRVIyXVOsw9dlw94pkZ6mPSH5JW2u8lbqtI9U1dP4hpred7Fx7fzlTGef+8amx6XkFRdOj0dZQ2DhjRWNDKbk3j45MzcRtzYDu68jExLBskyPjU382Trpl5ihbwWqat5/nFyPUqik5v7D2syyq5LGp6XbfyPeePv3x04XkeRH58IdF/eZqYOsU+E+cdv+Jb2PFI0epX8W6Uf1CTvuxjWyTsvXI9pN6LGl67fj/8f/j/8f/j/8f/z/+f/z/+P/x/+P/x/+P/x//P35m71rg4yyK+F6StgEKXF4QoWAoiFGxtAVKRISkadqUtklI0lIUvV5y1+ToJXfco0kRtSJqRcCKL3xhRUVUVHyjoNYHWEWx+KwCWsUHvkEUq+Ljv7uzc/Nt7i6XFtSfv+b3+9r7ZmZnZ2dnX7Oz+/3v/Ln1fuoEpfYvsCUYLTTtnueUKIShxLTBgPipn4pCFKbGZ06bZMpm/v7G+EhVIK/hTYsXzFDaSuNhaPOtkn063unEf9PGMD4+wZom+K/SRDKuab9DxKYEs8I9+rjx2q/A2AMJzS0VK/Y4qScxHo3FZhxOC6f9tKb5uISdxTdPG0hVJDp4f1XzPxFcmBhfsj9VYqIk9rvkhd5qLDFu96f328CmWuzjEzb6uMTJBnRNha2gRc8sHKKyEA+/BiHTghlW+ljsjAUVSF5ZtM4THrb0nwvI3K/IrgoixmZ+4mE/IuJmEmhXcazfjOMTZYKKJlv7Fdk5pfMeriSbyuJmi5xcqDjQwkxfK9iHjE8Op3Mz4aoJkj5jjcRvoIkgW8FmZrHogcp3aWci80gsMY08ZnPtoskx9KjZzUBFNoFnPHnaYvTQcXSvifF4rGX4Gc9oieZymcRQPqd76+HUWDoBsVvcrO9pFYrkoscObEM9Pn3BDyg2Zzp6Hnsq2ly3kUgVWGRloWwyRXwURJHBvkhnx+rVSzs6V0W6etat7O/tiaw7rRIrnDa+ZL92+2dsWuBX3KpmIBMHE1SgthmEXRxQMIVWQ+UdV8k4Ny5JMjo+Ajh3j/HRWDQXraDAmdxwJfwS2WgkujmaSEaHTFBBBZz5rVDcg6dcZ8jpgE65HkiOB3Bk9Qk4lblfzP4=
*/