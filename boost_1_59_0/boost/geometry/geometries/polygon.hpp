// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2018 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_POLYGON_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POLYGON_HPP

#include <memory>
#include <vector>

#include <boost/concept/assert.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/ring.hpp>

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost { namespace geometry
{

namespace model
{

/*!
\brief The polygon contains an outer ring and zero or more inner rings.
\ingroup geometries
\tparam Point point type
\tparam ClockWise true for clockwise direction,
            false for CounterClockWise direction
\tparam Closed true for closed polygons (last point == first point),
            false open points
\tparam PointList container type for points,
            for example std::vector, std::deque
\tparam RingList container type for inner rings,
            for example std::vector, std::deque
\tparam PointAlloc container-allocator-type, for the points
\tparam RingAlloc container-allocator-type, for the rings
\note The container collecting the points in the rings can be different
    from the container collecting the inner rings. They all default to vector.

\qbk{[include reference/geometries/polygon.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_polygon Polygon Concept]
}


*/
template
<
    typename Point,
    bool ClockWise = true,
    bool Closed = true,
    template<typename, typename> class PointList = std::vector,
    template<typename, typename> class RingList = std::vector,
    template<typename> class PointAlloc = std::allocator,
    template<typename> class RingAlloc = std::allocator
>
class polygon
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

public:

    // Member types
    typedef Point point_type;
    typedef ring<Point, ClockWise, Closed, PointList, PointAlloc> ring_type;
    typedef RingList<ring_type , RingAlloc<ring_type > > inner_container_type;

    inline ring_type const& outer() const { return m_outer; }
    inline inner_container_type const& inners() const { return m_inners; }

    inline ring_type& outer() { return m_outer; }
    inline inner_container_type & inners() { return m_inners; }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    // default constructor definition is required only
    // if the constructor taking std::initializer_list is defined

    /// \constructor_default{polygon}
    inline polygon()
        : m_outer()
        , m_inners()
    {}

    /// \constructor_initializer_list{polygon}
    inline polygon(std::initializer_list<ring_type> l)
        : m_outer(l.size() > 0 ? *l.begin() : ring_type())
        , m_inners(l.size() > 0 ? l.begin() + 1 : l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it shoudl be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{polygon}
//    inline polygon & operator=(std::initializer_list<ring_type> l)
//    {
//        if ( l.size() > 0 )
//        {
//            m_outer = *l.begin();
//            m_inners.assign(l.begin() + 1, l.end());
//        }
//        else
//        {
//            m_outer.clear();
//            m_inners.clear();
//        }
//        return *this;
//    }
//#endif

#endif

    /// Utility method, clears outer and inner rings
    inline void clear()
    {
        m_outer.clear();
        m_inners.clear();
    }

private:

    ring_type m_outer;
    inner_container_type m_inners;
};


} // namespace model


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template
<
    typename Point,
    bool ClockWise, bool Closed,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct tag
<
    model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList, PointAlloc, RingAlloc
        >
>
{
    typedef polygon_tag type;
};

template
<
    typename Point,
    bool ClockWise, bool Closed,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct ring_const_type
<
    model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList, PointAlloc, RingAlloc
        >
>
{
    typedef typename model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList,
            PointAlloc, RingAlloc
        >::ring_type const& type;
};


template
<
    typename Point,
    bool ClockWise, bool Closed,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct ring_mutable_type
<
    model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList, PointAlloc, RingAlloc
        >
>
{
    typedef typename model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList,
            PointAlloc, RingAlloc
        >::ring_type& type;
};

template
<
    typename Point,
    bool ClockWise, bool Closed,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct interior_const_type
<
    model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList,
            PointAlloc, RingAlloc
        >
>
{
    typedef typename model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList,
            PointAlloc, RingAlloc
        >::inner_container_type const& type;
};


template
<
    typename Point,
    bool ClockWise, bool Closed,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct interior_mutable_type
<
    model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList,
            PointAlloc, RingAlloc
        >
>
{
    typedef typename model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList,
            PointAlloc, RingAlloc
        >::inner_container_type& type;
};


template
<
    typename Point,
    bool ClockWise, bool Closed,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct exterior_ring
<
    model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList, PointAlloc, RingAlloc
        >
>
{
    typedef model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList,
            PointAlloc, RingAlloc
        > polygon_type;

    static inline typename polygon_type::ring_type& get(polygon_type& p)
    {
        return p.outer();
    }

    static inline typename polygon_type::ring_type const& get(
                    polygon_type const& p)
    {
        return p.outer();
    }
};

template
<
    typename Point,
    bool ClockWise, bool Closed,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct interior_rings
<
    model::polygon
        <
            Point, ClockWise, Closed,
            PointList, RingList,
            PointAlloc, RingAlloc
        >
>
{
    typedef model::polygon
        <
            Point, ClockWise, Closed, PointList, RingList,
            PointAlloc, RingAlloc
        > polygon_type;

    static inline typename polygon_type::inner_container_type& get(
                    polygon_type& p)
    {
        return p.inners();
    }

    static inline typename polygon_type::inner_container_type const& get(
                    polygon_type const& p)
    {
        return p.inners();
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POLYGON_HPP

/* polygon.hpp
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
*/