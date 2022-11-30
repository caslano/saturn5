// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_HPP


#include <boost/geometry/core/access.hpp>

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

template <size_t I, typename T>
struct compute_pythagoras
{
    template <typename Point1, typename Point2>
    static inline T apply(Point1 const& p1, Point2 const& p2)
    {
        T const c1 = boost::numeric_cast<T>(get<I-1>(p1));
        T const c2 = boost::numeric_cast<T>(get<I-1>(p2));
        T const d = c1 - c2;
        return d * d + compute_pythagoras<I-1, T>::apply(p1, p2);
    }
};

template <typename T>
struct compute_pythagoras<0, T>
{
    template <typename Point1, typename Point2>
    static inline T apply(Point1 const&, Point2 const&)
    {
        return boost::numeric_cast<T>(0);
    }
};

}
#endif // DOXYGEN_NO_DETAIL


namespace comparable
{

/*!
\brief Strategy to calculate comparable distance between two points
\ingroup strategies
\tparam Point1 \tparam_first_point
\tparam Point2 \tparam_second_point
\tparam CalculationType \tparam_calculation
*/
template <typename CalculationType = void>
class pythagoras
{
public :

    template <typename Point1, typename Point2>
    struct calculation_type
        : util::calculation_type::geometric::binary
          <
              Point1,
              Point2,
              CalculationType,
              double,
              double
          >
    {};

    template <typename Point1, typename Point2>
    static inline typename calculation_type<Point1, Point2>::type
    apply(Point1 const& p1, Point2 const& p2)
    {
        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point1>) );
        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

        // Calculate distance using Pythagoras
        // (Leave comment above for Doxygen)

        assert_dimension_equal<Point1, Point2>();

        return detail::compute_pythagoras
            <
                dimension<Point1>::value,
                typename calculation_type<Point1, Point2>::type
            >::apply(p1, p2);
    }
};

} // namespace comparable


/*!
\brief Strategy to calculate the distance between two points
\ingroup strategies
\tparam CalculationType \tparam_calculation

\qbk{
[heading Notes]
[note Can be used for points with two\, three or more dimensions]
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}

*/
template
<
    typename CalculationType = void
>
class pythagoras
{
public :

    template <typename P1, typename P2>
    struct calculation_type
        : util::calculation_type::geometric::binary
          <
              P1,
              P2,
              CalculationType,
              double,
              double // promote integer to double
          >
    {};

    /*!
    \brief applies the distance calculation using pythagoras
    \return the calculated distance (including taking the square root)
    \param p1 first point
    \param p2 second point
    */
    template <typename P1, typename P2>
    static inline typename calculation_type<P1, P2>::type
    apply(P1 const& p1, P2 const& p2)
    {
        // The cast is necessary for MSVC which considers sqrt __int64 as an ambiguous call
        return math::sqrt
            (
                 boost::numeric_cast<typename calculation_type<P1, P2>::type>
                    (
                        comparable::pythagoras<CalculationType>::apply(p1, p2)
                    )
            );
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType>
struct tag<pythagoras<CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename CalculationType, typename P1, typename P2>
struct return_type<distance::pythagoras<CalculationType>, P1, P2>
    : pythagoras<CalculationType>::template calculation_type<P1, P2>
{};


template <typename CalculationType>
struct comparable_type<pythagoras<CalculationType> >
{
    typedef comparable::pythagoras<CalculationType> type;
};


template <typename CalculationType>
struct get_comparable<pythagoras<CalculationType> >
{
    typedef comparable::pythagoras<CalculationType> comparable_type;
public :
    static inline comparable_type apply(pythagoras<CalculationType> const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Point1, typename Point2>
struct result_from_distance<pythagoras<CalculationType>, Point1, Point2>
{
private :
    typedef typename return_type<pythagoras<CalculationType>, Point1, Point2>::type return_type;
public :
    template <typename T>
    static inline return_type apply(pythagoras<CalculationType> const& , T const& value)
    {
        return return_type(value);
    }
};


// Specializations for comparable::pythagoras
template <typename CalculationType>
struct tag<comparable::pythagoras<CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename CalculationType, typename P1, typename P2>
struct return_type<comparable::pythagoras<CalculationType>, P1, P2>
    : comparable::pythagoras<CalculationType>::template calculation_type<P1, P2>
{};




template <typename CalculationType>
struct comparable_type<comparable::pythagoras<CalculationType> >
{
    typedef comparable::pythagoras<CalculationType> type;
};


template <typename CalculationType>
struct get_comparable<comparable::pythagoras<CalculationType> >
{
    typedef comparable::pythagoras<CalculationType> comparable_type;
public :
    static inline comparable_type apply(comparable::pythagoras<CalculationType> const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Point1, typename Point2>
struct result_from_distance<comparable::pythagoras<CalculationType>, Point1, Point2>
{
private :
    typedef typename return_type<comparable::pythagoras<CalculationType>, Point1, Point2>::type return_type;
public :
    template <typename T>
    static inline return_type apply(comparable::pythagoras<CalculationType> const& , T const& value)
    {
        return_type const v = value;
        return v * v;
    }
};


template <typename Point1, typename Point2>
struct default_strategy
    <
        point_tag, point_tag, Point1, Point2, cartesian_tag, cartesian_tag
    >
{
    typedef pythagoras<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_HPP

/* distance_pythagoras.hpp
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
*/