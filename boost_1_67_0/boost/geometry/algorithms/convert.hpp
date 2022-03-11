// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CONVERT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CONVERT_HPP


#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/for_each.hpp>
#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/convert_indexed_to_indexed.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/reversible_view.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
// Silence warning C4512: assignment operator could not be generated
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127 4512)
#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace conversion
{

template
<
    typename Point,
    typename Box,
    std::size_t Index,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct point_to_box
{
    static inline void apply(Point const& point, Box& box)
    {
        typedef typename coordinate_type<Box>::type coordinate_type;

        set<Index, Dimension>(box,
                boost::numeric_cast<coordinate_type>(get<Dimension>(point)));
        point_to_box
            <
                Point, Box,
                Index, Dimension + 1, DimensionCount
            >::apply(point, box);
    }
};


template
<
    typename Point,
    typename Box,
    std::size_t Index,
    std::size_t DimensionCount
>
struct point_to_box<Point, Box, Index, DimensionCount, DimensionCount>
{
    static inline void apply(Point const& , Box& )
    {}
};

template <typename Box, typename Range, bool Close, bool Reverse>
struct box_to_range
{
    static inline void apply(Box const& box, Range& range)
    {
        traits::resize<Range>::apply(range, Close ? 5 : 4);
        assign_box_corners_oriented<Reverse>(box, range);
        if (Close)
        {
            range::at(range, 4) = range::at(range, 0);
        }
    }
};

template <typename Segment, typename Range>
struct segment_to_range
{
    static inline void apply(Segment const& segment, Range& range)
    {
        traits::resize<Range>::apply(range, 2);

        typename boost::range_iterator<Range>::type it = boost::begin(range);

        assign_point_from_index<0>(segment, *it);
        ++it;
        assign_point_from_index<1>(segment, *it);
    }
};

template
<
    typename Range1,
    typename Range2,
    bool Reverse = false
>
struct range_to_range
{
    typedef typename reversible_view
        <
            Range1 const,
            Reverse ? iterate_reverse : iterate_forward
        >::type rview_type;
    typedef typename closeable_view
        <
            rview_type const,
            geometry::closure<Range1>::value
        >::type view_type;

    struct default_policy
    {
        template <typename Point1, typename Point2>
        static inline void apply(Point1 const& point1, Point2 & point2)
        {
            geometry::detail::conversion::convert_point_to_point(point1, point2);
        }
    };
    
    static inline void apply(Range1 const& source, Range2& destination)
    {
        apply(source, destination, default_policy());
    }

    template <typename ConvertPointPolicy>
    static inline ConvertPointPolicy apply(Range1 const& source, Range2& destination,
                                           ConvertPointPolicy convert_point)
    {
        geometry::clear(destination);

        rview_type rview(source);

        // We consider input always as closed, and skip last
        // point for open output.
        view_type view(rview);

        typedef typename boost::range_size<Range1>::type size_type;
        size_type n = boost::size(view);
        if (geometry::closure<Range2>::value == geometry::open)
        {
            n--;
        }

        // If size == 0 && geometry::open <=> n = numeric_limits<size_type>::max()
        // but ok, sice below it == end()

        size_type i = 0;
        for (typename boost::range_iterator<view_type const>::type it
            = boost::begin(view);
            it != boost::end(view) && i < n;
            ++it, ++i)
        {
            typename boost::range_value<Range2>::type point;
            convert_point.apply(*it, point);
            range::push_back(destination, point);
        }

        return convert_point;
    }
};

template <typename Polygon1, typename Polygon2>
struct polygon_to_polygon
{
    typedef range_to_range
        <
            typename geometry::ring_type<Polygon1>::type,
            typename geometry::ring_type<Polygon2>::type,
            geometry::point_order<Polygon1>::value
                != geometry::point_order<Polygon2>::value
        > per_ring;

    static inline void apply(Polygon1 const& source, Polygon2& destination)
    {
        // Clearing managed per ring, and in the resizing of interior rings

        per_ring::apply(geometry::exterior_ring(source),
            geometry::exterior_ring(destination));

        // Container should be resizeable
        traits::resize
            <
                typename boost::remove_reference
                <
                    typename traits::interior_mutable_type<Polygon2>::type
                >::type
            >::apply(interior_rings(destination), num_interior_rings(source));

        typename interior_return_type<Polygon1 const>::type
            rings_source = interior_rings(source);
        typename interior_return_type<Polygon2>::type
            rings_dest = interior_rings(destination);

        typename detail::interior_iterator<Polygon1 const>::type
            it_source = boost::begin(rings_source);
        typename detail::interior_iterator<Polygon2>::type
            it_dest = boost::begin(rings_dest);

        for ( ; it_source != boost::end(rings_source); ++it_source, ++it_dest)
        {
            per_ring::apply(*it_source, *it_dest);
        }
    }
};

template <typename Single, typename Multi, typename Policy>
struct single_to_multi: private Policy
{
    static inline void apply(Single const& single, Multi& multi)
    {
        traits::resize<Multi>::apply(multi, 1);
        Policy::apply(single, *boost::begin(multi));
    }
};



template <typename Multi1, typename Multi2, typename Policy>
struct multi_to_multi: private Policy
{
    static inline void apply(Multi1 const& multi1, Multi2& multi2)
    {
        traits::resize<Multi2>::apply(multi2, boost::size(multi1));

        typename boost::range_iterator<Multi1 const>::type it1
                = boost::begin(multi1);
        typename boost::range_iterator<Multi2>::type it2
                = boost::begin(multi2);

        for (; it1 != boost::end(multi1); ++it1, ++it2)
        {
            Policy::apply(*it1, *it2);
        }
    }
};


}} // namespace detail::conversion
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename tag_cast<typename tag<Geometry1>::type, multi_tag>::type,
    typename Tag2 = typename tag_cast<typename tag<Geometry2>::type, multi_tag>::type,
    std::size_t DimensionCount = dimension<Geometry1>::type::value,
    bool UseAssignment = boost::is_same<Geometry1, Geometry2>::value
                         && !boost::is_array<Geometry1>::value
>
struct convert: not_implemented<Tag1, Tag2, boost::mpl::int_<DimensionCount> >
{};


template
<
    typename Geometry1, typename Geometry2,
    typename Tag,
    std::size_t DimensionCount
>
struct convert<Geometry1, Geometry2, Tag, Tag, DimensionCount, true>
{
    // Same geometry type -> copy whole geometry
    static inline void apply(Geometry1 const& source, Geometry2& destination)
    {
        destination = source;
    }
};


template
<
    typename Geometry1, typename Geometry2,
    std::size_t DimensionCount
>
struct convert<Geometry1, Geometry2, point_tag, point_tag, DimensionCount, false>
    : detail::conversion::point_to_point<Geometry1, Geometry2, 0, DimensionCount>
{};


template
<
    typename Box1, typename Box2,
    std::size_t DimensionCount
>
struct convert<Box1, Box2, box_tag, box_tag, DimensionCount, false>
    : detail::conversion::indexed_to_indexed<Box1, Box2, 0, DimensionCount>
{};


template
<
    typename Segment1, typename Segment2,
    std::size_t DimensionCount
>
struct convert<Segment1, Segment2, segment_tag, segment_tag, DimensionCount, false>
    : detail::conversion::indexed_to_indexed<Segment1, Segment2, 0, DimensionCount>
{};


template <typename Segment, typename LineString, std::size_t DimensionCount>
struct convert<Segment, LineString, segment_tag, linestring_tag, DimensionCount, false>
    : detail::conversion::segment_to_range<Segment, LineString>
{};


template <typename Ring1, typename Ring2, std::size_t DimensionCount>
struct convert<Ring1, Ring2, ring_tag, ring_tag, DimensionCount, false>
    : detail::conversion::range_to_range
        <
            Ring1,
            Ring2,
            geometry::point_order<Ring1>::value
                != geometry::point_order<Ring2>::value
        >
{};

template <typename LineString1, typename LineString2, std::size_t DimensionCount>
struct convert<LineString1, LineString2, linestring_tag, linestring_tag, DimensionCount, false>
    : detail::conversion::range_to_range<LineString1, LineString2>
{};

template <typename Polygon1, typename Polygon2, std::size_t DimensionCount>
struct convert<Polygon1, Polygon2, polygon_tag, polygon_tag, DimensionCount, false>
    : detail::conversion::polygon_to_polygon<Polygon1, Polygon2>
{};

template <typename Box, typename Ring>
struct convert<Box, Ring, box_tag, ring_tag, 2, false>
    : detail::conversion::box_to_range
        <
            Box,
            Ring,
            geometry::closure<Ring>::value == closed,
            geometry::point_order<Ring>::value == counterclockwise
        >
{};


template <typename Box, typename Polygon>
struct convert<Box, Polygon, box_tag, polygon_tag, 2, false>
{
    static inline void apply(Box const& box, Polygon& polygon)
    {
        typedef typename ring_type<Polygon>::type ring_type;

        convert
            <
                Box, ring_type,
                box_tag, ring_tag,
                2, false
            >::apply(box, exterior_ring(polygon));
    }
};


template <typename Point, typename Box, std::size_t DimensionCount>
struct convert<Point, Box, point_tag, box_tag, DimensionCount, false>
{
    static inline void apply(Point const& point, Box& box)
    {
        detail::conversion::point_to_box
            <
                Point, Box, min_corner, 0, DimensionCount
            >::apply(point, box);
        detail::conversion::point_to_box
            <
                Point, Box, max_corner, 0, DimensionCount
            >::apply(point, box);
    }
};


template <typename Ring, typename Polygon, std::size_t DimensionCount>
struct convert<Ring, Polygon, ring_tag, polygon_tag, DimensionCount, false>
{
    static inline void apply(Ring const& ring, Polygon& polygon)
    {
        typedef typename ring_type<Polygon>::type ring_type;
        convert
            <
                Ring, ring_type,
                ring_tag, ring_tag,
                DimensionCount, false
            >::apply(ring, exterior_ring(polygon));
    }
};


template <typename Polygon, typename Ring, std::size_t DimensionCount>
struct convert<Polygon, Ring, polygon_tag, ring_tag, DimensionCount, false>
{
    static inline void apply(Polygon const& polygon, Ring& ring)
    {
        typedef typename ring_type<Polygon>::type ring_type;

        convert
            <
                ring_type, Ring,
                ring_tag, ring_tag,
                DimensionCount, false
            >::apply(exterior_ring(polygon), ring);
    }
};


// Dispatch for multi <-> multi, specifying their single-version as policy.
// Note that, even if the multi-types are mutually different, their single
// version types might be the same and therefore we call boost::is_same again

template <typename Multi1, typename Multi2, std::size_t DimensionCount>
struct convert<Multi1, Multi2, multi_tag, multi_tag, DimensionCount, false>
    : detail::conversion::multi_to_multi
        <
            Multi1,
            Multi2,
            convert
                <
                    typename boost::range_value<Multi1>::type,
                    typename boost::range_value<Multi2>::type,
                    typename single_tag_of
                                <
                                    typename tag<Multi1>::type
                                >::type,
                    typename single_tag_of
                                <
                                    typename tag<Multi2>::type
                                >::type,
                    DimensionCount
                >
        >
{};


template <typename Single, typename Multi, typename SingleTag, std::size_t DimensionCount>
struct convert<Single, Multi, SingleTag, multi_tag, DimensionCount, false>
    : detail::conversion::single_to_multi
        <
            Single,
            Multi,
            convert
                <
                    Single,
                    typename boost::range_value<Multi>::type,
                    typename tag<Single>::type,
                    typename single_tag_of
                                <
                                    typename tag<Multi>::type
                                >::type,
                    DimensionCount,
                    false
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct convert
{
    static inline void apply(Geometry1 const& geometry1, Geometry2& geometry2)
    {
        concepts::check_concepts_and_equal_dimensions<Geometry1 const, Geometry2>();
        dispatch::convert<Geometry1, Geometry2>::apply(geometry1, geometry2);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct convert<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    struct visitor: static_visitor<void>
    {
        Geometry2& m_geometry2;

        visitor(Geometry2& geometry2)
            : m_geometry2(geometry2)
        {}

        template <typename Geometry1>
        inline void operator()(Geometry1 const& geometry1) const
        {
            convert<Geometry1, Geometry2>::apply(geometry1, m_geometry2);
        }
    };

    static inline void apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
        Geometry2& geometry2
    )
    {
        boost::apply_visitor(visitor(geometry2), geometry1);
    }
};

}


/*!
\brief Converts one geometry to another geometry
\details The convert algorithm converts one geometry, e.g. a BOX, to another
geometry, e.g. a RING. This only works if it is possible and applicable.
If the point-order is different, or the closure is different between two
geometry types, it will be converted correctly by explicitly reversing the
points or closing or opening the polygon rings.
\ingroup convert
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry (source)
\param geometry2 \param_geometry (target)

\qbk{[include reference/algorithms/convert.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline void convert(Geometry1 const& geometry1, Geometry2& geometry2)
{
    resolve_variant::convert<Geometry1, Geometry2>::apply(geometry1, geometry2);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_CONVERT_HPP

/* convert.hpp
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
*/