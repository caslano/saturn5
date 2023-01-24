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
IyyrvNgGf/2nCgZb67xYpuA7pQsp32MAJVY81So0PGVUbgoFLYaQIlffsm6FC+7XtQ5ZJ6Tx7VtqI3lbi63rXmzMmE+Tt78zjSEeco0uVQALvz4HqFFm7cqmX9bVsf8GBvC+znsKmHi3ke7k61jcN4X99xxK5gYcVGAFucJprlgbXL4shDKsMpH81Np3bPw7Vuwn70SS7/h0QFe2Ym/mkiDXeOQtnrXYrgvmGGtIGTwer55titfjSJGDexu14v54R+MPqiOH89A6df6qZa8OHteLW8tScHmHTBzUiuvu5/EK79eExwuKt4DgydI22RMHiy682NVDx1SYXUmE/0s2zyDh7d1ZYcr+fK324hhvaoblRT9l02S5OB5tKNta7EAzlMz+QmXwhwcnBYvWpRtOWq9a5ZVlxuNmEUKurRbb/U3fvXkEH7IPrgEn/G7Ib+IGrzT6+hRbnvKz5/4Z2rRAlGZqmVF6rskvpsJYh4kR3gtyJXOFW6nQlUFIx3KQx4u2mxB90G+r4EOnaedma5Op18fiVbG+E80xyFAJJNIh7368eQbhQ/SxdHHhd3P8+6SqwXb4gcKhplgBh6WqPSBZ9tFL7ODxUfOj1gedN7Eojw0zUCTtS7K9PObyjdcfI5HhDO+2hM7QIZ/yzKg+2fIi/Jrd2wdm9tqP27mVe36lzMN97lvvTN6WCUn+8ujTaS1nSUzJeiogfJNp6gBT
*/