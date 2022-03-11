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