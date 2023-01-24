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
i3Rou7ypJr58q4BD0gnaijSNsSkwUyvnevLqTaqzdT0NE893mux36maDeMpGJk1bGmfkZ8XuIJN0Wb8u7K+bGtNJilMq4YnR5RdRrXamjgnOdRO7nvyCMxb/J9OA6Xf/+JC/S4ZM1nkWHRre8eQhxGfiHENq/sRNhZiK67TvgqGTG3o6R9qmlLliht9FXHYwNIoSpi7BdcWwprmFqvflPSupo+IuLsFGW6ziCgu5yVXvNXn0d0cWS40K5P+KrplTPD+6aOfvrKgGVBCaKdWLmc6Nl0CUK+Zymke4LL9csTILI7r+g7cX2ShKrKhhmfBMUWpNiYjyvWD+Xkd4++4xV4tHWtnhjEJVSZdJSKld2aFRyIZ29Nji5C8urWhwD1uuavQ/zUhFg2IujXBFg4szO1HD9vrhkpNSpvyvcqPlJR1zh5qXwGzXU7GVSwvZX/YNkLCEAHUJfK9K4hWjxszxDkD2lfxCoabDJe8DxaDiK/6ZsOoewY+87xTIdHiRZ7QDMXMiQ3D0d6TxR/xsfT+dFixDOu+fj0lvwEnpk7GbChizhseDt71S15aVu6SyITAZHvOd9R144KfmcQJ8kKCL3Bw8V1i2pB1JYYXKtco2VqVPgHbz65qnJIF2iSZ4Ek1M9eKCSFILrfk352mjNg6D33wSEb4v+Kz7PAMHgfaXPo3gip0p8dbMyVL4nsfe942d3ZbvqXJt3QNacc0J
*/