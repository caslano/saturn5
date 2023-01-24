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
rbEkRokuBoPXx62OD/39uxpy7beHWSu91dOPdfLiFQD7F3iBUIzuENzrO3tod6aV9ZCFb0Des4ts1DrzNfixDhoENW989Fq6UM+/s+Vx6c5wCKk/57EOHpeOvy5bqBpjUby2r5AFydAgvVL7UVFmvoPqvdL2my3hj23WbdyjE1sYmOPmw9egKAv9tmfXfcIJ7qSzy61XSR6YIoNv62N+y9kXmQ/QcTibPy0tlKLUey2xdvMv3EJ2TlsbWg/Bnc87W+cfDrme41UjflCcB1w+qtFHe22tFvnpJSmXUyMRPC7N5XZRzGJwHe5mZPUS/hE3eg/iDTg17Hr9PdZNICGlBUu827SI0qthmW5ITQoQTHarHzG+4kwxabEFtKAbN6wmoV/MAVcoXZIVOeOyfpXzzMSxrTsNTJFSTVJfZvP2JYrIlnsFdfpVIkvesahn/QzaUCMexeuWmr0l+evq7K2HDcz35ItGj1FHjUplCh/UwX9AhYyOihPb588NsbKLoudVHpemEn7jBP9AHO4oeM+uVbWF32R7PaHZDEIp0RGMmon49kO8H0aa2Phj27llAlXvTe/XZ8vAGbOs+ussT2DSY1i86STU47HQoBMJPmCMflc2X5ni6UKM5HvILupbSz6MOd16vb5p0pb1r9UBs93fXTscz1AQ2FgdNhMmJ7AcJLGIgYuMxhXp4+lTxwDi7+WuKys/UV6r6yWPddr3
*/