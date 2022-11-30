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


#ifndef BOOST_GEOMETRY_CORE_EXTERIOR_RING_HPP
#define BOOST_GEOMETRY_CORE_EXTERIOR_RING_HPP


#include <type_traits>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{


/*!
    \brief Traits class defining access to exterior_ring of a polygon
    \details Should define const and non const access
    \ingroup traits
    \tparam Polygon the polygon type
    \par Geometries:
        - polygon
    \par Specializations should provide:
        - static inline RING& get(POLY& )
        - static inline RING const& get(POLY const& )
*/
template <typename Polygon>
struct exterior_ring
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Polygon type.",
        Polygon);
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{


template <typename Tag, typename Geometry>
struct exterior_ring
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Tag, Geometry);
};


template <typename Polygon>
struct exterior_ring<polygon_tag, Polygon>
{
    static
    typename geometry::ring_return_type<Polygon>::type
        apply(Polygon& polygon)
    {
        return traits::exterior_ring
            <
                typename std::remove_const<Polygon>::type
            >::get(polygon);
    }
};


} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
    \brief Function to get the exterior_ring ring of a polygon
    \ingroup exterior_ring
    \note OGC compliance: instead of ExteriorRing
    \tparam Polygon polygon type
    \param polygon the polygon to get the exterior ring from
    \return a reference to the exterior ring
*/
template <typename Polygon>
inline typename ring_return_type<Polygon>::type exterior_ring(Polygon& polygon)
{
    return core_dispatch::exterior_ring
        <
            typename tag<Polygon>::type,
            Polygon
        >::apply(polygon);
}


/*!
\brief Function to get the exterior ring of a polygon (const version)
\ingroup exterior_ring
\note OGC compliance: instead of ExteriorRing
\tparam Polygon polygon type
\param polygon the polygon to get the exterior ring from
\return a const reference to the exterior ring

\qbk{distinguish,const version}
*/
template <typename Polygon>
inline typename ring_return_type<Polygon const>::type exterior_ring(
        Polygon const& polygon)
{
    return core_dispatch::exterior_ring
        <
            typename tag<Polygon>::type,
            Polygon const
        >::apply(polygon);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_EXTERIOR_RING_HPP

/* exterior_ring.hpp
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
*/