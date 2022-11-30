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

#ifndef BOOST_GEOMETRY_GEOMETRIES_RING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_RING_HPP

#include <memory>
#include <vector>

#include <boost/concept/assert.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tag.hpp>
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
\brief A ring (aka linear ring) is a closed line which should not be selfintersecting
\ingroup geometries
\tparam Point point type
\tparam ClockWise true for clockwise direction,
            false for CounterClockWise direction
\tparam Closed true for closed polygons (last point == first point),
            false open points
\tparam Container container type, for example std::vector, std::deque
\tparam Allocator container-allocator-type

\qbk{[include reference/geometries/ring.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_ring Ring Concept]
}
*/
template
<
    typename Point,
    bool ClockWise = true, bool Closed = true,
    template<typename, typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class ring : public Container<Point, Allocator<Point> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef Container<Point, Allocator<Point> > base_type;

public :
    /// \constructor_default{ring}
    inline ring()
        : base_type()
    {}

    /// \constructor_begin_end{ring}
    template <typename Iterator>
    inline ring(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    /// \constructor_initializer_list{ring}
    inline ring(std::initializer_list<Point> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it shoudl be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{ring}
//    inline ring & operator=(std::initializer_list<Point> l)
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
    bool ClockWise, bool Closed,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct tag<model::ring<Point, ClockWise, Closed, Container, Allocator> >
{
    typedef ring_tag type;
};


template
<
    typename Point,
    bool Closed,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct point_order<model::ring<Point, false, Closed, Container, Allocator> >
{
    static const order_selector value = counterclockwise;
};


template
<
    typename Point,
    bool Closed,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct point_order<model::ring<Point, true, Closed, Container, Allocator> >
{
    static const order_selector value = clockwise;
};

template
<
    typename Point,
    bool PointOrder,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct closure<model::ring<Point, PointOrder, true, Container, Allocator> >
{
    static const closure_selector value = closed;
};

template
<
    typename Point,
    bool PointOrder,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct closure<model::ring<Point, PointOrder, false, Container, Allocator> >
{
    static const closure_selector value = open;
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_RING_HPP

/* ring.hpp
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
*/