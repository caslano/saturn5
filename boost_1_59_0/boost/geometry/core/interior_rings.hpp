// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_INTERIOR_RINGS_HPP
#define BOOST_GEOMETRY_CORE_INTERIOR_RINGS_HPP

#include <cstddef>
#include <type_traits>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{

namespace traits
{


/*!
    \brief Traits class defining access to interior_rings of a polygon
    \details defines access (const and non const) to interior ring
    \ingroup traits
    \par Geometries:
        - polygon
    \par Specializations should provide:
        - static inline INTERIOR& get(POLY&)
        - static inline const INTERIOR& get(POLY const&)
    \tparam Geometry geometry
*/
template <typename Geometry>
struct interior_rings
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};


} // namespace traits




#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template
<
    typename GeometryTag,
    typename Geometry
>
struct interior_rings {};


template <typename Polygon>
struct interior_rings<polygon_tag, Polygon>
{
    static inline
    typename geometry::interior_return_type<Polygon>::type
                apply(Polygon& polygon)
    {
        return traits::interior_rings
            <
                typename std::remove_const<Polygon>::type
            >::get(polygon);
    }
};


template <typename MultiPolygon>
struct interior_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename core_dispatch::interior_type
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif



/*!
\brief Function to get the interior rings of a polygon (non const version)
\ingroup interior_rings
\note OGC compliance: instead of InteriorRingN
\tparam Polygon polygon type
\param polygon the polygon to get the interior rings from
\return the interior rings (possibly a reference)
*/

template <typename Polygon>
inline typename interior_return_type<Polygon>::type interior_rings(Polygon& polygon)
{
    return core_dispatch::interior_rings
        <
            typename tag<Polygon>::type,
            Polygon
        >::apply(polygon);
}


/*!
\brief Function to get the interior rings of a polygon (const version)
\ingroup interior_rings
\note OGC compliance: instead of InteriorRingN
\tparam Polygon polygon type
\param polygon the polygon to get the interior rings from
\return the interior rings (possibly a const reference)

\qbk{distinguish,const version}
*/
template <typename Polygon>
inline typename interior_return_type<Polygon const>::type interior_rings(
            Polygon const& polygon)
{
    return core_dispatch::interior_rings
        <
            typename tag<Polygon>::type,
            Polygon const
        >::apply(polygon);
}



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_INTERIOR_RINGS_HPP

/* interior_rings.hpp
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
*/