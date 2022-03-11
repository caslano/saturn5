// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_EXTERIOR_RING_HPP
#define BOOST_GEOMETRY_CORE_EXTERIOR_RING_HPP


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>


#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/add_const_if_c.hpp>


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
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POLYGON_TYPE
            , (types<Polygon>)
        );
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{


template <typename Tag, typename Geometry>
struct exterior_ring
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Polygon>
struct exterior_ring<polygon_tag, Polygon>
{
    static
    typename geometry::ring_return_type<Polygon>::type
        apply(typename add_const_if_c
            <
                boost::is_const<Polygon>::type::value,
                Polygon
            >::type& polygon)
    {
        return traits::exterior_ring
            <
                typename boost::remove_const<Polygon>::type
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