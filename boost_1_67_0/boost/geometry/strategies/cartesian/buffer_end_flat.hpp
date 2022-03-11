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