// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP
#define BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

template<class CT>
struct bounds
{
  static CT lowest  () { return boost::numeric::bounds<CT>::lowest(); }
  static CT highest () { return boost::numeric::bounds<CT>::highest(); }
};

template <typename Box>
bool is_inverse_spheroidal_coordinates(Box const& box)
{
    typedef typename point_type<Box>::type point_type;
    typedef typename coordinate_type<point_type>::type bound_type;

    bound_type high = bounds<bound_type>::highest();
    bound_type low = bounds<bound_type>::lowest();

    return (geometry::get<0, 0>(box) == high) &&
           (geometry::get<0, 1>(box) == high) &&
           (geometry::get<1, 0>(box) == low) &&
           (geometry::get<1, 1>(box) == low);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP

/* is_inverse_spheroidal_coordinates.hpp
jCNjyvEJvZH6LDywMtjp8IikAVGKGPXxq5kDTsKjrFPINnmv7kls2m0sn/2ufYagX8/vce+9qr1lOp9wiFUzCf38+gVizKVnJKSSOqnOrsWOPeefTgO7gI5HJHA4ZqQey/VRs6zo6trTGr6qI/TxCXfjSXTdB3Ijqys8WYSA3IkYVnNsURQdo/r49Zll1EFJfnqysDsd3XRlcQK1rjLY4P1ihTmHwlWebu3VbDMvkcmbyscdWlD7s42DLt/Fk41D0UnM55fwaYY7+pviTeljfQppv8IT5YvmTnuix3UNRnZ9f7h7Aoxfblb7cLowJ9dZbF/4pPMAWMYsVhH8fAqKyPfznxP40goVgBrcnTtfnHx0Q6/S9X+m4mVHiMRHFOdmvlD8Xbhz2DSx/mMsnON/CXeG/9pP5//7+z+WkDkYaP9dto95PeA/nn3wXRuJOR1IYas002861VkJ1SHsNiUTCk9kWWxfvJ48Pdc872TVdURmDcPEWuaaGkhyq6uHKGFl04rYMn9SUvjjEkKst/KFJkD9BwUhiKM6oejdm1823TdL840fWBPGGj4lOh90H67dwHIPnxFi7cZPxzupvoh0Co7ZXy4UmrP6xcIZh9YADKmf76PiLuyTFYqdnCHZUIpk37czec3FCrHzzK1T1kiN/sJ/Efsu/v3Vd9rv+FvCfBu5KcqzdyqwWxXZEZk7ORBz8VdhXuEr5jT+yrzj
*/