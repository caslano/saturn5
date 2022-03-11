// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP
#define BOOST_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP

#include <functional>

#include <boost/call_traits.hpp>
#include <boost/concept/requires.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/for_each_coordinate.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename Point>
struct param
{
    typedef typename boost::call_traits
        <
            typename coordinate_type<Point>::type
        >::param_type type;
};


template <typename Value, template <typename> class Function>
struct value_operation
{
    Value m_value;

    inline value_operation(Value const &value)
        : m_value(value)
    {}

    template <typename PointDst, std::size_t Index>
    inline void apply(PointDst& point_dst) const
    {
        set<Index>(point_dst,
               Function
                <
                    typename geometry::select_most_precise
                        <
                            Value,
                            typename geometry::coordinate_type<PointDst>::type
                        >::type
                >()(get<Index>(point_dst), m_value));
    }
};

template <typename PointSrc, template <typename> class Function>
struct point_operation
{
    PointSrc const& m_point_src;

    inline point_operation(PointSrc const& point)
        : m_point_src(point)
    {}

    template <typename PointDst, std::size_t Index>
    inline void apply(PointDst& point_dst) const
    {
        set<Index>(point_dst,
               Function
                <
                    typename geometry::select_most_precise
                        <
                            typename geometry::coordinate_type<PointSrc>::type,
                            typename geometry::coordinate_type<PointDst>::type
                        >::type
                >()(get<Index>(point_dst), get<Index>(m_point_src)));
    }
};


template <typename Value>
struct value_assignment
{
    Value m_value;

    inline value_assignment(Value const &value)
        : m_value(value)
    {}

    template <typename PointDst, std::size_t Index>
    inline void apply(PointDst& point_dst) const
    {
        set<Index>(point_dst, m_value);
    }
};

template <typename PointSrc>
struct point_assignment
{
    PointSrc const& m_point_src;

    inline point_assignment(PointSrc const& point)
        : m_point_src(point)
    {}

    template <typename PointDst, std::size_t Index>
    inline void apply(PointDst& point_dst) const
    {
        set<Index>(point_dst, get<Index>(m_point_src));
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

/*!
    \brief Adds the same value to each coordinate of a point
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to add
 */
template <typename Point>
inline void add_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    for_each_coordinate(p,
                        detail::value_operation
                            <
                                typename coordinate_type<Point>::type,
                                std::plus
                            >(value));
}

/*!
    \brief Adds a point to another
    \ingroup arithmetic
    \details The coordinates of the second point will be added to those of the first point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
 */
template <typename Point1, typename Point2>
inline void add_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_operation<Point2, std::plus>(p2));
}

/*!
    \brief Subtracts the same value to each coordinate of a point
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to subtract
 */
template <typename Point>
inline void subtract_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    for_each_coordinate(p,
                        detail::value_operation
                            <
                                typename coordinate_type<Point>::type,
                                std::minus
                            >(value));
}

/*!
    \brief Subtracts a point to another
    \ingroup arithmetic
    \details The coordinates of the second point will be subtracted to those of the first point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
 */
template <typename Point1, typename Point2>
inline void subtract_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_operation<Point2, std::minus>(p2));
}

/*!
    \brief Multiplies each coordinate of a point by the same value
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to multiply by
 */
template <typename Point>
inline void multiply_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    for_each_coordinate(p,
                        detail::value_operation
                            <
                                typename coordinate_type<Point>::type,
                                std::multiplies
                            >(value));
}

/*!
    \brief Multiplies a point by another
    \ingroup arithmetic
    \details The coordinates of the first point will be multiplied by those of the second point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
    \note This is *not* a dot, cross or wedge product. It is a mere field-by-field multiplication.
 */
template <typename Point1, typename Point2>
inline void multiply_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_operation<Point2, std::multiplies>(p2));
}

/*!
    \brief Divides each coordinate of the same point by a value
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to divide by
 */
template <typename Point>
inline void divide_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    for_each_coordinate(p,
                        detail::value_operation
                            <
                                typename coordinate_type<Point>::type,
                                std::divides
                            >(value));
}

/*!
    \brief Divides a point by another
    \ingroup arithmetic
    \details The coordinates of the first point will be divided by those of the second point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
 */
template <typename Point1, typename Point2>
inline void divide_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_operation<Point2, std::divides>(p2));
}

/*!
    \brief Assign each coordinate of a point the same value
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to assign
 */
template <typename Point>
inline void assign_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    for_each_coordinate(p,
                        detail::value_assignment
                            <
                                typename coordinate_type<Point>::type
                            >(value));
}

/*!
    \brief Assign a point with another
    \ingroup arithmetic
    \details The coordinates of the first point will be assigned those of the second point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
 */
template <typename Point1, typename Point2>
inline void assign_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_assignment<Point2>(p2));
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP

/* arithmetic.hpp
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
*/