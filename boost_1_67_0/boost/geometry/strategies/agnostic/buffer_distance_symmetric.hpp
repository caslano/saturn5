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