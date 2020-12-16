// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_ASYMMETRIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_ASYMMETRIC_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{


/*!
\brief Let the buffer for linestrings be asymmetric
\ingroup strategies
\tparam NumericType \tparam_numeric
\details This strategy can be used as DistanceStrategy for the buffer algorithm.
    It can be applied for (multi)linestrings. It uses a (potentially) different
    distances for left and for right. This means the (multi)linestrings are
    interpreted having a direction.

\qbk{
[heading Example]
[buffer_distance_asymmetric]
[heading Output]
[$img/strategies/buffer_distance_asymmetric.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_distance_symmetric distance_symmetric]
}
 */
template<typename NumericType>
class distance_asymmetric
{
public :
    //! \brief Constructs the strategy, two distances must be specified
    //! \param left The distance (or radius) of the buffer on the left side
    //! \param right The distance on the right side
    distance_asymmetric(NumericType const& left,
                NumericType const& right)
        : m_left(left)
        , m_right(right)
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Returns the distance-value for the specified side
    template <typename Point>
    inline NumericType apply(Point const& , Point const& ,
                buffer_side_selector side)  const
    {
        NumericType result = side == buffer_side_left ? m_left : m_right;
        return negative() ? math::abs(result) : result;
    }

    //! Used internally, returns -1 for deflate, 1 for inflate
    inline int factor() const
    {
        return negative() ? -1 : 1;
    }

    //! Returns true if both distances are negative
    inline bool negative() const
    {
        return m_left < 0 && m_right < 0;
    }

    //! Returns the max distance distance up to the buffer will reach
    template <typename JoinStrategy, typename EndStrategy>
    inline NumericType max_distance(JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy) const
    {
        boost::ignore_unused(join_strategy, end_strategy);

        NumericType const left = geometry::math::abs(m_left);
        NumericType const right = geometry::math::abs(m_right);
        NumericType const dist = (std::max)(left, right);
        return (std::max)(join_strategy.max_distance(dist),
                          end_strategy.max_distance(dist));
    }

    //! Returns the distance at which the input is simplified before the buffer process
    inline NumericType simplify_distance() const
    {
        NumericType const left = geometry::math::abs(m_left);
        NumericType const right = geometry::math::abs(m_right);
        return (std::min)(left, right) / 1000.0;
    }

#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    NumericType m_left;
    NumericType m_right;
};


}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_ASYMMETRIC_HPP

/* buffer_distance_asymmetric.hpp
t9jpIqPjTsfs9bfTpXY9ON3YzuwXvt782vza/Nr82vz6f3n1bM9XODaC/91XrvU2/PLvnwblP/k6/j/sz8X585rVLc2NtWu94Bbb/uqwc1z686dEXhq9bO3aXre8s/d1e5m0SXPMd6KS373XzxUi2f3+J8dy82vzqy7KZx69uD6M5kt4P35ndn8uCbGb4M4HcN2OHYWvOpRrUOz4YazPIq6nNR1+CzRr3X58NwWs0LpwTX8u5bHr4T4DaAe7FF4L5mjdgXy3CizQuoP4ngdowG6AvcFc/2JH4P6gFjsGPwMivfKlBe58OO+ZsCNwyfFcNlOm7nd8/g1O7kn6SSIVoBy7Fn4aHILdDPc8mc/lsGPwClCFHT6FWMC0nsQPb/97ka7YUXgK6NET//C7oC22lIgMBr170i94IRiI3QhvVyoyXOvCc0BHTYeHlPF5InYcfhSEetIX+MOR/D6ilh+FXc5nYOqzgnkBUfpYX4HP0XxWo2XgW8Bs9Qm/PIbPnDS9ku+agKUaP1w1VmRlT+rCW47jez/aLhyp4jti2nf4GvCkloc7jee7OeoHvnoCn/tqbPDpcW6V67jF8XMaMeuYw3nVfHeM9CL4O/CI1k2wRkBbysRq+C7KZN6OqD2F30eYynvqXviBf306a6wXdeELwWLtI/wRWIAtZ/C9AjAHOw7/GTT0Ik648EzWFXYpfDeoU59wx2msE7XhjmexfrCj8HRQrP7hfc9mvrEb4DfAVF1LcHt250rtF3wgKNXY4DIQ0xjguSCudeF/gBFaF26YzjGidfkiY+I8jguNEz77fNakloEPnMm4aDo8/2KOFx0TPmgcAyr3wz98IRiBXQffAUr3oy34aRDbj7rwR6BoP3zCW8yiX9hF8Akggl0KTwFh7Fr4WlCAXQ8/AAqxG+HXQHfsZngViGLrFxe3B/nYEfhAsFrHAT4BiPq/jO8vgqnqE+56OWOiMcBeHfOiNjwBzNQY4POvYI40fvhLsEDbuhJ3oFbLw1eCBi0Dd76KeceOwmeDxdqWps1mnDVmeNHVrB+14ZfmMLY6btcxlnOZX02HJ8xjnLUuPPcG5kXT4a430i/1Dx92E3OkdeFngfSmDHz8HRyn2EV3ckwsZPyxaxexl9zNvPSm/D30r4G5wA7zBaxjHmfcsOv/xveDnmacNX0Jexooxm6A+z5D29hxeNGzzDW2PMc6X8o4aLtw9HnGFjsGXwkatS580Av0H7sUvhrUaToc/jtxYEfhkaBB/cO3gMVaBh7SxJhrOvwYqNfYXmR/BpXaF/gbENf+vsR6eJtjX33+k70BLMFugb/8jnHTmNewNvRD6v2py4fRn4Ou2GE+iP6YD4ObNE4+5P2eD3Lbkt7EB7jt+FJUb+wIfCbogV0PfwWGal2+5HwzGK7l4QK+xN0NOwrPaO9xTmJ84KV8OWggdowvAbwJlmPrF4QmgWb12Yk0sGJ/YoZ36uxJo/qBTwBL9ic2+CKwQMvDT4MGbRf+ESzWeLanPKjHboS/BE3Y+mXHw3Yi5gPo+86eDNjNk0LseDdPlu3hSbm2tRf91S+xkN4E38gXVLpjN8MVfBk8pHXhY3syPmrD2/Cl3pOp2wD35QuMLdhxPsg/7gjGRMvAzw/1OA8T/1GMLV/inqrxl3jycIUns3RM+CLcWWCalocfADOwG+GPQTm2fllqd1CFHYVPAjUafyXlK4kBOzLWk5Fj8YldC/fhC7DztMzp9BHMxm6BPz6TsdL0acR8DuOMrVf674Al6ocvdv7xXMZN7fM82XYG44wdg28GyzU2uD1fiCs6kL7DlZfRdy3Pl55vAiHSG+H4lYwzdjP8Kl/gjGCX8kXYn0F37Cg=
*/