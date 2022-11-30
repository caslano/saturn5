// Boost.Geometry Index
//
// R-tree ostreaming visitor implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_PRINT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_PRINT_HPP

#include <iostream>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {
    
namespace utilities {

namespace dispatch {

template <typename Point, size_t Dimension>
struct print_point
{
    BOOST_STATIC_ASSERT(0 < Dimension);

    static inline void apply(std::ostream & os, Point const& p)
    {
        print_point<Point, Dimension - 1>::apply(os, p);

        os << ", " << geometry::get<Dimension - 1>(p);
    }
};

template <typename Point>
struct print_point<Point, 1>
{
    static inline void apply(std::ostream & os, Point const& p)
    {
        os << geometry::get<0>(p);
    }
};

template <typename Box, size_t Corner, size_t Dimension>
struct print_corner
{
    BOOST_STATIC_ASSERT(0 < Dimension);

    static inline void apply(std::ostream & os, Box const& b)
    {
        print_corner<Box, Corner, Dimension - 1>::apply(os, b);

        os << ", " << geometry::get<Corner, Dimension - 1>(b);
    }
};

template <typename Box, size_t Corner>
struct print_corner<Box, Corner, 1>
{
    static inline void apply(std::ostream & os, Box const& b)
    {
        os << geometry::get<Corner, 0>(b);
    }
};

template <typename Indexable, typename Tag>
struct print_indexable
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Indexable type.",
        Indexable, Tag);
};

template <typename Indexable>
struct print_indexable<Indexable, box_tag>
{
    static const size_t dimension = geometry::dimension<Indexable>::value;

    static inline void apply(std::ostream &os, Indexable const& i)
    {
        os << '(';
        print_corner<Indexable, min_corner, dimension>::apply(os, i);
        os << ")x(";
        print_corner<Indexable, max_corner, dimension>::apply(os, i);
        os << ')';
    }
};

template <typename Indexable>
struct print_indexable<Indexable, point_tag>
{
    static const size_t dimension = geometry::dimension<Indexable>::value;

    static inline void apply(std::ostream &os, Indexable const& i)
    {
        os << '(';
        print_point<Indexable, dimension>::apply(os, i);
        os << ')';
    }
};

template <typename Indexable>
struct print_indexable<Indexable, segment_tag>
{
    static const size_t dimension = geometry::dimension<Indexable>::value;

    static inline void apply(std::ostream &os, Indexable const& i)
    {
        os << '(';
        print_corner<Indexable, 0, dimension>::apply(os, i);
        os << ")-(";
        print_corner<Indexable, 1, dimension>::apply(os, i);
        os << ')';
    }
};

} // namespace dispatch

template <typename Indexable> inline
void print_indexable(std::ostream & os, Indexable const& i)
{
    dispatch::print_indexable<
        Indexable,
        typename tag<Indexable>::type
    >::apply(os, i);
}

} // namespace utilities

namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
struct print
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::translator_type translator_type;

    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    inline print(std::ostream & o, translator_type const& t)
        : os(o), tr(t), level(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        spaces(level) << "INTERNAL NODE - L:" << level << " Ch:" << elements.size() << " @:" << &n << '\n';
        
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            spaces(level);
            detail::utilities::print_indexable(os, it->first);
            os << " ->" << it->second << '\n';
        }

        size_t level_backup = level;
        ++level;

        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            rtree::apply_visitor(*this, *it->second);
        }

        level = level_backup;
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        spaces(level) << "LEAF - L:" << level << " V:" << elements.size() << " @:" << &n << '\n';
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            spaces(level);
            detail::utilities::print_indexable(os, tr(*it));
            os << '\n';
        }
    }

    inline std::ostream & spaces(size_t level)
    {
        for ( size_t i = 0 ; i < 2 * level ; ++i )
            os << ' ';
        return os;
    }

    std::ostream & os;
    translator_type const& tr;

    size_t level;
};

} // namespace visitors

template <typename Rtree> inline
void print(std::ostream & os, Rtree const& tree)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::print<
        typename RTV::members_holder
    > print_v(os, rtv.translator());
    rtv.apply_visitor(print_v);
}

}} // namespace rtree::utilities

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_PRINT_HPP

/* print.hpp
+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
*/