// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/range/concepts.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/concepts/ring_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{

/*!
\brief Checks polygon concept
\ingroup concepts
*/
template <typename PolygonType>
class Polygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::remove_const<PolygonType>::type polygon_type;

    typedef typename traits::ring_const_type<polygon_type>::type ring_const_type;
    typedef typename traits::ring_mutable_type<polygon_type>::type ring_mutable_type;
    typedef typename traits::interior_const_type<polygon_type>::type interior_const_type;
    typedef typename traits::interior_mutable_type<polygon_type>::type interior_mutable_type;

    typedef typename point_type<PolygonType>::type point_type;
    typedef typename ring_type<PolygonType>::type ring_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );
    BOOST_CONCEPT_ASSERT( (concepts::Ring<ring_type>) );

    //BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<interior_type>) );

    struct checker
    {
        static inline void apply()
        {
            polygon_type* poly = 0;
            polygon_type const* cpoly = poly;

            ring_mutable_type e = traits::exterior_ring<PolygonType>::get(*poly);
            interior_mutable_type i = traits::interior_rings<PolygonType>::get(*poly);
            ring_const_type ce = traits::exterior_ring<PolygonType>::get(*cpoly);
            interior_const_type ci = traits::interior_rings<PolygonType>::get(*cpoly);

            boost::ignore_unused(poly, cpoly);
            boost::ignore_unused(e, i, ce, ci);
        }
    };

public:

    BOOST_CONCEPT_USAGE(Polygon)
    {
        checker::apply();
    }
#endif
};


/*!
\brief Checks polygon concept (const version)
\ingroup const_concepts
*/
template <typename PolygonType>
class ConstPolygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename boost::remove_const<PolygonType>::type const_polygon_type;

    typedef typename traits::ring_const_type<const_polygon_type>::type ring_const_type;
    typedef typename traits::interior_const_type<const_polygon_type>::type interior_const_type;

    typedef typename point_type<const_polygon_type>::type point_type;
    typedef typename ring_type<const_polygon_type>::type ring_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point_type>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstRing<ring_type>) );

    ////BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<interior_type>) );

    struct checker
    {
        static inline void apply()
        {
            const_polygon_type const* cpoly = 0;

            ring_const_type ce = traits::exterior_ring<const_polygon_type>::get(*cpoly);
            interior_const_type ci = traits::interior_rings<const_polygon_type>::get(*cpoly);

            boost::ignore_unused(ce, ci, cpoly);
        }
    };

public:

    BOOST_CONCEPT_USAGE(ConstPolygon)
    {
        checker::apply();
    }
#endif
};

}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP

/* polygon_concept.hpp
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
*/