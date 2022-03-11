// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_INTERIOR_RINGS_HPP
#define BOOST_GEOMETRY_CORE_INTERIOR_RINGS_HPP

#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/interior_type.hpp>

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
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
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
                typename boost::remove_const<Polygon>::type
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