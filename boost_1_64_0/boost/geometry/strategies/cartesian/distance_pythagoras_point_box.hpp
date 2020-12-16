// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_POINT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_POINT_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/calculation_type.hpp>



namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <size_t I>
struct compute_pythagoras_point_box
{
    template <typename Point, typename Box, typename T>
    static inline void apply(Point const& point, Box const& box, T& result)
    {
        T const p_coord = boost::numeric_cast<T>(geometry::get<I-1>(point));
        T const b_min_coord =
            boost::numeric_cast<T>(geometry::get<min_corner, I-1>(box));
        T const b_max_coord =
            boost::numeric_cast<T>(geometry::get<max_corner, I-1>(box));

        if ( p_coord < b_min_coord )
        {
            T diff = b_min_coord - p_coord;
            result += diff * diff;
        }
        if ( p_coord > b_max_coord )
        {
            T diff = p_coord - b_max_coord;
            result += diff * diff;
        }

        compute_pythagoras_point_box<I-1>::apply(point, box, result);
    }
};

template <>
struct compute_pythagoras_point_box<0>
{
    template <typename Point, typename Box, typename T>
    static inline void apply(Point const&, Box const&, T&)
    {
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


namespace comparable
{

/*!
    \brief Strategy to calculate comparable distance between a point
    and a box
    \ingroup strategies
    \tparam Point \tparam_first_point
    \tparam Box \tparam_second_box
    \tparam CalculationType \tparam_calculation
*/
template <typename CalculationType = void>
class pythagoras_point_box
{
public :

    template <typename Point, typename Box>
    struct calculation_type
    {
        typedef typename util::calculation_type::geometric::binary
            <
                Point, Box, CalculationType
            >::type type;
    };

    template <typename Point, typename Box>
    static inline typename calculation_type<Point, Box>::type
    apply(Point const& point, Box const& box)
    {
        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point>) );
        BOOST_CONCEPT_ASSERT
            ( (concepts::ConstPoint<typename point_type<Box>::type>) );

        // Calculate distance using Pythagoras
        // (Leave comment above for Doxygen)

        assert_dimension_equal<Point, Box>();

        typename calculation_type<Point, Box>::type result(0);
        
        detail::compute_pythagoras_point_box
            <
                dimension<Point>::value
            >::apply(point, box, result);

        return result;
    }
};

} // namespace comparable


/*!
\brief Strategy to calculate the distance between a point and a box
\ingroup strategies
\tparam CalculationType \tparam_calculation

\qbk{
[heading Notes]
[note Can be used for points and boxes with two\, three or more dimensions]
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}

*/
template
<
    typename CalculationType = void
>
class pythagoras_point_box
{
public :

    template <typename Point, typename Box>
    struct calculation_type
        : util::calculation_type::geometric::binary
          <
              Point,
              Box,
              CalculationType,
              double,
              double // promote integer to double
          >
    {};

    /*!
    \brief applies the distance calculation using pythagoras
    \return the calculated distance (including taking the square root)
    \param point point
    \param box box
    */
    template <typename Point, typename Box>
    static inline typename calculation_type<Point, Box>::type
    apply(Point const& point, Box const& box)
    {
        // The cast is necessary for MSVC which considers sqrt __int64 as an ambiguous call
        return math::sqrt
            (
                 boost::numeric_cast<typename calculation_type
                     <
                         Point, Box
                     >::type>
                    (
                        comparable::pythagoras_point_box
                            <
                                CalculationType
                            >::apply(point, box)
                    )
            );
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType>
struct tag<pythagoras_point_box<CalculationType> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename CalculationType, typename Point, typename Box>
struct return_type<distance::pythagoras_point_box<CalculationType>, Point, Box>
    : pythagoras_point_box
        <
            CalculationType
        >::template calculation_type<Point, Box>
{};


template <typename CalculationType>
struct comparable_type<pythagoras_point_box<CalculationType> >
{
    typedef comparable::pythagoras_point_box<CalculationType> type;
};


template <typename CalculationType>
struct get_comparable<pythagoras_point_box<CalculationType> >
{
    typedef comparable::pythagoras_point_box<CalculationType> comparable_type;
public :
    static inline comparable_type
    apply(pythagoras_point_box<CalculationType> const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Point, typename Box>
struct result_from_distance<pythagoras_point_box<CalculationType>, Point, Box>
{
private :
    typedef typename return_type
        <
            pythagoras_point_box<CalculationType>, Point, Box
        >::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(pythagoras_point_box<CalculationType> const& , T const& value)
    {
        return return_type(value);
    }
};


// Specializations for comparable::pythagoras_point_box
template <typename CalculationType>
struct tag<comparable::pythagoras_point_box<CalculationType> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename CalculationType, typename Point, typename Box>
struct return_type
    <
        comparable::pythagoras_point_box<CalculationType>, Point, Box
    > : comparable::pythagoras_point_box
        <
            CalculationType
        >::template calculation_type<Point, Box>
{};




template <typename CalculationType>
struct comparable_type<comparable::pythagoras_point_box<CalculationType> >
{
    typedef comparable::pythagoras_point_box<CalculationType> type;
};


template <typename CalculationType>
struct get_comparable<comparable::pythagoras_point_box<CalculationType> >
{
    typedef comparable::pythagoras_point_box<CalculationType> comparable_type;
public :
    static inline comparable_type apply(comparable_type const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Point, typename Box>
struct result_from_distance
    <
        comparable::pythagoras_point_box<CalculationType>, Point, Box
    >
{
private :
    typedef typename return_type
        <
            comparable::pythagoras_point_box<CalculationType>, Point, Box
        >::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(comparable::pythagoras_point_box<CalculationType> const& ,
          T const& value)
    {
        return_type const v = value;
        return v * v;
    }
};


template <typename Point, typename BoxPoint>
struct default_strategy
    <
        point_tag, box_tag, Point, BoxPoint, cartesian_tag, cartesian_tag
    >
{
    typedef pythagoras_point_box<> type;
};

template <typename BoxPoint, typename Point>
struct default_strategy
    <
        box_tag, point_tag, BoxPoint, Point, cartesian_tag, cartesian_tag
    >
{
    typedef typename default_strategy
        <
            point_tag, box_tag, Point, BoxPoint, cartesian_tag, cartesian_tag
        >::type type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_POINT_BOX_HPP

/* distance_pythagoras_point_box.hpp
sBzb407sgBXYEaswAA9gZ3wPu+D7eBEew674GV6M0h5K63eXd38820PNY7yOuBAH42IciXkYiUtwGi7FJMzHObgM78U78TEswC14F27DFbgP78HXcCW+gatQbecgferiLot2Di/Ie1A7sSfuwoFYgVfibhyNezARX8RVWIlbcC9ux334PL6kvzcm/eDiZFmu8b0xu7w39nvsilk4ELNxBOZgJM5Fvd2BzK+5xXXVjYyneAs2w1jUrlOqZTqbxXXKDnlfuwL74G7sj3swHF+UdFTiDNyLcUiey30L6YMWoy3uW7zMeP74qqxfFY7G13A8vo4T8A2chAdQa6dRKfO9xqKdxhzJv1QMxjTJt3RU90fpLxYfstgfj8r7+x9hP/xY5nNc0vUJJuCnmIwnsAS/wKfxJJZjDe7Er/A1PI1v4xk8jGfxJH6DZ/GcpO88NlfeH8EA/A57YC2G4F9xBP6IEfgTpiErRPtfwIXYFO9DHyzGZqjeL5G+ZfFuL8/7JZewf7TBXtgNe+Ng7IPjsC9GYD+cjv0xEwfgIhyEd2Ewau9xVsvyelm8x3mxXL93wxDsjtdhIE7ES/AW7IEF2BMLMQjXYW/cgn3wXeyLH2E/rMH+eBYHYgfluIeBGIz6e8vLpTxZ7I+zpDwlYCAmYhDa8HJMwhGo9UegzLtQ5rdDjo/K+rWX4+PHrdT5fYb98ASG4ec4GU9iLNZgEp7CpfgVbsfT+AqewWP4NX6Df0If5dgs6/kNdsVzGIJ/xgj8DifgD5iCTaiXbsOmuAab4xN4Ae5FXzyCLfEMtkIf5XoHO6M/XoVtcQq2w7nYAZdjR3wau+B2vEjqQbal9O/KNFIuWivHAa1/ELn/fxAH4lt4LVZLPr2NN+I7GIfv4jL8I27D97AKj+ABfB9P4AeoPBf5EFvjUZT7ldKPK8u0uF/5obQzPIoD8CMch8cwDj/GBXgci/ATfAo/xSr8DNV2uNJ3K66waIfLtnDuD8uwH96B4/FOnIoFOAPvwhW4AjfiPViBK/EdXIWnsBC/wdXordzHwnFYhONxDdpwLWbh/bgUi/FOfADV44X0k4rPWBwvKhlvEO7DYfgSJuJ+TMaXMRtfwQX4Kj6AVSjvBUs/pszX2/O94INynlSNQXgI++M7OAIP42h8F6/D93A6HpF0fICp+CFm4VHMx4/wQTwm+fgxPoPH8Tn8BPfjp3gAP8M38QSexs/xL3gSf8RT2JT0f6Wvl/RrigUW67VNnrO9gMOwHCfiDrThLlyGFbgRd+Me3IOVuBc/wH1Ygy9hS2/mj+3xZeyIVTgAX8MofANj8ADOwDdxJr6FSXgI0/EdXIKH8XZ8F539GHhr/aBSpqWe66Xc35R6br3UcyV4EW7Ay3AjXo+bMBkfxVzcjAVYilvxcdyNT2A1bsEvcCt+h0+ir3Kejy3waeyJZTgKn8HxuA1vwGfRjttxOT6H9+DzeD++gBuwHCtwB76Hu1A5/6/Adrgbh+AevBJfxGuwEufiXszFfbgE9+NqfBkfwVewFF+VeqfGS/pAxXNSPro4z0Pkekrus63Fy/B+vAKLcQo+gDPwQYzHdViE6/FVfAj/hg+jkl8l2Ao3YG/ciNfgIxiOj+J43Iwp+BguwFJcjo/jPfgEbsEtWIFb8SA+jYdxG36Fz+IZ3I5aPRL2UN31yJ2MNwjvwmF4NybickzGFZiN9+ACXIkP4CqU+7rS1yjHSo/7umo/JB0xHINwLA7CcRiK1+JUjEQ7TsQFOAnzMQpX4mQsxqn4ME7DJ3Cm1n8OKudv8RiLiZiPSbgPZ+MBTMEmSrsunIapmIVpOA/TMR8z8Bm04x7Mwip04EHMwbdxLh7Fefg=
*/