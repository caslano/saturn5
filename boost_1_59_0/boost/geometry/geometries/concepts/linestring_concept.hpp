// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_LINESTRING_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_LINESTRING_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/concepts/concept_type.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>



namespace boost { namespace geometry { namespace concepts
{


/*!
\brief Linestring concept
\ingroup concepts
\par Formal definition:
The linestring concept is defined as following:
- there must be a specialization of traits::tag defining linestring_tag as type
- it must behave like a Boost.Range
- it must implement a std::back_insert_iterator
    - either by implementing push_back
    - or by specializing std::back_insert_iterator

\note to fulfill the concepts, no traits class has to be specialized to
define the point type.

\par Example:

A custom linestring, defining the necessary specializations to fulfill to the concept.

Suppose that the following linestring is defined:
\dontinclude doxygen_5.cpp
\skip custom_linestring1
\until };

It can then be adapted to the concept as following:
\dontinclude doxygen_5.cpp
\skip adapt custom_linestring1
\until }}

\note
- There is also the registration macro BOOST_GEOMETRY_REGISTER_LINESTRING
- For registration of std::vector<P> (and deque, and list) it is enough to
include the header-file geometries/adapted/std_as_linestring.hpp. That registers
a vector as a linestring (so it cannot be registered as a linear ring then,
in the same source code).


*/

template <typename Geometry>
class Linestring
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );

public :

    BOOST_CONCEPT_USAGE(Linestring)
    {
        Geometry* ls = 0;
        traits::clear<Geometry>::apply(*ls);
        traits::resize<Geometry>::apply(*ls, 0);
        point_type* point = 0;
        traits::push_back<Geometry>::apply(*ls, *point);
    }
#endif
};


/*!
\brief Linestring concept (const version)
\ingroup const_concepts
\details The ConstLinestring concept check the same as the Linestring concept,
but does not check write access.
*/
template <typename Geometry>
class ConstLinestring
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point_type>) );
    //BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );
    // Relaxed the concept.
    BOOST_CONCEPT_ASSERT( (boost::ForwardRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(ConstLinestring)
    {
    }
#endif
};


template <typename Geometry>
struct concept_type<Geometry, linestring_tag>
{
    using type = Linestring<Geometry>;
};

template <typename Geometry>
struct concept_type<Geometry const, linestring_tag>
{
    using type = ConstLinestring<Geometry>;
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_LINESTRING_CONCEPT_HPP

/* linestring_concept.hpp
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
*/