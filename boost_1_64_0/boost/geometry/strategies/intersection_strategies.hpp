// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016, 2017.
// Modifications copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP


#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/policies/relate/intersection_points.hpp>
#include <boost/geometry/policies/relate/direction.hpp>
#include <boost/geometry/policies/relate/tupled.hpp>

#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/intersection_result.hpp>
#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/strategies/cartesian/intersection.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>

#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>


namespace boost { namespace geometry
{


/*!
\brief "compound strategy", containing a segment-intersection-strategy
       and a side-strategy
 */
template
<
    typename Tag,
    typename Geometry1,
    typename Geometry2,
    typename IntersectionPoint,
    typename RobustPolicy,
    typename CalculationType = void
>
struct intersection_strategies
{
private :
    // for development BOOST_STATIC_ASSERT((! boost::is_same<RobustPolicy, void>::type::value));

    typedef typename geometry::point_type<Geometry1>::type point1_type;
    typedef typename geometry::point_type<Geometry2>::type point2_type;
    typedef typename model::referring_segment<point1_type const> segment1_type;
    typedef typename model::referring_segment<point2_type const> segment2_type;

    typedef segment_intersection_points
    <
        IntersectionPoint,
        typename detail::segment_ratio_type
        <
            IntersectionPoint, RobustPolicy
        >::type
    > ip_type;

public:
    typedef policies::relate::segments_tupled
        <
            policies::relate::segments_intersection_points
                <
                    ip_type
                > ,
            policies::relate::segments_direction
        > intersection_policy_type;

    typedef typename strategy::intersection::services::default_strategy
            <
                Tag,
                CalculationType
            >::type segment_intersection_strategy_type;

    typedef typename strategy::side::services::default_strategy
        <
            Tag,
            CalculationType
        >::type side_strategy_type;

    typedef RobustPolicy rescale_policy_type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP

/* intersection_strategies.hpp
IoN/uYk1Gf26TnTuY9DpXwOdB64TnQd/eH3sjUcYdHJr0D8nzH5ew3wfM/tnDXSmDDqfvdlGUZj58PqsF/OKzhp165MVnTXq1qcqOmvUiWVFZ406sQo6a2eotU7z4pk+fvpX39PP8dA5MbN6gXyJh86Vq6uXoNd46Fz/TV+w2vBahw6ceasOV310rq+en3eATjqsns4HNJ21GWWfBZ21T/jvCjprb1bwC9BZ+wT7naSz1i76o6Sz5i76yPrQ6Vd01qhbt2fQGVhlB91d0Vmjbr2PorNGnfhAk84a7M0HG3TWMl0f0YFObhV0JtaJzrkOdPpWQaf8kd79P51kfGkVdDrJeGMVdDppk5WP9O5n6yTjVww6eevjht0d6FxN0cndJJ2NsBE2wkZYzzAyNUXPO52emRo/PT49f+aUSMtg5Y+Nnxo5OzXP55V0CQHx+NgEYrqYwPcTRB7dwkA8ilxOUZquZVCk8ZOkKoscTnOKv9MlMsTiGoV4ZgN1U0wXJEQsoqK4ZyHyiI6AIhJpEKFY4A6rY0akcSUD3xVdWY9okmCcmwFaaByqoCCqHyHIiISLKgTqkbHxOcBHH0yfw7jjoe52iDiSBPimiLpDr+7OIxYfuguK76NJTIXce2Ppe1VWWpVX98/Ed/F4injBIX0VcaBvtWieTo+MAsbk1K0Z7iqcqV48InwLU3MXQUR9PwjyRpr7derM44PT42OTZ6kdE5OPggycmpyZk32M+y3UZeIazBH79i7DqZ8teG/PcdEBrDh0P1jq8pyTKJg864Snpp5UeQoeTuuKV66cj+JWYTlqLdXL8ZOoY8SzZtS/hcmxc08J9xwLMdQidH3eKpueGKtuBM/Twf4QNSOdpkucOi3uMZlwcS9JvKrSSt8iECC7QxMkBupZJvM+KPIhQElQ9zr9cD8+qrbxM+Fz87P68VmeS6NT448bnzqm0mcn58dPUg1npqeeYKZp/llwu/zDDvdyb//WXm/rB4HWjYlOvXWPR3neuoe1gApKDZrqT32DWhJ6Rz7ua6owmhf7b3lI8hzeEZFx6CFHkcPjuJ8ao5JCH5lp6CZkJOOgkjp9OKlA6iUUMdO6CPQU4EnahR9FASOtC4zS/ZBqtVJEATONAqxDGWbqK0AtPfcgdc/W4F68njV9bw9n39NnpsdlmRreBiy0m07T1ZZD6XThUCotCC20caVF5YsrMPiuvkD3l8riQc/a+Woky+HOTNSy3ofboGsm0j8ZnS+WxD2eWnS+3qoUW/qSkQVnNHEFqBaVFC2mjztAyw2BWKD/oGTBO5KIW82KSM1VzteKrXYzGqmep4dyW0vLMcMr54tVbjb3P+7A+Esn7wEuaDTgtKnmmGCIk/k4U2zS6LfoFpXBL+WUCyjJuLhXNUdc1tCqmWa9VS/Vq6r86UrNylqu1AoNmQF4ccWGF1cs+Bl0HBgw7uWcrpcjybvQ4ouVUrHFGeLKEPNRuUh5jzHudbHeQS9P1hbrpyosApLOUrFSGx2ZKbaWmA6nG0gncCAZ8EWkNV9MILn/pQloOAhoOBNIxg1wM63ppUejvNQQ6U7ugf7UtnpA/JkfCK7YxfK2D+9E+ku//sshp9M5fPAnfa8GLp3bcdY9xZ/dX+L8Tch3/ULINxh7hJsPFkJJZ0uSv539ME4+2vtAWX5zis5RmT+QKv+ujyE/zR8aZPKVQzrhJ490wkcf0qhfv4dK1mu912hCpm+n+Dgh6cj826v8AalvkM+N2GaM54rMv61uTx5/XyDzt4NEUsFVmX83nZ/D38/qfsFHh+/K/K2p/F/I/EHw43qVBr6c8NufT0Rlu8zfIsoY+WEqv0/5ITUdzt8U+MP2j6Ncpnc=
*/