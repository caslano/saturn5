// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_SYMMETRIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_SYMMETRIC_HPP


#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{


/*!
\brief Let the buffer algorithm create buffers with same distances
\ingroup strategies
\tparam NumericType \tparam_numeric
\details This strategy can be used as DistanceStrategy for the buffer algorithm.
    It can be applied for all geometries. It uses one distance for left and
    for right.
    If the distance is negative and used with a (multi)polygon or ring, the
    geometry will shrink (deflate) instead of expand (inflate).

\qbk{
[heading Example]
[buffer_distance_symmetric]
[heading Output]
[$img/strategies/buffer_distance_symmetric.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_distance_asymmetric distance_asymmetric]
}
 */
template<typename NumericType>
class distance_symmetric
{
public :
    //! \brief Constructs the strategy, a distance must be specified
    //! \param distance The distance (or radius) of the buffer
    explicit inline distance_symmetric(NumericType const& distance)
        : m_distance(distance)
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Returns the distance-value
    template <typename Point>
    inline NumericType apply(Point const& , Point const& ,
                buffer_side_selector )  const
    {
        return negative() ? geometry::math::abs(m_distance) : m_distance;
    }

    //! Used internally, returns -1 for deflate, 1 for inflate
    inline int factor() const
    {
        return negative() ? -1 : 1;
    }

    //! Returns true if distance is negative (aka deflate)
    inline bool negative() const
    {
        return m_distance < 0;
    }

    //! Returns the max distance distance up to the buffer will reach
    template <typename JoinStrategy, typename EndStrategy>
    inline NumericType max_distance(JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy) const
    {
        boost::ignore_unused(join_strategy, end_strategy);

        NumericType const dist = geometry::math::abs(m_distance);
        return (std::max)(join_strategy.max_distance(dist),
                          end_strategy.max_distance(dist));
    }


    //! Returns the distance at which the input is simplified before the buffer process
    inline NumericType simplify_distance() const
    {
        return geometry::math::abs(m_distance) / 1000.0;
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    NumericType m_distance;
};


}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_SYMMETRIC_HPP

/* buffer_distance_symmetric.hpp
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
*/