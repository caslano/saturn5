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

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_BOX_BOX_HPP


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

template <std::size_t I>
struct compute_pythagoras_box_box
{
    template <typename Box1, typename Box2, typename T>
    static inline void apply(Box1 const& box1, Box2 const& box2, T& result)
    {
        T const b1_min_coord =
            boost::numeric_cast<T>(geometry::get<min_corner, I-1>(box1));
        T const b1_max_coord =
            boost::numeric_cast<T>(geometry::get<max_corner, I-1>(box1));

        T const b2_min_coord =
            boost::numeric_cast<T>(geometry::get<min_corner, I-1>(box2));
        T const b2_max_coord =
            boost::numeric_cast<T>(geometry::get<max_corner, I-1>(box2));

        if ( b1_max_coord < b2_min_coord )
        {
            T diff = b2_min_coord - b1_max_coord;
            result += diff * diff;
        }
        if ( b1_min_coord > b2_max_coord )
        {
            T diff = b1_min_coord - b2_max_coord;
            result += diff * diff;
        }

        compute_pythagoras_box_box<I-1>::apply(box1, box2, result);
    }
};

template <>
struct compute_pythagoras_box_box<0>
{
    template <typename Box1, typename Box2, typename T>
    static inline void apply(Box1 const&, Box2 const&, T&)
    {
    }
};

}
#endif // DOXYGEN_NO_DETAIL


namespace comparable
{

/*!
\brief Strategy to calculate comparable distance between two boxes
\ingroup strategies
\tparam Box1 \tparam_first_box
\tparam Box2 \tparam_second_box
\tparam CalculationType \tparam_calculation
*/
template <typename CalculationType = void>
class pythagoras_box_box
{
public :

    template <typename Box1, typename Box2>
    struct calculation_type
    {
        typedef typename util::calculation_type::geometric::binary
            <
                Box1,
                Box2,
                CalculationType
            >::type type;
    };

    template <typename Box1, typename Box2>
    static inline typename calculation_type<Box1, Box2>::type
    apply(Box1 const& box1, Box2 const& box2)
    {
        BOOST_CONCEPT_ASSERT
            ( (concepts::ConstPoint<typename point_type<Box1>::type>) );
        BOOST_CONCEPT_ASSERT
            ( (concepts::ConstPoint<typename point_type<Box2>::type>) );

        // Calculate distance using Pythagoras
        // (Leave comment above for Doxygen)

        assert_dimension_equal<Box1, Box2>();

        typename calculation_type<Box1, Box2>::type result(0);
        
        detail::compute_pythagoras_box_box
            <
                dimension<Box1>::value
            >::apply(box1, box2, result);

        return result;
    }
};

} // namespace comparable


/*!
\brief Strategy to calculate the distance between two boxes
\ingroup strategies
\tparam CalculationType \tparam_calculation

\qbk{
[heading Notes]
[note Can be used for boxes with two\, three or more dimensions]
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}

*/
template
<
    typename CalculationType = void
>
class pythagoras_box_box
{
public :

    template <typename Box1, typename Box2>
    struct calculation_type
        : util::calculation_type::geometric::binary
          <
              Box1,
              Box2,
              CalculationType,
              double,
              double // promote integer to double
          >
    {};

    /*!
    \brief applies the distance calculation using pythagoras_box_box
    \return the calculated distance (including taking the square root)
    \param box1 first box
    \param box2 second box
    */
    template <typename Box1, typename Box2>
    static inline typename calculation_type<Box1, Box2>::type
    apply(Box1 const& box1, Box2 const& box2)
    {
        // The cast is necessary for MSVC which considers sqrt __int64 as an ambiguous call
        return math::sqrt
            (
                 boost::numeric_cast<typename calculation_type
                     <
                         Box1, Box2
                     >::type>
                    (
                        comparable::pythagoras_box_box
                            <
                                CalculationType
                            >::apply(box1, box2)
                    )
            );
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType>
struct tag<pythagoras_box_box<CalculationType> >
{
    typedef strategy_tag_distance_box_box type;
};


template <typename CalculationType, typename Box1, typename Box2>
struct return_type<distance::pythagoras_box_box<CalculationType>, Box1, Box2>
    : pythagoras_box_box<CalculationType>::template calculation_type<Box1, Box2>
{};


template <typename CalculationType>
struct comparable_type<pythagoras_box_box<CalculationType> >
{
    typedef comparable::pythagoras_box_box<CalculationType> type;
};


template <typename CalculationType>
struct get_comparable<pythagoras_box_box<CalculationType> >
{
    typedef comparable::pythagoras_box_box<CalculationType> comparable_type;
public :
    static inline comparable_type
    apply(pythagoras_box_box<CalculationType> const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Box1, typename Box2>
struct result_from_distance<pythagoras_box_box<CalculationType>, Box1, Box2>
{
private:
    typedef typename return_type
        <
            pythagoras_box_box<CalculationType>, Box1, Box2
        >::type return_type;
public:
    template <typename T>
    static inline return_type
    apply(pythagoras_box_box<CalculationType> const& , T const& value)
    {
        return return_type(value);
    }
};


// Specializations for comparable::pythagoras_box_box
template <typename CalculationType>
struct tag<comparable::pythagoras_box_box<CalculationType> >
{
    typedef strategy_tag_distance_box_box type;
};


template <typename CalculationType, typename Box1, typename Box2>
struct return_type<comparable::pythagoras_box_box<CalculationType>, Box1, Box2>
    : comparable::pythagoras_box_box
        <
            CalculationType
        >::template calculation_type<Box1, Box2>
{};




template <typename CalculationType>
struct comparable_type<comparable::pythagoras_box_box<CalculationType> >
{
    typedef comparable::pythagoras_box_box<CalculationType> type;
};


template <typename CalculationType>
struct get_comparable<comparable::pythagoras_box_box<CalculationType> >
{
    typedef comparable::pythagoras_box_box<CalculationType> comparable_type;
public :
    static inline comparable_type apply(comparable_type const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Box1, typename Box2>
struct result_from_distance
    <
        comparable::pythagoras_box_box<CalculationType>, Box1, Box2
    >
{
private :
    typedef typename return_type
        <
            comparable::pythagoras_box_box<CalculationType>, Box1, Box2
        >::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(comparable::pythagoras_box_box<CalculationType> const&,
          T const& value)
    {
        return_type const v = value;
        return v * v;
    }
};


template <typename BoxPoint1, typename BoxPoint2>
struct default_strategy
    <
        box_tag, box_tag, BoxPoint1, BoxPoint2, cartesian_tag, cartesian_tag
    >
{
    typedef pythagoras_box_box<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_BOX_BOX_HPP

/* distance_pythagoras_box_box.hpp
OBZfwAn4F9k/X5Ttske2x0u4DF/G9fgKbsK9KO1j8l5jjlmH9rHXmK827kM17+so5S3vJyYth/JeIsfvUuyAy3A2LseleANejytwH65E9dzhRuyGN2FfXIXj8WbMwdV4L96Kf8Db8XG8A/+Iv8Nn8U58Hteh97jKMtsxA4+rnjX0/tEbjf61aPRTR1W+/XAO9sciHIgb8Qo0t+cJif8Hh+35dhV9HL2LndR+hmPwA5yIhzFHlSnegh/h7XgUt6jjEg+p4xI/U8clfqWOR3l+9qW402W+U5dtJNulLv9+RPJxivka4GmMwDPYGs/iZJV3/Ks6PvEd/BXV+rhUOxvxBWE0VsJRGIxjsDLOwlC8FqvicqyON2MNvAVr4nqshRuxDt6HdS3Pe+R9uLwnN/B5T59K+rjojx1xAPZQ2wP74SAchdE4AQdjEQ7BxTgUl2IcPosj5LgeiWq9x+AJHIdBpDke62ASNsaJ2BknYR9MxpE4GZNwKk7FaajW/0rcgtPx95iCT2MqPodpqI6fGfgGpuNJdKN63pKJDTELjeO1svmeW6Ptg/LR+3MrpqvfsZr6uPsU26v9RfoLH0dVPp9hgtpv5LnpVzgPv8EleAJX47f4JJ6UfuLf4X48hafwNIYEsf9gPfwe2+BZVOXyI47Gn3Ac/oyT8BfMwXNYiL/iGqOzvt4vglAd35XwJQzB97AyHsFL8DiG4gmsht9jDTyHNbFqJaLDzhiGfTAcY7E2xmMdHIuNVbrYFDfhZbgTm6n0sTl+g63wFLbGn7GNSg/bY7C6TsJq2BFrYBesjV2xMUZiU+yBzbEntsde2BGjMBL7YhT2w344EAfhFTgcB+EIHKLyjyMxD+OxGEfjy5iAZ3EM/oiJKt84VuUrhP0bG+F4jMAJ2BonYzROUenhVIzHaZiAV+JknI4ZmII3YSo+gWn4NM7APZiu8oMZuBfd+DrOwjcxE9/Cq/AAzsajmIuN1Vh0bIse7IJzsAfm42AswHFYhFfiXMzCebgG5+ODuEBtT1yI+3CRSg8X40G8Gg/jNfgRFqt84HXoqsL5C0PxepU+3oD9cQUOxBsxFm/C4XgzjsE1OAVvxyxci1fjHbgKf4er8U58GNepcsP1+DHejT/gBqSOdd2Dl+AmvBQ342V477/Yuxe4Kqo8gOOgaKz5AF+omZLiKx+BWqJZoaJRoqKSklmAcBHkdRcuiqaJhkVpSoZGaRuaGaUVmRUqGpoVlRaWbVZmVpZk2pprG7u1tb+585+5M/cOAbXvT3z695VhHmfOnDnzOnMGe+BGDMJHMBgfxYn4GMZiKabiE5iLW/Be3IoP4VP4BD6Nh7AMT+Ez2NSX+3bYBp9Ff3wO2+EL2AfLsR/uwP64E0OxAifjbpyJe3Et7sPN+BI+h/vxPXwZP8VX8AS+it/gQazFN7Ep9d9b6IdvY098B/vgH7E/vofn1Pc+pE9hliXHxU7KeY0cFzvLe1BdcShejFOxG87AQLThJbgYe+Aa7InrMQg3Yy/cjb1xP/bBauyLJ7Effo2X4lnsj9/hQPRX2hNgJ7wMr8dgfBBD8AUcjBU4BPfgUDynzl/6BGYfluNmD3V9nD+rlef3eB/2xyK8CtfgOFyLE/EBvBnX4+34ByzAElyDG/B+fAQfxk34OG7GA/gYHsZSrMXH8e/4JLYnLU9hKJbhHHwWV+J2vA+fxzVYjptwB1bhTnwdd+NJ3CPXuS9iX6zES3EvDsB9OBT343h8GSfhK3L9SdrU/nmxRspDV+d7pOrPWSkPtTga/4oz8G+Yhd/jI/gDvoB/xx34I+7Cn/BV9FKO6wr4R2yKx7EZ/oTN8SLluIY90BdD0A+vwLaYjO0=
*/