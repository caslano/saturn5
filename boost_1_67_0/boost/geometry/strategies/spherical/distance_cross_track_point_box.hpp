// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_POINT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

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

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

namespace details
{

template <typename ReturnType>
class cross_track_point_box_generic
{
public :

    template
    <
            typename Point,
            typename Box,
            typename Strategy
    >
    ReturnType static inline apply (Point const& point,
                                    Box const& box,
                                    Strategy ps_strategy)
    {
        // this method assumes that the coordinates of the point and
        // the box are normalized

        typedef typename point_type<Box>::type box_point_type;

        box_point_type bottom_left, bottom_right, top_left, top_right;
        geometry::detail::assign_box_corners(box,
                                             bottom_left, bottom_right,
                                             top_left, top_right);

        ReturnType const plon = geometry::get_as_radian<0>(point);
        ReturnType const plat = geometry::get_as_radian<1>(point);

        ReturnType const lon_min = geometry::get_as_radian<0>(bottom_left);
        ReturnType const lat_min = geometry::get_as_radian<1>(bottom_left);
        ReturnType const lon_max = geometry::get_as_radian<0>(top_right);
        ReturnType const lat_max = geometry::get_as_radian<1>(top_right);

        ReturnType const pi = math::pi<ReturnType>();
        ReturnType const two_pi = math::two_pi<ReturnType>();

        typedef typename point_type<Box>::type box_point_type;

        // First check if the point is within the band defined by the
        // minimum and maximum longitude of the box; if yes, determine
        // if the point is above, below or inside the box and compute
        // the distance (easy in this case)
        //
        // Notice that the point may not be inside the longitude range
        // of the box, but the shifted point may be inside the
        // longitude range of the box; in this case the point is still
        // considered as inside the longitude range band of the box
        if ((plon >= lon_min && plon <= lon_max) || plon + two_pi <= lon_max)
        {
            if (plat > lat_max)
            {
                return geometry::strategy::distance::services::result_from_distance
                        <
                            Strategy, Point, box_point_type
                        >::apply(ps_strategy, ps_strategy
                                 .vertical_or_meridian(plat, lat_max));
            }
            else if (plat < lat_min)
            {
                return geometry::strategy::distance::services::result_from_distance
                        <
                            Strategy, Point, box_point_type
                        >::apply(ps_strategy, ps_strategy
                                 .vertical_or_meridian(lat_min, plat));
            }
            else
            {
                BOOST_GEOMETRY_ASSERT(plat >= lat_min && plat <= lat_max);
                return ReturnType(0);
            }
        }

        // Otherwise determine which among the two medirian segments of the
        // box the point is closest to, and compute the distance of
        // the point to this closest segment

        // Below lon_midway is the longitude of the meridian that:
        // (1) is midway between the meridians of the left and right
        //     meridians of the box, and
        // (2) does not intersect the box
        ReturnType const two = 2.0;
        bool use_left_segment;
        if (lon_max > pi)
        {
            // the box crosses the antimeridian

            // midway longitude = lon_min - (lon_min + (lon_max - 2 * pi)) / 2;
            ReturnType const lon_midway = (lon_min - lon_max) / two + pi;
            BOOST_GEOMETRY_ASSERT(lon_midway >= -pi && lon_midway <= pi);

            use_left_segment = plon > lon_midway;
        }
        else
        {
            // the box does not cross the antimeridian

            ReturnType const lon_sum = lon_min + lon_max;
            if (math::equals(lon_sum, ReturnType(0)))
            {
                // special case: the box is symmetric with respect to
                // the prime meridian; the midway meridian is the antimeridian

                use_left_segment = plon < lon_min;
            }
            else
            {
                // midway long. = lon_min - (2 * pi - (lon_max - lon_min)) / 2;
                ReturnType lon_midway = (lon_min + lon_max) / two - pi;

                // normalize the midway longitude
                if (lon_midway > pi)
                {
                    lon_midway -= two_pi;
                }
                else if (lon_midway < -pi)
                {
                    lon_midway += two_pi;
                }
                BOOST_GEOMETRY_ASSERT(lon_midway >= -pi && lon_midway <= pi);

                // if lon_sum is positive the midway meridian is left
                // of the box, or right of the box otherwise
                use_left_segment = lon_sum > 0
                        ? (plon < lon_min && plon >= lon_midway)
                        : (plon <= lon_max || plon > lon_midway);
            }
        }

        return use_left_segment
                ? ps_strategy.apply(point, bottom_left, top_left)
                : ps_strategy.apply(point, bottom_right, top_right);
    }
};

}  //namespace details

/*!
\brief Strategy functor for distance point to box calculation
\ingroup strategies
\details Class which calculates the distance of a point to a box, for
points and boxes on a sphere or globe
\tparam CalculationType \tparam_calculation
\tparam Strategy underlying point-point distance strategy
\qbk{
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}
*/
template
<
    typename CalculationType = void,
    typename Strategy = haversine<double, CalculationType>
>
class cross_track_point_box
{
public:
    template <typename Point, typename Box>
    struct return_type
        : services::return_type<Strategy, Point, typename point_type<Box>::type>
    {};

    typedef typename Strategy::radius_type radius_type;

    // strategy getters

    // point-segment strategy getters
    struct distance_ps_strategy
    {
        typedef cross_track<CalculationType, Strategy> type;
    };

    typedef typename strategy::distance::services::comparable_type
        <
            Strategy
        >::type pp_comparable_strategy;

    typedef typename boost::mpl::if_
        <
            boost::is_same
                <
                    pp_comparable_strategy,
                    Strategy
                >,
            typename strategy::distance::services::comparable_type
                <
                    typename distance_ps_strategy::type
                >::type,
            typename distance_ps_strategy::type
        >::type ps_strategy_type;

    // constructors

    inline cross_track_point_box()
    {}

    explicit inline cross_track_point_box(typename Strategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline cross_track_point_box(Strategy const& s)
        : m_strategy(s)
    {}


    // methods

    // It might be useful in the future
    // to overload constructor with strategy info.
    // crosstrack(...) {}

    template <typename Point, typename Box>
    inline typename return_type<Point, Box>::type
    apply(Point const& point, Box const& box) const
    {
#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointDistanceStrategy
                    <
                        Strategy, Point, typename point_type<Box>::type
                    >)
            );
#endif
        typedef typename return_type<Point, Box>::type return_type;
        return details::cross_track_point_box_generic
                    <return_type>::apply(point, box,
                                         ps_strategy_type(m_strategy));
    }

    inline typename Strategy::radius_type radius() const
    {
        return m_strategy.radius();
    }

private:
    Strategy m_strategy;
};



#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType, typename Strategy>
struct tag<cross_track_point_box<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename CalculationType, typename Strategy, typename P, typename Box>
struct return_type<cross_track_point_box<CalculationType, Strategy>, P, Box>
    : cross_track_point_box
        <
            CalculationType, Strategy
        >::template return_type<P, Box>
{};


template <typename CalculationType, typename Strategy>
struct comparable_type<cross_track_point_box<CalculationType, Strategy> >
{
    typedef cross_track_point_box
        <
            CalculationType, typename comparable_type<Strategy>::type
        > type;
};


template <typename CalculationType, typename Strategy>
struct get_comparable<cross_track_point_box<CalculationType, Strategy> >
{
    typedef cross_track_point_box<CalculationType, Strategy> this_strategy;
    typedef typename comparable_type<this_strategy>::type comparable_type;

public:
    static inline comparable_type apply(this_strategy const& strategy)
    {
        return comparable_type(strategy.radius());
    }
};


template <typename CalculationType, typename Strategy, typename P, typename Box>
struct result_from_distance
    <
        cross_track_point_box<CalculationType, Strategy>, P, Box
    >
{
private:
    typedef cross_track_point_box<CalculationType, Strategy> this_strategy;

    typedef typename this_strategy::template return_type
        <
            P, Box
        >::type return_type;

public:
    template <typename T>
    static inline return_type apply(this_strategy const& strategy,
                                    T const& distance)
    {
        Strategy s(strategy.radius());

        return result_from_distance
            <
                Strategy, P, typename point_type<Box>::type
            >::apply(s, distance);
    }
};


// define cross_track_point_box<default_point_segment_strategy> as
// default point-box strategy for the spherical equatorial coordinate system
template <typename Point, typename Box, typename Strategy>
struct default_strategy
    <
        point_tag, box_tag, Point, Box,
        spherical_equatorial_tag, spherical_equatorial_tag,
        Strategy
    >
{
    typedef cross_track_point_box
        <
            void,
            typename boost::mpl::if_
                <
                    boost::is_void<Strategy>,
                    typename default_strategy
                        <
                            point_tag, point_tag,
                            Point, typename point_type<Box>::type,
                            spherical_equatorial_tag, spherical_equatorial_tag
                        >::type,
                    Strategy
                >::type
        > type;
};


template <typename Box, typename Point, typename Strategy>
struct default_strategy
    <
        box_tag, point_tag, Box, Point,
        spherical_equatorial_tag, spherical_equatorial_tag,
        Strategy
    >
{
    typedef typename default_strategy
        <
            point_tag, box_tag, Point, Box,
            spherical_equatorial_tag, spherical_equatorial_tag,
            Strategy
        >::type type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

/* distance_cross_track_point_box.hpp
B5kG2YgXq688zAkxjY7N9Au58hWBFZO8SfhEtk5K8drYRodhjOcV5lCXL+xkbKbpXS+VsHtmMVtZ1gaLyjhKsuTJO+yTWylqWDN20QpOn+8X18fsJfm63dIrBtcgJ6uR9qiW4zDBGkdrYznw/LZFWoDB5+la+/LW+dHWkgmtQxQnrJET1Ej/cdri0lHHk0sQE8lS7ruC6d905sm9DdpQopcpYMYmdQmEm+h6B/BFb6vyGt4n874Knn/xhd21vWQbNSgWta8OL3VQlm7zarefHpBp4Ppqis0luGLSTC8fx4LOkmTPuEzccAEM933CJuu/8QXmfsLzl/Q1YC1hjqvVmFY44vx99FIudzKxJGpf2vDaurRBl7cB2hBswSGn4npTvPg9wuNOLTrTgq5g8cDdeoR1ZB1bEwjJ59KBh+PCV2Gl8LzHJ92wzLAc6SLsnEn/MzE15FBw4nGEpwaCqRfgmbZDss0nUqmVS+nJTFO/BPxf3KNxLomz+7G1sUaLkMmefVWP/2xcZceQPDTWl4awuzcZPEi7Ny/2el7uVLx3FRSiRpk865qrlDeWC3ENo/JZ+/atv7sV3cTNSnAfT1J2i88W6L46Vsbl+m6sv//xZDAXsDIm7xdtoPE8hyblmH9n+6pl8dlEFA+iBipM80ycYFaMWQenYvkVbv5DMEqumqhGoZ9SzGXPHqTPUk2fQaLR5CrJbe7sp4S5FXXwxaKmKvtvoi3exsZSDB4UOy0sC43HH/7gYn01OsMOlxs3DLs2aeTzeTUjehkRh8x3NHKNWc3fw4h8q5sesgdGp4Mih6stnI5dMM0OADdHVyyD78c1zSB57LJLZuzhkn2IgZRX6c2gbbp5FkBXJO2kliQkTnOF7tRc8Qwut+sg+tYlALVgqOl+x1nQcyTz37+qDJ5tTckWelR6PduSVaKHqssMqUFx0hbwC8aFsu5Evuo09EeI81V+jk3BkRN+kS6XSXssu0aUEDMCC/V8C0aKueLT2Q5s+S7kx6DYPQBgKzZg+UvssTz2ZrYaZkbJJ5+Jorct3Xc+L3iUXHX+3NFFPB+cLbcwklUVaqqwl2aea1vsBQs6jJTwN691aa54H++bqhu2U7xZ1n8/HhC+CZQtnWStgRfYFBkld6vp64r5FM7mO24Y8KJ3CLo7QteCIXUbKhwTf68yxulxNxVGfvNK+qwqu6mLUfqtiIZXLGCkIpHLGwbKkkAQm6/BIj0nVYoA+bxSWawIvuT5BasF+C1SMh+3i2I9J82kVJ1TuXh1k+oDT8CkhPGfW67gY6qkCcuJmg7ECWEJ+QRnWdAWkUmeiOzMNVOe0wgZ+XbghHOV7BeCD0p5FRnsimLm7EKOqY7iz7QGqXOIqLLjBNzwihdKZgTz7o4kom+T7n25FYUN0pS0K3DmMOG7X7MH+gOvXmby8iHU+IjsyWF432+ftbEVA6hlmh5BMLedAmPM53iVZ1laa0lLQ04UJhZWaDJQjDSyCbtZ/js93BOfwWat7vl1jZ98Yb9TLeyZ4SHOfu7LWXJc+TymzapkC6W5Y/oOUmnMot9H6rXCcONy+4wFvBVrVzjejX/tcBhdkh9zdYxH5MUeH6/IOSrK4/iiTHDoa7lXXSNW4+fSB9x2blx7CiUJtXZdyE/oXHbj6+Wt4nDzPRPyFp837RRruAYBOtrqg0Su49yYuNTwepAdJ5n9bY/EgN5VrQh3vEk24L0W+Ih3OoLtFrw/3ljgvfQNpSBeWnALQujY6m6iFpR1TP3YCzCLJ5VT8Rq+NwTgfVFggG8lTjSQjBAw4mRpjBA8UT4UJ/v5kIQM2D6YsbEYGIceJGzI8kZ7JV9TOytzm1yeWqJ2VucxdwyZfEnHVEsvU2Y/fXN32rGhU4lz9lokrQAhdY0F+0yxoZt0gaGr2hiwdcQs2qnRoatkBfst6jvVTUX7rCgep/YsMKXFx6LlpUAsPIFzd/OZGBf0jUNxH6N8KOXYCMh1LQz3moPDi8JhD8QYWsJg+obADA0B6RiwxDEpKP4R99LXhuFOjRER0Bi6K/YEsdFeRgdj4EIKwvsp2PmPgIRGQdmjYgpkCqLlxwVfksjzpq7zIBSw/YsgeBljnlCYMGpxoto+CPasJE/Atm/1QlB9QeWeTPmWRssreiEwAstgwsvEi8EwWHVE7MCVuvGQ4V8zCJ5YQUuiEBVqRMV0R/GabITPhtjFqUmErJWm27hCrD2ELVvgxWIKCDrRPTTMiJdHKG9Na4H866fvLu3/CsAFLIKE/fy6OFm43lpF8uK5/OM1eyGKR+UIzxLMl1xoE/5DR7SXLUNgcAIQsuyAP2rDSMizlsWN1+PnhW/w/LEqjW8s4rK4mKcHLdY1DVtqhKw4jhK8GAFSeiWeMsIVStVTb6yuaM0G/usUYEXS58LU9C6zxHfGKkq9nkQMMUzz/yXh7saIMZrniPGP+l8URjgAVjScUhz7vVFaZApe8NTZM0v28AwtlQa47wQu/ejGa2KLxn8458V71kAeqyIWtxrPzVz4komyBqc6E3MtPvTtnH2ItaXrHhI1qF6FoRYYq/AOy5Z7GkIguGRiI7AKhUITXQirZALV/gybKAsy96vLeP2Dgy/WqifpRhZsnVW5SS4DGRfbF6MBiveRtYvPSQNq9Gmu9FCf4HukDLziQTbuEv7Uvp8AsMxENOU3KbxI4/z34/bY/y4H2LQo7e5sXwb8T9egBE+SVjw9xpkH7PzNxaJntbTa9ENpREssYkdozU/uSWxtVhPiUzK2/tYMwguW8ErAD8LrKk54DcfoKajJz5btHNyG/tQcmwnahDtWyERk86gTFAcKznCdPgl5ZtCO2q7JEbgbTbJyl9L6Pu2ABnirjanfx4mZi26nKN4gm1omaObEqFgZEVE7rVzGccyxndCG+UUFJP2dmjoTX1c/aHNOoJcF1DYrx7aTGe4VdOuErgQG5xdZeN3kTWro7RnZH2nfYA8UL6vjc66rNEFacn+KBgeOY5PevnUI1vTolOOTm3smVTa7Z2F4nV+og19Fc/JY/1OjbM+PhHVT0rKbf1j/wIfH/uO5S96h2AdmuVsOU7yIMdkHgPkQSNBNepa9E1u+k9idIjAMCVBoaxxzhb5fiPK3eyBrySBJiXHlRQ95PPm6Z2GhoZc3hpz3pfeZP08IIHIkwBLUUWBfzpodA5xhehBMTJHwl3tXRWLLKP3QHhkTcK2VLPS4jecfXWz/dioBCLNw8H9piKrHFi7VvHMxTpnU8jeEK4TTFlRMB2S+rEoXEdhwmxdXp2K6UFXMOuZX+Hn3yx6RdXK56rjdFKikRlaJ6WL4mGAS2tS+18oSu1EWNzH0AshxN79bNKZn4suZtLKONmJmHpiJEiZsCm7zHkJ17CUXz0F2tD1S+z5/41/84FYfhlWxE1uhM2vyGC/YMntRikasWne03hMT/27SI3h5cYqI2xjRVepF8gL/rhUdBuGZR7DCCONXcgu+nDfrdaL+kwwJ4cdA3JfB90dL2fbb8YWxQSrYznvUZzDmtc8GLD8DdM0Xzu7LBbs4TxsvGUn0A2sl1IudNaUh7Gm4xL6qeyAlIsf3m/alSMqXeh2BSKsQJJ9iTu3GABpHyPlSxfEpjx3avsujZtFBsFY/M4aaY94ZsFZfejOkIzDl5bDv3bKwC9691k1wNGc9BrIW2xQGnp1Uf2cZlOGO2ps3pA65i5Ohr0py/OeVFeSfuCROul9/5sVrz6aBBCxMRty5mDUPplh4S5NyQKIp5ZcF243kkPB5rc1FPnSHr4VIwX/NeLrPQpC2zbNUITSQrvCZOkrCYCxu9ydKb6or4gcsOHgauBTr9BVDjfuM6W2dxfZibNcKZvvdsQFXFylv61F1otv14LwgeuKHlxzeOQF1Rvcu3uz6E4O2WwW2RjpXodTQCvEGFw4mNBuGM5CAMwXywJ/oezhw89NBgNn8kXs8owPvYCCnfi1BjzG8HNpfmN6j/TW1CMKn7wFzQ7kRkyYFpnEBSsG646AxobrjQW3D34T9p3PmgYmjWKSpIRh8fcTDd++DCEOnj0IweWrBGHz04N5wizLa8G/e1f2naa973cig1eirPnNR1PckEQtBmgDRsbuFdzVkYDXrMr2i5Pjil5dnZNFwLyAY38boYa32/gwf7tYdQ0GeI3zJ1HfnrimOqshwRzAtxDJhs2DZgTVW3gx2n5oeAT6XWLLG/QQbnaP0dYIo5vpWcGxSsyY0A7PVYGLjcIeWFGWhPgeOli71+pbUe8VEmanJoCEMQ1ubCE63zw891tPA4x2dxYpQfQegS99avWm8YxtTO4HLhJUiwklpS16YwXHyJvQJFNFYNNVMx0q/sWvYV7OYYbNX2veKvqkDtxRvxFV4UsgaA4wndclTMRQaWDMf11o2TXAj3ds4wUZJTu4opZQVVGLyPHurdvxiql0BWrRsZrtp4BgCAWQsrQF8yOHulUVUw0D8oFAgysRzyoSqZ3Hw5ywDS5AgZxTry64TP9AhEHZglbIhb/2AH/+IKgokNnBHGLPSLZeZ08+vlBiD9xF6evlXV6pKE0PJVJ+pdzOkg72Z071da5bWWpguKSxMbCJVUx8cWFAWVaRUf4N+sljPAmQIfVe2VErGWQvWUozd4QeRidUyoWlPQcy0ShuX1rVo7bG1NCnelkdUJfFpQDINIZvf0VAo1NVlmRo4KlFminTp18p+xJvwTey7Y94DplnGyKQhFPD4SB3f9dfb1kx3T5mG+X4g0/a7cBgvlerSWzTnvTCjPa/QlON7cSGhtNHBHph7BqtIn18BHhqcFiUJKlBvIyZXO9ACR5+6XlwxNL1aJolmCVc4NE3fYjzNJx1v4KGfB/iBExylMwnSdahCLu8MM/ZhsoSMnuD4nYQh2qOiPcM1nb4+DgpyRol8hrXu5HU77guqSzagigURS63tvYhgGUaBGEJwTppnJbmrbkN83gyNoEIh86ESr88R2xTmIrMAuQS7NelYm0Uu5gjQFxD1YbmY8cdhXOAS8XoA1YNmvE2ocjZpKg4DOM3Xqq7p2TCaaX7voGmhUEGE0xds49LeuYy3D8RadKC8tgQKoad9Y56f1R1DzdbSBIwh9t6BT0o9ErKC3NaMgVn09PHcE4reIwBj/rlLhRanEmbjL9qoC+OIc/ghXQJKyNz/yl3WtOwppQJmKJpRAK+FkdEgw9TgmRb85EdrX4+b/TcrrDAlqsIz7uyW+bxYLZQQ/BpsOyQmOCb03VEkAQSSph+2/rNZMNUY8O7QTlqtCl4iyRP5jpcdnwMCr42tj3mOVyEIRddBrPDAyPwtxrP4IJC5ZC9gFSHSNKcGb4dRwxob8MuQhsUXUZ6+uXMajl/L4erlFCUVQ3FiqkqxX3eVDMCts5WJEf0FhwCpCY3T3QhhWUmqolyj7wQfbFqP6lCWoZHc6POlEc6T+qonnDoMYEUNoCpxJ7f/IWzb7KFdHz5tCQ7ampYzeNabIdxgvphjSmOZVhX4H0HYlZ2YH/ixnKB0ErR7K3AowJhsGVMpZhK37cTsEO37BMZ/mfbSeOAx8g2jWzzgMLjcSAeAsgC8neUkApn6YHLYnrF5Zjqz8KWiDe3VT+KGd7W/s7vxs9QWqY/palMZe/MXt2sXdIF97rxNKq9wNOKKIfcxCvisHQeXnTLgOXXwY99fTUruXZto9mJFWkLxjLxMPEu0PKDuYGfx7qF4W7NjUFHTfbAeYNX6NY3A5WA0nImVkb7odgYeSgmA/1E0haFKcCjQlp8I020IngqOyz4IPxn0dAvy0lWYyd65HgjDOfKP4NpoU5cwcGRINsp7PgH/++lQDxDwoVaH4EAZEI5YHhbqNyvCi72El+4X0k/ismbCDq1mDPsHh8DkS1BitkdAda1zucoHG+sevAlZglFhoCdB77kRcQ1m9Ft67CFp4Qi4utjONLeIaGti5vUvpWbpdE4UoKiC4d9g5dNncgcU0yAShF31qMs/v9LeG4nlJxXlxdXB5v+cNqSoj+djSlPBE1L9cP2lgcSGSAGJMWMrBkf1aglwt1Ui1ICtb2vA90k//1UBJp7wGbT63LhhrmxRZ69snWsCIIC/o8rUF/68y4fVe7ajAdDkHsCyc/5tuByuqMzJFaPUgVJckaUWgKiHIlXeeSG4AsVTBrtnQpYrODTdam/c0ZQR50v+K19nrHrAnATS87fYj3x7sNPoDOX/dlD1VMRb3lfEhekzShZXgZ/X8zv4T+RZIZhjn8DY83tAzeH1VwJd/On3igmRVy6K+EMQFl3gif054Ix8Lc7Jn3kT2usZt6RZrW9cYlWPKsTF/PR08/gq3y3B1x7dwPTYXcCqd/EIxPRlBDK7mQPQmWFQfzqdMQKz3glI/G45DBCpNOKrH7YLhL/eCfIeGNiJg78evFlVcfY9IMHVN3/6CHzHJB9/PYBQ27mDJAI3HoHg5v7SzJ4YrbjadD/5GYKfS9fOEQTxCKIcMPtIZoDNGOqks/juw3pj3G5Mo3mPmgmUcdJZ9A0qarMY7mpU9gPxiS13x3ROC7BHtrBNcRxrmEHdX0UtZzPsN1WgeGA+iLI4oAzdwr6fBHZQAqt7WjLoM4HFfV0Oi4KXA2sFWWlImwS2Fiq41ZOMSlhYFi9IGzRInCQVeH6+GKaVyGTOmXFS3/s3eUC1GCZTO4ILqRjcBSAZ0DdKrlEZbJfAREAEoBZSAYyc08T+XzGMHNSkPpIiWKzxJEGOMliSdfIASSGMuRl+pdPaet98b1Oc62Md3cb6GL2W2UP3SZMiGB/MjNxbHiROmnVYIs31g1NuPqt0ciz62jH/Cqnre9JJSNcXnDMVA9XWMX7WiNv7LzBmWFy3d9ovpDFOpZR6xVZ49JDeG59fSMts3zaVPmsKRph4gEM7LAb40UOzq03YrDHeX0nIaIwrRnBpPzzK9cZxGZ83yPXm2QTXZLaGgi4k39AE16uyMhBGulbx+mmA611+9IWysl+FYpwWhwhwEJ97ijZuOyCgOPtt0inbSLJiIG+3MvBqpBG2edWD5CVSLcz/YOMI+b4jsjKQBuUmSQ0O/wTp9gh586G0Z8sf1KkjqQKO/ltxqZziKLgyYGaE641ugPtw/XcaEO8eClCPYQOcxapWddDsKNeRVrWwY96HedkIV/U/Fg3w3TgD3Fb5puneWRMKv1ty7dAwHMMVO43qIJaaVyaMZ74oF4zYNLT06iHVujtr1WfCS/8jKrfEVpQVwvtMfVxTD9kVQr16uL5XkiY4cZkVQEqoJzh9XDHEyz2ClX1nrnq4uq8I9TAHzJMSqGEud5BLhonhWdBhrrerauERzkslUBgPFHrPR/jMEf7sTKhKy4glA3+Dvhx8qRPcE+gdQI4wjR7OMGXJ7CGBGU7zdKziO4Q22TZe92kh9IJMo78G8H0UHwRSkJGbD1UIUkdzj7kjzNbXYuC/X7WNZ3BRh+17bo44ZforRD/GCKgMQxYE3IsKSCcVxSL9SJQgsfBlMkQ/RdkFh7bcopAmLy3OVNQyYmRGg2bU6pocsTJDmwVh3+ZsVcv59NHM5gVMrvVrV6oYTzcF48/e3ba2tnBTpmv815dtL7vduNvP3le+3dleH2zoeEMtaJHKLU5XsbUI7eHoz9GHMYi2+Kj8WTJ9E4XaaEzaqUjYEiXShq80cvvDYinsEQJj2QtsQbEtX/iJcL6caPcBOOPhmHnj4aMpPQmxp684Y5GLofHwiDgCYrLR8fCl37BodxsZax84kAaSK3UTvejEMxaN5jQxrWZ7FSBN6nYG08WQBk456OTFN6hbsEwQOBDaSooQ56sHDtR9TNM+JOVTRRYQFQhziBYKU0jaAF4Q1PXL5Pf7RLA8YKBBMVnqHqE4EgKKa4ksLEAECXygnuIWGEJjeVExId97s3HRvTvXDYEppXME7j3iCSQ7nqA5YbVzXC7EhgkREZateXZumMyxCRycvDcYqDlJzUJGJf/gegySYFx2bnVnJKJIEhAgQ2Y4QCwgxvCLNybcl30g5bB7iOoItGo2ZYSkZ154XffK3iQgW+T7+o5FGZ50SXAeOuh1HEXHDEnw4X8YxbZlxUHQkuAk3qMWQZm5xXhJ1eGoFgjwz1YwBwYiN1z3CLO6fHq4zO1mMWR42RI87QcKVsn320y7JLikhkR4PxJ582YKHpw1xFqWCnD3lRSNIySLtj5lg1EEiyYNYD8sK/1j3M4ZvTVTzlIypfwCGYGKoNhoaEr01ur2l6lzqv/0Ty2pCtQ2sggDakR+RnyTQXoMgnmi/3p3o+YPUkTiYJmrgRQlyzJ8+3GYqH+dIEayhCcmvFbjoN0Xf9FlC3lGgkOFH48olxNtPzIRnvEqbuuRHo42D2MJrpQk7nKZLIKogKTDKHWwa5tPkhiQSEDpcJx/Tsia4XstIHOlcOSrLvQkOtgcUHAq4g0MTErHp2nRguDugX1SePmhmW86wc8J2IVhvxa7NRIP1IWR7XyfuhsKP/FgvqlcCbyC1nFOoYT7G62IC0B/xIUVLmpPx/kbbPDOXhesA7vNCHdUOBDwlMUR30CONxjQ7fi5jzOO5OQekT46O+ykpov2SZ0XMquk3pwi1+HAlVGWyvkWcgTnq0j2unYu6qjPxVtQcjFr/L6HBGSBvYLpRdwNaYon8lvPlL0JLI4mQe4Q0xGwfY/t/Dl/LaYm1ga+/XimC5LRPc+SP6FnhUfAPCy4xnSvRiedu2gNUdqKAOL00kuXvvhaoe9PWkFU32Ma+KmUXwLf9ImyzbaWoOCX1f5jFe0HKdmUDP+iePjWxqC2NENosJC4s7WgQyljBb54kZQk7/GuO4qranNT3xVjQcpG4jSplbCE14JYPQeybGn2ogeqkkvY3XQYnZaWz1rcLFx64pyFtWbHosAJdAvX5nrnyJWBDbGi0T8F5yomCMgNSRBfD74DmkrQI+yxeLeZHBO6W1lN+uNzFgapTMlQiJSsffAKa+o4+0CIndKjzooCIaTDMxTNQptrVIwIlHJvZNB5XsoCtfjhxSWsj8JTVPxd/LUt2OTjadzamGuDvratAjb5CTeu4Esg/O+Y4qQxUOcQe2uydw97a6b0A8yNcdBXvJoX7UC5O/5fU05Wtwq8s8bTjNIKt+GzG2UVjF9nY/SbFZITuv2ij1f1Y7tKIPezl89oj3wCS4etDGNaqXkoiiYqzVm6EDE=
*/