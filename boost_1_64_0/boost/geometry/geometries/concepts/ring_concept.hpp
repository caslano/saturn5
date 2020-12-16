// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_RING_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_RING_CONCEPT_HPP


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
\brief ring concept
\ingroup concepts
\par Formal definition:
The ring concept is defined as following:
- there must be a specialization of traits::tag defining ring_tag as type
- it must behave like a Boost.Range
- there can optionally be a specialization of traits::point_order defining the
  order or orientation of its points, clockwise or counterclockwise.
- it must implement a std::back_insert_iterator
  (This is the same as the for the concept Linestring, and described there)

\note to fulfill the concepts, no traits class has to be specialized to
define the point type.
*/
template <typename Geometry>
class Ring
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );

public :

    BOOST_CONCEPT_USAGE(Ring)
    {
        Geometry* ring = 0;
        traits::clear<Geometry>::apply(*ring);
        traits::resize<Geometry>::apply(*ring, 0);
        point_type* point = 0;
        traits::push_back<Geometry>::apply(*ring, *point);
    }
#endif
};


/*!
\brief (linear) ring concept (const version)
\ingroup const_concepts
\details The ConstLinearRing concept check the same as the Geometry concept,
but does not check write access.
*/
template <typename Geometry>
class ConstRing
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(ConstRing)
    {
    }
#endif
};

}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_RING_CONCEPT_HPP

/* ring_concept.hpp
+k5J7sUN98wr0/FHOZS9amAKrIDdYTWcC5dCHc/oOwsZwzQYz1yg4f0URsBVMBZeDPvBS+zxjM7TyzuChuOZtRrOtbAFvE7HQ9fDnnA9HApvgLnwRlgOb7b3NNR5c5mPb7in4blme4GLtH8t0/61HPaBldrequBUWA2r4RL4E3g+vBX+FG5WfYfqu2ENPARXwj/Ci+H7cBU8qvpnMNKeW6ZOaX1sZ9YXjefpupfbJHgKnKz3+amwFM6AVfAMeD48E14Bz4Jr4Vx4IzwbboZ58GXoga/A+fB1WAJ/BxfCz+EiaOheXC5YDlvDxVpPK2BnWAnT4RJ4GlwGx8PlsAKu0Pp4AbwV1sC74Er4a3gRfBKugtIvGdacKG1F70tDvHutyW+v7m34G3gWfANeCN+EV8BDcB38DN4M/wJvhU7zeVV1nglEHwFbwpkwHhbC1nAVTIW3wQ5wG0yDb8Au8Cv4CuH8Fb4KnSE8L+n9Iw/7XjABZsNEOBr2gNNhLzgL9oGLYKb2y1nwFjgM3gaz4V1wONwKR8AH4Gj4EJwAH4ET4eNwEtwHZ8JX4Cz4BxgNP4Mx8BsYCr+DYbA5+RsOW8IviH9b+CVsD9/R+9i7sB/8I8xSfTI8C39nwzlQ7mewEh7B/lL4IVwPP4J3waPwKfgx3A/fgq/Dt2HpCfa4SkWGIqUvUDcQa0+rvchbyLGm/a2+9/5W33dvq6Z9rf6/97Xa8UJje1sF3tdqzwvB97Y6+MLJ7W91FHfR+8hjZBZSg2xB9iNfIJ1epPyQFcgGZA9yDEl9ifQgy5BNyH7E8TLmLzuafk2/pl/Tr+nX9Gv6Nf2afk2//4vfv27/v8LSRVU/fv8/c9++KxOYY9b1elsNnZv2QubJ8uL5jwkQc5p0+MgJo3PN7z9YMV5S5Qh4ht94w3LfXuzTo7H32Y9kQj37jo6Ga0HVvpG1w6l1e9z4n6lnr8nmuphxXZ812R3tNdn67bymO0X3K5yq386fjpQRZoZfugvLypfnFSyvks9H66fdXqM4Ufyc4kir+3Zew0lpsLeRfUau2Pfi/WMrzSPLT+v6eWSvsz1d7Afjy9B8s/wk8o/vT+RdHe/ZyAc3H3mGuEMjzTV0lt0u7O7HzpkSHu52hdvfNKSeIL8zAuR3lt/eSbrmrWF+22cdbtH8DtXQTXUtYW70y28JS9LvaVjH1G3oSdcRj/+5i3advyy04XnbFbjd7heX+WUVS/MrihxB67y6TwlYpyfU2UvZbCXBQ0O9ZeNyUzQRTsn/k01Lg/reSF6vCtMzbqyQkHz8H/JNn6zC7RMsbeq2g9hX2/VX01ZnL2lbTbqSwrxpk6+dQr1pS1a7LOzuxs7loN5FRLidbsePTnu1Xff8y3ZHeMOyPRf/0bvrpV2bdeD0q3st227RDdOv9kH7M+ztsr8sjDwI1/yJqcsfyy4Xu21W/oSH/+i8Ib6aN4H6Qf/12qOa6fkK+n1FMVJCmNkN8gu/C6qKzf2O2O7OUxS87qjfOPtbm+mizyYulvvK6gLxovlp+1nos6ej93qWmxi4WNw0V52dG0UPse85DquMtI+9YHfdPWcHL8wizfX6urY5x1ozIW7aORIxm6rvy/LFbCJnHrVWt+JYrxch65dRpWx3UnYr8HSPWbYDKL+WkQ3rhObLEvGfobphhSfhHI9gjjVS68hp1BG31hG1W4bdNusazjCxk3qicTiE/V2mfSs+RolzVZquQrl2MvY12O3SsAnZ2Z3PVZyEafq37N9C7lb/7tCW7lC1t+pi0gnqYmq9uqjfOamZlre6lXYaq98Y1KuP23UvumVaHyu1Pu4/YX3sG7Q+7vepj9PR3xXd01h9VD/LgtY=
*/