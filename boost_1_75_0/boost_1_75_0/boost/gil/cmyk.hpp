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
q3Jx1782beB035eahPHdSfbkG+TVlzGdgEhK/nJ9IXplAlAv1cibzpd1BLfve2yLDw42tfJQmpSze5AoYHujoEEEA/cfslN3xNYFW0b9U86tzX/rX0Nt0i6h4COZ2YfN24FYkKdfKdxXOGN5Vgx0M/kF2NjHOHF6QLac8jdUU/4N1ZZ/UI32B9Wggf60z5j/QPWzP6gm/IPq4j+oBv7lH6hG/YNqmr+hGu0Pqv/cWV/p6qiBh4BgYs4AABvMVXGyKHo5k2GSQuAPqkX/oHrWzVswn6nCT79pe5ReoarO+w4DxqB/Keqb0DG+btE0lQ2KoPobquvON0ndw+Gp8MSOyYDBF8yl4+ZRb0VdNfqNURT5BAs/lr2ny9IZMRUtTlVzS++NNaDm6pGzypa7TbTZiYpMfsk7RiGdCRr2qY1N0+TXVynMF3WE1Lev7leNCQ6W3U0P0Yo+LknL0fkeHJjFwg62BU2G8JOc6tsfoADMeGkkpvgIG8Rmmj8LMBjdnjbPyVyxmzg3o5ml5G2UNn31BaPoaYZPcCz1LWOGFr/PGaN5Zk/RcEbDGHLQW41PzJ2Xxc/LtxAvHRLwOJr8VBzjLTCV0wW+GXv63WupQIypt2ng1+G933EN4DLsMyzi6R7tuM4hfh/GM9PiLUV0HfSw/OBsQlo1t85yWNK7PdxCASlNv5BIqkBF4I16fsdoSQgEd7IXZTijcTS/8E4N
*/