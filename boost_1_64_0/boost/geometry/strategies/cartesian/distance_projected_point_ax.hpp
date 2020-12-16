// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_AX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_AX_HPP


#include <algorithm>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>

#include <boost/geometry/strategies/tags.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/default_distance_result.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

// Helper geometry (projected point on line)
#include <boost/geometry/geometries/point.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace distance
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename T>
struct projected_point_ax_result
{
    typedef T value_type;

    projected_point_ax_result(T const& c = T(0))
        : atd(c), xtd(c)
    {}

    projected_point_ax_result(T const& a, T const& x)
        : atd(a), xtd(x)
    {}

    friend inline bool operator<(projected_point_ax_result const& left,
                                 projected_point_ax_result const& right)
    {
        return left.xtd < right.xtd || left.atd < right.atd;
    }

    T atd, xtd;
};

// This less-comparator may be used as a parameter of detail::douglas_peucker.
// In this simplify strategy distances are compared in 2 places
// 1. to choose the furthest candidate (md < dist)
// 2. to check if the candidate is further than max_distance (max_distance < md)
template <typename Distance>
class projected_point_ax_less
{
public:
    projected_point_ax_less(Distance const& max_distance)
        : m_max_distance(max_distance)
    {}

    inline bool operator()(Distance const& left, Distance const& right) const
    {
        //return left.xtd < right.xtd && right.atd < m_max_distance.atd;

        typedef typename Distance::value_type value_type;

        value_type const lx = left.xtd > m_max_distance.xtd ? left.xtd - m_max_distance.xtd : 0;
        value_type const rx = right.xtd > m_max_distance.xtd ? right.xtd - m_max_distance.xtd : 0;
        value_type const la = left.atd > m_max_distance.atd ? left.atd - m_max_distance.atd : 0;
        value_type const ra = right.atd > m_max_distance.atd ? right.atd - m_max_distance.atd : 0;

        value_type const l = (std::max)(lx, la);
        value_type const r = (std::max)(rx, ra);

        return l < r;
    }
private:
    Distance const& m_max_distance;
};

// This strategy returns 2-component Point/Segment distance.
// The ATD (along track distance) is parallel to the Segment
// and is a distance between Point projected into a line defined by a Segment and the nearest Segment's endpoint.
// If the projected Point intersects the Segment the ATD is equal to 0.
// The XTD (cross track distance) is perpendicular to the Segment
// and is a distance between input Point and its projection.
// If the Segment has length equal to 0, ATD and XTD has value equal
// to the distance between the input Point and one of the Segment's endpoints.
//
//          p3         p4
//          ^         7
//          |        /
// p1<-----e========e----->p2
//
// p1: atd=D,   xtd=0
// p2: atd=D,   xtd=0
// p3: atd=0,   xtd=D
// p4: atd=D/2, xtd=D
template
<
    typename CalculationType = void,
    typename Strategy = pythagoras<CalculationType>
>
class projected_point_ax
{
public :
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : public projected_point<CalculationType, Strategy>
            ::template calculation_type<Point, PointOfSegment>
    {};

    template <typename Point, typename PointOfSegment>
    struct result_type
    {
        typedef projected_point_ax_result
                    <
                        typename calculation_type<Point, PointOfSegment>::type
                    > type;
    };

public :

    template <typename Point, typename PointOfSegment>
    inline typename result_type<Point, PointOfSegment>::type
    apply(Point const& p, PointOfSegment const& p1, PointOfSegment const& p2) const
    {
        assert_dimension_equal<Point, PointOfSegment>();

        typedef typename calculation_type<Point, PointOfSegment>::type calculation_type;

        // A projected point of points in Integer coordinates must be able to be
        // represented in FP.
        typedef model::point
            <
                calculation_type,
                dimension<PointOfSegment>::value,
                typename coordinate_system<PointOfSegment>::type
            > fp_point_type;

        // For convenience
        typedef fp_point_type fp_vector_type;

        /*
            Algorithm [p: (px,py), p1: (x1,y1), p2: (x2,y2)]
            VECTOR v(x2 - x1, y2 - y1)
            VECTOR w(px - x1, py - y1)
            c1 = w . v
            c2 = v . v
            b = c1 / c2
            RETURN POINT(x1 + b * vx, y1 + b * vy)
        */

        // v is multiplied below with a (possibly) FP-value, so should be in FP
        // For consistency we define w also in FP
        fp_vector_type v, w, projected;

        geometry::convert(p2, v);
        geometry::convert(p, w);
        geometry::convert(p1, projected);
        subtract_point(v, projected);
        subtract_point(w, projected);

        Strategy strategy;
        boost::ignore_unused(strategy);

        typename result_type<Point, PointOfSegment>::type result;

        calculation_type const zero = calculation_type();
        calculation_type const c2 = dot_product(v, v);
        if ( math::equals(c2, zero) )
        {
            result.xtd = strategy.apply(p, projected);
            // assume that the 0-length segment is perpendicular to the Pt->ProjPt vector
            result.atd = 0;
            return result;
        }

        calculation_type const c1 = dot_product(w, v);
        calculation_type const b = c1 / c2;
        multiply_value(v, b);
        add_point(projected, v);

        result.xtd = strategy.apply(p, projected);

        if (c1 <= zero)
        {
            result.atd = strategy.apply(p1, projected);
        }
        else if (c2 <= c1)
        {
            result.atd = strategy.apply(p2, projected);
        }
        else
        {
            result.atd = 0;
        }

        return result;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{


template <typename CalculationType, typename Strategy>
struct tag<detail::projected_point_ax<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_point_segment type;
};


template <typename CalculationType, typename Strategy, typename P, typename PS>
struct return_type<detail::projected_point_ax<CalculationType, Strategy>, P, PS>
{
    typedef typename detail::projected_point_ax<CalculationType, Strategy>
                        ::template result_type<P, PS>::type type;
};


template <typename CalculationType, typename Strategy>
struct comparable_type<detail::projected_point_ax<CalculationType, Strategy> >
{
    // Define a projected_point strategy with its underlying point-point-strategy
    // being comparable
    typedef detail::projected_point_ax
        <
            CalculationType,
            typename comparable_type<Strategy>::type
        > type;
};


template <typename CalculationType, typename Strategy>
struct get_comparable<detail::projected_point_ax<CalculationType, Strategy> >
{
    typedef typename comparable_type
        <
            detail::projected_point_ax<CalculationType, Strategy>
        >::type comparable_type;
public :
    static inline comparable_type apply(detail::projected_point_ax<CalculationType, Strategy> const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Strategy, typename P, typename PS>
struct result_from_distance<detail::projected_point_ax<CalculationType, Strategy>, P, PS>
{
private :
    typedef typename return_type<detail::projected_point_ax<CalculationType, Strategy>, P, PS>::type return_type;
public :
    template <typename T>
    static inline return_type apply(detail::projected_point_ax<CalculationType, Strategy> const& , T const& value)
    {
        Strategy s;
        return_type ret;
        ret.atd = result_from_distance<Strategy, P, PS>::apply(s, value.atd);
        ret.xtd = result_from_distance<Strategy, P, PS>::apply(s, value.xtd);
        return ret;
    }
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_AX_HPP

/* distance_projected_point_ax.hpp
qvLETfg1bsHqNTgusCduw/74IObgQ7gJH1XL4WMqf/gHPI07sbU6r2AnfAan47O4HXehqxb7PTbCP2MkPo+xuAcz8CWcja+o5XAvPoV/RXW8Jrvkfdm4wKWP11DUw59Yrqa+z34V2+BrOBL3YZY6xtGDb2A+vintCvvlvmWNS95zLe+/Jn6yzXaQ+POq6nYBDzbGOdgCr8HheC0ux6X4sFoOj+NKVPXATdgEV6nl8BbsjWtwIN6O8XgHjsU7UeVru0veW42xkq868v4E9TtcVa/3h6jW+xN043EsxM+xGL/BtSou3Iff4jE8hd/haTyNZzGEdH7AOvgj1sNzGIG/YisMqcb9LFbG/hiK0XgpSruI+Q5qF+sf0C7S+hLdvhKDkRiHWTgCczEei3A0LsQx+C6OQxVpEqp0GgaZ72423ulMOvpeprqaoKymt1sNbIw1sQXWx0HYAKdhUzyMEajKpTn+ii2wJ3G1xCRspebH1jgd22IqtsNZ2B5vwo54B3bBe7Ab7sXuGFaJ+kiVG/bBJRiNW3AwPoVD8BWMwU9xGP6Cw1H1/RmJTXAUtsAElU9MxL44TraDxyXvY8ZG0j5RzXg+o38zg3W7USamYhZehVfhtTgbV2I2HsJc/ATz8E0inYPvYYHcNxXK/W5YkPedy67Fsv0v598hsl2+qqW3y9fYWO2f2EnlFXvjtzgeT2IefocL8DQuwTO4FL/H2/AsbsWf8An8GXfhOdyDv+JrLpUxvR8F4YdYCb/EYDyj8ocqj1UwDC8Jk/0bY/FSHINVcTJWwyuxBmZgLZyNYZiP4TgPa6O0j8s7mI1/Uy729vHWl+pyaYfNsQMOxY44HDvhCOyCo7Armtv5iMT7oCtwO4ddquuJcLwca2NfrINjsS66sR5mYQOchw3xbmyEm7AJGu9uQWmXNN+PzDs2AtslJ1TT6U5Ele4k7ITJ2AMno1qPKZiCUzEdp+McTME7MBXvwhm4EdNR2u/k/cccs5K+tf0uo6puz3djE5yJETgLpT3efIcx5RXYHn+VLD8bq2K2LBfGxP2y3EPV9XKqfEKYrn7pl+jjyo0qrkzsjlkYo+LFiSo+zMM8vBM9+DjOQbW/5uN3WICqPb0Q2+IiHICLcSwW4wJcgrfjdXg/Xo8v43L8AFfil3gTnsNVGMxxu1rlF2/Blngr9sTbsD/ehRPwbpyNGzAfN+Iy3IRH8D78HLdiKGVyP9bC36v48QHshNuwG/5FrQfuxQz8q4ofD+JGPKTWA/+Oz+A/cB8ewYP4EX6Ex/Ab/AR/wU8xJITrWuyAn2MUfoGD8GtVbvgNTsRT+D6excP4Ix7FX/AHPIfGA59Q3c4ShA3xEuyHoRiHl+IYrIZJWAtTsA7egHVxNTbATdgQP8Km+A1ehmfwcvwJI7CKus7F0dhWxYsd0I0d8QHsik9hJO7CHvgC9sK92Bs7U9H0x/44AIfgQByOV+A4HIp3YQxuxuH4OMbhSRyJP2A8nsPRyDq7ErAdJmJXHI8xOBGnYDKm4XRcjKmqHDANt+AM3IHp+BfMwL/iTHwNZ+Hf8So8hXPwcnV9jW2wCKNwLk7G+So9XICZuEili4txOV6NN2MxPoRLVPp4nUofl6r08Xp8A1fgMVyJX+BNGFSV4wfr4M3YBW9R6ePteC2uVenhnbgC78H1uEltf9ypthOyjsZ1/z78B76pyhffQq5NXG9jS/ybKmc8gNPxA7VeeBCX4iGVDn6It+Df8T78Qq0ffoWh1dn/sRaewLp4UpUjnsGe+D1G4TmchS7q+yIMwrswGO/B6rgFa8j5YHeI+W5otpXUi6r+3sF09evBfE2xF7bC3tgJ+2Is9sdJOBCvxSs=
*/