// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP


#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/add_const_if_c.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename GeometryTag, typename Geometry, typename Range, bool IsConst>
struct as_range
{
    static inline typename add_const_if_c<IsConst, Range>::type& get(
            typename add_const_if_c<IsConst, Geometry>::type& input)
    {
        return input;
    }
};


template <typename Geometry, typename Range, bool IsConst>
struct as_range<polygon_tag, Geometry, Range, IsConst>
{
    static inline typename add_const_if_c<IsConst, Range>::type& get(
            typename add_const_if_c<IsConst, Geometry>::type& input)
    {
        return exterior_ring(input);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

// Will probably be replaced by the more generic "view_as", therefore in detail
namespace detail
{

/*!
\brief Function getting either the range (ring, linestring) itself
or the outer ring (polygon)
\details Utility to handle polygon's outer ring as a range
\ingroup utility
*/
template <typename Range, typename Geometry>
inline Range& as_range(Geometry& input)
{
    return dispatch::as_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Range,
            false
        >::get(input);
}


/*!
\brief Function getting either the range (ring, linestring) itself
or the outer ring (polygon), const version
\details Utility to handle polygon's outer ring as a range
\ingroup utility
*/
template <typename Range, typename Geometry>
inline Range const& as_range(Geometry const& input)
{
    return dispatch::as_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Range,
            true
        >::get(input);
}

}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP

/* as_range.hpp
FZctaJkxgga8YscbtzJOg0jVhJ5Vn/4wqmuKlr9REWEgpLy8GhOfgirpCm5Y/BV2Tc/4AJvhrgivnExV5E3wgCZHgISk4ggoP0kGisj7ojCWUFjbZ2UbIEA/yneG5SwLdgeIMMPh2xrOoGfmmxpMXcsZJgQx3CC/hk3IiNI/VxPWL7YRUfOS7FPQ6Fn4TLpN2IWZcsGSndQdaKeEVQmHcv3lNLXbcOCUhZJqB9vjyHWEwkRWpD5lfPjx820jcVCLoJqJGLo8oZiram3/eD+hRzIUJzAjxR5DB6QJWjHKQBUKk2s3UGREk+i/stewx8hQmDetDOa9ADFVvUissuWqqdDwtoX7monhhl/ZZjZY3mkGcH0XON24qHGpeiG0g6WviSjV3Gq5OlYrR1sLKHCUAN7RP92FAIPE4sXOojTu284VOgAHznDUfvD6mn8lXBu974TSJ32IenpKJvPTB+Q8oWcBfDtSEwGRxsMkCRj8X9FO4h1MoN+Lz7cNs2VdJs8mua78oCQvP7PA0cHH0e1IapAAXmPRnLwHqa+U3uvlJ0l+ziGqbrNUpep+uw==
*/