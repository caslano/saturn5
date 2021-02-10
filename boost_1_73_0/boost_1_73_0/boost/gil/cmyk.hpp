//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CMYK_HPP
#define BOOST_GIL_CMYK_HPP

#include <boost/gil/metafunctions.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>

namespace boost { namespace gil {

/// \addtogroup ColorNameModel
/// \{

/// \brief Cyan
struct cyan_t {};

/// \brief Magenta
struct magenta_t {};

/// \brief Yellow
struct yellow_t {};

/// \brief Black
struct black_t {};
/// \}

/// \ingroup ColorSpaceModel
using cmyk_t = mp11::mp_list<cyan_t, magenta_t, yellow_t, black_t>;

/// \ingroup LayoutModel
using cmyk_layout_t = layout<cmyk_t>;

/// \ingroup ImageViewConstructors
/// \brief from raw CMYK planar data
template <typename IC>
inline typename type_from_x_iterator<planar_pixel_iterator<IC,cmyk_t> >::view_t
planar_cmyk_view(std::size_t width, std::size_t height, IC c, IC m, IC y, IC k, std::ptrdiff_t rowsize_in_bytes)
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC,cmyk_t> >::view_t;
    return view_t(width, height, typename view_t::locator(planar_pixel_iterator<IC,cmyk_t>(c,m,y,k), rowsize_in_bytes));
}

} }  // namespace gil

#endif

/* cmyk.hpp
F+VyMpHk9ewMO8rnaWLytzvbJZy5FpZhjvMYZa83CdF+KYZTKNUOc/EiiGv5dK2e7YSTbWi4c1C5U2AX53yMxPbQu8CVYmdfJG+bT9RLyJqxtji1sndsha3pVF5s+RANLGK5yO/qgdqRkTknfViVWzrVjJjMFRfVJkhmMRvJeU1gf9Kni1DIy83G7qdoF3a5TKflHicrGlWS5urGu/QX1cUAb9TaU0iKHzPJeVd0I2W78/nh6opUjvcYhaNOai4uFkErRsckc0xKtwRdPeZpPOaULLo2ACEDJMIu6bjGkrXA5HU2Ixj5MIunbKofnXVOOELAFjtzjFJuIrUdqh38G5bW0mndD9V8/uRJS9/xwOd4br3CZfechLnnxhWYLP6Q/Y7JeezY5kVjB3WjfBM4mIcwIWya9MQme1qgb2xPMA65XsqX2Zt8WYo75QIRTQD6WQtGc31ZA4g0HWjaHx0ovmw7HbwtRcYfHx2f59a73vq7YY7H0g0egG/KNhtdbGsulzLeYURCAGwWgDc5L0oMVRShUO4v4IXTRTIyxvb2YaIg8dgaLVfiaJLj+A4P9cBZDfXSvBYLglk+B9BESzgnU7hS/GSF2cy0kQhfG3b0pRjwlMVxlji2IKGAm/9mvHSE4Gt7fYwv02O66I8d
*/