// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_FLAT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_FLAT_HPP

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/tags.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace buffer
{


/*!
\brief Let the buffer create flat ends
\ingroup strategies
\details This strategy can be used as EndStrategy for the buffer algorithm.
    It creates a flat end for each linestring-end. It can be applied
    for (multi)linestrings. Also it is applicable for spikes in (multi)polygons.
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_end_flat]
[heading Output]
[$img/strategies/buffer_end_flat.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_end_round end_round]
}
 */
class end_flat
{

public :

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a flat end
    template <typename Point, typename RangeOut, typename DistanceStrategy>
    inline void apply(Point const& penultimate_point,
                Point const& perp_left_point,
                Point const& ultimate_point,
                Point const& perp_right_point,
                buffer_side_selector side,
                DistanceStrategy const& distance,
                RangeOut& range_out) const
    {
        typedef typename coordinate_type<Point>::type coordinate_type;

        typedef typename geometry::select_most_precise
        <
            coordinate_type,
            double
        >::type promoted_type;

        promoted_type const dist_left = distance.apply(penultimate_point, ultimate_point, buffer_side_left);
        promoted_type const dist_right = distance.apply(penultimate_point, ultimate_point, buffer_side_right);

        bool reversed = (side == buffer_side_left && dist_right < 0 && -dist_right > dist_left)
                    || (side == buffer_side_right && dist_left < 0 && -dist_left > dist_right)
                    ;
        if (reversed)
        {
            range_out.push_back(perp_right_point);
            range_out.push_back(perp_left_point);
        }
        else
        {
            range_out.push_back(perp_left_point);
            range_out.push_back(perp_right_point);
        }
        // Don't add the ultimate_point (endpoint of the linestring).
        // The buffer might be generated completely at one side.
        // In other cases it does no harm but is further useless
    }

    template <typename NumericType>
    static inline NumericType max_distance(NumericType const& distance)
    {
        return distance;
    }

    //! Returns the piece_type (flat end)
    static inline piece_type get_piece_type()
    {
        return buffered_flat_end;
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_FLAT_HPP

/* buffer_end_flat.hpp
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
*/