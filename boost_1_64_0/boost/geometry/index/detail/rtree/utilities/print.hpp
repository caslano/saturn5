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
P8yQsr0Vt5S9/s7vCPmd/5f7fn6m3+1/qe/t9t/DQ3/Htp/XEOq7feh5DZHN1ff5N997vf+Xr9T/5MVu97e7Zed1ob6Hn/l3/l/q+7n9vIDQ39Xt5wuEnvdhP48g9HwB++/2ob/D23/PP/N5JV+q74sytsm4qWz28Xs14pA9tRJgDmwBZ8EZMA9eCvNhCVwCF8F58DpYDNfDErgJlsL3YRn8FFbAH2EljJA9sjrBxbALXAK/VHtzSZ8v44tHbLrukfQ1kj2OEuFA2ByOhW1hFkyC8+EQWAlbwtthK7hejt8LO8BnYHf4HEyG+2EPeAD2hO/AXvA9mAI/hH1hOGnqD6PgAEn/QNgNDoH94CA42HTLnnLSN0rf7gnYUy4NlUQ4AvaCI+FQmA6Hw9HwQjhG8jkW5sPxcB6cBP8AJ0v5Z8EnxL1T3LHhp9+LIgkx957AHzmInLDZh8K6B4Xd3hOBe078/76zbfgZ39rsvrPt/4W/taWMr/v3ttr9HPz3cqjjPg7I2v/R97e6fntzTPF9fzu7/RfqsvdCXfddkO9wst/CL/ctLsnme9zm//E3ufV+3+U6pIY5MpCK1HPf3c79/U+e/4uLZv3853/DNtzfmppjqcthPArJw2W5ud7/yziHXnfvDbHuPjas7uvu0T3luvv4sJ+77l6lVc85jDSBj2mXLM1MqzxA51EMlLA8Q78ea1n/IrqR4me1yyR+dbbVSnhtiylWu2dZ5rGfCAu2a/UOdeMx01w+Ty3bGTnGkzHqouzZRSX5Us5rtS09Xc4Sxq381yh/r66HccrfagPLFeeo8xzwtbV21vQz5Rp1TJ3DkqdqV3Ce3iNPXrs8lSyY72s7B5sG58kbkOb6Z5Bm4pM0W9NXHB6cvkPorrVL38Lc4gUFIdMnYdy1z/ZWe7/aX9vqO8v0W5/j1Tks9u3GRwTn6UPCb9V5yjLMzU0cPmFUtrfUmz27rKDAV+7N4wLzJeHkfdAW1ZaMELMXlOTp9qR1tH3BM8gb59R5c0veOA/H9Hks1/Y2m/wdIX/7rPkrKfgVLaq4WKcp8j/snQmcTfUewM+9d+4sZjBzh2vsY0gI2Q1FI0ukMtYozM5oBtPMYPJSQvJK0oZC6aWeSjUveU+vhYq0eD2VpFJJKqqneVJpf9/zP7/7v/fcJTOlt31M/Xzv77+d/3b+//85579UI06B11kcHXqdj7lOle06OgvDnWtJ/ol7yb+DyeHzr+pX5B/XDMk/rhOcf7odHxsTmq5DpCvRZU/XjLLCiGnCra7rw0LbF+zt6Yn/hemx6jp6UPtytqSlW6zsTyjpaIE8RjvfSdLCAs+SnLKyWdNL8ymk6VM5WnESr1F5BA97tr/4qxf23Pih2r6xb98Anb4fkqp/Lp/9fVzIufH6XXybOMtzZwmkE3Ib5Vri0u8t9dnFWXl0vuHTJO47B575PjVft0t2++VW/dT7TmT6/Ve7rwtMX6Jup7hmwFouroMZ1wlKc3ltff4WtYcw4Wdm2xWY5sLp08t8L8HDp1nct9Vrst5UepVjl8MZ0GfmFU8rl7LVfkYH9qmlM0slH4Lsl/j3xtHnyj7mts5z96KPQn9Buf/J8aKjCVd2ijuHcbPbNwbCndYb6uuS46VTphv6Xf5hFc5eRwwjtLHsbH+Pow1usdN+G6u9JLLx+YVyu4erxQeeOz/F9+7eC09xW++Yzzf6iJmD/WRNs3zHPzE1/aXJN5bJWTnKzTTzm45yc4i9wZuImc/fFMcdmNbS+ZKn35sPUvYzHD0cXYPjHJBeKvH0WcrPaPzsUGn41vGuwx3yjWI69skqzD85biVHPDquU3NouIp86fTAJ5W7HOM8lReYoZU=
*/