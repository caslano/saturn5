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