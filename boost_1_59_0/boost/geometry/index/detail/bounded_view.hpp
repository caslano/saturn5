// Boost.Geometry Index
//
// This view makes possible to treat some simple primitives as its bounding geometry
// e.g. box, nsphere, etc.
//
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_BOUNDED_VIEW_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_BOUNDED_VIEW_HPP


#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/index/services.hpp>


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
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for these Geometries.",
        Geometry, BoundingGeometry, Strategy, Tag, BoundingTag, CSTag);
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
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(Segment const& segment, Strategy const& strategy)
    {
        geometry::envelope(segment, m_box, strategy);
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
            typename strategies::index::services::default_strategy<Geometry>::type
        >
{
    typedef typename strategies::index::services::default_strategy
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