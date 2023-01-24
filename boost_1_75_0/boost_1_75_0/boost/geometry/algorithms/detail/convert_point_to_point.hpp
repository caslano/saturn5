// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_POINT_TO_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_POINT_TO_POINT_HPP

// Note: extracted from "convert.hpp" to avoid circular references convert/append

#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace conversion
{


template <typename Source, typename Destination, std::size_t Dimension, std::size_t DimensionCount>
struct point_to_point
{
    static inline void apply(Source const& source, Destination& destination)
    {
        typedef typename coordinate_type<Destination>::type coordinate_type;

        set<Dimension>(destination, boost::numeric_cast<coordinate_type>(get<Dimension>(source)));
        point_to_point<Source, Destination, Dimension + 1, DimensionCount>::apply(source, destination);
    }
};

template <typename Source, typename Destination, std::size_t DimensionCount>
struct point_to_point<Source, Destination, DimensionCount, DimensionCount>
{
    static inline void apply(Source const& , Destination& )
    {}
};


template <typename Source, typename Destination>
inline void convert_point_to_point(Source const& source, Destination& destination)
{
    point_to_point<Source, Destination, 0, dimension<Destination>::value>::apply(source, destination);
}



}} // namespace detail::conversion
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_POINT_TO_POINT_HPP

/* convert_point_to_point.hpp
WR+YZwbqfY7PM/2kOMv3ByIBaezJpH1da4H+FyLGa0tBZKWJn1960lI33JWdjU6k+xfjadI2UiLXKwVyBcnDEZTAPilGdLnA1L1MRnpalUP3sgrK+QXFON4ExE5IL59M2sfV5ScqCSHS0ycZw3L8ZHLstGQnm5LJTkalG3diPFuaT6rg+LoAe+hrU/s/n7Sv/6dg/T8l1v9TzvX/TekG9zroXq9WcUqsC/2/FUITIPMTVpaiTrWVRcVfZySb1mySMk9awCRvltbMXLN6Q121pBxs1ynbWeIQZE6Luh6zymeyiHelQdTSgvkGMvlnNuob93aJJfa5Wd/050MoCKnw+WQ/N9ssSZtmsC2E9XPkeecK/mkP71tkhjxS2qBcwVINfMcU7tqvBFKeQeY8b2vvhZD5+fNC/vG8s71PYbkXxotRsWjzbvA6nn1ejNUXgfgHpF6/T8pJ7a5OYi2eYa25An2U6xC/sX0WjU2Srea9RcZLEblM+Zt8QS3WPtMb1YBcKblhjS2HfYW6PY1m8VdgnaXyP4b/0dvE/+Dxf35vyv+AeAjS1t8n9azdIqByPevPf+88CU+XvKsxbAL5Skwtl2kotCp1GrB2I9VYapyO139vxh8fHEKXIfMPWiLMmg9+7xwrHxB1KZmL4VNbUIHkZzwOw7O2cF/8LwCfMxAuUyF5tPPZFMKYXj6jF8kHFw+95NKLThmgQp/JCp2k
*/