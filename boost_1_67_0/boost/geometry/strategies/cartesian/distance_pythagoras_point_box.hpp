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
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
*/