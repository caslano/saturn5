// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP


#include <algorithm>

#include <boost/range.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/util/add_const_if_c.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace for_each
{


struct fe_point_per_point
{
    template <typename Point, typename Functor>
    static inline void apply(Point& point, Functor& f)
    {
        f(point);
    }
};


struct fe_point_per_segment
{
    template <typename Point, typename Functor>
    static inline void apply(Point& , Functor& /*f*/)
    {
        // TODO: if non-const, we should extract the points from the segment
        // and call the functor on those two points
    }
};


struct fe_range_per_point
{
    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {
        // The previous implementation called the std library:
        // return (std::for_each(boost::begin(range), boost::end(range), f));
        // But that is not accepted for capturing lambda's.
        // It needs to do it like that to return the state of Functor f (f is passed by value in std::for_each).

        // So we now loop manually.

        for (typename boost::range_iterator<Range>::type
                it = boost::begin(range); it != boost::end(range); ++it)
        {
            f(*it);
        }
    }
};


template <closure_selector Closure>
struct fe_range_per_segment_with_closure
{
    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {
        typedef typename add_const_if_c
            <
                is_const<Range>::value,
                typename point_type<Range>::type
            >::type point_type;

        typedef typename boost::range_iterator<Range>::type iterator_type;

        iterator_type it = boost::begin(range);
        if (it == boost::end(range))
        {
            return;
        }

        iterator_type previous = it++;
        while(it != boost::end(range))
        {
            model::referring_segment<point_type> s(*previous, *it);
            f(s);
            previous = it++;
        }
    }
};


template <>
struct fe_range_per_segment_with_closure<open>
{
    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {    
        fe_range_per_segment_with_closure<closed>::apply(range, f);

        model::referring_segment
            <
                typename add_const_if_c
                    <
                        is_const<Range>::value,
                        typename point_type<Range>::type
                    >::type
            > s(range::back(range), range::front(range));

        f(s);
    }
};


struct fe_range_per_segment
{
    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {
        fe_range_per_segment_with_closure
            <
                closure<Range>::value
            >::apply(range, f);
    }
};


struct fe_polygon_per_point
{
    template <typename Polygon, typename Functor>
    static inline void apply(Polygon& poly, Functor& f)
    {
        fe_range_per_point::apply(exterior_ring(poly), f);

        typename interior_return_type<Polygon>::type
            rings = interior_rings(poly);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            fe_range_per_point::apply(*it, f);
        }
    }

};

struct fe_polygon_per_segment
{
    template <typename Polygon, typename Functor>
    static inline void apply(Polygon& poly, Functor& f)
    {
        fe_range_per_segment::apply(exterior_ring(poly), f);

        typename interior_return_type<Polygon>::type
            rings = interior_rings(poly);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            fe_range_per_segment::apply(*it, f);
        }
    }

};

// Implementation of multi, for both point and segment,
// just calling the single version.
template <typename Policy>
struct for_each_multi
{
    template <typename MultiGeometry, typename Functor>
    static inline void apply(MultiGeometry& multi, Functor& f)
    {
        for (typename boost::range_iterator<MultiGeometry>::type
                it = boost::begin(multi); it != boost::end(multi); ++it)
        {
            Policy::apply(*it, f);
        }
    }
};

}} // namespace detail::for_each
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag_cast<typename tag<Geometry>::type, multi_tag>::type
>
struct for_each_point: not_implemented<Tag>
{};


template <typename Point>
struct for_each_point<Point, point_tag>
    : detail::for_each::fe_point_per_point
{};


template <typename Linestring>
struct for_each_point<Linestring, linestring_tag>
    : detail::for_each::fe_range_per_point
{};


template <typename Ring>
struct for_each_point<Ring, ring_tag>
    : detail::for_each::fe_range_per_point
{};


template <typename Polygon>
struct for_each_point<Polygon, polygon_tag>
    : detail::for_each::fe_polygon_per_point
{};


template
<
    typename Geometry,
    typename Tag = typename tag_cast<typename tag<Geometry>::type, multi_tag>::type
>
struct for_each_segment: not_implemented<Tag>
{};

template <typename Point>
struct for_each_segment<Point, point_tag>
    : detail::for_each::fe_point_per_segment
{};


template <typename Linestring>
struct for_each_segment<Linestring, linestring_tag>
    : detail::for_each::fe_range_per_segment
{};


template <typename Ring>
struct for_each_segment<Ring, ring_tag>
    : detail::for_each::fe_range_per_segment
{};


template <typename Polygon>
struct for_each_segment<Polygon, polygon_tag>
    : detail::for_each::fe_polygon_per_segment
{};


template <typename MultiGeometry>
struct for_each_point<MultiGeometry, multi_tag>
    : detail::for_each::for_each_multi
        <
            // Specify the dispatch of the single-version as policy
            for_each_point
                <
                    typename add_const_if_c
                        <
                            is_const<MultiGeometry>::value,
                            typename boost::range_value<MultiGeometry>::type
                        >::type
                >
        >
{};


template <typename MultiGeometry>
struct for_each_segment<MultiGeometry, multi_tag>
    : detail::for_each::for_each_multi
        <
            // Specify the dispatch of the single-version as policy
            for_each_segment
                <
                    typename add_const_if_c
                        <
                            is_const<MultiGeometry>::value,
                            typename boost::range_value<MultiGeometry>::type
                        >::type
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brf_for_each{point}
\details \det_for_each{point}
\ingroup for_each
\param geometry \param_geometry
\param f \par_for_each_f{point}
\tparam Geometry \tparam_geometry
\tparam Functor \tparam_functor

\qbk{[include reference/algorithms/for_each_point.qbk]}
\qbk{[heading Example]}
\qbk{[for_each_point] [for_each_point_output]}
\qbk{[for_each_point_const] [for_each_point_const_output]}
*/
template<typename Geometry, typename Functor>
inline Functor for_each_point(Geometry& geometry, Functor f)
{
    concepts::check<Geometry>();

    dispatch::for_each_point<Geometry>::apply(geometry, f);
    return f;
}


/*!
\brief \brf_for_each{segment}
\details \det_for_each{segment}
\ingroup for_each
\param geometry \param_geometry
\param f \par_for_each_f{segment}
\tparam Geometry \tparam_geometry
\tparam Functor \tparam_functor

\qbk{[include reference/algorithms/for_each_segment.qbk]}
\qbk{[heading Example]}
\qbk{[for_each_segment_const] [for_each_segment_const_output]}
*/
template<typename Geometry, typename Functor>
inline Functor for_each_segment(Geometry& geometry, Functor f)
{
    concepts::check<Geometry>();

    dispatch::for_each_segment<Geometry>::apply(geometry, f);
    return f;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP

/* for_each.hpp
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
*/