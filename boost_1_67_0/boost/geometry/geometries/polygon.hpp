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