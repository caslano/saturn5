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
qFDnt+LZ2rdAUVKaMJIoyCl4Cv0pvyiG3k2J6gokaTpMmct14f3rlzfa0GCFZFFId9k+FR63IV15I91pS2O0yDOE96gG3hGye87WFt3XIbfiCjvnx8MM1QKO2JIeXpvYMbNZchdCrZZwhdLA532nvnBfwWuL7RNVLJlJ4i32SzgQ7CgWB2r1mterJKKpOQ9KsoVsQQmKm5+WYDv4CJCnfSDQRxIB8NUBu5o75YISiDaNOQfiJnGlIhGVFNDFHCTBXjMFpMZTnhJYuAepwVi5vuLrPVhrQKi40tbs+Jj9JGCyq8PkfUVaTVmgeZFOl7pLBfeXOJLd6I6Vjckt8UfiWojV+jppiPJEBN4ijoGN0X9+41EobbgUMpah2jSFuhHnYmk0OX2VNi8Hl+LhyonoYNxNuDoAEEGRSZ51h3vGx9z+QBlePHJZhEkh5v3fQNLsKWEZIk2lSpsK2JujTuVG3um+Bb9mUvzPwddMtO+IXuVD33LwWquhOkG1Zdu/DrBWRGoT2+ZpqkbvZ0j4qYtZFZ7Kcyer+r/K2dRByFAlh2gWxgnlqNhI4jRQz+JfAxE+luADAbGy72nTR6Q87Y4I6yVIghKlhBK0X0PXRaHTlQB9xRrhjkLPP8hFljxMeN06td5cdU+GnV7XavXP
*/