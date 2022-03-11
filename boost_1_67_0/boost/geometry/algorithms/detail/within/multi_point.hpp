// Boost.Geometry

// Copyright (c) 2017, 2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_MULTI_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_MULTI_POINT_HPP


#include <algorithm>
#include <vector>

#include <boost/range.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/disjoint.hpp>


namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within {

struct multi_point_point
{
    template <typename MultiPoint, typename Point, typename Strategy>
    static inline bool apply(MultiPoint const& multi_point,
                             Point const& point,
                             Strategy const& strategy)
    {
        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            if (! strategy.apply(*it, point))
            {
                return false;
            }
        }

        // all points of MultiPoint inside Point
        return true;
    }
};

// NOTE: currently the strategy is ignored, math::equals() is used inside geometry::less<>
struct multi_point_multi_point
{
    template <typename MultiPoint1, typename MultiPoint2, typename Strategy>
    static inline bool apply(MultiPoint1 const& multi_point1,
                             MultiPoint2 const& multi_point2,
                             Strategy const& /*strategy*/)
    {
        typedef typename boost::range_value<MultiPoint2>::type point2_type;
        typedef typename Strategy::cs_tag cs_tag;
        typedef geometry::less<void, -1, cs_tag> less_type;

        less_type const less = less_type();

        std::vector<point2_type> points2(boost::begin(multi_point2), boost::end(multi_point2));
        std::sort(points2.begin(), points2.end(), less);

        bool result = false;

        typedef typename boost::range_const_iterator<MultiPoint1>::type iterator;
        for ( iterator it = boost::begin(multi_point1) ; it != boost::end(multi_point1) ; ++it )
        {
            if (! std::binary_search(points2.begin(), points2.end(), *it, less))
            {
                return false;
            }
            else
            {
                result = true;
            }
        }

        return result;
    }
};


// TODO: the complexity could be lesser
//   the second geometry could be "prepared"/sorted
// For Linear geometries partition could be used
// For Areal geometries point_in_geometry() would have to call the winding
//   strategy differently, currently it linearly calls the strategy for each
//   segment. So the segments would have to be sorted in a way consistent with
//   the strategy and then the strategy called only for the segments in range.
template <bool Within>
struct multi_point_single_geometry
{
    template <typename MultiPoint, typename LinearOrAreal, typename Strategy>
    static inline bool apply(MultiPoint const& multi_point,
                             LinearOrAreal const& linear_or_areal,
                             Strategy const& strategy)
    {
        //typedef typename boost::range_value<MultiPoint>::type point1_type;
        typedef typename point_type<LinearOrAreal>::type point2_type;
        typedef model::box<point2_type> box2_type;

        // Create envelope of geometry
        box2_type box;
        geometry::envelope(linear_or_areal, box, strategy.get_envelope_strategy());
        geometry::detail::expand_by_epsilon(box);

        typedef typename Strategy::disjoint_point_box_strategy_type point_in_box_type;

        // Test each Point with envelope and then geometry if needed
        // If in the exterior, break
        bool result = false;

        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            int in_val = 0;

            // exterior of box and of geometry
            if (! point_in_box_type::apply(*it, box)
                || (in_val = point_in_geometry(*it, linear_or_areal, strategy)) < 0)
            {
                result = false;
                break;
            }

            // interior : interior/boundary
            if (Within ? in_val > 0 : in_val >= 0)
            {
                result = true;
            }
        }

        return result;
    }
};


// TODO: same here, probably the complexity could be lesser
template <bool Within>
struct multi_point_multi_geometry
{
    template <typename MultiPoint, typename LinearOrAreal, typename Strategy>
    static inline bool apply(MultiPoint const& multi_point,
                             LinearOrAreal const& linear_or_areal,
                             Strategy const& strategy)
    {
        typedef typename point_type<LinearOrAreal>::type point2_type;
        typedef model::box<point2_type> box2_type;
        static const bool is_linear = is_same
            <
                typename tag_cast
                    <
                        typename tag<LinearOrAreal>::type,
                        linear_tag
                    >::type,
                linear_tag
            >::value;

        typename Strategy::envelope_strategy_type const
            envelope_strategy = strategy.get_envelope_strategy();

        // TODO: box pairs could be constructed on the fly, inside the rtree

        // Prepare range of envelopes and ids
        std::size_t count2 = boost::size(linear_or_areal);
        typedef std::pair<box2_type, std::size_t> box_pair_type;
        typedef std::vector<box_pair_type> box_pair_vector;
        box_pair_vector boxes(count2);
        for (std::size_t i = 0 ; i < count2 ; ++i)
        {
            geometry::envelope(linear_or_areal, boxes[i].first, envelope_strategy);
            geometry::detail::expand_by_epsilon(boxes[i].first);
            boxes[i].second = i;
        }

        // Create R-tree
        typedef strategy::index::services::from_strategy
            <
                Strategy
            > index_strategy_from;
        typedef index::parameters
            <
                index::rstar<4>, typename index_strategy_from::type
            > index_parameters_type;
        index::rtree<box_pair_type, index_parameters_type>
            rtree(boxes.begin(), boxes.end(),
                  index_parameters_type(index::rstar<4>(), index_strategy_from::get(strategy)));

        // For each point find overlapping envelopes and test corresponding single geometries
        // If a point is in the exterior break
        bool result = false;

        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            // TODO: investigate the possibility of using satisfies
            // TODO: investigate the possibility of using iterative queries (optimization below)
            box_pair_vector inters_boxes;
            rtree.query(index::intersects(*it), std::back_inserter(inters_boxes));

            bool found_interior = false;
            bool found_boundary = false;
            int boundaries = 0;

            typedef typename box_pair_vector::const_iterator box_iterator;
            for (box_iterator box_it = inters_boxes.begin() ;
                 box_it != inters_boxes.end() ; ++box_it )
            {
                int const in_val = point_in_geometry(*it,
                    range::at(linear_or_areal, box_it->second), strategy);

                if (in_val > 0)
                {
                    found_interior = true;
                }
                else if (in_val == 0)
                {
                    ++boundaries;
                }

                // If the result was set previously (interior or
                // interior/boundary found) the only thing that needs to be
                // done for other points is to make sure they're not
                // overlapping the exterior no need to analyse boundaries.
                if (result && in_val >= 0)
                {
                    break;
                }
            }

            if (boundaries > 0)
            {
                if (is_linear && boundaries % 2 == 0)
                {
                    found_interior = true;
                }
                else
                {
                    found_boundary = true;
                }
            }

            // exterior
            if (! found_interior && ! found_boundary)
            {
                result = false;
                break;
            }

            // interior : interior/boundary
            if (Within ? found_interior : (found_interior || found_boundary))
            {
                result = true;
            }
        }

        return result;
    }
};

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_MULTI_POINT_HPP

/* multi_point.hpp
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
*/