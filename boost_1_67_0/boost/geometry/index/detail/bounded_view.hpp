// Boost.Geometry Index
//
// This view makes possible to treat some simple primitives as its bounding geometry
// e.g. box, nsphere, etc.
//
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_BOUNDED_VIEW_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_BOUNDED_VIEW_HPP

#include <boost/mpl/assert.hpp>

#include <boost/geometry/algorithms/envelope.hpp>

#include <boost/geometry/strategies/index.hpp>

namespace boost { namespace geometry {

namespace index { namespace detail {


template <typename Geometry, typename BoundingGeometry, typename Strategy>
struct bounded_view_base_cs_tag
{
    typedef typename Strategy::cs_tag type;
};

template <typename Geometry, typename BoundingGeometry>
struct bounded_view_base_cs_tag<Geometry, BoundingGeometry, default_strategy>
    : geometry::cs_tag<Geometry>
{};


template
<
    typename Geometry,
    typename BoundingGeometry,
    typename Strategy,
    typename Tag = typename geometry::tag<Geometry>::type,
    typename BoundingTag = typename geometry::tag<BoundingGeometry>::type,
    typename CSTag = typename bounded_view_base_cs_tag
                        <
                            Geometry, BoundingGeometry, Strategy
                        >::type
>
struct bounded_view_base
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THOSE_GEOMETRIES,
        (types<Tag, BoundingTag, CSTag>));
};


// Segment -> Box

template <typename Segment, typename Box, typename Strategy>
struct bounded_view_base<Segment, Box, Strategy, segment_tag, box_tag, cartesian_tag>
{
public:
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(Segment const& segment, Strategy const& )
        : m_segment(segment)
    {}
    
    template <std::size_t Dimension>
    inline coordinate_type get_min() const
    {
        return boost::numeric_cast<coordinate_type>(
                (std::min)( geometry::get<0, Dimension>(m_segment),
                            geometry::get<1, Dimension>(m_segment) ) );
    }

    template <std::size_t Dimension>
    inline coordinate_type get_max() const
    {
        return boost::numeric_cast<coordinate_type>(
                (std::max)( geometry::get<0, Dimension>(m_segment),
                            geometry::get<1, Dimension>(m_segment) ) );
    }

private:
    Segment const& m_segment;
};

template <typename Segment, typename Box, typename Strategy, typename CSTag>
struct bounded_view_base<Segment, Box, Strategy, segment_tag, box_tag, CSTag>
{
    template <typename S>
    inline void envelope(Segment const& segment, S const& strategy)
    {
        geometry::envelope(segment, m_box,
                           strategy.get_envelope_segment_strategy());
    }

    inline void envelope(Segment const& segment, default_strategy const& )
    {
        geometry::envelope(segment, m_box);
    }

public:
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(Segment const& segment, Strategy const& strategy)
    {
        envelope(segment, strategy);
    }

    template <std::size_t Dimension>
    inline coordinate_type get_min() const
    {
        return geometry::get<min_corner, Dimension>(m_box);
    }

    template <std::size_t Dimension>
    inline coordinate_type get_max() const
    {
        return geometry::get<max_corner, Dimension>(m_box);
    }

private:
    Box m_box;
};

// Box -> Box

template <typename BoxIn, typename Box, typename Strategy, typename CSTag>
struct bounded_view_base<BoxIn, Box, Strategy, box_tag, box_tag, CSTag>
{
public:
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(BoxIn const& box, Strategy const& )
        : m_box(box)
    {}

    template <std::size_t Dimension>
    inline coordinate_type get_min() const
    {
        return boost::numeric_cast<coordinate_type>(
                geometry::get<min_corner, Dimension>(m_box) );
    }

    template <std::size_t Dimension>
    inline coordinate_type get_max() const
    {
        return boost::numeric_cast<coordinate_type>(
                geometry::get<max_corner, Dimension>(m_box) );
    }

private:
    BoxIn const& m_box;
};

// Point -> Box

template <typename Point, typename Box, typename Strategy, typename CSTag>
struct bounded_view_base<Point, Box, Strategy, point_tag, box_tag, CSTag>
{
public:
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(Point const& point, Strategy const& )
        : m_point(point)
    {}

    template <std::size_t Dimension>
    inline coordinate_type get_min() const
    {
        return boost::numeric_cast<coordinate_type>(
                geometry::get<Dimension>(m_point) );
    }

    template <std::size_t Dimension>
    inline coordinate_type get_max() const
    {
        return boost::numeric_cast<coordinate_type>(
                geometry::get<Dimension>(m_point) );
    }

private:
    Point const& m_point;
};


template <typename Geometry,
          typename BoundingGeometry,
          typename Strategy,
          typename Tag = typename geometry::tag<Geometry>::type,
          typename BoundingTag = typename geometry::tag<BoundingGeometry>::type>
struct bounded_view
    : bounded_view_base<Geometry, BoundingGeometry, Strategy>
{
    typedef bounded_view_base<Geometry, BoundingGeometry, Strategy> base_type;

    bounded_view(Geometry const& geometry, Strategy const& strategy)
        : base_type(geometry, strategy)
    {}
};

template <typename Geometry,
          typename BoundingGeometry,
          typename Tag,
          typename BoundingTag>
struct bounded_view<Geometry, BoundingGeometry, default_strategy, Tag, BoundingTag>
    : bounded_view_base
        <
            Geometry,
            BoundingGeometry,
            typename strategy::index::services::default_strategy<Geometry>::type
        >
{
    typedef typename strategy::index::services::default_strategy
        <
            Geometry
        >::type strategy_type;

    typedef bounded_view_base
        <
            Geometry,
            BoundingGeometry,
            strategy_type
        > base_type;

    explicit bounded_view(Geometry const& geometry, default_strategy const& )
        : base_type(geometry, strategy_type())
    {}
};


}} // namespace index::detail

// XXX -> Box

#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Geometry, typename Box, typename Strategy, typename Tag>
struct tag< index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag> >
{
    typedef box_tag type;
};

template <typename Geometry, typename Box, typename Strategy, typename Tag>
struct point_type< index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag> >
{
    typedef typename point_type<Box>::type type;
};

template <typename Geometry, typename Box, typename Strategy, typename Tag, std::size_t Dimension>
struct indexed_access<index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag>,
                      min_corner, Dimension>
{
    typedef index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag> box_type;
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    static inline coordinate_type get(box_type const& b)
    {
        return b.template get_min<Dimension>();
    }

    //static inline void set(box_type & b, coordinate_type const& value)
    //{
    //    BOOST_GEOMETRY_INDEX_ASSERT(false, "unable to modify a box through view");
    //}
};

template <typename Geometry, typename Box, typename Strategy, typename Tag, std::size_t Dimension>
struct indexed_access<index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag>,
                      max_corner, Dimension>
{
    typedef index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag> box_type;
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    static inline coordinate_type get(box_type const& b)
    {
        return b.template get_max<Dimension>();
    }

    //static inline void set(box_type & b, coordinate_type const& value)
    //{
    //    BOOST_GEOMETRY_INDEX_ASSERT(false, "unable to modify a box through view");
    //}
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_INDEX_DETAIL_BOUNDED_VIEW_HPP

/* bounded_view.hpp
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
*/