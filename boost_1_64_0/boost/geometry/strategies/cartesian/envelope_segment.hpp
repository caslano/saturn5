// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/envelope.hpp>

namespace boost { namespace geometry { namespace strategy { namespace envelope
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct envelope_one_segment
{
    template<typename Point, typename Box>
    static inline void apply(Point const& p1,
                             Point const& p2,
                             Box& mbr)
    {
        geometry::detail::envelope::envelope_one_point
            <
                Dimension, DimensionCount
            >::apply(p1, mbr);

        strategy::expand::detail::point_loop
            <
                Dimension, DimensionCount
            >::apply(mbr, p2);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename CalculationType = void
>
class cartesian_segment
{
public:
    template <typename Point, typename Box>
    static inline void apply(Point const& point1, Point const& point2, Box& box)
    {
        strategy::envelope::detail::envelope_one_segment
            <
                0,
                dimension<Point>::value
            >::apply(point1, point2, box);        
    }

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_segment<CalculationType> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP

/* envelope_segment.hpp
w8Pqv01t7FNlmLHtfKwMM7adnyrDjG3nw2WYse385TJMazvfW37X2s4HyO9a23lf+V1rO/9XJQ8MbedP6b8PlXbfxnIm/dqp/Vgp292Uz7Ud+J9826atuEA5BvjVlc/p8blaDiuN7RrxXkmgvyuf/f0986WFvzlfmvqb8+UHP3O+fOtnzpcaP3O+fOJnzpdAt3zxtciXiZIvmzq67tF1lHt0i5R88a8rX2hh7OAuRWYCeaNlUP37mMf2kv1ruvP3eUrCLLahuS1sdIA6wxJvNa3rUEmrX9ufTeu8zKzUf1n6lHortJ26vbM7mNO7SQpLgPK+kqikN7B9nenNsjmT25D8VMta+47md5jOd3CVvSMdPPfxmzp47uPBHTz3594dPMvt9+3N5XRne3O5XKb/PvRX5edaWYd97c37cHVn/iffqwsQc5m2smOd+Wkupg04Fmj5WBLgysdlAZ554Qgw78MJAea8mRJg3odHBZjzKjjAvA93D6g/7wz3MOqt74IvUldqeFPKnqi8OxTYqa68yrLFJ8Y6suLpgtZBJ7QN6E9Qy6uhF5nLoN9Frrx7pgv/dnsXbo0MM773NlaGGd9TC5RhxnfSdnVmmNv7Yg+4hl2ubZ+HOpnz+9ZO5vyNcsvfGFcba5Dr7J/JX6+LCX7SmzKuuJhxg7vWlb/zslIcNkMGN7ws5nY3529od1f+/r2bnpd6fpxyDdP3+/dcw/T8ndvNczukyTDj+4fTZJjx/cPBrmH6Mlq7hg3V03Ixw9zeIRx+sWd9c9nFnvvYa13N+9BjXc3b9N6u5n3ozq6NPz/Qn4nI9hwhry0NJ+Yq900CnfNU75Noz4UacM1S97PEuu+11UoanpP7Itu91HPBajUN2bYMepTlNdeUpJQESpZ2iqumpZ5jm68rL0zLzOumjjhfzoscsszKS1zLlALMyxW8rqW+cNiAcyHP8xAvufZW+mudHZtquo47L+m4RNLRlfiMSj6uh5qO1Fhn193XRUWMnRLLbZqGXBtr1xmRznsyXC253TtM7u65zM9ZZqHVMpUeSBuxzEI/WabbNj4gywwgWslyv+CXSqtlZtjmOW91N2C5pnuigZ7rNZE8OG65jJz0f0ZeVsky+8u69SauZ1y/nhbLtOdkJzdimVpeGuvlldozX7d0RF2izqGfnM8GKcM6EFbp4NW4HFvD02Fc97bm90kTc831CfuP5zY4q5QtczomTYhStkDD0/B1gHX+R/TwXO9vlXLlsTx1rRuzzb8OaPh6l/fwXO+cACVBWjpiLg8eHjtx1ISxyoo3OA3Zdax3WE/P9Z7PuMEWy1NWvDH7cHYj1nt9T8/9eirlxW5Oh7ZH15sG471j3yDPPF2klCXTvBtXjm51y09ZD+bpuR/fwHpUmpdlz7Q7a8QGL2+qtg8bnhvUtNP6Q0/KyUgwr7NfL890TO/A/3qZ00FN8ovSoG3PSW71iOQDL5N45vliEhJmXn52ckpSo57pkgbLfPfp7VmOl7A8u2l5jd93b21AGdaOTdv7SFvpZuo5yjP4rnKfTdKQnaY+3ot1ZGodDqSlZDsa9K7lDf2Zh7xr6f6ubBf1XVk5V5I5Z+eksCj9ndmWndT1sMs9uHJ9PUjW3MGcmKXH6+9uW/QLH2E8jni8J5+hv8e5UutHQPLvj11cadK+A+Hbmzzpo7QZJ119WC+Pe4jcjTSUc7nPyfWVkn1q+u3GNkrq7LO1+4tx0vZC1k3+6novdpzWXkYKgPP9AGlbsll5Vj5A314JybYEnvRl2Z1d+Y9xfvEkQrlN2pD7opbXoRZ5G/gz7y936qd9O5xxcT46390d6Eyj+ZazcnLrvGrKyW5Y+pr5t7rMWK4=
*/