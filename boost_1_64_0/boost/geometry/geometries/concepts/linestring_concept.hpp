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
Ebr6C2lwZmRvrVM3in1fGQNGIM2ROKQ10h7pjPRwhJ0wP1o43IBnTAmvTt+nunkO6ePevztNnNynr0PNflVn1kfSgdkDttkg0e+x9SzR77T1gaLfausDRL/J1vuLfp2tZ1rzetCes/LL/6wkb6JuwEMHZZY55zmnLv+1rlZWl5eXVVQxSg08/lE/3e3x+I2ilxklRkhjdVT9dRV/8eg/F73CmG3ENxzH69jqnbkyztXnO8ORLfpzjlsx28NfDcYb6i9F3HXScXxgv2nm2XvUyzmtyCsZc5xK5x4S6VrB8YhxEfyd1j5QP3+PxLvYbp9HJdzW1nl8EuaKVvbYWAba7Yij3MvVfr9lv7KdPe5o4wo87hgh4a/WMYKVjqcJ76YfPHb2v6cEfr57YW7gMfV+rUsYy6+N3mPKz7bPJi3kyNuqiupC7jRygGyedbJuuacw0DOe+k05ifZIPa/rw/3qeHGynlujY5QSuJI+eWOgeM1nPr2ymEoeeB72cdMPVxhWNzbRcNrbc4WGzhXaYxPbzSifOW6ZJxT74jp7u5yJpX0fPCx2zMvq+OR90QcYHQzDd17WfuY7JPZZRkejbt4mJ8aUHzY/a9WFMNF950GZH7friKaH+sH1rTlL0Z/P85+3HazlsqmNXhTLODgQDsdNzTyrXLQ08qgrRZXFTOEGHItcL+67GFoe+K+bF58pbpdWVtn9jdpTO83noiy9l3hjVFjgO6c4Ll/C5dk5Qp+v6c3y9f0O+Wpm+yH8/ZprhNEBvBrvlRejT669+Yw57DnGmaJrfMm7hXI9Bznmn3dZbfUMK827N+FY8i61wMo7eX5dyMxvPs2soKxoecD6nC3ud/PcE6712QojVfIlLdz/HP4Jtn1b+4zXU0Xfy7Oatz6SFfI2sYXW1/PFfonhW7djtW7vELtzmKWd6jVDWyNm5r2vi/97B63f5WJ/iWGVwd8SvOeRvyei5zT/iPc7pBmdNGsZ3CfXw53W5w2Fgd/3TGwvYcveqm1hLjzdrM9FgcqEQXa+NKSAdfpO8dM3xK7TonfF3p4LqLL7F9u+k/08v0n0YSG+eZ6sef6J2I03enGC0X5OLOtmJDkSNe+3i901PPfP4Fyw3/q/O1L/y+frOF7ve3eK3sq/rPR+e4+ENyQk0WeMX7ikyB7HJWoY34q7JKMDcXrJ0UPG85SNxmdQSCJlHYquZSvlveQkytgccyXNr38efOBy12dfiWayX9/mE2etEx8V+deJyz1WnfC/J+7STqCXttM0OJQ6sWZB/fO6A90RA9+DNovfGOPFujar4SUGPl9d7PUMZbt9yrtjv+eLu8RNpT1+Oa1YrlN/LG2fo/57cX8T9s0cnZGhjHWSKacw7MbE+p/bXxZz4vuOWVa5xX5ldVJnpvv2ixlp3gBX671+qeZ3dEn9/Lbv9AHzuL+4n2ncU/eemjAaPcNe7dNEn4reV/T5qhuOe0SP8L3H2+8nzhW7DKM5rgc4JgY9836kuLvLEU08Rjra2PehjTG++a33+5PM86dKflieW+sm3B29AeZowFOQh1IcJEry3Hp+KFxYHvC5Qd3F+Yxx8/VebdnlNBj/Fhu2nY4NG58viawb26L7Pqvmi55k6wX2edOORs6bDnz+crDzf//zzo/+vudEBz53OPj50XyTivnahJ+NzPVcPezoc3MvLSyau/o/7/zof9c50d/3POjve1554HOxv/856V/5PM9xE+apgriHoOjfj/C3fbbe5Lqzdsc6Tu6sXdNfjfoLE38nd3biGlPUH8mSuOhZf/Jrr2c1psHBsBM8DXaGw+FgOBV2gWfodapgBrwA9oFXwL5wN+wPn1Z/v4UD4ZswC/5ezK0=
*/