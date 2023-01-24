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
3zGkzn9igVGRf1wuVNtutHtVUHYbiqpF25llaqHQ2DKNaiMb8EW10GPn4jpdDuEDGze58rn8+D48W7J64QQbLTj0z8e/PwcKDTYleWv1sENsX9CcbzCaf5jOqrxiddz+cCq7/7Cit6peumvyzfAb5ybhaa0qCoelUFzk8SN+ycL1yKznX9KeQJw8nUtNUmOnDGDobGn+GHCzRkFyiZCxz/ExLFS54G5TV4CEmKyYsMA3NX14p+jycwuaiUi6Yu2Mhz39Xo1kWLnDkV2Blkul4xbJO1HDhaHVoVNnlfnIvoaSIJPknDz+Oq9OLk0vWzUPZq//vRY/8zh9JqT4z8rQWUfTcvvsT/ndCZR0OoYq8pVOyV9euk9LpwaPx6RCjZ2+CEw/h8lkJ6dpOf6Dt+FPfl1x7c2GgewO/V3hwIf5zQYWN84Lq7+wbLg1/l6Rmtqg030uViBR1+Q+/oJ50TUxTVK1MZyV8DLRrCLeaVUjs604Ebtq38qrWncweG/+7b75ObXwhHTmuVNVHSKhlXJW4i4sdLwQ3buqcU1QOW+0N8Yn/H7zg1jVkmoBvDNiAvdVr313jvv0aA6Bj/l+Ggl8eGItaXoXvgOrFbwzn+I+vKzwvChFYMCrTCZ6sGx4m+g01/hyqv540mUOWEx/eize3SBcVSxNzN4n5WVtqTczUq34PHfsUELVw70XtymfLp5uFvCl6euDR8RHVgwM
*/