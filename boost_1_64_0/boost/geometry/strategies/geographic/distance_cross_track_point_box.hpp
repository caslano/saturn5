// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

#include <boost/config.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{


/*!
\brief Strategy functor for distance point to box calculation
\ingroup strategies
\details Class which calculates the distance of a point to a box, for
points and boxes on a sphere or globe
\tparam CalculationType \tparam_calculation
\tparam Strategy underlying point-segment distance strategy, defaults
to cross track
\qbk{
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}
*/
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_cross_track_point_box
{
public:
    // point-point strategy getters
    struct distance_ps_strategy
    {
        typedef geographic_cross_track<FormulaPolicy, Spheroid, CalculationType> type;
    };

    template <typename Point, typename Box>
    struct return_type
        : services::return_type<typename distance_ps_strategy::type,
                                Point, typename point_type<Box>::type>
    {};

    //constructor

    explicit geographic_cross_track_point_box(Spheroid const& spheroid = Spheroid())
             : m_spheroid(spheroid)
    {}

    template <typename Point, typename Box>
    inline typename return_type<Point, Box>::type
    apply(Point const& point, Box const& box) const
    {
/*
#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointSegmentDistanceStrategy
                    <
                        Strategy, Point, typename point_type<Box>::type
                    >)
            );
#endif
*/

        typedef typename return_type<Point, Box>::type return_type;

        return details::cross_track_point_box_generic
                        <return_type>::apply(point, box,
                                             typename distance_ps_strategy::type(m_spheroid));
    }

private :
    Spheroid m_spheroid;
};



#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Strategy, typename Spheroid, typename CalculationType>
struct tag<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename Strategy, typename Spheroid, typename CalculationType, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy, Spheroid, CalculationType
        >::template return_type<P, Box>
{};

template <typename Strategy, typename Spheroid, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy, Spheroid>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy, Spheroid
        >::template return_type<P, Box>
{};

template <typename Strategy, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy
        >::template return_type<P, Box>
{};

template <typename Strategy, typename Spheroid, typename CalculationType>
struct comparable_type<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
    typedef geographic_cross_track_point_box
        <
            Strategy, Spheroid, CalculationType
        > type;
};


template <typename Strategy, typename Spheroid, typename CalculationType>
struct get_comparable<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
public:
    static inline geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>
    apply(geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> const& str)
    {
        return str;
    }
};


template <typename Strategy, typename Spheroid, typename CalculationType, typename P, typename Box>
struct result_from_distance
    <
        geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>, P, Box
    >
{
private:
    typedef geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> this_strategy;

    typedef typename this_strategy::template return_type
        <
            P, Box
        >::type return_type;

public:
    template <typename T>
    static inline return_type apply(this_strategy const& strategy,
                                    T const& distance)
    {
        result_from_distance
            <
                Strategy, P, typename point_type<Box>::type
            >::apply(strategy, distance);
    }
};

template <typename Point, typename Box>
struct default_strategy
    <
        point_tag, box_tag, Point, Box,
        geographic_tag, geographic_tag
    >
{
    typedef geographic_cross_track_point_box<> type;
};

template <typename Box, typename Point>
struct default_strategy
    <
        box_tag, point_tag, Box, Point,
        geographic_tag, geographic_tag
    >
{
    typedef typename default_strategy
        <
            point_tag, box_tag, Point, Box,
            geographic_tag, geographic_tag
        >::type type;
};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

/* distance_cross_track_point_box.hpp
dd/tx/U57bsaP+W7HhE6afKsbHIx3heZJ02dd1er3/cXLX3sP5ZnJ0/j58wfKvlge0bES9Fb13t+Ic9LPhDFvHne+ZaWb1uk69S9tartwzTVM+CRsWFRiUr/iC/IH99jO9ieXaxTw7w8Fmjrn9cwz7Ov/up+NMrz4T8pz3fbnvk+y/JZ1sSIfGXVrKyMF+/Id9EXHams1y3ra6v7plcjFqMPUDAVgDyQnNTdPHmvrHr2eLz5Gc7YMhQueTnMtO7Rtmc4myHHG76XZC5E8q7KfxnpD36oNOWPr+M5vp8Wkz//MXEx8i7w9EK2dfuJyraW7aheH9O0TXjcnC8Oq7a+ArK9SdZcv0wva06ia4S8zzNfGQTlLQPZdtury3YKiY1JTJL93Po90kpCvT5UpjJsRfldt4x16PDOeHW/A8pQ8mWri8a86SXa+upUZ135Llm3LLcHy/yGOMm/DYm1bZtgVf22pJWqzM8yzWVg+W6Ktg4q7/dbLMtcVU1dN9Nl284hXIgZxGWWEfQf9s4EPKrqCsCETWSdIIS1EmRfDZusYthkESFAFBQwCcmEBEIyJBNkNwiKC2JUVNyjgrIVo6CCogRFAUWlqBQtLaFWi4hKEZUq1f7vvfPuzJv3JpmZ0Pbr95mvtz9zffeec/f77nJetlG2khj99kylMGzKBLbJWGv7k++qqrKq0Lfrztd5YOfzusHPAzufTw5+ntn5nG2w86Xhf3Mu3HO5zueHw//2W7jnlh3P90bwrTvnc9fBznUHP4c8Sz8XXfzZdS0fSt5Q85Za+6Nifnh2e/Bz2tfq35xzXbC8dsmjFy1Z+dTeNvdu7vBU8PPVzuexIzsnHKe5VN++eFHAvvhbsh/zNmwP90AznEfCdXYIN1e+XTEPtoPz/cIVlyGvROTtEnlvqG/SyTxI5keeAFvmLdRzMneBHcp4blKUzC1kzlGE0+SNlvnlHbKvfydsA++CXeC9cAi8D06Hq2AWfAAuhg/CW+FquAE+BN+ED8O98FF4ED4GP4WPw6PwCfh3WCT6PQn/BZ+CdWXfKRaugZfAtbA7fAYOhevgtXA9TIEbYB7cCBfDTXAF/D38CG6G38Hn4C+wGFYTG6+d4BY4Fm6FD8CX4Gq4DT4Gt8ON8FX4ItwBD8LXoHGOSOYjMk8pCjhH1EbOD7TzOz/REnaAV8GOMBV2gotgZ7gWdoHvwK7wFLzUrFewDnK6wfqwO+wEe8DLYE84CPaS54uiZL4h8xD0IyzlKeXfR+phP9gCXg57woFwDLwCToHxMA0OgnfAIXAzHAr3wGFwPxwO/wxHwF/hSFhLzl30glfBq+FomAyvhgvgGHgXHAvvhwnwVTgBHoWJsC66XwMvghPhZXASHASvg1fC6+FEOBkugFPgcjgVroA3wIdhEnwDpsDDcBo8CdNgDfLJDV0wHbaAGTAOZsKxcAacA2fCu2AWvBvOgqtgDnwIeuCTMBeug3nwReiF22G+Oh8kcweZUxQFnA9aJPWogP81hUvgxfBmeANcCr1wGVwAb5H6dCu8CS6HaVXLt5lb1BkblJ2jyrWdW5G9wtHzy98vDNd27rIFwfcMkxeen33DBovK3zssWFT+/qGxdwg7R5W7f5ixuNJ/3JZuRfYPj3eOKteO7rIIbegGs5+7dcn/bg/xHOkNto/oufn82dJt0CVK7SNmLY18L/F87yPGoVcCzosrxBXjPsKdwrm6su/X9bc9v9/+fvv77e+3v9/+fvv77e+3v9/+fvv7f//7z+7/Z2VOOw/2/7X9/+mNeb9dp+3VpKVku5PYOzL297Prs9ESsL8/HNccNxj3HOGKWXThP40dPCppWp47JTc1I0nfLMv0ZLg=
*/