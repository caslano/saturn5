// Boost.Geometry Index
//
// R-tree OpenGL drawing visitor implementation
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_GL_DRAW_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_GL_DRAW_HPP

#include <boost/mpl/assert.hpp>

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
    BOOST_MPL_ASSERT_MSG((false), NOT_IMPLEMENTED_FOR_THIS_TAG, (Tag));
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