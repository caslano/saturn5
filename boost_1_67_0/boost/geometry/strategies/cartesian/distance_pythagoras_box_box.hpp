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