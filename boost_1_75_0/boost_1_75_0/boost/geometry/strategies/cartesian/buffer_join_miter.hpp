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
/XhYRmuSbfaq+vx5SXdcY77nBR9pMhFacXzrY85bIQbwp5/LfGUrDWkgyKBEjxy0GVeLaHqMer/msI0vWRl9XCoq+vWZqbD0WDfL21TAwWU3zIRn4E+iYuuf9LiDHUyG2PzEnf3+ahv1bz4jQ3zFjAIlqJ3R8pdaOYMPlXeOIdxrZyeU59hAo5DVV+s5W+eNC5VbH1czPwJFpqZXqM8vzm0LOG6Y9t+fMNkWTecrxjFgpo4vy/Bl8jD75DJ3Dp/cujtcNXq3WUbEuEh3cCPOyhE53d15Sj6SUnJQ+huuKpmLCbn7CcV7Qm/mHI+RQvPhay3z93Ti7ufY7htv3p0OGxU+cfKLfngvHvpt8MgXRikeQd0pubS1yvALsnvbctu74iXpDRtLyfkZ2PuC0otiyCEl4a/o1d1mrXfCs8+8JuryWWNcaS6fzjR3f+5Ac/xE+7oxburMz8U1/Af2sNcq9L3cNmnpO6XeEzuGUjs/TtJZzhB7I61WauVF9sPWpSatibxA11j3MrIEjtTpO+b6D7Cx704Y4U3b716I4qDgUyzBSqXpgzzzc+OnHcUtMbLOJHJOHV8l7Cz20RoLnzVe8RfeXrWB/tUfyyElRPfTDxsv6upFB4fiwPdgFmM33CBfdfVm8BQ6cfj0tXOYoJLke7VRTyphNE7vpdAj3IfwKGfd+kMWhxKCFjcuxnHThhbuLy90pjy8Kwa7fdEn
*/