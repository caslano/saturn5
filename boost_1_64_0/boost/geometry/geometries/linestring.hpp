// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_LINESTRING_HPP

#include <memory>
#include <vector>

#include <boost/concept/assert.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost { namespace geometry
{

namespace model
{

/*!
\brief A linestring (named so by OGC) is a collection (default a vector) of points.
\ingroup geometries
\tparam Point \tparam_point
\tparam Container \tparam_container
\tparam Allocator \tparam_allocator

\qbk{[include reference/geometries/linestring.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_linestring Linestring Concept]
}

*/
template
<
    typename Point,
    template<typename,typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class linestring : public Container<Point, Allocator<Point> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef Container<Point, Allocator<Point> > base_type;

public :
    /// \constructor_default{linestring}
    inline linestring()
        : base_type()
    {}

    /// \constructor_begin_end{linestring}
    template <typename Iterator>
    inline linestring(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    /// \constructor_initializer_list{linestring}
    inline linestring(std::initializer_list<Point> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it should be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{linestring}
//    inline linestring & operator=(std::initializer_list<Point> l)
//    {
//        base_type::assign(l.begin(), l.end());
//        return *this;
//    }
//#endif

#endif
};

} // namespace model

#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template
<
    typename Point,
    template<typename,typename> class Container,
    template<typename> class Allocator
>
struct tag<model::linestring<Point, Container, Allocator> >
{
    typedef linestring_tag type;
};
} // namespace traits

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_LINESTRING_HPP

/* linestring.hpp
q1IgF4tUO0hG+p5db1NKF6CpvZuYnz3z0DEnskxgT2qXN/k3eC5HOG1ud4jzTD/pESINfBURnyf50fWOp22b5BrWiR0Z8D6BpNJqSRJ6yPkDbETYEazqXIZ82Fbqb/w5WFG2IZm/s0RKatAEA4mvR4jWkjmZw5DUZ9rWEDziE7Cyks8WAqUSWiOttMqYbIn5vWP4VA6bwBDvLdiekhvlGqXK/1HbYVGc4JO9MN961UyikMD1Dzm7KBjFhQm7U+POe9ib0gPl00lOQtNqI+5eEkhTEKsbUm7gwDOWR0oBcY8P/k6dGvO3MbHd0LHopYLDI3/2ZOfk6JiqdGj97H37OMUagyhaM5iH4YLXcTAMAz+DO9iMsSxXhkzWosZEx/2Oka+mQS6JPwghmF4nvWQTEAp7tnDVTxOXdQGpMVY2AnYsULnA+rWKUrIDSB++eZOBPLgO1W0zvMeWCOkP4qG1FphT2y+Revhq8q4RN2DosH3yVi2v7UR1idnJ7Z0o4B0GfF4VJX6j/CS7hn2wAyvrZdmfhKucxpxFRMlfPOH1PLYQI41+BHm4Y4mblQ==
*/