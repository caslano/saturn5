// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct isinf
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return boost::math::isinf(t);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_infinite_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::isinf,
            boost::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP

/* has_infinite_coordinate.hpp
YBba7TQFkPiXWOqx6TXXtNzBkRYy0o5Bsw+RFLpAE+A1ZWbclaKJWFmhwA82J25vFMv/SCvH8hOkBdWzZ79sBSirL9vfNV/p0nZGlslGU3uLzy4B+a5QS8W2ilRljt3ykpMFM5JPzzDVO8/9xgaxNqVN+p/Ra+qu7EmUrI7CoR5UKAPzveMl1aGIlU3yZV5FyyiUGADO7ypKCVgPw6yzjcAyQM14Z5qHxoGzOSfgcZ0Nqy0RD27vVB8D4lN93yC19thOaJvjhLYqbEE1lXy5x8y+ZKQM6K3MvIbpolOqiJwFT3fJ2YslFg2yYnbDHfWlChPYNlfk6J+Puq9sat8umekyrTvfxAz1isptMNBYhq3z3YqbdpfsnEglHtzaTnyRuFjHNbLLBik03Ws4oukBkIfzT2gmYIrS8pIrKBBbk+nnWB7AMhMTOcLnDPsmCMNtJkOT6SrBHZTpO7RfouOWCwnRhbZOgHLsidA4pcrbv6cLihe/bXFlq5ii5hRB3RQIIv2xhKR67fgwOMx848ZBOITWFYkeWhAbt9V0JnUAtcoz5U+4W2QacIm6vR+71jFDtbDQMGzbGElskVIHDJtjUm2SXk8kMMnRAwIVMENBM7Yt429c1HAVXYerKWEJm6wNDQqlmI2Mg4OzaU63
*/