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