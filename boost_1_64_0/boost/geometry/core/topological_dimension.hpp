// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_TOPOLOGICAL_DIMENSION_HPP
#define BOOST_GEOMETRY_CORE_TOPOLOGICAL_DIMENSION_HPP


#include <boost/mpl/int.hpp>


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{


template <typename GeometryTag>
struct top_dim {};


template <>
struct top_dim<point_tag>      : boost::mpl::int_<0> {};


template <>
struct top_dim<linestring_tag> : boost::mpl::int_<1> {};


template <>
struct top_dim<segment_tag>    : boost::mpl::int_<1> {};


// ring: topological dimension of two, but some people say: 1 !!
// NOTE: This is not OGC LinearRing!
template <>
struct top_dim<ring_tag>       : boost::mpl::int_<2> {};


// TODO: This is wrong! Boxes may have various topological dimensions
template <>
struct top_dim<box_tag>        : boost::mpl::int_<2> {};


template <>
struct top_dim<polygon_tag>    : boost::mpl::int_<2> {};


template <>
struct top_dim<multi_point_tag> : boost::mpl::int_<0> {};


template <>
struct top_dim<multi_linestring_tag> : boost::mpl::int_<1> {};


template <>
struct top_dim<multi_polygon_tag> : boost::mpl::int_<2> {};


} // namespace core_dispatch
#endif





/*!
    \brief Meta-function returning the topological dimension of a geometry
    \details The topological dimension defines a point as 0-dimensional,
        a linestring as 1-dimensional,
        and a ring or polygon as 2-dimensional.
    \see http://www.math.okstate.edu/mathdept/dynamics/lecnotes/node36.html
    \ingroup core
*/
template <typename Geometry>
struct topological_dimension
    : core_dispatch::top_dim<typename tag<Geometry>::type> {};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_TOPOLOGICAL_DIMENSION_HPP

/* topological_dimension.hpp
H4IQsea1ufQl1rweLCPW/GYudcSavwAxYs13nc7+Emt+Bfj+zbbO5Dd4MJS4bgzfhscqNZI4MBY/MJrYdxa/64FBunwcv1mDebp8PL8vggHkrNmaQBtizWeCIHHdBHIDdcQxOPts9oW++fBGUETcCNdPJKZNIzzsHPpQHoTfAv0pV5P4Lfi3SkV0X3jwubwbQxyCHwZriWNwynm8s6Rzg0eDrcSa/ww+J9accb5SqXgG4ScvYLx0+wuVOgiUUx6AnwdLdG5wJI/XB/T4wEPy0fp4wSsK+Dqic5tMvmAZcUMRC36x/qGQPOGrQDpxFC4pYay241PCdkET7aPwW2Cb7gt/Axq05xR+eQAxYj98NGgkzoEngi3E+fD1pRxH/Bvgm8oYE70tOPMi5g/b0txjKmNBrDkMQsQN8BnlHC/aaz5/GtORWPObIJ9Yc7cKvhsS18FXVzImxJpfBPXEmg8KcSyJNQ8HDcSax4DtxJrnAx/bzQ/zDhVYSlwLfwkWEIcivBsGVunxgf8O1hJrHlrNOBBrPhVsI66pxgMsJw5M570x4PuafYcHz2D8iUMzOf6X8JWTOHgpxxQMJG6Al/CiaRZx7Sz2fTbjSax5WA05E2ueBLK+oS8vgU69Ck2s5rBNsFSXX82372vJj7gWPnQu3+vpq3klKCXW/EMtY0isucONnOPEmgeA5ToHXhrcdwHHAp8c+GGQSxyDx9zCHNP7At8EQpRrTuPFvZnEmjuDWuIA/BaIEvt4ke94sJq4Hv4axHSbxcw9sEX734r/3ZwX3zKe93L+3se50dTR5jUrGCtizW+D0cShet7nAauJNT/9KD7Emgc/zvwk9q3iN1zwOf6aS55g/uOv+WvgJ9b81ZPMFWLNKU+xJhBr7gxKiTUfDGYRaw6AWmLN54BVxJovA28S569mzEE+OWi+9mnOU2LNL4B5xJq/BUv1vjyj1D2g/3eMD9xhDftO7IcLQJC4Bn4ATCLW/BkoJ9actpapQByAK0Gqbg9PWsdxJa6Flz/L3CDOf44xAcu/72jzS2AVseYN4E3ihijr/IvksIPjAnd5ieP4Q0eb7wUNxJqv3MC6QRx4mXfVwFb8NQ//I+OMj+YLgZ848CeO6WbmFe19vHhbDDKJa+Cur7Hv2gd+HyzGR3OXGMeXWPOzIKb38c/4vMN5h2fdu+T4HseLvppHgyJizXPALGLNMbCAWHOXv7PvxCH4BTAUH823foQPseY1IERc+wnvyP4TL+Kcz/l9/ivyZ0w0j9xOe2LNsa85FsQ5TbzjCgYQ1/Jyw2k7ONd0+U+cR5alAj9SnmKpz8EkYl8HSz2QaqnUn4g7WqpbmqXqKde8Emwk1vwCaCAO7GWpGrCduA5OSbfUDmI/vKKzpbLwCXahPcinXPPMrvQh1nwbWKJ9eNFuE1hAbvol+eFgKbHmBWA5seYmsJ5Y84+ggVjzaB/bJdac1R3g2Qh36mHxDmGaCsIlIEI+IfgaUERcC98Pyonr4Q1gJHEM/hiMJm6E03iR7Xw9JvBBYAJxAD4XNOJfD/szGTdizY/0IgdizWtANrHmP4FJxPm9LfV0H0stI/ZlWWqwn3HWPr+y1CeHMs66nJenrj2CnLVnwFJ5YMnP5A9fNpjxIY7Bhw8hf+0JXwrmEEfhv4JZxA3wq7y4nmGlcV9nqWlgNX01vwOixJo/AVuINX8JGon9vFD9F9Ck8zmaeQLqiAO8yLoQzNM5H0M5GEB7zR9ks7/Emv8NgsTBYy1VCYqINdeBcmLNK8EcvS9wwXHE+rjA94EFxJqfAkuJNY8bbqm1xJr/ALYSa64HCp+c4y21DmQSN8ArTmCe6DnAy3+zwSztDy8Dw/U=
*/