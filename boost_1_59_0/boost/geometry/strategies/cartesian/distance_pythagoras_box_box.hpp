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
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
*/