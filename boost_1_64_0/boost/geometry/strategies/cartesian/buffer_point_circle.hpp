// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_CIRCLE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_CIRCLE_HPP

#include <cstddef>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/strategies/buffer.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*!
\brief Create a circular buffer around a point
\ingroup strategies
\details This strategy can be used as PointStrategy for the buffer algorithm.
    It creates a circular buffer around a point. It can be applied
    for points and multi_points, but also for a linestring (if it is degenerate,
    so consisting of only one point) and for polygons (if it is degenerate).
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_point_circle]
[heading Output]
[$img/strategies/buffer_point_circle.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_point_square point_square]
\* [link geometry.reference.strategies.strategy_buffer_geographic_point_circle geographic_point_circle]
}
 */
class point_circle
{
public :
    //! \brief Constructs the strategy
    //! \param count number of points for the created circle (if count
    //! is smaller than 3, count is internally set to 3)
    explicit point_circle(std::size_t count = 90)
        : m_count((count < 3u) ? 3u : count)
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a circle around point using distance_strategy
    template
    <
        typename Point,
        typename OutputRange,
        typename DistanceStrategy
    >
    inline void apply(Point const& point,
                DistanceStrategy const& distance_strategy,
                OutputRange& output_range) const
    {
        typedef typename boost::range_value<OutputRange>::type output_point_type;

        typedef typename geometry::select_most_precise
            <
                typename geometry::select_most_precise
                    <
                        typename geometry::coordinate_type<Point>::type,
                        typename geometry::coordinate_type<output_point_type>::type
                    >::type,
                double
            >::type promoted_type;

        promoted_type const buffer_distance = distance_strategy.apply(point, point,
                        strategy::buffer::buffer_side_left);

        promoted_type const two_pi = geometry::math::two_pi<promoted_type>();

        promoted_type const diff = two_pi / promoted_type(m_count);
        promoted_type a = 0;

        for (std::size_t i = 0; i < m_count; i++, a -= diff)
        {
            output_point_type p;
            set<0>(p, get<0>(point) + buffer_distance * cos(a));
            set<1>(p, get<1>(point) + buffer_distance * sin(a));
            output_range.push_back(p);
        }

        // Close it:
        output_range.push_back(output_range.front());
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    std::size_t m_count;
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_CIRCLE_HPP

/* buffer_point_circle.hpp
GEN9LfEc989cQ1i6myhj9UHGi6W2PtVk9qmo2qfuOorLJGXdLPipqJsz8rmv4tliFtapBWxMu/na3fXnZGf9uza08JbYKwuDqCtOf/+F7+R9+cyzLm38xTvByPppL2H9wemnPHj6rvznJ9y47Ow/nBx9d821uFbhY+P9P7n7+X8e1Xj6Y0uTT3+/6rs4kPtXLv/6juKvlH4v9v5ZB3Z96+xdU25D7LIYPV104dtnrbhq3Wdnr74mv2oUDkA8M4LRE/v6z3v7jRlPPPv5uklzX63GYal/5DF61sMF4e5NpV+7as9dq/9d8hQeZP/Ow+jl5bv9v3vmnxM7fn76pI5rJuGA0cXZjH5Ssf7OGV29c7IGew/Z9kcdF6/VhYz+2KFjvx2oqvruiTlzFm2a7EWsNnJ6gy9U9Oqat+aOSkx66TPz34Xdbbxcu54/fNFns1r/1Tj98Id+NP3lJ7Cm5/JHPx86JHrK8nNeHHVe4thZ7V9HbMcy+u4rezruyf7Lrx+6fvoHV11+wfWo/9GM/uLt+2vuumLXrnV/3rdq/dWvvcKuKxn93Bu/8tPfPl5eftbjnVsiF9+AAxKruJ4R10dKjj3znUVF7xYVjL+3+5dYL3P6fZds+sLcHff3vHzEv259e+ZUNNxXOH3CoeHmp1e83j972pUXbtt6y9sYG3MZ/bTCK7/znU1FK/d97dR7X5q1fgHm5nGMfvdJLW+9v3jBs1f88eXHQ54QDjB5eHnfqG2bNDBz5469E5fsHPXSv3Hg4xwuX/Toth3vH7PmofO3LLvzvAdvx6GpR3icN02ZVXzPEZff+d7W+y54+sIDHXjHYQ6jv/PO6C/fdNzOc5c8uT01Yf4r+ANiT3E9z5z+7BMfvH3JW1svmnLE3TvWw0c/bw9t993k+80HtzX/7ZYvfmn0nmlXw/8RPJ535T4w44Sd782/Om/PWv9VOMw1jdv92WWvPlGrR649683Tuu8quRk2i8Yz+pK/z5zhf2fb+bc2rpv4+siL8FKBDk6/vbxoWVXv4HVLFjectOuy66cgzrz97Fl72prXc3fuPvOmsS89dcNlOAR3gF3LaXR/g+57/AG+jAL6qVNi78b2qcCzgGzsOBt4PPAcYDfwXOAm4HnA+4HnA78NvBD4KJvjgMxOnofuXfB1vrAzGd/fJzuo2u1s3BwHLAKO14TdCcCTxDXL9nbWn4FB4JFAft4LeA7wKODlwEnA3cCjgfeyMRX4OHAK8GdsPAP+Xtzf2f53YAmQnS84BngEG1iBM4DTgAvFOmJ7I3AGcDVwJrAXOAvIxvjZwPOBc4BXAucCbwSWMvvAMuBjwOOATwLLNRGPRzS6r8LKRPEYj+/3UDy+BLkc4JeBbGq5CjgO+FXgscBrNFEf1wHrgV8HsjrbBWQT224gG9NvAJ4LvJHicxNwF/BmILN1C/B7wD3A54C3Al8D3gZ8E/gNIDv7cTurH+CdFKe7eDlYeYx7Ndo8aj9ZwGOpHN/1QB74PWAZ8DGPma+d8pVnyLeP8v0EOIe1TSXfpcPYu5Py3UX27lby7aN8lRny3Qu5CcD7gKXAbyn58vcObe9Wsncb2fuGWr69Q5fvCcr3JJXvKbV8w+R7iPLtpXyPKP1r396h+9c86l9V1L/mU/9aQP1rIfWvaupfi6h/Lab+dTy1nyXUv06g/nUi9a+TqH8tpf5VQ/2rlvpXHbWbeupfXupfDdS/Gql/NVH/aqb+tYz613LqXy3Uv1qpf/mof7VR/2qndrnUI6/p2bW+iMc0zbzH20nxWAVcBFwNXApcA1wPXAccBJ4MvAy4AXgrMAR8GBgGPgPUgb8F9gDfBfYC2ZmhPuBkYARYATyV9VM=
*/