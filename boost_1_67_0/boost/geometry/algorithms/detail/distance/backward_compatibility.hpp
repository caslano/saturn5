// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>
#include <boost/geometry/algorithms/detail/distance/point_to_geometry.hpp>
#include <boost/geometry/algorithms/detail/distance/multipoint_to_geometry.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template<typename Point, typename Segment, typename Strategy>
struct point_to_segment
{
    static inline typename strategy::distance::services::return_type
        <
            Strategy,
            Point,
            typename point_type<Segment>::type
        >::type
    apply(Point const& point, Segment const& segment, Strategy const& )
    {
        typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Segment>::type,
                Strategy
            >::type segment_strategy;

        typename point_type<Segment>::type p[2];
        geometry::detail::assign_point_from_index<0>(segment, p[0]);
        geometry::detail::assign_point_from_index<1>(segment, p[1]);
        return segment_strategy.apply(point, p[0], p[1]);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Point-segment version 1, with point-point strategy
template <typename Point, typename Segment, typename Strategy>
struct distance
<
    Point, Segment, Strategy,
    point_tag, segment_tag, strategy_tag_distance_point_point,
    false
> : detail::distance::point_to_segment<Point, Segment, Strategy>
{};


// Point-line version 1, where point-point strategy is specified
template <typename Point, typename Linestring, typename Strategy>
struct distance
<
    Point, Linestring, Strategy,
    point_tag, linestring_tag, strategy_tag_distance_point_point,
    false
>
{

    static inline typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Linestring>::type
        >::type
    apply(Point const& point,
          Linestring const& linestring,
          Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
                    <
                        Point,
                        typename point_type<Linestring>::type,
                        Strategy
                    >::type ps_strategy_type;

        return detail::distance::point_to_range
            <
                Point, Linestring, closed, ps_strategy_type
            >::apply(point, linestring, ps_strategy_type());
    }
};


// Point-ring , where point-point strategy is specified
template <typename Point, typename Ring, typename Strategy>
struct distance
<
    Point, Ring, Strategy,
    point_tag, ring_tag, strategy_tag_distance_point_point,
    false
>
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Ring>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
            Ring const& ring,
            Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Ring>::type,
                Strategy
            >::type ps_strategy_type;

        return detail::distance::point_to_ring
            <
                Point, Ring,
                geometry::closure<Ring>::value,
                ps_strategy_type
            >::apply(point, ring, ps_strategy_type());
    }
};


// Point-polygon , where point-point strategy is specified
template <typename Point, typename Polygon, typename Strategy>
struct distance
<
    Point, Polygon, Strategy,
    point_tag, polygon_tag, strategy_tag_distance_point_point,
    false
>
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Polygon>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    Polygon const& polygon,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Polygon>::type,
                Strategy
            >::type ps_strategy_type;

        return detail::distance::point_to_polygon
            <
                Point,
                Polygon,
                geometry::closure<Polygon>::value,
                ps_strategy_type
            >::apply(point, polygon, ps_strategy_type());
    }
};




template
<
    typename Point,
    typename MultiGeometry,
    typename MultiGeometryTag,
    typename Strategy
>
struct distance
    <
        Point, MultiGeometry, Strategy,
        point_tag, MultiGeometryTag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<MultiGeometry>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    MultiGeometry const& multigeometry,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<MultiGeometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                Point, MultiGeometry, ps_strategy_type,
                point_tag, MultiGeometryTag,
                strategy_tag_distance_point_segment, false
            >::apply(point, multigeometry, ps_strategy_type());
    }
};


template
<
    typename Geometry,
    typename MultiPoint,
    typename GeometryTag,
    typename Strategy
>
struct distance
    <
        Geometry, MultiPoint, Strategy,
        GeometryTag, multi_point_tag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint>::type,
            typename point_type<Geometry>::type
        >::type return_type;

    static inline return_type apply(Geometry const& geometry,
                                    MultiPoint const& multipoint,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                typename point_type<MultiPoint>::type,
                typename point_type<Geometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                Geometry, MultiPoint, ps_strategy_type,
                GeometryTag, multi_point_tag,
                strategy_tag_distance_point_segment, false
            >::apply(geometry, multipoint, ps_strategy_type());
    }
};


template
<
    typename MultiPoint,
    typename MultiGeometry,
    typename MultiGeometryTag,
    typename Strategy
>
struct distance
    <
        MultiPoint, MultiGeometry, Strategy,
        multi_point_tag, MultiGeometryTag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint>::type, 
            typename point_type<MultiGeometry>::type
        >::type return_type;

    static inline return_type apply(MultiPoint const& multipoint,
                                    MultiGeometry const& multigeometry,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                typename point_type<MultiPoint>::type,
                typename point_type<MultiGeometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                MultiPoint, MultiGeometry, ps_strategy_type,
                multi_point_tag, MultiGeometryTag,
                strategy_tag_distance_point_segment, false
            >::apply(multipoint, multigeometry, ps_strategy_type());
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP

/* backward_compatibility.hpp
dGvBk7avFjPlC4mvOCfxAlaJK7D34LQbuE+w2vvN7bRFaDzgBrbWAH8iKmCGP5ClHqbvePnWX+QiOg20MgFPgyZ7r5n86GqVRt07QNnVuF0RPDr66ZZhvYHrtPLSSH2HyHyDDP/KxBYw2zFqC2gxSsDjFD5okXyxp5Fk4JVyMCRf+CPkZj76uXA0LP/f3HSZRtxpFyty9UjpSSiD/xR2U48tyeaP+wPyN/FMdoB5DLXE5yzS2P37aSkFL4FVcjusGZ/G6sP4eiz88fuBx1/rXCrUPNUjbDaXFUSvDX/S1DgWvn+fXlGYpo8vT8BLdBYfcjUQX7cX6C0BetF2GJ2YTmy8KWJ+vsVYS+aZ6EfE37prHLKyE0m7/Vd3HkjAAcmB3kC1wG74+T1/zkOYlU14Pg+Xng5fEF3grKKwC1jgcrSpav7+SRBBB7pUtS9K8uhGR6xK0NZV6fRm+OWHUQAT4QsR52p2cW+0xaKY79sTHTaGrogOW0KXRIdtoenRYUcIRAlD3B7tdXRvxlwZwsS91xY3Rnst8axor7G2FnWIJWTmEjbxW3YRGrGf/xm4JJo3/KJVJ8kSGUUkkEP8cPKfR7Zg9i3LnFV8H3Ceo1vy21XYEgyxVX4O5zgC3hIyp7/9UGgOmhKFrsNpNPkYsIDuEbbZTsqHyCTY3SVai83CgYZE6YFxQttMqUQAEtWfTJNtFpLQUYV2JCRztU8XkibUVhx9OZ/0ELnKMwReNz4wEdV+z5Ha7131pRSw6l4mRKKrqNwCIRKZclAbWesNbE4KKO/W1mrkCcJiL+OO1K6E8qMbIOtXRNbL4mYEiRWO1cgcqj/zMwkfvjfVBFLrja/7Yy+TSKfAWGNpF7BpxDt6MTwR9pDyHCaFQ//So8B3J8ieQWTnJv1uVWlqmTBC+SJseFOtkIIxhrM/OJ4dD0yAzpFL1O55C9l0ZM/HU7hTtJHCjYi/exS4LdH/2TaSrGFyw7KfwDY+JVgGB6L/Cqm9e3O+OlP5Dfflavn+PE3NZy1F/ItNj2UK1cIL4ggIJ2t4nFKivRXhDtt51kdmFPEuY1SpedPKTNLtjhrxtwYWZIptPkEWbEqhKchRylVWVmVh5bBZhT9lZEBg3vQQ3WYQHiIVp2od0o5EvvBHuZJ22SJqIuOfgcYMMoZTm82X7cDGosKeH8lLqkOuxqNnjhVKop59SVJFh3ZU5amKDu5I5n0iTygVwmuUNVb1c8aORD+256n9iNvuItyoj3Iz4YLnE0biOVuyafuYLdHAnmDj7gNSgcz2JbD5Ipnh2+OT2VInNmQ8NmSp0bW+MPy/rvVVoXo2pxxbhIg8COJCo2XjdXpy7Jq0opGhJ4//+94xyYEd0yKmKTaIbsvWQmNnwRmD8xO7PJgRyNQNPL3KormcOpPDbzIxCVIyZ37ZzDJtMMk7NW7TQCj4sR2W1IBgZO7VT3GbDsA3Za0lxmgQqo28Ynti/P5ohSKGYf9SQlfCUdjygVkqHQ5PYfegPC4vdDISzONmds/vtBf0w5MPJWLEMew0darcYVXNby4Y8lgdwOxUmTBDuSk+nlUZ6acRMoroTyS7q9tDrA23sjFABFCRy3dMSBoFTRC7XOB9czozgHyEn50i7+rv+xL78z+mJlEo2GaBQQdd8tKPQIKAvZjuZZ7X3cv8mDCF3wz9jc0rj0+K3WGEjjnouiZ0ERvf3hv+pHgIAwbH5pWBjFIzd1hRsbENcLjH/6G7aeyuzJX4niNDSmlXY3gCAXwPVM46rYxlpcX/jol3pCTm82eeTvOvxLNNMHCJK2V2qlZ5HjdcONmIOytE460RcZ1PH5R3St3G0EWKON9qtZcu90jz29EeRT0R4PiLn1BrQo0JHXlwANXChrxFdwSV7m3+GpxK9+te4Yr/F2yWmp+ybv+HwveOeSNQvp1uBIT2OzGK6NaB6vovdOvQ7r9iOpcMek2XZANb0zw10I2CMuzf+oVuFJSYivnZFydWYySTYanbGBg/JcXp4uoHc5M3Gx3S/bp702xpc4T/5evatdz9j53BMKTVI905lffj1fQTcGzMfADvWFA6xXsH+W4bKq3uttO/DvoXpU3+4hqTdF2GlCPN6IweORbtXCFvflLcpt1UpF1F6NqWKJrv+NkZ5Vztq+E3l51WluBiGdi2zZKQl1F5pjedQvPTbasyx47pFj0WSIm5fZzHzcBXI8RbMyNCY9U7azAujHsnywnYDXTH5H5wSsL0UAl38J0W3GGkhTAq0yzqDmMSAOCo7Y1PCQ5CMmBggSnaw+3RIxms+tE9A1knD0Y/yCjdE5pysn9Gb/SD7BpK9dr5ZCTAugki8+dTR4Xz0Nsk1PqUdQ7Wz/6lYdHA1vHDeywScHsnSWelItR8xO7E1kQXGorkHDbHUUvkyh4H/44ZKS7uBTouZeQ7wixt/5/0KCyWmlj1CXKqQAssBJ1mNxjil6rGT3L1Mbl6UK4+Qc7QwgvyBKseLnAfK6ge9MkL84OK7HGycYEJ2Gv7RXf52SD/9bU0bthFySHDFneRjv9356WCgqaMEfo21lng7LCKeJIwFoSuEH4U473AUzZZ/z0JG+Qkdr2hrfrBjfSiJ1a3k7+E6FQq9OhCrCUtXI6+njobGgPUPYq3gnVPQJ2J+hC7Qq7brdY3TtSHxTeK4ov/3MQHp2DpaRGF2449mOIWs1PE8yajHGF6Y9ON4osxmNM5pEwyGQS8Aalv+sS8xDOfDPHXqYFB5tdq0xPYA938BFGHn5yUmKBrJ6lXMPoJeh5MUFQY6mcoSEL6KcryvLWBSwQh27Hg0vfD7ewCtDGMbXIiRohXfpGaBH8eFH8eFX8QVF01zBG8xQYF1YaCbMG2EulaxD9B+BCwMsbwQki21Ylmi1rK8QYqdJsoe4f4o6tX5AaaRHgz0c1eEEN3Tm+KoA9MuE0jOAGnFdCSQxlbRFFbpfRqgPEJW2IiLCweKm/+4YzCRL6CTZSebSUK2A5KU7CDcmf1QCLsiaxXgTMUP9WErhZLuLBgK5X+B2WDYMWbZCN8xlTIQcleA3/crBkmFYjW/J7SHogfOFegFHIHq2WnYKJY+W+/eVqhWbWSwawKW1jXpYpSLrW1WA0cGkh28eHx0R6j+BlAXAf5kZ1k3/4thFxJQVNPAt3g8NcqYWvbhwszXyFM74kU6MrhbXtjYaaU6asNGOHEAKnMdB6BWzubTvY1zuiElp3s43+anBa0ChmT4ATCfbIzz2L03CAUMYrXoE085GjSTDh1G2JxJzl3p1trslOqywK171Lc3gTwv5e+7ueG38Nouo9l5DD3YIbHAHtZhsfI3IhAm+Ex0ZYxY7JuK27bgyfVwH/VDCspo6AuZt1C/lS2SOLiC95zjJ8Vfc3Ehv38Jmpp+DwtlAxyWv+w5krxXFfEEe7G12hdAasUsi5qHo0byuqMbR99WwR4/mgq4lo0/3lIYXu4rR9RrVTTjMSRn8jc4bw/5SafJo8tOXmsxJsTZz4biMdA6z6Bd8GuExbk8Tp4cQBeXIe36iF3cNAnNg8M4GEJzaLLhSSQK/xjw3sRKociPJLloCXFctCOxuPvskGo92cwU+xNjSBA/MIk1HGsKx7Xj/iqFKPdFH4Qd0uy92N300bp3iFX74SdukhgFFfE3Du9Yq+kVNGWDil0GR7jB424Sz7lBebDa1SP8UnIztNGicGp5pQ27Lj9lYSZ7gST7jY6gBOr452DCDmBl/tuI2sxefl8I5rCB7DHYc/4y7hpOOTjy3nz5RT1RWzm/lgspKANwwr4l//2iSGlWBF2o7HV+L5lhL/71kRitJjHwS44XM0iQYSBwC73xtoxEYKT/gVGnx5ghimrT4hSvfzCpUOK/FIAS3pplYIoolAhPpIBya2fZ0nKs5gSzhYyNbUBiSVUGaUq3R8aB2xUhuI1qKV3DvK5y7GukPrkwqfugcvgMVa9EfiGLTXKrCNApdyyUW7ZIopdAMV+1dWyBYGftqg83Zi1FCtz4/dRObFm+AJFHcWiXsKHZFEXQilsFpaivLPERR9DTynP4l/lnfiuPd/fmCmEYvUEJbtPl3tjaLouo5Z+ycBt1NGbXC0bW99n7k2kbVOzye0RTASZN5ljb+BR8CwOVMy9NShpSmkaOkJI3wrvvcqzmKXbvQ0NWhOT7a3gCSX8pBg2dh81p3qTy3BX6EKFqtBXCtXRu+bt8cbSGP4KTakRxQYu15Kw6i3FnXKl2Qo/4I9N/HGIP0XiTxVzb4lVjjO0Ob6H0c/cW7K6QSLYFJioFaK4N0GDo90rSt0bzVslqKBYGej7XLWoDNo77sNJ3XXJNDSy5z/IRgZZTGjYNrO1Cb3dKSY08ZkIqQfMofsI/8djMJmHVJwYkxwe4ZMOqjN57uiZ7DbBNP7Fm2Saqc7h6kEvb6iHCRzuk8OHfb5YdR9N2+dPw7QND2pz1ophsKjY6r7SN5ITFsqB+Xl/w5AWc+lu/Nk1sACa6fOJztZsgmS3sbQrPG10KcVDnvizxb3BFd86+Xfztj0n+yf21PB5m0cU2X0Ug4/3Bg36L0XwhYXRawQ+mn+DcPnofI3zJPqdY7D9W1EXsNYX7XKy6iMxz2EYj2OyUTBBniO3TdTbunuORo9kwrxZO5LVmZGjzp1q2Pu5bLgrunJEiq49YqmIdq0Ahry02nj7f6ONbxZ743u9K0CeOAp9QwtR8Rbh2z0fZMJbjm+Pirf4pC2G8FFYCUvU9rf3Dpz+XO/ch1saHIkm1YC3JvBs/q3oCvj2WDBZqSljBaNT4kkNwuyOB1EOMcgeo+xBlIOYx84fzz6NlkNz/g+e890ZWGCswj7wQyhE4yuCFwYvZMejK0tIBxzzgEycuwIv1FeWQY9br8brBw9KsJpkDkLw0Q0w640XUxCxFmPxIblhpPR06HxlbhHb72qwhLLhEItn4RXC0k/OgKhjY56S0r2hC131ZeHprMquVBXBG1d90QYju6GMr34TEjWWME/ZqERliUTzKVEZEoiQaKs1fyO3pXRv+CJEHGstYRsR7Fn2WPlFF5NRY8esr98a2RsflFvL4n9P07ABBX6ycMlSyovY/BKKZfHSAeB1PCXynJJolyG23iCCYRrZXKs8x8rmliWSl1HyuzH53LLYGrs8p4x/rXmcFJtr9/GRLEkaZXKkDurvcAwWFunHlZtgMsUWruYGFJNggrwhb0ZVFl+sORoa/iNTadUndbWojEqFGhsHTp9RksN+K/x/AjsenKAb8oU2BfZMjx2EX5BPZU++7CmEOSBZJL225jh/UaES+UtniO7Ggd+d0a+GGiG3PYdtCKy6964InyEh04BezLB2wplsH5/jOaWgMJkVlPBavxDFaLKeCN2krC3kyyXSTD4Ked9X8lCHHzZh8rkOhKOFOoEyhLq0xjwh5FG5I0+CEfMlDCeYewTG6ma615i1G9fzavXuJb6QtYxAPS7ciRcWsQwskUqa6RU2Bo+iMNnDd0CZUCFqPSmGILozwNyKT/ZC/WxKrRdoUBZZSQ9nTNNmhrJZRSCew8jjc7SyEz+vws9Pjvk5VjEznBWrCI2dsRIzbjpruVX4ecsYnxE05rYF4ZzY0yiR8eY7xpE/Ml8o3ESNo4jAtG1b9SUpt+XzP35uhaEJLIGZVfk5Dk3ahTAsxdD5zGuVa6zMmy/X5Ef3FLEp0c4ir7LIFnf4/LHVhtgdYmV5C+Wawuie1fh9NX5Pd7cTYNYij7oaq6zyfCvsD/J8O6tyyPMdrMopz3eyKps838aq8uX5+ayqEOqT5xd6Y/OL+AVCmYA1xOav5pMJDJeQVw2jamJVJT6/PL9kdH1Uerm21L8ZGSfKhNV+lgJJwpnSYpH8LGJoV0JTfRixCvadb/JX7xxS2pXwJ0L9rNmPWydvjvAfzJgGMmVxp6vBJDcc026b/9RskRKAcv/smUgmeLDp7g1NXemyhWBGwvt/1wwpA6hR4D3fM0hQKe/Ev+WG4l5Xfb35vj2l+0LP8ieT71aJd48FDuCeBCU8AyUo6+oRXq7q/iFFnHbHWMWJl3c83hTB2rw1mI7fOKT48MenD2CGVfTuAfXd+w8I3GD4+bb2bh/82NIwokLSXVYHfEZ4MNo16ONPL4bfLdCRFnkcbGJ8Qh05iDTNmJZwbAxKQq0+/arTymOvX8ki6R8k/PB24oMYzj2s2ngoo992qMLQX29IG2v82A8f+8f42A8b8B745DbRp1SQcBi+PSCFiUg0ebKlfQiO8bUGebWhcYwqZCOip1alldL/MX2EjTC7v84YzwZCGoxQa78Nz5S/9SFR4sWYdLMpsoXdYKBiR30ULYacRtHuQxXQCtNZW48JRR/0j5HwXISKVzlYhEqrUfcy2QCtSSbtjeksvW1BUqjP+91WSmYZs+U1RtlrZDUGGTjYG6Bz0xtXhyP0JoxQL4zQBNmo/s5i84xyle4JO7D9TRi9RSbZazrL4OFVhhhCVm2luixp08GPaU1sGLcK6J96CzS+qb/eOtptmFpwXE1ZYaGkVjXpqMqh22x4iH7J5DAMfRf/Lbtowc2Rw739vTSqpr6bDO/BT1N/ubFPzPW+ctM55hT1qTYnzjJtYIxN/R/3QzpLv9cYn/qlM6qrDfoKRzhDm3emsUBkIVF3juNRZH4J9aszND3mNYKgwP7EfcfI6c6Iv6cPWMZAcfhi9qjC2J2BxWPBwPJ6jTVQ2Jm4heKReuH3big4lbVmOYrXrhnFe206R+CZD4+N38ALUOpdaZK6cyKPkoPxf0onMNpDt8CR8N1c9bZJlERBeRu+JpH3NogCV6Bi5Ot5Kf5X0I8IfNgZ+ips9RjBLbrBJIXt0e/A8WyM1RkXoXReM5NsaWCm32iKZ3dkl0sbm9KMtGqid0A+GHEoEEa83hC3swoTFjG8CAqw9GO8r/7p/eUGWMRLDKMxXSt0c+EgvxFP4lf1dB7kpfAON4bz2aujYtUdpLO73+0I5vSfvyT2A0MsbPx0VxN7NQ0BOHrM1s99/XXcj1tWf90xSF83uKS/bjgWga1oJBbm/XUnPiTcY4wwPJAA4G9337Vt27Zt27Zt27Zt27Zt27Zu7+7HkzT91aaZzEyazPYy7Jfw7U7STLaf69m3Q+DdKsMD3Yd6kPRwmfrFDMaQeNtOEIrFg4fkV0Fe9m4HjMd3X8KCq+ChfklTXsFB414b8d37orYV7W8783TmxWTsY0h5uD3O0gi6vdKSvUvh74TWJRP3HdRjHh67P7o+XRTbetpowKqojry0U7GwRgEqgj2bIAqawJZLNPO3C2mMQQACxnXVT+zrAt4gqaaHDqJXv7EfbrU5lMmHq6dDfJWENtE/kj29bwm0VSRdaECJJ5NKJE3byGDlpeAbqk3DOou48obS55NrXah/hHMsyEKlCgMqVUDCVGgGVSDpiK/wtWX+uAK9I/1qk3grkkh7tWeWJdpDi88XfI6dgWi/nhIGSXS80QjMesXKmOWA//Q8z7qekMGbBte0CFWM5JuWg+7jNasV1tK1Us0u9hv3Nxz6DoQIod3zlXXKqmef7iLQtP+jlBm9qakrqeqCsHwiybshUbSYEu4GasVNSenT3R5+GSLou9Aw3Dc0oBpCGrzbEUPdPryvhTmO7iBa0u0h8OvPMRuieP/CZ0RKGbuNMhXmtHYrZR+TiXxY11FC7/287SqaaDOcHOyQfJ1inrufpAaflajsUKtFlwf7TJ0z6XD00Fu+g2gyoTzatlSSI6B0qD+7QZrqo+rFjW0RJzvW8N/Eail679ErnZl4C1j2uHMZ4mUgHbMfMBppcM1dGasnHXuvFjpKMjtiU3awEouRtoTQtrMSx68GEHckusB6wy1rxFcvFdTmZER03kBw9hFcet+4tsiGaZ7RqlJU3ReTCB7Nu0tqFoGAXDd0bI/ON//JC6/1BzSOxU7X05NMubKIMO03lFidQ3C3cTAIfzLDVHd0IGQEGO9azrqgqwImgXYvwIRSKMtKGW2e0KAEe5XA0ZZFWmBItxSrQjpppLC8nrgm2bJCmBxO0aIpHIh3MYxSj+U2jmwqtYlv8rIqnxxF6R5P6fFSC8Z2kyYjV2wRuq3Dt9mEZkmpLxO551h4w6U2RqkTNxfPNpW1kJLM4AVxcjejoHIWAwjk1FG3NlC0SBIO7rjmkv/viHZj0qZOcIAqpZ51o1CDsZgkvZyEvg5icH0hiWgRLdGco2v82eLSDQl1TLFEPvFZ5l+9t2INZrh71Tb7cZ33hI1h69PZ7F4oapqYv4AFUWU6R2flTIMLgMPuMoze2n4fBGfAuqQBdeh+XjSaJK9lTQSzcR3/j3oPkbdsvUBEVRi//Wb6Jo4zZ1Uai1fb27Ssa3IHdWsvICBpBnUeeKb0C9JED4HWL0nGI9fbNxJkF62zCW+Aovfu0JDS6EmZ39WXAJPUk1o773jJMf/mO4rixP10LfrIu1oR72Bk03TXYbhQqotTjL0Pyv66SlnQoznQwooTZXZxsl3KTFRw9YY6xtzMwkBT982orleKwho2b7a25PB6cxrKqcBJY+B/zKnUTcsMmlXNY7VV1EorJ7QV9xTNM8V1OLUD/JSscG9wVevxwhPM9LtSam1uMEeRwJwEtFVLtGrcM1s1mvmhtulxZ/t+Ljs9AqfWxSvNaM05uvT0zZa+FSXozS2Uiqsuxk8lE/KWmm1dqlNJlhJr0Ml0m6Rva8qRXcwRs/Qa/MLik0cZD01FM/JsPvOcFPQLhsLGAYEzsabDFCYEiNTZ0dE4lJr4JpScmi0xg4ZSqQhZNIz6G3NF8yWT0W4BO118ECdU8Iwnihm0m03vDI+8x0bmUznMJCNWmSwmiOHK6nnR65By9L2GXhP4d7+LUpRSU03AhjNM9Lo9rARnmMy6KEUzqcDzmShZnj1Ubw+Pxv3tJ5ASwpIUwgXiY3WmeIM8H0R5TsqGRZRY1NPUeeFNePTxET1bX5KzLI9Zj7LB5SNaiOSoR2Thps+qSgFUK7c485l1xcSUg0bK5OMcIbMk+q8+BWUt/0Fab7PHElw23qaHKzxAANGq2o3iSr7oJN8P2yWMjclLSxdadohXjxNVFeSTLI0DkgaHRmXDoIMmm0lWQb9CqGG+mpLGCGPSjTdzXSJ2KYPYI06UcCxBFJkOGddtWaRqYjtUits0j1W/n4GZ4d9GshrFJhLmaHmBvKO8f/s=
*/