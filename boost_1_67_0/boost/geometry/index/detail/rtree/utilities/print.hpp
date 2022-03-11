// Boost.Geometry Index
//
// R-tree ostreaming visitor implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_PRINT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_PRINT_HPP

#include <iostream>

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
    BOOST_MPL_ASSERT_MSG((false), NOT_IMPLEMENTED_FOR_THIS_TAG, (Tag));
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
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
*/