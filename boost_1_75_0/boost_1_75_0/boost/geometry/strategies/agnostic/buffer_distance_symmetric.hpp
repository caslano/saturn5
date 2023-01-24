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
vgwivi3LjtUdlU462Wx0q95X5oDFOMYzXCefC53vQZbcgsQ65W8dHuE18L1uXOk1w91UHux6NluJn5haW1WlWC5yXrK/t1jL0AUmdZC0fLlgzu+7+drifeTA7lC6gQvVcKA8BIfZM6go8EQ9D/2sIrzCtqMtT78rZgJtth+midLka8Gc5uIwrkAw4FkxDVvNa/7Dpam6YvoKC8MFp1R7RTZFa1upBito8aMJ7vxJ3ULevLMJhtHyDpZXfVBV8528KU+tPX4HG19lBtc5k13F7IFEU8Uj1UyJ9pOmcKVWJKVDTwB7ZcvKtk53ldkA56kJy+VK1QJ8SERLoz9ty+b9KjvfL/DJJ2oH/LSjuwaJc0wabweqGsmaplI9xhPeyIn4Wr0n76r7TawY+TbeMav3CGCz9GSTkUw4bxyyA4XXacIpnpc7a+stk/sP1vYppVIL87ZoHlkdfpjHca0u+CnLpFt9jIQyTjgW4bRh7/Rd2vSlkqPC3bn7l1qX/gXIy3+qTeaipBkEOiI9K2i6jNYqXY54Rj8y+Imb4lJbLVS02YZ1suLcrXG8TYAj3z3e+Tf7uWDhBN/I5glEdpRi60E1G3392sowo17Rrzg/fmcpA2xkkFA2rmlVnsBOqOis2hIGNg7BtRPcyY0o7vIbRjGavwUXnuxIhzrLw1pQXurFujMluxcKb31iY2Q4fTR5MlbGIxXXAbs12S3jzh4t
*/