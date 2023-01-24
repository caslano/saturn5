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
6ODIXUVRo0OGzQjwS6PDA0GqE5e1Y0xYwm58IjsCcGY4jqW6Pve5DF1DvglYqhiF5x8WnigsTcRt+U8AloiTkLht/6hQFnbpZp5UiOKAdO/1SMWQ6FEA3pIHnr9eOqsjXnLktWZlTcBzOmItLgliGJzUAP9PZGas1Wt8efahlkZ7fihSDU/hL3MXqXtecQLkwPcuF17hdrD6l22RG1iqZ/6BR2elSP666yn06QnuOR6hfMVjd61HdRoDpMUIomq7O4iPicMiCD346CvcVA/6mLP0c68Jw6pnB/11aBeONOzzoW8UgPvqwSXqWReAUw7VvIrUO9fvyi//hdE7l48C57zGK1p+Z8H+PCTodYDH0bYnjP6hh4SxzaLZ4qdlMEXWOaYNC9aLzDehn3sVj1DrkkcVx+h8VXwob6Mi/mwKwIJX0Bkjf4vj6JAhvFbwJeDTtnFxLBfTF1jvYD/Lpm8jQ18s4Fe4OIrABugzS12kosZ3qovfGLTuJbYrKYJCOhjDGPjporkEm1+AzS/ccs0wuC7F7rNdqN1LuiabBPOV4e9bvz6nMgy9sT+DCoX2etAKgMK9MHQhT/nyO+L4aRc2LVdSv42DhyuUA8l5HZra+uVc7f7Nsb+QhiUvHj/HqykoIa7j0NSrHFGKmWyIL0yCN/cr6WWzAhHOOjnW6vHuR//pyF/F1ra/s1XiykB/uKZPV6vQn//xsYh+rcPv
*/