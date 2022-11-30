// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TOPOLOGY_CHECK_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TOPOLOGY_CHECK_HPP


#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

// TODO: change the name for e.g. something with the word "exterior"

template
<
    typename Geometry,
    typename Strategy,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct topology_check
    : not_implemented<Tag>
{};

//template <typename Point, typename Strategy>
//struct topology_check<Point, Strategy, point_tag>
//{
//    static const char interior = '0';
//    static const char boundary = 'F';
//
//    static const bool has_interior = true;
//    static const bool has_boundary = false;
//
//    topology_check(Point const&) {}
//    template <typename IgnoreBoundaryPoint>
//    topology_check(Point const&, IgnoreBoundaryPoint const&) {}
//};

template <typename Linestring, typename Strategy>
struct topology_check<Linestring, Strategy, linestring_tag>
{
    static const char interior = '1';
    static const char boundary = '0';

    topology_check(Linestring const& ls, Strategy const& strategy)
        : m_ls(ls)
        , m_strategy(strategy)
        , m_is_initialized(false)
    {}

    bool has_interior() const
    {
        init();
        return m_has_interior;
    }

    bool has_boundary() const
    {
        init();
        return m_has_boundary;
    }

    /*template <typename Point>
    bool check_boundary_point(Point const& point) const
    {
        init();
        return m_has_boundary
            && ( equals::equals_point_point(point, range::front(m_ls))
              || equals::equals_point_point(point, range::back(m_ls)) );
    }*/

    template <typename Visitor>
    void for_each_boundary_point(Visitor & visitor) const
    {
        init();
        if (m_has_boundary)
        {
            if (visitor.apply(range::front(m_ls), m_strategy))
                visitor.apply(range::back(m_ls), m_strategy);
        }
    }

private:
    void init() const
    {
        if (m_is_initialized)
            return;

        std::size_t count = boost::size(m_ls);
        m_has_interior = count > 0;
        // NOTE: Linestring with all points equal is treated as 1d linear ring
        m_has_boundary = count > 1
            && ! detail::equals::equals_point_point(range::front(m_ls),
                                                    range::back(m_ls),
                                                    m_strategy);

        m_is_initialized = true;
    }

    Linestring const& m_ls;
    Strategy const& m_strategy;

    mutable bool m_is_initialized;

    mutable bool m_has_interior;
    mutable bool m_has_boundary;
};

template <typename MultiLinestring, typename Strategy>
struct topology_check<MultiLinestring, Strategy, multi_linestring_tag>
{
    static const char interior = '1';
    static const char boundary = '0';

    topology_check(MultiLinestring const& mls, Strategy const& strategy)
        : m_mls(mls)
        , m_strategy(strategy)
        , m_is_initialized(false)
    {}

    bool has_interior() const
    {
        init();
        return m_has_interior;
    }

    bool has_boundary() const
    {
        init();
        return m_has_boundary;
    }

    template <typename Point>
    bool check_boundary_point(Point const& point) const
    {
        init();

        if (! m_has_boundary)
            return false;

        std::size_t count = count_equal(m_endpoints.begin(), m_endpoints.end(), point);

        return count % 2 != 0; // odd count -> boundary
    }

    template <typename Visitor>
    void for_each_boundary_point(Visitor & visitor) const
    {
        init();
        if (m_has_boundary)
        {
            for_each_boundary_point(m_endpoints.begin(), m_endpoints.end(), visitor);
        }
    }

private:
    typedef geometry::less<void, -1, typename Strategy::cs_tag> less_type;

    void init() const
    {
        if (m_is_initialized)
            return;

        m_endpoints.reserve(boost::size(m_mls) * 2);

        m_has_interior = false;

        typedef typename boost::range_iterator<MultiLinestring const>::type ls_iterator;
        for ( ls_iterator it = boost::begin(m_mls) ; it != boost::end(m_mls) ; ++it )
        {
            typename boost::range_reference<MultiLinestring const>::type
                ls = *it;

            std::size_t count = boost::size(ls);

            if (count > 0)
            {
                m_has_interior = true;
            }

            if (count > 1)
            {
                typedef typename boost::range_reference
                    <
                        typename boost::range_value<MultiLinestring const>::type const
                    >::type point_reference;
                
                point_reference front_pt = range::front(ls);
                point_reference back_pt = range::back(ls);

                // don't store boundaries of linear rings, this doesn't change anything
                if (! equals::equals_point_point(front_pt, back_pt, m_strategy))
                {
                    // do not add points containing NaN coordinates
                    // because they cannot be reasonably compared, e.g. with MSVC
                    // an assertion failure is reported in std::equal_range()
                    // NOTE: currently ignoring_counter calling std::equal_range()
                    //   is not used anywhere in the code, still it's safer this way
                    if (! geometry::has_nan_coordinate(front_pt))
                    {
                        m_endpoints.push_back(front_pt);
                    }
                    if (! geometry::has_nan_coordinate(back_pt))
                    {
                        m_endpoints.push_back(back_pt);
                    }
                }
            }
        }

        m_has_boundary = false;

        if (! m_endpoints.empty() )
        {
            std::sort(m_endpoints.begin(), m_endpoints.end(), less_type());
            m_has_boundary = find_odd_count(m_endpoints.begin(), m_endpoints.end());
        }

        m_is_initialized = true;
    }

    template <typename It, typename Point>
    static inline std::size_t count_equal(It first, It last, Point const& point)
    {
        std::pair<It, It> rng = std::equal_range(first, last, point, less_type());
        return (std::size_t)std::distance(rng.first, rng.second);
    }

    template <typename It>
    inline bool find_odd_count(It first, It last) const
    {
        interrupting_visitor visitor;
        for_each_boundary_point(first, last, visitor);
        return visitor.found;
    }

    struct interrupting_visitor
    {
        bool found;
        interrupting_visitor() : found(false) {}
        template <typename Point>
        bool apply(Point const&, Strategy const&)
        {
            found = true;
            return false;
        }
    };

    template <typename It, typename Visitor>
    void for_each_boundary_point(It first, It last, Visitor& visitor) const
    {
        if ( first == last )
            return;

        std::size_t count = 1;
        It prev = first;
        ++first;
        for ( ; first != last ; ++first, ++prev )
        {
            // the end of the equal points subrange
            if ( ! equals::equals_point_point(*first, *prev, m_strategy) )
            {
                // odd count -> boundary
                if ( count % 2 != 0 )
                {
                    if (! visitor.apply(*prev, m_strategy))
                    {
                        return;
                    }
                }

                count = 1;
            }
            else
            {
                ++count;
            }
        }

        // odd count -> boundary
        if ( count % 2 != 0 )
        {
            visitor.apply(*prev, m_strategy);
        }
    }

private:
    MultiLinestring const& m_mls;
    Strategy const& m_strategy;

    mutable bool m_is_initialized;

    mutable bool m_has_interior;
    mutable bool m_has_boundary;

    typedef typename geometry::point_type<MultiLinestring>::type point_type;
    mutable std::vector<point_type> m_endpoints;
};

struct topology_check_areal
{
    static const char interior = '2';
    static const char boundary = '1';

    static bool has_interior() { return true; }
    static bool has_boundary() { return true; }
};

template <typename Ring, typename Strategy>
struct topology_check<Ring, Strategy, ring_tag>
    : topology_check_areal
{
    topology_check(Ring const&, Strategy const&) {}
};

template <typename Polygon, typename Strategy>
struct topology_check<Polygon, Strategy, polygon_tag>
    : topology_check_areal
{
    topology_check(Polygon const&, Strategy const&) {}
};

template <typename MultiPolygon, typename Strategy>
struct topology_check<MultiPolygon, Strategy, multi_polygon_tag>
    : topology_check_areal
{
    topology_check(MultiPolygon const&, Strategy const&) {}
    
    template <typename Point>
    static bool check_boundary_point(Point const& ) { return true; }
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TOPOLOGY_CHECK_HPP

/* topology_check.hpp
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
*/