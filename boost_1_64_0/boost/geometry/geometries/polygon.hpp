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
YQOVm6jcD56GQ1UeAX+BY1R9IvwNzoC/w1vhH/Au+Jffbmf9On8UBf8NgzAet6NhCoyDNWE8bAgTYQuYFLDjowy8HCbDMTAVGr+XM/kOlodzYRqcDyvDG2Am3AhrwK0wCz6j8kFYF34Kc+DXsB48auIGnoIN4e+wEYzzU75gGdgEdoDNYFfYHPaEbWB/2BaOhu00n4/nGdnbjv8Tms/j4TDNb9OS7Pw9HWbCmTBHZVOeZ0FTbmbDx+GV8EXV9wWcB4/A+dCprzf0sd2rGqG+3pJof3/dD2PgNpiocnlTXmBF+CBMh9thFZXddRZqf3YE+3ep/bthMtwDK6hcAz4Ka8K9sBZ8GNZV2fn+Te5r2z8xwvfvz+hLNfkRZsJfYZbJfzDb5E/YWdW7qHpPVR9m8i0cbvItHKXvx6rsjO9sUPfPizC+8xX6AvAbjb9/aziPwvIqV4c/aHiPq/+OwVyVnXHNw+rOCF/Jcc0zGo9/Jdr5wZ9k1/vpWg9Fw2YqN4fxsI3KbWEZ2FHlC2AK7KJyV1ge9lT5ElgR9lHZ+O9Zng39bf/dp/FQwaSn+u9Vv+2/N2FtExbYAn4GW8PP/bY79DGlnfoCmjj8Eg4y8Qjz9f1YE5+wAH4LZ6n6bPg2NA69A5ep+nL4EbxZ5Vvge3ADfB9uVnUnngsG2OF4LcL48ROJ9jqxp2A1+LTmqwOaXs/APLgPjlN5qokfOBM+D2/S97eqfDd8AW5S9a3wJbgd7oe71X7jv47GfwNt/3VQ/wVhMyee0ZcED8LzTBhgC5XbqOyE81m151SEcC7Wdu1qaPLnUpit8ki4HJrwrIBz4Up4vcqmff6HaV/gKnifsRdug6vhc/AGrZeWan10K5TxUU+9ZA2y/bcxQr3RTOvBFpo/W8HusD0crupTYEu4ELaBq+D50An/IbW/KEJ5eiva7k/8M9p2532Yqep1VDbp9zEsMvkZ/mryLTyj6vFmngzOhkdhITwG18Bv4TqVN8LP4GaVHf8dH2L7r0UE/51Q/52GA+Gv0TouC6+Gfxl7jcYY+/vUBz+FfvglDOj4fHn4IwzG6DgsLGPaS1jOZ7+vBuNhTZWN/yz3jn++GdR/VY2/1H8t/Xb5aKv9hXawkYl/mAsnwI4mD/t13aKW9wnaX7gALoIXwiWwG9wEu8OtsLffzke0odI/vxQeMlkGvmfyD/wIDoHfwGHwGLwc/q5yDH4eARPhSJgMR8HKcDSsCvNgLZgPW8LxsD2coPVFdpRzt7ncSy/xYPxbRcchvyxjt1dHoAn3dzpf9QMcbdIYjoU/wtXwJ7jGtFvwDtNuwftMOkOTbr/pPNfv8Bf4J4zzkd6wIrTK2vO5ftgWRsHuMBbmwQQ4zoc2uAwmw5UwBd4EU+FtMAO+btIUfgqrwa9gDRjl5/sURsPaMAHWgUkwB5aF9WB5WB+mwUYwHTaGVWEurA6bwhqwGawDm8Ns2ArWg61hY9gGngfPh01he9gK9oAXwUvgQNgTjoS94ERVnwP7wkLYDy6HA+EqeCFcDYfArXAofBAOg0XwcrgbjoCPwOHwMZX3wZHwsMrfw13wZzgK/gpHwz9gHvQF6H/DAJwIo+EUmAOnmvDBAtgSzoA94SzYD15pwgdnwyEqF8A5cB6cCz9T9RNwHvwNzofxUeRJWAUug23gdfBCuBF2g/+AveAqeCm8CebBm008wlvgZHgrnA/XwcXwdrgGrjf5RuV7oux42AjvgFvgBhN/cLOJN7gFHoJb4TtwG/wQbodH4A74HXzQxCfcCU1DV2TCE7TtrxS01euqnAMfgrnwUZM/4GMmvPBx2Ak+CXvDp0y8wufgLPg8XAL3wVvhS/Au+KIJj8o=
*/