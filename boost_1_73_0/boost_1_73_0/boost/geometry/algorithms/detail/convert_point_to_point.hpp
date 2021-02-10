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
CNPjhfwEZnhARytak/Q5Pj/rUocIM4UBp8UZMBDyNm5F2v54eKyH9ltDo8/yAf4NVGHN+NJE2seMHQuwyEDyaUu+xIzmGUcdpWpjHKcbEuEDI+J4wA6RYx9x6dx1En1qer5t9Gnb83fTEVwSDgbjilMg/z28E5r25uSsKcmceZhWmxo7x8ElzYpZCocbjZt6Nj3D8K5FR8WulSyPkKSDzZqA1vT5JY2V0/3GRwEeXQlBRryhemmc8ioX+OBXDLY1BxQWwmvlmVYNenGhlAcAFKjjRiFoJevds52daJxEeZyzX6Jel5phol+LLqVvs5S2CU1gRvX8QP32hYuHIML4mLyv7Zcsbp53e4Oj8zNhqHtr2h3sI1oHjftqGhf3GTwlRt/Fkg3g4XBGs0eA2OKByXCQzw9w+6P5tJlrvhL5PSRe0kI/aqEMjkhPJD+M5qkQ4Xl1SEfWS47sfO9pBxS7Wa/GRSOl24nXLlyWdlalcFW2mBE8KEpjILCQtco22jqBed5S36hdVyypHUGS3NPOyT0uFXbxZm5Ctoiz06Bafa83WXYdzeo3iYkTZdR9hyQGUUL4Xw7lQ8x1fTl9GoLfcq1AgAdfe6fwB6KxYKt+kL0qofhfuRk8EGVLc19BGGL9wMVuev/Kq2D3soZd
*/