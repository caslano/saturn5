//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/targa/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// TARGA Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , targa_tag
                     >
{
public:

    using format_tag_t = targa_tag;

public:

    writer_backend( const Device&                        io_dev
                  , const image_write_info< targa_tag >& info
                  )
    : _io_dev( io_dev )
    , _info( info )
    {}

public:

    Device _io_dev;

    image_write_info< targa_tag > _info;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* writer_backend.hpp
p6sHVXNi46ff1R/QuRg5r7vNu7Or8vf5y6//fvBXO8XL5M6bizmW6/rT2w4X29vzAv4VukFXMOnUbvbz1/g3wTgs8RhUJ3CkkI9mzSb6RDZ79K/ze+jPUc51m7BpsuG4eiqWpH6pdIAstUIwQm8sSzhSnSQhyuAi5FOvEyiOfYmjhgTZiT+sy/236YOYDnO/fcA5C8JUGhCXEE8TV5laOL4mdUqiJaAGnyOAFQXT+ARQsETYLdAU67wh9yBqRHizK0YH5GAeVI8MoNFG7qeHS61VjnrGO99LP7auE1R8e+8X/cpsMBJ0rSkB9aST/7uvl7/TmZG5E31jOXJ3z/5qjtq3rn4+e5ozVwy40qpWmb3Qw0BsjLNjYhCN3OFD8EWT0maVs5HbodQXX5K7dg/rerC3fPDZLsTMO3uOhND2Wu6lRvft2XVm5oL0hy8zmuYx89Tav87JOtI/Br/IqH5pIWJRoadAJIMeT8jcNl8hbby/KZaWHSAC7W5eEyEugGjFboqXl3pEd2wPuBiIIQs1DLW5G+sNuRuq9bkbQw25246Hzdy224IB/RnsdWd2ShvRmPu0CWWZX7efkXMJF8P16TaIdII5/KEOyPZ8EQiY/v5tabm1vU2ncAp26+CwSYTzQujdjJqvz5F1599fv+v1dbnfo6wl4Rk/6bIMRfGxEvVToBV1YObprilM/qq0fKALNfjdd+ztLdbjENhR
*/