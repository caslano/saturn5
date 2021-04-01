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
hMCI+2r6hiXKjNrzCj0Hg8/Esg3A61En8veWApqjV/7rYa8zRlEPq9T11YddUDKqv0KtR+UCCFebKc5Sz96oDMfT4EmW/Shzx49hvnSWM1E2JpiG0vEvT/ZB5YW9qcAHAKlD6dBZk6Hl0VvDZmwIadtGvAI4P1DhfWy4qn7tZrdBTDVLipUIx7yWJjh2lUmV3s3ye1fcP/g9M1gpg9a4hxcPv3C2AfNz4S2Tr4/yfJ+BfgqLjX2iaLhzMGV/LjTM/6cRcHxdDBIC0aoLq4yPOoyIwwGtgD3DeHG2wTzcYvo7OmEx/a0zQfwEPNurFRAN/Jgxim5uoaFz86ysXJj2jq0p+yLo9UNmbFNe+AN79H5zmGr7fAf8DZDpoucYp5j10VTCz7Y7uALy5pR8ShU69wQ5G6tsCALH4e1Ta391D4D7NOvq9oQlA5W1fRvMKC6urA1m7mqS6iUJsSINbwm7KYfT5t3fZTh+ct0ELIDxsnJRELuxrxNx4RglxD09sN77wlyKyO7MwzOBEv6Clrmv+WRThbsuUmUoprJpYyR+M6vo95pYrmq9CDavNg==
*/