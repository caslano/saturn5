// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2018, Oracle and/or its affiliates.

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

template <typename Geometry,
          typename EqPPStrategy,
          typename Tag = typename geometry::tag<Geometry>::type>
struct topology_check
    : not_implemented<Tag>
{};

//template <typename Point>
//struct topology_check<Point, point_tag>
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

template <typename Linestring, typename EqPPStrategy>
struct topology_check<Linestring, EqPPStrategy, linestring_tag>
{
    static const char interior = '1';
    static const char boundary = '0';

    topology_check(Linestring const& ls)
        : m_ls(ls)
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
            if (visitor.apply(range::front(m_ls)))
                visitor.apply(range::back(m_ls));
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
                                                    EqPPStrategy());

        m_is_initialized = true;
    }

    Linestring const& m_ls;
    mutable bool m_is_initialized;

    mutable bool m_has_interior;
    mutable bool m_has_boundary;
};

template <typename MultiLinestring, typename EqPPStrategy>
struct topology_check<MultiLinestring, EqPPStrategy, multi_linestring_tag>
{
    static const char interior = '1';
    static const char boundary = '0';

    topology_check(MultiLinestring const& mls)
        : m_mls(mls)
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
    typedef geometry::less<void, -1, typename EqPPStrategy::cs_tag> less_type;

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
                if (! equals::equals_point_point(front_pt, back_pt, EqPPStrategy()))
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
    static inline bool find_odd_count(It first, It last)
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
        bool apply(Point const&)
        {
            found = true;
            return false;
        }
    };

    template <typename It, typename Visitor>
    static void for_each_boundary_point(It first, It last, Visitor& visitor)
    {
        if ( first == last )
            return;

        std::size_t count = 1;
        It prev = first;
        ++first;
        for ( ; first != last ; ++first, ++prev )
        {
            // the end of the equal points subrange
            if ( ! equals::equals_point_point(*first, *prev, EqPPStrategy()) )
            {
                // odd count -> boundary
                if ( count % 2 != 0 )
                {
                    if (! visitor.apply(*prev))
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
            visitor.apply(*prev);
        }
    }

private:
    MultiLinestring const& m_mls;
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

template <typename Ring, typename EqPPStrategy>
struct topology_check<Ring, EqPPStrategy, ring_tag>
    : topology_check_areal
{
    topology_check(Ring const&) {}
};

template <typename Polygon, typename EqPPStrategy>
struct topology_check<Polygon, EqPPStrategy, polygon_tag>
    : topology_check_areal
{
    topology_check(Polygon const&) {}
};

template <typename MultiPolygon, typename EqPPStrategy>
struct topology_check<MultiPolygon, EqPPStrategy, multi_polygon_tag>
    : topology_check_areal
{
    topology_check(MultiPolygon const&) {}
    
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