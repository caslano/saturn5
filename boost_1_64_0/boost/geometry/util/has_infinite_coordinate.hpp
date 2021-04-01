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
+ITt1ILH1IPiXRPKNeVOvKUzJBxn493eEeRYHANh9aScaQgOsqg4ei8g/O5nF7QSU4SRkNne64AxCnqtQouPkjh4qKN/t4AYQxiE36J3ogfUSZmMjsrSOwu90SjoV0wo/YIyApHYK81ZtrEFWBXbHg3xkDBQS0IYAAcmgbmBfdMzQY6HDJ4dJb8FdfyrMFPxiLtgSQUl1ebdNA9XA6wveDFP4+qWUQ+zAJYMeZJu7HYKUK5puFoMPueUqKUuQJ/8bHpZEa98xel3yVkevXv9wcRnq3h45xUxAoBlJNEAwT8ofWjX2xENYJwPZelKOcg9kiZF/+u4BPGV21EadSJvKO28rddWrL7K9F58ZqGPsr/ZRUgFlEScPVBSVmzvM+sT4mifbnTdOQI4KBhSuQoNmF+MP8mK0SkFDsoXrLybRYrLhpGxkxo7MmtloHKEIh7xkPNgOIrnx+GFiSYVFImqbSB2ziaZPQ5lQuqUsWQI7esLYIoWgXBtqIrT4GI1Z0N12Q4DdRvNOf6bepewl6BHnPz033EAunKNaoQmW5RVx7z7EyRpggtr+ttwqg==
*/