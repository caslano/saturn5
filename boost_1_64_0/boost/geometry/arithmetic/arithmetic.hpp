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
VO2k9yVrKxDrHAhvLIs9VmvORBJ7hAzGC/YSFDYtCnMnQQ4EscJC52yWQr/11gEplNdsHNXkA0ElZE6IfOGICpukwj7HsKOz5fmyUGw+tDVfNKq+gLPpuNgqr5s3mqMtP9seet6pdKr82iHCxu8q80auHg57V9/XvOQGKTBLrXlF3GMSPGvrqbaivM4wle8W7sOV4ZEPrjQ++Ps/+utqf9yWkfl6a2e6PTZeIlB81TgEz6NyAh2DAWcfPquwq40vhyhC1yPo+dendFN56rTf4nIfDBPcx2j1t0r7An8gm4t3tUNP42oKT/hd8OZ8PBSvwv1KKF5N35TRnvRP2xtae/R351eOsDHjuHJQ6VvfdDhEn5SFTfaqQ8HzWapoLLvH1UkCq/BN6mhQjaJDcSvlH7Pk+AC4JtIj+Uyl/M+j2F4m9BsHVCM2+Wr3Z3FB3IQVvw1enUsYLs18Omzc4VUHd6zdZrXS5YjlS1CLnMOwTKqZU9la3oijGOZeE3NwW03SOoo1Wy7sXtqqZutTsIg0V02RaZm605aMTn88Q3HidMhpFCg5jTUe5QC1boWHp7egZNlzHDN5EtvmNXiTg1UTQgBsGbxCJmF7QR2upNG4ia77KWJtv1/LlLCNdc6RvfAcHnSbF8o6keHsS3bHF3zBwR1lD8kwHBkw1w+cke4m3d4Tj/CkOZ9rcPCnfL7pqx2OSnVyYAwYatOFtw8QWE6PfgLZ9N6SNrMN7iurjHXKbC13l7CL5FZMxs+G1R5jjdvCDR4oQqMXuk3HWGRW9IzYSlmxfYu+a6VcIiknWSnvl5R9o98AwosUwr+NH16g8YdCS/6GXyvAi7BvNs+6Tu4CGMu/6wLxPwZd2kXt5ZSFafi9Sn3kdmWW9zVmiCODRpCTvA4NVkt7AbLUJMXqU12R9q6X2ieorSdoUORHYitaVAuf0GpFV2Gv02bv/6r2CiE04KRju72pPmSdmnjqsrzeIGW8+hAy74VD0DY2KoZYAptrkW7Hb0NGbasST7FMLk5uhUfEFJnfztZw4/Jh/KY85rgAN9yz9qD5k+nciVZXInT3txn6NEOf/3zKRQ7r3qt871IUuwXVt5rHoXbBd+U55wQRlfa9neyzfF/dLiWPwWh/bLmp5FJ+hzRq/P8W6cToB08VePBaxj+arKHBg0bdLUgmmLtZpXdg7AB5jGc645CkuhaRIU6Gyj6xgLOf4BRM59h4S3V6FsIxNo4gTAkFcWwwT0owRt64xz7ksMZGFsrmiMDAMJ2LU4kVQ6/dgeiuzmSHx5K9uYu0J5Z1a9QRp5FHnE1HiKGB0fNOlMfxLfo9ImmaESJgeGqO2dvDeyTXoOg5Ohf8KyCTPW3chGg9smP1Ypq1/ToEicMbEgbaouy9szkfWcvmwN8xm3ORHApz1O6x/Uxkxdsk9XaKevuKestzqumsbh+YvuV3CN/mytj8oDM6mcYU9ZAMWRNMufBTcOo8zIH30Vzpg5pvOXF9Pj19dmKqLnKOvkWUlITHTbBRypXvVg83pues8KsW6X1p6be0x9jc1L60j7n8c7IvvUYjJ3KJRpmRr6tperXHwa2GoOngltItcNwROQfZ00veeZsq+UqUzEopO/pp8xqUbO94ubNdpgV1PpAy/+Dv3ewLJtbJZg9iCSvpFEssYO3DvShko9tjECHA0rsRFi5r1ufDEIdpOmXXNbThW1QbvAjBfRi8RQXnNCQYXFSzsS9CYZ4CeSn6ge3aNS7bJ9SK23jkDmwwmv45Q39d4cEeVsO0fK2CiWLde8XGTTuNJvZXfiVmXSN3oCu1HPez0L71rwLsXGLRVNwaHyzdWmVssmDej3Q0BSIwty+U2+rjSOs=
*/