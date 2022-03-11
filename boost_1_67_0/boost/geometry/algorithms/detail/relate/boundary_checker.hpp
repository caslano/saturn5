// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/sub_range.hpp>
#include <boost/geometry/algorithms/num_points.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

enum boundary_query { boundary_front, boundary_back, boundary_any };

template <typename Geometry,
          typename WithinStrategy, // Point/Point equals (within) strategy
          typename Tag = typename geometry::tag<Geometry>::type>
class boundary_checker {};

template <typename Geometry, typename WithinStrategy>
class boundary_checker<Geometry, WithinStrategy, linestring_tag>
{
    typedef typename point_type<Geometry>::type point_type;

public:
    typedef WithinStrategy equals_strategy_type;

    boundary_checker(Geometry const& g)
        : has_boundary( boost::size(g) >= 2
                     && !detail::equals::equals_point_point(range::front(g),
                                                            range::back(g),
                                                            equals_strategy_type()) )
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
        , geometry(g)
#endif
    {}

    template <boundary_query BoundaryQuery>
    bool is_endpoint_boundary(point_type const& pt) const
    {
        boost::ignore_unused(pt);
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
        // may give false positives for INT
        BOOST_GEOMETRY_ASSERT( (BoundaryQuery == boundary_front || BoundaryQuery == boundary_any)
                   && detail::equals::equals_point_point(pt, range::front(geometry), WithinStrategy())
                   || (BoundaryQuery == boundary_back || BoundaryQuery == boundary_any)
                   && detail::equals::equals_point_point(pt, range::back(geometry), WithinStrategy()) );
#endif
        return has_boundary;
    }

private:
    bool has_boundary;
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
    Geometry const& geometry;
#endif
};

template <typename Geometry, typename WithinStrategy>
class boundary_checker<Geometry, WithinStrategy, multi_linestring_tag>
{
    typedef typename point_type<Geometry>::type point_type;

public:
    typedef WithinStrategy equals_strategy_type;
    
    boundary_checker(Geometry const& g)
        : is_filled(false), geometry(g)
    {}

    // First call O(NlogN)
    // Each next call O(logN)
    template <boundary_query BoundaryQuery>
    bool is_endpoint_boundary(point_type const& pt) const
    {
        typedef geometry::less<point_type, -1, typename WithinStrategy::cs_tag> less_type;

        typedef typename boost::range_size<Geometry>::type size_type;
        size_type multi_count = boost::size(geometry);

        if ( multi_count < 1 )
            return false;

        if ( ! is_filled )
        {
            //boundary_points.clear();
            boundary_points.reserve(multi_count * 2);

            typedef typename boost::range_iterator<Geometry const>::type multi_iterator;
            for ( multi_iterator it = boost::begin(geometry) ;
                  it != boost::end(geometry) ; ++ it )
            {
                typename boost::range_reference<Geometry const>::type
                    ls = *it;

                // empty or point - no boundary
                if (boost::size(ls) < 2)
                {
                    continue;
                }

                typedef typename boost::range_reference
                    <
                        typename boost::range_value<Geometry const>::type const
                    >::type point_reference;

                point_reference front_pt = range::front(ls);
                point_reference back_pt = range::back(ls);

                // linear ring or point - no boundary
                if (! equals::equals_point_point(front_pt, back_pt, equals_strategy_type()))
                {
                    // do not add points containing NaN coordinates
                    // because they cannot be reasonably compared, e.g. with MSVC
                    // an assertion failure is reported in std::equal_range()
                    if (! geometry::has_nan_coordinate(front_pt))
                    {
                        boundary_points.push_back(front_pt);
                    }
                    if (! geometry::has_nan_coordinate(back_pt))
                    {
                        boundary_points.push_back(back_pt);
                    }
                }
            }

            std::sort(boundary_points.begin(),
                      boundary_points.end(),
                      less_type());

            is_filled = true;
        }

        std::size_t equal_points_count
            = boost::size(
                std::equal_range(boundary_points.begin(),
                                 boundary_points.end(),
                                 pt,
                                 less_type())
            );

        return equal_points_count % 2 != 0;// && equal_points_count > 0; // the number is odd and > 0
    }

private:
    mutable bool is_filled;
    // TODO: store references/pointers instead of points?
    mutable std::vector<point_type> boundary_points;

    Geometry const& geometry;
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP

/* boundary_checker.hpp
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
*/