// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_NORMALIZE_HPP
#define BOOST_GEOMETRY_ARITHMETIC_NORMALIZE_HPP


#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Point>
inline typename coordinate_type<Point>::type vec_length_sqr(Point const& pt)
{
    return dot_product(pt, pt);
}

template <typename Point>
inline typename coordinate_type<Point>::type vec_length(Point const& pt)
{
    // NOTE: hypot() could be used instead of sqrt()
    return math::sqrt(dot_product(pt, pt));
}

template <typename Point>
inline bool vec_normalize(Point & pt, typename coordinate_type<Point>::type & len)
{
    typedef typename coordinate_type<Point>::type coord_t;

    coord_t const c0 = 0;
    len = vec_length(pt);
    
    if (math::equals(len, c0))
    {
        return false;
    }

    divide_value(pt, len);
    return true;
}

template <typename Point>
inline bool vec_normalize(Point & pt)
{
    typedef typename coordinate_type<Point>::type coord_t;
    coord_t len;
    return vec_normalize(pt, len);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_NORMALIZE_HPP

/* normalize.hpp
g3vjc6fO8D7k0ppayv+6XXe1uF5XapWYS8j2I0LtwyTucj7rlQ52gJfF60aqmX2+QfJB0D42mGcM51nsGbLDicMOpznFq25j84UQ41WKcpZGYSxn8qLr8WP5jhH+ecnPV+ow5D8mY0BIlbRVlUpUoQrRHglVOuv7fu4ntPpnyZVP2ghyvgslkUaXYU6FC5oxyVa2YFvW4xIraDwG+rpwCViX5K74IrQGbJ5YvciK49HTXZviLa7KG6zStrIl2a3nMFnekA0Rh1o4QPyzPw4hm7tWXxAUKebVDs/e/KWJducdtYdqK+NDd9JSZchJJL8no676uCY0nrxxW2i+RntrQGdwa8KlmifbcriUCdN8fDDHQvEQ9otKcdTveCsN843K2zZbFA9Aoj3aa2e0V1ILr13RXsktvMxory4tvHZHe6W28Nof7dWjhZfFHuWVFuWVTaXK+FBqcjEfuIMrmJFo5g9fqs6F6oVZ7sKoc6GzB0tlFVkYz1VdtMZ86+aI8LhQJQVqSjhNuSQuE9rSlt1n8qUR4uGB5tuDJLGz8YqUdkiLuTUqMfMXaNJfQbbc12GOMT6zXQVW6nb1mNYm+L1LpG01uWruby8HvQt6QCyK1IlL3aWaFw2Uofldb9UD4gpLWhWEi2MZ3RNCsUJ8BR2Fbh/r2A1CHdckN07wdB/uWSSeFfT8I5f4F0RT4U1TVHjjFBXeKFmou417ozgXnibnQj4c3VGO5FzAgXHPcij6fTqdG6Kn1YYIjrPFUW2IaMFpMpz2LVUiR3Ihc0VyBxGWS9Ua9tEam1hcTzR3Dzt/6jWCYJlgQ1SebsXg+iJuVDlqK46up14LyuiBQWuUkKmihttcLBPOH1G95oEBktQuStM8PDrufyT+9Sq+rm/VqqpEC1/rhNtazdB/jmGhlfYXbnqRQT9phWbW+4RMC6/L2fTeWqtP1DmfxWFtVQdFs52BGnt1kppft/aXUptKqJRWS2HgiCuoNPBhmVBddjDYQr+d0Y5buI0Z3IOFt3CBLUHu4jbK1s4Yj4Ffn5dI2IUt92uBRoZdslH2cSClSwwcCPouEJKyPFdlsqwmXODf9fAc7cWyFchvf+QXjciXI+KOWJoHOgh/UT8p0iNwgbWBbTfbVbMGXojz6UQl2vmTvlxD9EVUN6M+JFHf6MuobhW1KNwS9MyjeSnRBE7x9HNcg+8rpDWyhze/tTy0PrlhSnh9UsoOsjG8PsEMhuE0ZUkwyJUJ1youtAFZq4TWJzcOPHJ9ki8tQfgrjBdlvP2ogusTSZ7rkwtXqPXJahvXJ+W2r7g+4V62RJrobIOlCVyXhWHwAPay/iRFLloiuy6eB0/P/DBw4JD/8sPOGd1HXIepy7DONfey2yJiOBleia3dapMTsybj2ZaeoGAxbn2T3CvLcZ8q3OJduUgLvG01b/uQF8kDXMYdoSDlkSAZ+17CJa+E+y7D+ZMza1smLrUnEXCSLJI7K+VR9uDG5zzWFjYJN0mD5SuyOEKOtp6D3/2SG2m1v/VaLbKJzgj1N90Y/1G49F3f9c4zRK5K/Ei7vxD2BOvI8Vb/2CW1/qxqV3BUj2uzSDzPPb17lZz95RtJyyDddZljXZzFRsqSgfjMcjSEn8rDT+XnHPKVYg8fbIDDMDiQsjXny7JVbkNnUpeKLAmbbOG8i0qU6TjMdgklTf5HXgOl09WNXhO+/FD1QDrkcEUh6+dbAR2EULMRWQ/s73HtBuTXY8xZ9lnz4899k4ymVw6xiN1fGRKLD3ZX3AHuqwhpkQUJs7Mj2kmhYWK69zmwd+pKnbI+6pSlQtnf3HgwaDQWVo1I19NeftUffLaQFJ+KH1DX9I1OtCzyC2niYXc=
*/