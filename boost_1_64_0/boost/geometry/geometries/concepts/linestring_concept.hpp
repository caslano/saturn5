// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_LINESTRING_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_LINESTRING_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/point_type.hpp>

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

}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_LINESTRING_CONCEPT_HPP

/* linestring_concept.hpp
WbmFqFQJUWKXHrXOkowszJQgCQuW4L3hRGS3PqB6ZOTzRrqNN1ckBYweUZ65FwHVS7msLYOgM7mCp57BT+D0FbDpScGP2s5JeAeY6h2eT4C4/fOCRFvUxTitwzCGBNQNoyrTPo7p/6sogMy7JR+uG0i7Rcq/HBGlDWrdMdUWayPJyGfNelIyNofRZVivB7cHWzAhUHC7akgRjaEtHhGXpq73Zuyf+CEDU5uUF4U7Fs8dpzGNRUa7r0I//gwX/zfqvQHciRBHXvXVeFDL1CCmBvT9+t+Diioa/r8n7u4tsqRq5o5o1XPrcRLN+p6BVyHkOcjWsR4+4bwQ96AZfzJxmdLjjItZdt150P/GUH4WJHu/Rg/JT5sSRmkaEFb9wBlRRX5kephhsaCctxNSZHk9lNtxzYS5lUOREE5s/D1HmFCdYAY/IMeQ4wiM94Gff9QSMjzlcXJD95sDWzCHmUCRFrsxAXInHzf4gjfWnbTSTTSuhytDOmLJnoObYxZ6JBitDMkATybRfTJKWD7CxjUdVFSJwJxTZhJ4jMXl88JJXSzWW4stQQwU1zR6Zw==
*/