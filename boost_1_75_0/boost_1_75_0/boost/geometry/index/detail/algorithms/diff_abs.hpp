// Boost.Geometry Index
//
// Abs of difference
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename T>
inline T diff_abs_dispatch(T const& v1, T const& v2, boost::mpl::bool_<true> const& /*is_integral*/)
{
    return v1 < v2 ? v2 - v1 : v1 - v2;
}

template <typename T>
inline T diff_abs_dispatch(T const& v1, T const& v2, boost::mpl::bool_<false> const& /*is_integral*/)
{
    return ::fabs(v1 - v2);
}

template <typename T>
inline T diff_abs(T const& v1, T const& v2)
{
    typedef boost::mpl::bool_<
        boost::is_integral<T>::value
    > is_integral;
    return diff_abs_dispatch(v1, v2, is_integral());
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP

/* diff_abs.hpp
NAMNnWTK066y7Nl75xV3UetJaq+/HqnhZjXVc1l97IXenqJwMvvqVXau6cdZc7aTMtE+4qVZfwZd4haNia0ihzvM98TqXg9/rJAfk38XwY9i5IZ43/R5G+DfugO1hviBXJmnmuQI3BNEzFnbJCJ3dEyS+eXVrjifJfxqWXDYzLFB0OrhOBGPz+7lz04U7w8w463NM2TS5xd4WXvLbSNLRoSTKfAvLvKwtDG4fji120r2n/jlcY5VZiRZ9jaR4kYSR1zMGnm5ZtOOV7ChETebIS0dV26Kn2Xkv/uLnCdqx9Z9s+TRMOP8pKfBx1sb2G8WYJS+dSidd+njLAYf/2VqPTltfgR3R16YC9n6nrTN/Xa9ivWT9Z/kETnSL+FCis456tNoVuV8sfOtk+78S/am5n2V2o2cb9lTij7CU1uOa88fEKsKr0TSY3fq2g5EUA7pU65GYe+Yck9cUDrMkcw9cWsjDRdteyUn9bgPf9s2twyP0PwmcUH6QqXHIss4pC8k1KKKoE7SJToE1GXsVVyd+mhtz9G/Sd1/H13qrVJkAmUPtf1V4d75/WgyVoyyBQ8xNw9rT6S3HTPatker2x0NbDWPUqKe6NnmXxJcjEb3ioYrOJKTWj6M1VGW1MOMztjzvdvkvPsC/P9VSbCm7OF0qoTkQnrLOa1laRmaO7LsfK3p5+mnhtxzJUHOtJCVbq+40eGfiIr9eJrjdan+
*/