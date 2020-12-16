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
Pa113Q382LSvt6f13/RsQRzUdAAhPme1zIbhMB9GwW3QBV+CbrgftoSvwRbwiOp6loGuWaFvkuv6n2VQrNctgx3hYtgVVsAsWAmHwirNp2o4Di6Bk+ByuAT+xOesm416vVPlev5n3czXM7YWwNawGLaB58BUWAKzVLfO7KrV8NZJeP5ndoXjLhpGwPYwEqbBdrArjII5MA7OUPPZMBrmqV4EW8D5qp8LW8Fy1as1nAthG3ixml8BW8OrRbfqn67TgA8GqH/HcWfqYU5vPMNhV5gM+0I3HAObwxzYAnpgS1gKE+BimAivVH0djIU3aTi3wlbwXtE1H631C/DhAPn4Cz3L4nbYG94BB8Pn4Gj4AJwMt8MZ8GE4Dz4Ki1Qvg3thlfr7Kfw1vAw+Dq+Gu+HN8AmN51PwDrgHbhV/uneeQ9/j63qALB0nb9L45mn+lcAucKHmXxkcARfDq2AF/Dk8D8qZZvBOuAI+AC+Cz8JLYAzXuBzGwytgF3g17AYvgn3hNXAMXAvz4ZVwPrxK482tQN+7Sh2TeJv1/IDG+xDuEuAR2Ad+CrPgZ5rfp4R64/81+gT4BcyH0ZifA2OgzJ/DpWq+BraCG2AbeAtMgZtUv1P1LQb1FG6FqfB+2AHugGnwYdgJ7oZt4dMwFh6FPWBkiMRP0rnRoe/VQIGWT4y0UT2rO8Tbzz4M28JH4Aa4C94Kn4f3wcfgC3A33K/mh+CT8CP4FKxVc/Nie2ASfBq2haZ5L/gMHAKfhdlibvVH+g4KDgrQHw0O9bbHU2EHOAx2hiNgHzgS9oOjNN011rsTOFHC898joxvlZbI7DIU9YATsCaPgdOiCg2EbOAH2h2PgQLXPgqfDkXAqPB1OgxPU/jO4036nQdo1HvFwq7XHp57N2Ql2humwOyyEPeBQmKF6H5gNB6g+EI6CQ1U/FY6BI1QfCSfBsaqPg2fCyapPgXNgruozYB6crbreD3V+X94tNLgfvqZniv4ODoG/h3fAP8Jt8A/wQfg+TMDvh3AhPALPg5/AFbAWXgePQj3LTeeOaROSb/5nueFG8u1LGAm/gW3gt9DuR9X/BUbDfvRUHV+MgO3hKDgGIpIv43RcMR6eB3NgDZwKb4HT4KNwOnwO5sIX4Az4AcSv7AUzE8bD2XAgPAvOhHPgmXAe1P5I5zWJk9GwP4plnJAI28M2sAPsDbvAgbArHAK7w5GwN5wLM2AhzIRL4QC4Eg6Eq2EW/BkcBNfDwXAjHAJlL1m4E54Gn4TDdTwzEr4Dx8BP4DhoRn4CjICTYV84DQ6E06GMF635R537zKp3dsejuIuDu2FP+CTMhE/BQdCp9fgZ9BnwWTgf7oXl8Dm4Dr6g6dkPb4G/gZvgG/A++Dv4K/g2fBr+AR6G78BaeBh+CffB4/A7GG4QZxgL34ep8AOYBj+Ep8CjcAj8BJ4KP4Xj4Gfwp/BbeDk8Du+Bf4WPwe/g09AI4T4HQ+A+6NT2MM+eI+Reqverbma903zjOVT67zkwA+bBbDgPlsEiLf9iuAoug1fBn8ANcCW8A16o49bL4T54Ffwj/Bl0m/dTGAPPg+3h+bADXKjlXanprYZnwyWwDC6FVbAMrocPwbvgw3A79MCH4XzNj+vgU/B6+CpcD9+FG+En8Db4HdwEI8iPO2AM3Azj4J2wG9wGB8DtcAS8D45VfQrcAXPhTq2fDnuujWcVrZ/kq3c+Qc9WTYQXw9bwStgd/gwOhL+AMrbWcfet8Ex4GzxL3eXBNbAIXgPL4bWwAl6v4/Sfw/PhengpvBFeDjfDX8A74W1wC9wDH4MH4OPwLbgbvg2f0P5oK/wG0qalfd4LW8LtsC3cBdMg7iUfah06HwY=
*/