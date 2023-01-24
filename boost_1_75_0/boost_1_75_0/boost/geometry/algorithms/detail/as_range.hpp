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
cij8sDMftfT9U4xsNLOX7yImc6RauVyapCTU8dpE9U6C30dlTADC+ycB/fMd6J/8Lv1TA8X9J63PPUA0Q/r1o0lszBbbYGwroDUcYYaas6rV8CoDUdllVSsN/w7q9aTHd5eLxOB0vZ8o89U8PU3WRmB5GUaTsKoE9dmmLNYL47IvMtLcSVns548K3wCG/74zhPrt5G3da6e1r3W8BStmOhkscdlZNpXb1fRBfeMG6rvW+kpm/7FT9Ns4IKpFWXfRv2kNoT7ZiAazbcDpBKHu7c9X7RR6sU1APArpxZ3c/nx8H9P+/MBOZn/+m53J1SvksD9/lTD782wR7yiF/fPOTnE3bsIP8kEaIpTr/jrpjYOP2fTGgyHzL49x3eXQx5ya3A+wsgs/TipQEelOXzfnsU6604XwA3PTiYp1zwfrXjase27OM4q+2vmY6Kv9QCiPA99Pk12P0WCfzXx9q3Mw89aOz5n85rX8PGbJ/fgJrfqedIz9AeNxawJcvOxF9+ojz+FnSLFcoUTUWmWlVqe7jTx3xFjk2eN9xxf1jveXBvL9xV634dbdSomcgK17NJpGPDLVChge3ZvwB1nfp45j3W7GsW56XHzrViBuQDKeCKGwqSNgf4q6fHH7/68v5lxH9avwxYEgecL6YhrVertR8TZuhoNoPSlWKuDIU6uu1OsMtzvPE3HP877ne8cf9Y0PlAbzA8U+txu+Wy1R
*/