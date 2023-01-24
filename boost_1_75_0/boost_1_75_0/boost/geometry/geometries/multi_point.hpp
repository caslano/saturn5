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

#ifndef BOOST_GEOMETRY_GEOMETRIES_MULTI_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_MULTI_POINT_HPP

#include <memory>
#include <vector>

#include <boost/concept/requires.hpp>

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
\brief multi_point, a collection of points
\ingroup geometries
\tparam Point \tparam_point
\tparam Container \tparam_container
\tparam Allocator \tparam_allocator
\details Multipoint can be used to group points belonging to each other,
        e.g. a constellation, or the result set of an intersection

\qbk{[include reference/geometries/multi_point.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_multi_point MultiPoint Concept]
}
*/
template
<
    typename Point,
    template<typename, typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class multi_point : public Container<Point, Allocator<Point> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef Container<Point, Allocator<Point> > base_type;

public :
    /// \constructor_default{multi_point}
    inline multi_point()
        : base_type()
    {}

    /// \constructor_begin_end{multi_point}
    template <typename Iterator>
    inline multi_point(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    /// \constructor_initializer_list{multi_point}
    inline multi_point(std::initializer_list<Point> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it shoudl be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{multi_point}
//    inline multi_point & operator=(std::initializer_list<Point> l)
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
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct tag< model::multi_point<Point, Container, Allocator> >
{
    typedef multi_point_tag type;
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_MULTI_POINT_HPP

/* multi_point.hpp
jmNHHh5813TjdI4a2WaEqXPMcnKi80ZHYxUhHfDZ7bTB1Xv90axoRFyNcfkvj3Ctmy09/6LbuRR8ozrUv8C/0TtCFaATXKqru90CBfdknmIAXajNbN/DU1e9ml0hGPNApwsTorpw1+x396C9qpysmMdn/3N4sMsYOeEuXGzzkpEaLH61fnjdP+VKyMPlWHQXcRKqs2bQ83xf++C2Q9oizWS9Mpvm74+eJbuC11nc/YSOqHr3ufkLQW6Z3+6gyWZFU8Ijfr8AN+838jWaYyqssze5Vye2VOQDJBjKzpmmh0sIh8vwFmu9wqixO45W2SVSDhNCdFRzFdsNM+6uP0V0SWrkG17Vdn13r7hcNs/w8gQ4FP1qHinbFZ4cVgyQnoK+efXnTv2f2nWniy6oafGl7CSu3a/LTslfXPD6UqHUsDS8WOz5UUuQWM2uYN7W10HNE8JyliXxqVqU75Wv5OSCYjqHF1/aieie8zYIh7EzG0sPWLZNJT8KdpY5tziYptfz/eMLFa515akRtC0lP0KmhEhjejw7jinf+TS9+eryWrNy4aNvs6dnqvZCfvqcJCvz8MEJSSxiRr7BzPvG7GuVoLKxuTduWm1LcvJEsQm0UpmRyyLUWDFZt4HKe6DTdI7g/uL5dtYeG1C58fGky+ZLxM6Kh33dQYq1+Na2ud4I1bZ/tiCGs6YXEzjipTYXnLjZGCBVFMg+ed3+WPNI
*/