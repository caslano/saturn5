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
s8/7YOi/dqY+1nT+mMLQ65O/Mefc6vXDW51qTrB6F5kDm4WZ7zALOZ6N+2L9m3DqN8LvGfK7zEHbkN9H+K3XuPTVa2nxs875uNThNxc6Vc/BIC0/b+1YShgi8fVzqfOqOVkd5BMaOmpO1dewA/wWdpfjPeV4f3Vc5lbBIeIeJu7h4h4jc0Inwh/hJfAnmCdzQAtBPTgfRsLrYSN4I5wH74TFcBOcD7fCEvgILIV/gQ3hUQkXTl4aw3owHkbBJjAONoXJ0A17w+awH2wLy+F58PewM7wLdoWbYDf4IEyGO2FP+CzsBV+GveGbsC/8EKbCj+AAGBtGPcEEOBT2hiPgGJgOc2EGnAvHwHI4Fl4Fx8HVcDxcByfAW+BE+Ds4Gf4RXgQfgFPgXpgJX4HT4DtwOjwIs+CH8FL4A8yFLuo/DybCAtgezoYd4RzYAxbqNXLyLhe2tmmv2dK+svQ7UPXuVel18fsOtQi98+BvYTq8GU6F1TAX3g5nwztgCfwdvBzeCcvh7+Fi+Ae4VI6vFPe9cCPcCu+BT8E/wvfhDvg5vB/+BB+EiaRpK+wJH4Xnw20wHT4GJ8AnIHlS4Sg7FW6WhKOsVLx3w51wC9wF98Jn4BtwN3wT/gka19geWAFfgHvgS/Al+DLcL+53xf0RvAkeg6/6r2UbfPp68CI5olcgetEwX/QOo9ccHoFt4EdQzaWEHeFnMAV+DAfCT+AgOT5K5opPhsfhFPO47q8OyXnj1Xmt/dUc6a8KYTgsgpFwLmwE58E4WKzjk3tmMMwmvsslvjIYAculf1oIB8AFcKhyy5xIxCPxrZT46sNMie9vUh5vwr7wLcn/AThE+tk0+B70SH9bJP1tqRzXc+7kvitRndc6584tc+cSYRxsBmtcp54vl04HkgQHI8xJCZwjp+fHhY+0zokrJpxvXtxqfst8OJt5cCHnwOl5b1sR+7lu/vPc/Oe4BcxlC5jDJvPXAuauWeatyXw19FngkwkD56qdQKzz0/znpgXOS7Ofj7YfOYEEzDmT+WZ6rpmeZ7aecvTNMTuBpNRhPtkmROaNBc0Z8yK+uWJ7EPs5YqefH7aLdFnniFnmhek5YTVI0hTKFSlE9hn5gTW9w85oHljAHLDA+V8y78s650vme+m5XjVIh+l287rOfE5XKuJBFiPVMn9L5m3JnK3g+VqHkZNI4iXWeVn5SOA8rIOI//yrdMQ372obsgeJ6sM8JyQdyUdWIZuQl5EaJLYv86SQzL7n5i2d+zv3d+7v3N+5v3N/5/7O/Z37O/d37u/c3//qLxyZ9d+a/983e375HGP2/8+b+2/M6R8V79D2U5LksbGv7IfQBf7b+E7Ry/cttW92flG5N7cirzA7lxgq7Pd/f0PpRzsncwb51ihxtA/adz2RX/VTTBvhbS324Obqub5/Vf4u9H3fndXJ1cdn5p6reTsfqfh/UN86zdyITSD5dn2LiiNN3E7Hm8rdUH+jXUUYr9iiSnOc3r6Fb/9xt7hJF27/dJ0ft1qdg+9Wcab7r+KOlT3JR0i5L3bJfi1S7oOl3FN6+5V7qbHnfsmcgmyZI1XuLchzWMu/hZR/pgrX2jmRcyxBop26HiTODkH1EM+v1D7m3LWWMmclQua1luTTWPxsWYQrvZ7EHK5tKaBHvtGROotSOt3IZ5Qu4+rYutv78tvjXZXdLb1lnXFTsyyPinu023T37GO6L3Rb52sfCJe9+uR96U6kL3Ec6lNbtkYOT9Wef1K6f3Cs4UxSjhK+rc6/U2xJiN0I8e+g7S6Hq29yG4mjvoSROSB5Dn0dNFM6tziqVLlSjvo8vXQZFpOrq+NOP5fA1l6Xnv+j0hpgf0KlRZVltHw=
*/