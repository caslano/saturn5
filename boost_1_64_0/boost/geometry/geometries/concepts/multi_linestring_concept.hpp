// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_LINESTRING_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_LINESTRING_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/metafunctions.hpp>


#include <boost/geometry/geometries/concepts/linestring_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief multi-linestring concept
\ingroup concepts
\par Formal definition:
The multi linestring concept is defined as following:
- there must be a specialization of traits::tag defining multi_linestring_tag as
  type
- it must behave like a Boost.Range
- its range value must fulfil the Linestring concept

*/
template <typename Geometry>
class MultiLinestring
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::range_value<Geometry>::type linestring_type;

    BOOST_CONCEPT_ASSERT( (concepts::Linestring<linestring_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(MultiLinestring)
    {
        Geometry* mls = 0;
        traits::clear<Geometry>::apply(*mls);
        traits::resize<Geometry>::apply(*mls, 0);
        linestring_type* ls = 0;
        traits::push_back<Geometry>::apply(*mls, *ls);
    }
#endif
};


/*!
\brief concept for multi-linestring (const version)
\ingroup const_concepts
*/
template <typename Geometry>
class ConstMultiLinestring
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::range_value<Geometry>::type linestring_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstLinestring<linestring_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(ConstMultiLinestring)
    {
    }
#endif
};

}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_LINESTRING_CONCEPT_HPP

/* multi_linestring_concept.hpp
XWTTWCUMMlZA6YSzVpqtAPJEe9tGXil5Ps68+8ARPAZbcIYu0+PMoZAkZl01hv/ePNiCC3dwAVfg6wnuC802o+a8btvhhphp1wWnwEJ0KQ8ahgv24NNG6nNra7E3ilk7vqbmF9Y7g5pc4exMSN72CjF8Ke2w0LgcolK1hwpn7+lMz9dQ7Cb5+GUrK/yiMb7VqjSL4faIjnHYDAahoOZfsxTcie4ZsZsJh5/2sQc4r6YoQ9v0oX8nsm6DggsOft/tkVV7/xNQyxId9rIpGhsBZbztzN8spz9jIZy/o9A2b86m97B2N+ueXIRcklscNj/paUGWvB1oXJIgiJhF7wdloAxpR/hWvPYb3Ql22/62kFzp0370ER8SecBL6iLHgt9Au/RfTarzGo7PLF9/XF3n4sqLS3tzZ5GfCJcA1Uaiu+1Bl3BQXrs1RCiD6beBOWQhDSGsM1wmtTwCvWBoxQoKvzhWE0aD3zkcepU5iozDe+cAkPs3fjqkTZ6e0e2xP6HiH33a2nOPlplOHNkN9cVm1O3M9ztIpk4FurnMgQnGGF1JepNRNJ1rWid3Kw==
*/