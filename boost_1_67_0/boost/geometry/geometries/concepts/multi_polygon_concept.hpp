// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POLYGON_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POLYGON_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/metafunctions.hpp>

#include <boost/geometry/geometries/concepts/polygon_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief multi-polygon concept
\ingroup concepts
\par Formal definition:
The multi polygon concept is defined as following:
- there must be a specialization of traits::tag defining multi_polygon_tag
  as type
- it must behave like a Boost.Range
- its range value must fulfil the Polygon concept

*/
template <typename Geometry>
class MultiPolygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::range_value<Geometry>::type polygon_type;

    BOOST_CONCEPT_ASSERT( (concepts::Polygon<polygon_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(MultiPolygon)
    {
        Geometry* mp = 0;
        traits::clear<Geometry>::apply(*mp);
        traits::resize<Geometry>::apply(*mp, 0);
        polygon_type* poly = 0;
        traits::push_back<Geometry>::apply(*mp, *poly);
    }
#endif
};


/*!
\brief concept for multi-polygon (const version)
\ingroup const_concepts
*/
template <typename Geometry>
class ConstMultiPolygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::range_value<Geometry>::type polygon_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPolygon<polygon_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(ConstMultiPolygon)
    {
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POLYGON_CONCEPT_HPP

/* multi_polygon_concept.hpp
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
*/