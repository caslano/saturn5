// Boost.Geometry Index
//
// R-tree OpenGL drawing visitor implementation
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_GL_DRAW_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_GL_DRAW_HPP

#include <limits>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

namespace utilities {

namespace dispatch {

template <typename Point, size_t Dimension>
struct gl_draw_point
{};

template <typename Point>
struct gl_draw_point<Point, 2>
{
    static inline void apply(Point const& p, typename coordinate_type<Point>::type z)
    {
        typename coordinate_type<Point>::type const& x = geometry::get<0>(p);
        typename coordinate_type<Point>::type const& y = geometry::get<1>(p);
        /*glBegin(GL_POINT);
        glVertex3f(x, y, z);
        glEnd();*/
        glBegin(GL_QUADS);
        glVertex3f(x+1, y, z);
        glVertex3f(x, y+1, z);
        glVertex3f(x-1, y, z);
        glVertex3f(x, y-1, z);
        glEnd();
    }
};

template <typename Box, size_t Dimension>
struct gl_draw_box
{};

template <typename Box>
struct gl_draw_box<Box, 2>
{
    static inline void apply(Box const& b, typename coordinate_type<Box>::type z)
    {
        glBegin(GL_LINE_LOOP);
        glVertex3f(geometry::get<min_corner, 0>(b), geometry::get<min_corner, 1>(b), z);
        glVertex3f(geometry::get<max_corner, 0>(b), geometry::get<min_corner, 1>(b), z);
        glVertex3f(geometry::get<max_corner, 0>(b), geometry::get<max_corner, 1>(b), z);
        glVertex3f(geometry::get<min_corner, 0>(b), geometry::get<max_corner, 1>(b), z);
        glEnd();
    }
};

template <typename Segment, size_t Dimension>
struct gl_draw_segment
{};

template <typename Segment>
struct gl_draw_segment<Segment, 2>
{
    static inline void apply(Segment const& s, typename coordinate_type<Segment>::type z)
    {
        glBegin(GL_LINES);
        glVertex3f(geometry::get<0, 0>(s), geometry::get<0, 1>(s), z);
        glVertex3f(geometry::get<1, 0>(s), geometry::get<1, 1>(s), z);
        glEnd();
    }
};

template <typename Indexable, typename Tag>
struct gl_draw_indexable
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Indexable type.",
        Indexable, Tag);
};

template <typename Box>
struct gl_draw_indexable<Box, box_tag>
    : gl_draw_box<Box, geometry::dimension<Box>::value>
{};

template <typename Point>
struct gl_draw_indexable<Point, point_tag>
    : gl_draw_point<Point, geometry::dimension<Point>::value>
{};

template <typename Segment>
struct gl_draw_indexable<Segment, segment_tag>
    : gl_draw_segment<Segment, geometry::dimension<Segment>::value>
{};

} // namespace dispatch

template <typename Indexable> inline
void gl_draw_indexable(Indexable const& i, typename coordinate_type<Indexable>::type z)
{
    dispatch::gl_draw_indexable<
        Indexable,
        typename tag<Indexable>::type
    >::apply(i, z);
}

} // namespace utilities

namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
struct gl_draw
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::translator_type translator_type;

    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    inline gl_draw(translator_type const& t,
                   size_t level_first = 0,
                   size_t level_last = (std::numeric_limits<size_t>::max)(),
                   typename coordinate_type<box_type>::type z_coord_level_multiplier = 1
    )
        : tr(t)
        , level_f(level_first)
        , level_l(level_last)
        , z_mul(z_coord_level_multiplier)
        , level(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        if ( level_f <= level )
        {
            size_t level_rel = level - level_f;

            if ( level_rel == 0 )
                glColor3f(0.75f, 0.0f, 0.0f);
            else if ( level_rel == 1 )
                glColor3f(0.0f, 0.75f, 0.0f);
            else if ( level_rel == 2 )
                glColor3f(0.0f, 0.0f, 0.75f);
            else if ( level_rel == 3 )
                glColor3f(0.75f, 0.75f, 0.0f);
            else if ( level_rel == 4 )
                glColor3f(0.75f, 0.0f, 0.75f);
            else if ( level_rel == 5 )
                glColor3f(0.0f, 0.75f, 0.75f);
            else
                glColor3f(0.5f, 0.5f, 0.5f);

            for (typename elements_type::const_iterator it = elements.begin();
                it != elements.end(); ++it)
            {
                detail::utilities::gl_draw_indexable(it->first, level_rel * z_mul);
            }
        }
        
        size_t level_backup = level;
        ++level;

        if ( level < level_l )
        {
            for (typename elements_type::const_iterator it = elements.begin();
                it != elements.end(); ++it)
            {
                rtree::apply_visitor(*this, *it->second);
            }
        }

        level = level_backup;
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        if ( level_f <= level )
        {
            size_t level_rel = level - level_f;

            glColor3f(0.25f, 0.25f, 0.25f);

            for (typename elements_type::const_iterator it = elements.begin();
                it != elements.end(); ++it)
            {
                detail::utilities::gl_draw_indexable(tr(*it), level_rel * z_mul);
            }
        }
    }

    translator_type const& tr;
    size_t level_f;
    size_t level_l;
    typename coordinate_type<box_type>::type z_mul;

    size_t level;
};

} // namespace visitors

template <typename Rtree> inline
void gl_draw(Rtree const& tree,
             size_t level_first = 0,
             size_t level_last = (std::numeric_limits<size_t>::max)(),
             typename coordinate_type<
                    typename Rtree::bounds_type
                >::type z_coord_level_multiplier = 1
             )
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    if ( !tree.empty() )
    {
        glColor3f(0.75f, 0.75f, 0.75f);
        detail::utilities::gl_draw_indexable(tree.bounds(), 0);
    }

    visitors::gl_draw<
        typename RTV::members_holder
    > gl_draw_v(rtv.translator(), level_first, level_last, z_coord_level_multiplier);

    rtv.apply_visitor(gl_draw_v);
}

}} // namespace rtree::utilities

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_GL_DRAW_HPP

/* gl_draw.hpp
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
*/