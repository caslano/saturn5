// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP


#include <algorithm>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/value_type.hpp>

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

#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/type_traits.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace for_each
{


struct fe_point_point
{
    template <typename Point, typename Functor>
    static inline bool apply(Point& point, Functor&& f)
    {
        return f(point);
    }
};


struct fe_segment_point
{
    template <typename Point, typename Functor>
    static inline bool apply(Point& , Functor&& )
    {
        // TODO: if non-const, we should extract the points from the segment
        // and call the functor on those two points

        //model::referring_segment<Point> s(point, point);
        //return f(s);

        return true;
    }
};


struct fe_point_segment
{
    template <typename Segment, typename Functor>
    static inline bool apply(Segment& s, Functor&& f)
    {
        // Or should we guarantee that the type of points is
        // point_type<Segment>::type ?
        geometry::detail::indexed_point_view<Segment, 0> p0(s);
        geometry::detail::indexed_point_view<Segment, 1> p1(s);
        return f(p0) && f(p1);
    }
};

struct fe_segment_segment
{
    template <typename Segment, typename Functor>
    static inline bool apply(Segment& s, Functor&& f)
    {
        // Or should we guarantee that the type of segment is
        // referring_segment<...> ?
        return f(s);
    }
};


template <typename Range>
struct fe_range_value
{
    typedef util::transcribe_const_t
        <
            Range,
            typename boost::range_value<Range>::type
        > type;
};

template <typename Range>
struct fe_point_type
{
    typedef util::transcribe_const_t
        <
            Range,
            typename point_type<Range>::type
        > type;
};


template <typename Range>
struct fe_point_type_is_referencable
{
    static const bool value =
        std::is_const<Range>::value
     || std::is_same
            <
                typename boost::range_reference<Range>::type,
                typename fe_point_type<Range>::type&
            >::value;
};


template
<
    typename Range,
    bool UseReferences = fe_point_type_is_referencable<Range>::value
>
struct fe_point_call_f
{
    template <typename Iterator, typename Functor>
    static inline bool apply(Iterator it, Functor&& f)
    {
        // Implementation for real references (both const and mutable)
        // and const proxy references.
        typedef typename fe_point_type<Range>::type point_type;
        point_type& p = *it;
        return f(p);
    }
};

template <typename Range>
struct fe_point_call_f<Range, false>
{
    template <typename Iterator, typename Functor>
    static inline bool apply(Iterator it, Functor&& f)
    {
        // Implementation for proxy mutable references.
        // Temporary point has to be created and assigned afterwards.
        typedef typename fe_point_type<Range>::type point_type;
        point_type p = *it;
        bool result = f(p);
        *it = p;
        return result;
    }
};


struct fe_point_range
{
    template <typename Range, typename Functor>
    static inline bool apply(Range& range, Functor&& f)
    {
        auto const end = boost::end(range);
        for (auto it = boost::begin(range); it != end; ++it)
        {
            if (! fe_point_call_f<Range>::apply(it, f))
            {
                return false;
            }
        }

        return true;
    }
};


template
<
    typename Range,
    bool UseReferences = fe_point_type_is_referencable<Range>::value
>
struct fe_segment_call_f
{
    template <typename Iterator, typename Functor>
    static inline bool apply(Iterator it0, Iterator it1, Functor&& f)
    {
        // Implementation for real references (both const and mutable)
        // and const proxy references.
        // If const proxy references are returned by iterators
        // then const real references here prevents temporary
        // objects from being destroyed.
        typedef typename fe_point_type<Range>::type point_type;
        point_type& p0 = *it0;
        point_type& p1 = *it1;
        model::referring_segment<point_type> s(p0, p1);
        return f(s);
    }
};

template <typename Range>
struct fe_segment_call_f<Range, false>
{
    template <typename Iterator, typename Functor>
    static inline bool apply(Iterator it0, Iterator it1, Functor&& f)
    {
        // Mutable proxy references returned by iterators.
        // Temporary points have to be created and assigned afterwards.
        typedef typename fe_point_type<Range>::type point_type;
        point_type p0 = *it0;
        point_type p1 = *it1;
        model::referring_segment<point_type> s(p0, p1);
        bool result = f(s);
        *it0 = p0;
        *it1 = p1;
        return result;
    }
};


template <closure_selector Closure>
struct fe_segment_range_with_closure
{
    template <typename Range, typename Functor>
    static inline bool apply(Range& range, Functor&& f)
    {
        auto it = boost::begin(range);
        auto const end = boost::end(range);
        if (it == end)
        {
            return true;
        }

        auto previous = it++;
        if (it == end)
        {
            return fe_segment_call_f<Range>::apply(previous, previous, f);
        }

        while (it != end)
        {
            if (! fe_segment_call_f<Range>::apply(previous, it, f))
            {
                return false;
            }
            previous = it++;
        }

        return true;
    }
};


template <>
struct fe_segment_range_with_closure<open>
{
    template <typename Range, typename Functor>
    static inline bool apply(Range& range, Functor&& f)
    {
        fe_segment_range_with_closure<closed>::apply(range, f);

        auto const begin = boost::begin(range);
        auto end = boost::end(range);
        if (begin == end)
        {
            return true;
        }
        
        --end;
        
        if (begin == end)
        {
            // single point ranges already handled in closed case above
            return true;
        }

        return fe_segment_call_f<Range>::apply(end, begin, f);
    }
};


struct fe_segment_range
{
    template <typename Range, typename Functor>
    static inline bool apply(Range& range, Functor&& f)
    {
        return fe_segment_range_with_closure
            <
                closure<Range>::value
            >::apply(range, f);
    }
};


template <typename RangePolicy>
struct for_each_polygon
{
    template <typename Polygon, typename Functor>
    static inline bool apply(Polygon& poly, Functor&& f)
    {
        if (! RangePolicy::apply(exterior_ring(poly), f))
        {
            return false;
        }

        typename interior_return_type<Polygon>::type
            rings = interior_rings(poly);

        auto const end = boost::end(rings);
        for (auto it = boost::begin(rings); it != end; ++it)
        {
            // NOTE: Currently lvalue iterator required
            if (! RangePolicy::apply(*it, f))
            {
                return false;
            }
        }

        return true;
    }

};

// Implementation of multi, for both point and segment,
// just calling the single version.
template <typename SinglePolicy>
struct for_each_multi
{
    template <typename MultiGeometry, typename Functor>
    static inline bool apply(MultiGeometry& multi, Functor&& f)
    {
        auto const end = boost::end(multi);
        for (auto it = boost::begin(multi); it != end; ++it)
        {
            // NOTE: Currently lvalue iterator required
            if (! SinglePolicy::apply(*it, f))
            {
                return false;
            }
        }

        return true;
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
    : detail::for_each::fe_point_point
{};


template <typename Segment>
struct for_each_point<Segment, segment_tag>
    : detail::for_each::fe_point_segment
{};


template <typename Linestring>
struct for_each_point<Linestring, linestring_tag>
    : detail::for_each::fe_point_range
{};


template <typename Ring>
struct for_each_point<Ring, ring_tag>
    : detail::for_each::fe_point_range
{};


template <typename Polygon>
struct for_each_point<Polygon, polygon_tag>
    : detail::for_each::for_each_polygon
        <
            detail::for_each::fe_point_range
        >
{};


template <typename MultiGeometry>
struct for_each_point<MultiGeometry, multi_tag>
    : detail::for_each::for_each_multi
        <
            // Specify the dispatch of the single-version as policy
            for_each_point
                <
                    typename detail::for_each::fe_range_value
                        <
                            MultiGeometry
                        >::type
                >
        >
{};


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct for_each_segment: not_implemented<Tag>
{};

template <typename Point>
struct for_each_segment<Point, point_tag>
    : detail::for_each::fe_segment_point // empty
{};


template <typename Segment>
struct for_each_segment<Segment, segment_tag>
    : detail::for_each::fe_segment_segment
{};


template <typename Linestring>
struct for_each_segment<Linestring, linestring_tag>
    : detail::for_each::fe_segment_range
{};


template <typename Ring>
struct for_each_segment<Ring, ring_tag>
    : detail::for_each::fe_segment_range
{};


template <typename Polygon>
struct for_each_segment<Polygon, polygon_tag>
    : detail::for_each::for_each_polygon
        <
            detail::for_each::fe_segment_range
        >
{};


template <typename MultiPoint>
struct for_each_segment<MultiPoint, multi_point_tag>
    : detail::for_each::fe_segment_point // empty
{};


template <typename MultiLinestring>
struct for_each_segment<MultiLinestring, multi_linestring_tag>
    : detail::for_each::for_each_multi
        <
            detail::for_each::fe_segment_range
        >
{};

template <typename MultiPolygon>
struct for_each_segment<MultiPolygon, multi_polygon_tag>
    : detail::for_each::for_each_multi
        <
            detail::for_each::for_each_polygon
                <
                    detail::for_each::fe_segment_range
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


template<typename Geometry, typename UnaryPredicate>
inline bool all_points_of(Geometry& geometry, UnaryPredicate p)
{
    concepts::check<Geometry>();

    return dispatch::for_each_point<Geometry>::apply(geometry, p);
}


template<typename Geometry, typename UnaryPredicate>
inline bool all_segments_of(Geometry const& geometry, UnaryPredicate p)
{
    concepts::check<Geometry const>();

    return dispatch::for_each_segment<Geometry const>::apply(geometry, p);
}


template<typename Geometry, typename UnaryPredicate>
inline bool any_point_of(Geometry& geometry, UnaryPredicate p)
{
    concepts::check<Geometry>();

    return ! dispatch::for_each_point<Geometry>::apply(geometry, [&](auto&& pt)
    {
        return ! p(pt);
    });
}


template<typename Geometry, typename UnaryPredicate>
inline bool any_segment_of(Geometry const& geometry, UnaryPredicate p)
{
    concepts::check<Geometry const>();

    return ! dispatch::for_each_segment<Geometry const>::apply(geometry, [&](auto&& s)
    {
        return ! p(s);
    });
}

template<typename Geometry, typename UnaryPredicate>
inline bool none_point_of(Geometry& geometry, UnaryPredicate p)
{
    concepts::check<Geometry>();

    return dispatch::for_each_point<Geometry>::apply(geometry, [&](auto&& pt)
    {
        return ! p(pt);
    });
}


template<typename Geometry, typename UnaryPredicate>
inline bool none_segment_of(Geometry const& geometry, UnaryPredicate p)
{
    concepts::check<Geometry const>();

    return dispatch::for_each_segment<Geometry const>::apply(geometry, [&](auto&& s)
    {
        return ! p(s);
    });
}


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

    dispatch::for_each_point<Geometry>::apply(geometry, [&](auto&& pt)
    {
        f(pt);
        // TODO: Implement separate function?
        return true;
    });
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

    dispatch::for_each_segment<Geometry>::apply(geometry, [&](auto&& s)
    {
        f(s);
        // TODO: Implement separate function?
        return true;
    });
    return f;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP

/* for_each.hpp
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
*/