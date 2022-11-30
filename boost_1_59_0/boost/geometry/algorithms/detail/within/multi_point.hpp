// Boost.Geometry

// Copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_MULTI_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_MULTI_POINT_HPP


#include <algorithm>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

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

#include <boost/geometry/util/type_traits.hpp>


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
        auto const s = strategy.relate(multi_point, point);

        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            if (! s.apply(*it, point))
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
        geometry::envelope(linear_or_areal, box, strategy);
        geometry::detail::expand_by_epsilon(box);

        // Test each Point with envelope and then geometry if needed
        // If in the exterior, break
        bool result = false;

        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            typedef decltype(strategy.covered_by(*it, box)) point_in_box_type;

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
        static const bool is_linear = util::is_linear<LinearOrAreal>::value;

        // TODO: box pairs could be constructed on the fly, inside the rtree

        // Prepare range of envelopes and ids
        std::size_t count2 = boost::size(linear_or_areal);
        typedef std::pair<box2_type, std::size_t> box_pair_type;
        typedef std::vector<box_pair_type> box_pair_vector;
        box_pair_vector boxes(count2);
        for (std::size_t i = 0 ; i < count2 ; ++i)
        {
            geometry::envelope(linear_or_areal, boxes[i].first, strategy);
            geometry::detail::expand_by_epsilon(boxes[i].first);
            boxes[i].second = i;
        }

        // Create R-tree
        typedef index::parameters<index::rstar<4>, Strategy> index_parameters_type;
        index::rtree<box_pair_type, index_parameters_type>
            rtree(boxes.begin(), boxes.end(),
                  index_parameters_type(index::rstar<4>(), strategy));

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