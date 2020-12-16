// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016, 2018, 2019.
// Modifications copyright (c) 2016-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SSF_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SSF_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/spherical/envelope.hpp>
//#include <boost/geometry/strategies/concepts/side_concept.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename T>
int spherical_side_formula(T const& lambda1, T const& delta1,
                           T const& lambda2, T const& delta2,
                           T const& lambda, T const& delta)
{
    // Create temporary points (vectors) on unit a sphere
    T const cos_delta1 = cos(delta1);
    T const c1x = cos_delta1 * cos(lambda1);
    T const c1y = cos_delta1 * sin(lambda1);
    T const c1z = sin(delta1);

    T const cos_delta2 = cos(delta2);
    T const c2x = cos_delta2 * cos(lambda2);
    T const c2y = cos_delta2 * sin(lambda2);
    T const c2z = sin(delta2);

    // (Third point is converted directly)
    T const cos_delta = cos(delta);

    // Apply the "Spherical Side Formula" as presented on my blog
    T const dist
        = (c1y * c2z - c1z * c2y) * cos_delta * cos(lambda)
        + (c1z * c2x - c1x * c2z) * cos_delta * sin(lambda)
        + (c1x * c2y - c1y * c2x) * sin(delta);

    T zero = T();
    return math::equals(dist, zero) ? 0
        : dist > zero ? 1
        : -1; // dist < zero
}

}
#endif // DOXYGEN_NO_DETAIL

/*!
\brief Check at which side of a Great Circle segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam CalculationType \tparam_calculation
 */
template <typename CalculationType = void>
class spherical_side_formula
{

public :
    typedef spherical_tag cs_tag;

    typedef strategy::envelope::spherical<CalculationType> envelope_strategy_type;

    static inline envelope_strategy_type get_envelope_strategy()
    {
        return envelope_strategy_type();
    }

    typedef strategy::disjoint::segment_box_spherical disjoint_strategy_type;

    static inline disjoint_strategy_type get_disjoint_strategy()
    {
        return disjoint_strategy_type();
    }

    typedef strategy::within::spherical_point_point equals_point_point_strategy_type;
    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    template <typename P1, typename P2, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        typedef typename promote_floating_point
            <
                typename select_calculation_type_alt
                    <
                        CalculationType,
                        P1, P2, P
                    >::type
            >::type calculation_type;

        calculation_type const lambda1 = get_as_radian<0>(p1);
        calculation_type const delta1 = get_as_radian<1>(p1);
        calculation_type const lambda2 = get_as_radian<0>(p2);
        calculation_type const delta2 = get_as_radian<1>(p2);
        calculation_type const lambda = get_as_radian<0>(p);
        calculation_type const delta = get_as_radian<1>(p);

        return detail::spherical_side_formula(lambda1, delta1,
                                              lambda2, delta2,
                                              lambda, delta);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

/*template <typename CalculationType>
struct default_strategy<spherical_polar_tag, CalculationType>
{
    typedef spherical_side_formula<CalculationType> type;
};*/

template <typename CalculationType>
struct default_strategy<spherical_equatorial_tag, CalculationType>
{
    typedef spherical_side_formula<CalculationType> type;
};

template <typename CalculationType>
struct default_strategy<geographic_tag, CalculationType>
{
    typedef spherical_side_formula<CalculationType> type;
};

}
#endif

}} // namespace strategy::side

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SSF_HPP

/* ssf.hpp
o7gNb+En6Ki/v8OKuAvl/kee4bKuGvc/J+R+6xTWxNPojt+iF57FgfgdDsMfcBT+hBH4szJGtTyHVb6/q8eo3inxZnvwLdyLQ3AfzsT9OBdTUb6vy7NRlpEr6/f1JbK8ZeiFK7EPJmMApmAIrsWpuA4/wPW4AzfgWdyIF/E9TMdN6EB+m7EefoCN8CNsglvR1/7l4xL/t8SQbZlmZ4sjs8WR/V/FkR3/+t8bS3aUc+w+qSQ3Yy1JYaQU0lnSY1JJbs6akvxIc0ibSKdIupl2OteZtpgx22SbbJNtsk2vd/qXt/83tLiQ1oOvqf3/Ayed0g9/fC5pIyhtUh6RPnbRcW1VtUnRF0UKId3wv0K7D2mbm6W9nrO6PU1I6LAYpT1odSdpSyOfq2JqE5zZvklZF1+5zB+XdTlC2kZe6TOyrouxJaL/0JDgoSNfpQ3Li9alSjbXxVVjXdylLUu+3MbMH9qxLngHP9Gvy0xjP/VDYqLHBDZuGJiTNvfG/GPrZx3fLNY983dOWExpK8jvVGPxhSmfg8zfsbw/19e8dtsP621OtNsG5LzNiXbbDOttWrTbVFhvy6HddsV6WwvtNiQ5b+uS0zYk2m1jrLUteX1tZrTbouS8bYl2G5WctxXRbqNivU3URkPbFedv0laOCr2cOvJqkZExAwuxMZVnVNPlXRUpw+IZVUt5JtQaq6EXemEb9MG22B3bYX9sjwnYAZejD+7EjrgbO+EB7Ixfoy8+wq4o5ZF6kPXRKE81KU9NKU9tKU8dKU9dDMB6OBzr42h0x4nYAKdiQ3wPG+EH2AQPYlM8gs2U8ih1GXVc1vIUkfIUQy8+5IIT+ExxTMBSuBZL4wdYBj/DsngIy+NJrIDn0BXTsSLewMp4B6tgSXvm83z586bX9axpmbvdn3re9N/yrGmPVy7b8ybb86Z/y/Omf+ezJh+eF8WQkm3PjWyTbbJNL5jsSYH/ku//kYaADcNX/tfwnf+qk07GNjS1l6srMd41SKv0Y6DRMIw/ReqjQnIa124RT6LktUXyipPv5GNJa/hsille2Y1ll1hcs3hSwxdgJc4it+H3hhBN+X5tvVx+UrUfkHKlktbyWc8phnIZN77/sNDwoJeXy1ndj8FoZQxfjbKqy6UPcJSx/pTfDYsYQ6ZSVukbIOv+Wq8va7yqrOyw7O8vpawW8ZIp8tzBgQWXQB1uJK94VV6h4dEEpGXnuYnECaryk/gfzfhffidj2lluF7aVxOsdZXskU079ifFAXy7rz1NU6+YkcfwVZTuWJb3Hsk9NNV83yhM1JCYi6tW3ZeZ+i5P8GpAKy/7b5MI/08zz4+DPxrEv62c1r98kr56ybl1IH+qPEXVebMPsj5+52WL/6JR9wbMhi/xDHIwLcCQ5kArLtt2myl8fk/ry8c7lmZPVdc2QvLxlXb0y96M6r4jIbIzrrrVdlXXVrjuUcf67Sv4dSVv4rNt08/zpdyAHY5Va5p9P4/zQmY5v6ogY2zM32zO3/7tnbmXz6n//R9ThFivbvj/VY0TGl6tytSPoxxg/I/cwUtdmWMTPVJT24ZWwBlY2b78u88XJfNJ+S4lbKoEu2ADfwBZYHFtjSeyLpTEYy2AUlkND3S75JOrk/gIPSD5FcIbkEyz5DEdXjXH6wnAAjpLlhuNUjMDpOBpnYgyuxTH4IY7FT3Ec7sYJmIoTUbYb9xIa200jLqwG1pP50nRyXyD3C8zHtuF7tMznLuvTCCthY6yHTbAZNsce2AJHY2tcgJ6YhF64DtviB9gO96I3HkEf/AY74insjD+gL/6MXTAdu+Ed7I7PsKfE4fVS1l/uAbCixvpPlvWfgmUxXuZrqpNrOTSQ+ew=
*/