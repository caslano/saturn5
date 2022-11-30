// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

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
#include <boost/config.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

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
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
*/