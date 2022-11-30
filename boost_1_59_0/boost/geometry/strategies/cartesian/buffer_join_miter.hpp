// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_MITER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_MITER_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/strategies/buffer.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*!
\brief Let the buffer create sharp corners
\ingroup strategies
\details This strategy can be used as JoinStrategy for the buffer algorithm.
    It creates a sharp corners around each convex vertex. It can be applied
    for (multi)linestrings and (multi)polygons.
    If corners are sharp by themselves, the miters might become very long. Therefore
    there is a limit (miter_limit), in terms of the used distance, which limits
    their length. The miter is not changed to a bevel form (as done in some
    other software), it is just adapted to the specified miter_limit but keeps
    its miter form.
    If the buffer distance is 5.0, and the miter limit is 2.0, generated points
    will be located at a distance of at most 10.0 (2*5) units.
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_join_miter]
[heading Output]
[$img/strategies/buffer_join_miter.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_join_round join_round]
}
 */
class join_miter
{
public:

    //! \brief Constructs the strategy
    //! \param miter_limit The miter limit, to avoid excessively long miters around sharp corners
    explicit inline join_miter(double miter_limit = 5.0)
        : m_miter_limit(valid_limit(miter_limit))
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a sharp shape around a vertex
    template <typename Point, typename DistanceType, typename RangeOut>
    inline bool apply(Point const& ip, Point const& vertex,
                Point const& perp1, Point const& perp2,
                DistanceType const& buffer_distance,
                RangeOut& range_out) const
    {
        geometry::equal_to<Point> equals;
        if (equals(ip, vertex))
        {
            return false;
        }
        if (equals(perp1, perp2))
        {
            return false;
        }

        typedef typename coordinate_type<Point>::type coordinate_type;
        typedef typename geometry::select_most_precise
        <
            coordinate_type,
            double
        >::type promoted_type;

        Point p = ip;

        // Check the distance ip-vertex (= miter distance)
        // (We calculate it manually (not using Pythagoras strategy) to reuse
        //  dx and dy)
        coordinate_type const dx = get<0>(p) - get<0>(vertex);
        coordinate_type const dy = get<1>(p) - get<1>(vertex);

        promoted_type const distance = geometry::math::sqrt(dx * dx + dy * dy);

        promoted_type const max_distance
            = m_miter_limit * geometry::math::abs(buffer_distance);

        if (distance > max_distance)
        {
            BOOST_GEOMETRY_ASSERT(distance != 0.0);

            promoted_type const proportion = max_distance / distance;
            set<0>(p, get<0>(vertex) + dx * proportion);
            set<1>(p, get<1>(vertex) + dy * proportion);
        }

        range_out.push_back(perp1);
        range_out.push_back(p);
        range_out.push_back(perp2);
        return true;
    }

    template <typename NumericType>
    inline NumericType max_distance(NumericType const& distance) const
    {
        return distance * m_miter_limit;
    }

#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    double valid_limit(double miter_limit) const
    {
        if (miter_limit < 1.0)
        {
            // It should always exceed the buffer distance
            miter_limit = 1.0;
        }
        return miter_limit;
    }

    double m_miter_limit;
};

}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_MITER_HPP

/* buffer_join_miter.hpp
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
*/