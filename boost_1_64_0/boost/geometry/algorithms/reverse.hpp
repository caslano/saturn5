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

#ifndef BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP

#include <algorithm>

#include <boost/range.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/multi_modify.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace reverse
{


struct range_reverse
{
    template <typename Range>
    static inline void apply(Range& range)
    {
        std::reverse(boost::begin(range), boost::end(range));
    }
};


struct polygon_reverse: private range_reverse
{
    template <typename Polygon>
    static inline void apply(Polygon& polygon)
    {
        range_reverse::apply(exterior_ring(polygon));

        typename interior_return_type<Polygon>::type
            rings = interior_rings(polygon);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            range_reverse::apply(*it);
        }
    }
};


}} // namespace detail::reverse
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct reverse
{
    static inline void apply(Geometry&)
    {}
};


template <typename Ring>
struct reverse<Ring, ring_tag>
    : detail::reverse::range_reverse
{};


template <typename LineString>
struct reverse<LineString, linestring_tag>
    : detail::reverse::range_reverse
{};


template <typename Polygon>
struct reverse<Polygon, polygon_tag>
    : detail::reverse::polygon_reverse
{};


template <typename Geometry>
struct reverse<Geometry, multi_linestring_tag>
    : detail::multi_modify
        <
            Geometry,
            detail::reverse::range_reverse
        >
{};


template <typename Geometry>
struct reverse<Geometry, multi_polygon_tag>
    : detail::multi_modify
        <
            Geometry,
            detail::reverse::polygon_reverse
        >
{};



} // namespace dispatch
#endif


namespace resolve_variant
{

template <typename Geometry>
struct reverse
{
    static void apply(Geometry& geometry)
    {
        concepts::check<Geometry>();
        dispatch::reverse<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct reverse<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<void>
    {
        template <typename Geometry>
        void operator()(Geometry& geometry) const
        {
            reverse<Geometry>::apply(geometry);
        }
    };

    static inline void apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry)
    {
        boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief Reverses the points within a geometry
\details Generic function to reverse a geometry. It resembles the std::reverse
   functionality, but it takes the geometry type into account. Only for a ring
   or for a linestring it is the same as the std::reverse.
\ingroup reverse
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be reversed

\qbk{[include reference/algorithms/reverse.qbk]}
*/
template <typename Geometry>
inline void reverse(Geometry& geometry)
{
    resolve_variant::reverse<Geometry>::apply(geometry);
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP

/* reverse.hpp
fmpnDmHCVAuIfBNajmCOO7UQsTDkgABHibLl8gfiexIKSEs88SoQni/2jgKiHmaRxUCYJVKDYJZIC4R4iKoBbVq2gCCrF+6Z1lDqN8kRAFAI3avE9kQh6H7IDX40IhiKD0/WAOZ6hVYbv8wcUAOoKaBGEDNAnZ6YJOn01PzPS0/v++ZV7336+/d8IZ0SBOnBQ24BTvXEIYQjGBNNY1HiFsgRid8xH4nt88qfggsDThFvossBxNH/BSKSus4NgIlCNQjIRp+ioV6YzXQ5GegDQnQVhDnGxSBgzObKr+/JMV537kAuZYBkeCVOxRphstOlGs5isPxDCaXCEEtAI0w/PJXGtBPpIMhiCA1pMcReT4Oh+1lGd5uMuh1JQ+KdaCrYUEptbS5A2DJ4itTA5xhim6FG4P/iWwUMgOY+agTNWHqnhEWIJ5oagVEBLpfhFGCbuCtNA7BBh3HBa0zQiEjmgSCZV0PgvnyZrsDQvGidJDgKvYzppVmL0rIaNBBf31BgmKMorQkER1RlqxdiUmMxRHyXxVDjJoUh99kZEHdSgcHAbralp9RYhJ9RJt1rEtcyGQRzPlSOgN7ok5KmMKHUr6UhVEyuQVBTrxyCgA7xXUQFBAdxicNAckyvJT9Zy0BYTQsATECbGmbpoFxWwoIhSYPaZZdjoNFpXjAsISoZoVV4mqcm4oCVHEKsJ+YIZiWxgERzxZ3SIIgJdYHwB/JRrIEQS40FwiwytneZEwQ43sYcvo9Yl7SYeqtZdxqcpGbeGC30M8zST9myIwSgvb0u1MR4wLAftaMwwGmtKnH5tnmLOcXPBrhZdA6+w+dk2FcaUSHwmNya5kL4CQicGJVkQ3W9iD9HtTRsSrDDdoigGkL001jMfX6Ju5h5/AvGbpCIAfl99qLKMnUkSlrUK3zJfnx6MxWXB//qZzISyqyJUpr7/8VF+Mv97SIiaRZgxCAQhyRTQgS9pA1GHAtLhX8N01DesHNxbxcGswKJtn+pWa+IV6d1B8npAp7npnkHwCv4nptuidWjHLVfTmivww9K5xz7V0ZOSjV0S3yWIk5jEYjAsZBKZtz+3DkpzU5SzDCouUMvCbQe8DK/I0IXFYgPHay8dyEI1QUFaK66oCoeJJk4eTqMhek1R3p3g9+eK02veSeIqAu5ouz0OdjUrO6TV5uvGdgQX8FhkqGvIQBaAESX8bBRDtWdzD1FLceHqo/KYfkH5RGEjYBSUKdjxIp4qjISdK6el3WmdymdzP7VLCySpKt7KF8q6uO66KKU1obyEI3Ql5VFEttr/9JTGuUPpUDhaX6om0KgscLOnAx+/9DrD2ORBBSfAwRR4el5UV+EyyW1eOcwpg6HrZSDmXf0i/SkbGDYm+e3b377Zt555plnQbxU5vQXfS5SYv+E4tx37LCzNYy6QT743OKUtLH1Njva707bYbstzNhtiyBsDecW38N6m2HqYfsGW8ZBa56FUBH3zjP6mTd/3xFPD8/8eH63P4s5n+f5/+f/n/9//mDvKsObt4Gwxry1Y2bmdczruo73rfvWMWRp4rRZQ7OddszMzMzMzMzMzMzM9Eo6y4qbNrqse/ZnfurGlvVKp7vTiaX/r/+v/6//r/+v/6//r/+v/6//r398Re3UF04XgrdXZ9oLmp30t+ySy2HSn2pvx90dsk9hNAIcrXBq+2FGMcRmg6qZKln6p8HoNvu2g0Eb+rBGLax8ZdRCy5fUHNw+nlaqQ0a4IM9vGE+9scPRSeVyLsmk6JNHbJstB/4hy6FTxXwpGh1jck+ODXMxagViw1QnUPpYUy5I7rzBxWBO1eJNSkRyg7FncAKvonaB1xMCG6Q3JeGi0L/ser7cP5k=
*/