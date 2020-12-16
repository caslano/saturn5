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
7NrcwQOjJUJRpgThv+xFl89jMnFenKjebVYjc+mB9pEulfCcPIvu2js1uZwlQbcw6GUddLoE9WLQU05UY9lOHqKqyVLVsIKX0CWTTfNFqeRPrNmoS9naKaH8R47aDlyEvMhkb5CaSQK/k4wCRnuNbBLr0u/zIv1Lt4KlCWoonaCUja6SRIl0JkLNy0p55En5Tegh+yW8YQAyBQNVyxrxE68halJlyKZy40tSN4M0LbplN3IfYyGFCuAobKavQ+aNE7ngj/mNBEs0Tx9/NGkzRasVjl7M1jgyTOx/Zplr2wRFFJ3GNc3No5BkVbaWWUUO7BpSyDHvabPR0nEDUADomtvUpOXn/MIZ6sBxpf+tC7lCoVfvlA+y92cUmZ+UgpRH33551r6U/ck2jkHetFpHIDFuYmRfRjC3VRxN8tc59miS100FLwlm++CHLfoO+s4AsvQUNfOD24qTvh8OGrsV729wlUyBonKzUwnwxuc3wGI3bffH51dWwSOcAc2bfebkAGU9JwWMvUixzE+b2Ew7hYNijXTBZV65FlX+wbLB+6XqWXKDWMO9zEtbeTfyqnRWkBZgfQ9jkGW7eM3Roi5IxyOJS3EHfuWmF2ijCQZAx8iNX17c4A65/VZN479nAi+ffuaWKyxFT3vcoKf5Nj1tfR5ZNuemXRj8yC3p1qp0mmnwAJMtzeWov9mLncD0XA0AbdbG70DFfGWj8zaodrDlwdh473He3FIHSXuh8tVxaIvKhIxQ5Vi8qu6AZbHiE/qy+iVVJm99UA2NKrNIVMeNBhIxiulWsI2smSlTKAsAZ+nJ7lDJKtOThY2BarlgSj+UHnyLLey97rYGYvtiLNU15fS05Vv0aUz3BuHTfrMMNxxNtYzRHqcawQK97TwkoX86InGhy6XuOt1q9kjh/TPPUaD6p9wDR/vgoYwPcMXPouPuP41nxUU9xHoa+aobiTPeRVUdCrm3+mHKOT55bzA+kA2XBL+yEkxuhQJalcGkO3SCUMV6X21c3Sjkh4rXg9oYHL1JxA4DFfBVP6FRC9HQ+UY9xRTx86D6eVT9PM4jH6x9l2jj9bgawxh4gsB8+BhnsHBizG1OF5JG2/DBjDrH2f6oXqxyPBZTtP1Crwo6bNOnqSjuU84UZTL1Uyz6fLjlgFsAXp54ZWN4gjwlZ729P1Z2QB7L4SE+23dWVSOYCTuEmdBYzZif5oiwZiPuXsTmyWqaLm/01RoSDr366h1QiQPSWuXKZTK16Vp8RVWNVA0EZcyRq8ICj00VM5Gxq32xL10HQWvWF/mEqgTyiC2YDWBiBSVPCQJ7H1GdtAwVtihNQQps6YpM18e1LbLhvLUc4k+Md7YHchS+hqXq3p8tqrh7CfpTP1Gg/yG7C+hB381NIjFxT7YCHa1QrWKLSDMLEIHmCBellQ1ia3RTSg8QlrYuEPoW/VUP3iljdEsj2rOTVn2hkfgiqAzyNgeVLoMJYWq8a4nQSoHhAk5TH8mW7uTaHzBgbZjDoWpKdCZQtszcsZO7KWMTrOejvKu02bbmhR5tyJPNqikT54OXszUfvUikgi4GFfVCoMgWeboOuV3YrqgBJsMr7m5vzsKztT2bkGrbdxEe/yPnKSM6CR1xTaB82oWRngdjiomAWqshf9uq3PW3mcmxyvroKfoUYXjL86IDmmMsQG4LLhB5mutRqu3K4w/AHxWL2j+VHvoDhLIzP54l+rqVAVq8qWqQmw52ONM8+DAdjX6+QTapj6DRUIGZFCh/gLVFbpYmcDTqO6SAcW0+UDrJPAPQU0Lbtr/AUONpsx/CA+VT8yMXMQAWEI5ik1yxd16b7fnkfo8MzwePOTk8iaTt4uX/r+ZdeEA=
*/