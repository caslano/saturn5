// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGIES_COMPARE_HPP
#define BOOST_GEOMETRY_STRATEGIES_COMPARE_HPP


#include <cstddef>
#include <functional>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/min.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace compare
{


struct less
{
    template <typename T1, typename T2>
    static inline bool apply(T1 const& l, T2 const& r)
    {
        return l < r;
    }
};

struct greater
{
    template <typename T1, typename T2>
    static inline bool apply(T1 const& l, T2 const& r)
    {
        return l > r;
    }
};

struct equal_to
{
    template <typename T1, typename T2>
    static inline bool apply(T1 const& , T2 const& )
    {
        return false;
    }
};


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template
<
    typename ComparePolicy,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct compare_loop
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        typename geometry::coordinate_type<Point1>::type const&
            cleft = geometry::get<Dimension>(left);
        typename geometry::coordinate_type<Point2>::type const&
            cright = geometry::get<Dimension>(right);

        if (math::equals(cleft, cright))
        {
            return compare_loop
                <
                    ComparePolicy,
                    Dimension + 1, DimensionCount
                >::apply(left, right);
        }
        else
        {
            return ComparePolicy::apply(cleft, cright);
        }
    }
};

template
<
    typename ComparePolicy,
    std::size_t DimensionCount
>
struct compare_loop<ComparePolicy, DimensionCount, DimensionCount>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& , Point2 const& )
    {
        // On coming here, points are equal.
        // Return false for less/greater.
        return false;
    }
};

template
<
    std::size_t DimensionCount
>
struct compare_loop<strategy::compare::equal_to, DimensionCount, DimensionCount>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& , Point2 const& )
    {
        // On coming here, points are equal.
        // Return true for equal_to.
        return true;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename ComparePolicy,
    int Dimension = -1
>
struct cartesian
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        return compare::detail::compare_loop
            <
                ComparePolicy, Dimension, Dimension + 1
            >::apply(left, right);
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
template
<
    typename ComparePolicy
>
struct cartesian<ComparePolicy, -1>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        return compare::detail::compare_loop
            <
                ComparePolicy,
                0,
                boost::mpl::min
                    <
                        geometry::dimension<Point1>,
                        geometry::dimension<Point2>
                    >::type::value
            >::apply(left, right);
    }
};
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{


template
<
    typename ComparePolicy,
    typename Point1,
    typename Point2 = Point1,
    int Dimension = -1,
    typename CSTag1 = typename cs_tag<Point1>::type,
    typename CSTag2 = typename cs_tag<Point2>::type
>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false,
            NOT_IMPLEMENTED_FOR_THESE_TYPES,
            (types<CSTag1, CSTag2>)
        );
};


template <typename ComparePolicy, typename Point1, typename Point2, int Dimension>
struct default_strategy<ComparePolicy, Point1, Point2, Dimension, cartesian_tag, cartesian_tag>
{
    typedef compare::cartesian<ComparePolicy, Dimension> type;
};


} // namespace services


}} // namespace strategy compare


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_COMPARE_HPP

/* compare.hpp
VP8SIHXreYYEmJhH7kRq02E3RtL+oAsVYmTac/0L4677F8adguIvjPv8T8dXrVSPNnDXSsKDU+eqGuU/K+6hllo+NM3tzxK1GgdJSGZiCS99sSG54nbCIskoWOKsq1T38vNuEISUsfW9lU805m9aM4Ju+Qy2YDSAidBll4gkAfVzIKFZw2MjGCL71LR519XJ9ONiSgXyKNQcjCFgbxL62NP/69DvUvQsgsY8O3ATGAN06LgUFmsc+4yUtrc7Q/S3oedHGKEbByBY2qvZOQQ+Pq78WuLZBke8BVUnPXL8GYj7of/jz4p7W+CD+b8r7j7/Q3EnkiKq1z5fIrEUPGeoxwIoVzTZ0Gw+SfFuYARK4WxgGYUKFFAJoXihaKDn9UtvpGzYUdB2hrgUYD1HkX7z7JxnW+2oPuNX9J3hxnO3V0KYlFjqKMyheyHaObd8m7xSfZOSyXeU52hu1O1vbCHyw2xXl1fccf44AGwAWQw69ipTLMCkXDsGGvJnxf0KzkGcBB6egDZ8b/djF86N/UrLRqKRlAuiFAwfBdiyv+SByrI4rrR+iQXRIvCYiAZImIt22ch4ua1Bqozgn2ni948dTXP14uTctZ81u8Ct2nMWwwLQ8p9sPnVkTbwsnhtyDguqhrGfQ9JjSpkerC5wSxISmYlsf1DvKyVaD6ekqA5t9v625LEunaAVzc6hFLJUByUsFn8YUmfcUt5BzaMQ
*/